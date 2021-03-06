//**************************************************************************/
// DESCRIPTION: Applies modifications to an input mesh using Fabric
// AUTHOR: Stephen Taylor
//***************************************************************************/

#include "StdAfx.h"
#include "FabricWSModifier.h"

class FabricWSModifierClassDesc: public DynPBCustAttrClassDesc {
public:
	void *			Create(BOOL loading = FALSE) { return new FabricWSModifier(loading); }
	const MCHAR *	ClassName() { static MSTR className = GetString(IDS_SPLICE_WSMODIFIER_CLASS); return className.data(); }
	SClass_ID		SuperClassID() { return WSM_CLASS_ID; }
	Class_ID		ClassID() { return FabricWSModifier_CLASS_ID; }
	const TCHAR*	InternalName() {return _T("FabricWSModifier");}
};

DynPBCustAttrClassDesc* FabricWSModifier::ParentClass::GetClassDesc() 
{ 
	static FabricWSModifierClassDesc FabricModifierDesc;
	return &FabricModifierDesc; 
}

//--- FabricModifier -------------------------------------------------------
// Only initialize the splice graph if loading.  Else,
// we initialize the class on every time the Modifier list
// is dropped down in the UI.  If Fabric is not initialized,
// this takes about 4s (every drop down), which is just not polite.
FabricWSModifier::FabricWSModifier(BOOL loading)
	: ParentClass(true)
{
}

FabricWSModifier::~FabricWSModifier()
{
}

void FabricWSModifier::RefAdded(RefMakerHandle rm)
{
	if (!m_binding.isValid())
	{
		Init();
		ResetPorts();
	}
}

Interval FabricWSModifier::LocalValidity(TimeValue t)
{
	return m_valid;
}

void FabricWSModifier::NotifyInputChanged( const Interval &changeInt, PartID partID, RefMessage message, ModContext *mc )
{
	if (message == REFMSG_CHANGE)
	{
		m_inputValid.SetEmpty();
		Invalidate();
	}
}

//////////////////////////////////////////////////////////////////////////
void FabricWSModifier::ModifyObject( TimeValue t, ModContext &mc, ObjectState* os, INode *node )
{
	if (!m_binding.isValid())
		return;
	if (node == nullptr)
		return;

	TriObject* pTriObj = static_cast<TriObject*>(os->obj);
	Interval ivValid = FOREVER;
	Matrix3 tmNode = node->GetNodeTM(t, &ivValid);

	// Check our node transform is valid.  If its not, 
	// then we invalidate to force a recalculation.
	if (!(tmNode == m_cachedNodeTM))
		Invalidate();

	// Here we pre-check the cache.  This optimization allows us to return
	// the cache before sending the mesh to Fabric - normally we would 
	// need to post the mesh before calling Evaluate (which checks the cache)
	if (m_valid.InInterval(t)) {
		pTriObj->GetMesh() = m_value;
		ivValid = m_valid;
	}
	else {

		// Suspend hold, so FE does not record changes to our mesh/Mtx ports
		HoldSuspend hs;
		// A modifier is a special kind of mesh, in that we pipe our
		// mesh into the output port as an IO port
#pragma message("TODO: Clean up caching based on Fabric's version number")
		//if (!m_inputValid.InInterval(t))
		{
			DoSyncing ds( *this );
			m_inputValid.SetInfinite();
			MaxValuesToFabric<Object*, Mesh>(m_binding, m_baseMeshArgName.c_str(), t, m_inputValid, &os->obj, 1);
			ivValid &= m_inputValid;

			// If Fabric does not have an output value for us, then
			// nothing will be read into our cached value.  In this
			// case we don't want to change the base mesh, so ensure
			// that is what is in the cache.
			FabricCore::DFGExec exec = GetExec(nullptr);
			if (!(exec.haveExecPort(m_outArgName.c_str()) && exec.hasSrcPorts(m_outArgName.c_str()))) {
				m_value = pTriObj->GetMesh();
			}
		}

		{
			DoSyncing ds( *this );
			// A WSModifier is a special kind of modifier that has access to its nodes transform
			MaxValueToFabric( m_binding, m_baseMeshTransformArgName.c_str(), t, ivValid, tmNode );
		}

		// Set our output.
		if (GraphCanEvaluate())
			pTriObj->GetMesh() = Evaluate(t, ivValid);
	}

	// We may have changed any of these attributes.
	// OPTIMIZE: We should not invalidate things we haven't changed
	// Perhaps we should add the ability to set channels via MxS
	pTriObj->UpdateValidity(GEOM_CHAN_NUM, ivValid);
	pTriObj->UpdateValidity(TOPO_CHAN_NUM, ivValid);
	pTriObj->UpdateValidity(TEXMAP_CHAN_NUM, ivValid);
	pTriObj->UpdateValidity(VERT_COLOR_CHAN_NUM, ivValid);
}

#pragma region Mesh management methods

int FabricWSModifier::Display(TimeValue t, INode* inode, ViewExp* vpt, int flags)
{
	// TODO: Nitrous support here
	Interval ivDontCare;
	const Mesh& mesh = Evaluate(t, ivDontCare);
	Mesh* pMeshNoConst = const_cast<Mesh*>(&mesh);
	pMeshNoConst->render(vpt->getGW(), inode->Mtls(), NULL, flags, inode->NumMtls());
	return 0;
}

int FabricWSModifier::HitTest(TimeValue t, INode* inode, int type, int crossing, 
							int flags, IPoint2* p, ViewExp* vpt)
{
	Interval ivDontCare;
	const Mesh& mesh = Evaluate(t, ivDontCare);
	Mesh* pMeshNoConst = const_cast<Mesh*>(&mesh);

	HitRegion hitRegion;
	GraphicsWindow *gw = vpt->getGW();  
	Material *mtl = gw->getMaterial();     
	gw->setTransform(inode->GetObjectTM(t));
	MakeHitRegion(hitRegion, type, crossing, 4, p);
	return pMeshNoConst->select(gw, mtl, &hitRegion, flags & HIT_ABORTONHIT);
}

void FabricWSModifier::Snap(TimeValue t, INode* inode, SnapInfo* snap, IPoint2* p, ViewExp* vpt)
{
	Interval ivDontCare;
	const Mesh& mesh = Evaluate(t, ivDontCare);
	Mesh* pMeshNoConst = const_cast<Mesh*>(&mesh);
	Matrix3 tm = inode->GetNodeTM(t);
	pMeshNoConst->snap(vpt->getGW(), snap, p, tm);
}

void FabricWSModifier::GetWorldBoundBox(TimeValue t, INode* mat, ViewExp* /*vpt*/, Box3& box )
{
	Interval ivDontCare;
	const Mesh& mesh = Evaluate(t, ivDontCare);
	Mesh* pMeshNoConst = const_cast<Mesh*>(&mesh);
	box = pMeshNoConst->getBoundingBox(&mat->GetNodeTM(t));
}

void FabricWSModifier::GetLocalBoundBox(TimeValue t, INode *mat, ViewExp * /*vpt*/, Box3& box )
{
	Interval ivDontCare;
	const Mesh& mesh = Evaluate(t, ivDontCare);
	Mesh* pMeshNoConst = const_cast<Mesh*>(&mesh);
	box = pMeshNoConst->getBoundingBox();
}

#pragma endregion

void FabricWSModifier::ResetPorts()
{
	MACROREC_GUARD;

	const char* metadata = "{ \n\
			\"uiHidden\" : \"true\", \n\
			\"uiPersistValue\" : \"false\" \n \
		}";

	// Add an in-port to send in the Max mesh to be modified.
	const char* portSpec = MaxTypeToFabricType( GetValueType() );
	QString res = m_fabricCmdHandler.dfgDoAddPort( GetBinding(), "", GetExec( "" ), "baseMesh", FabricCore::DFGPortType_In, portSpec, "", "Geometry", metadata );
	m_baseMeshArgName = res.toStdString();

	// We add a transform value so that our Fabric operator can evaluate relative to the input matrix
	portSpec = MaxTypeToFabricType( TYPE_MATRIX3 );
	res = m_fabricCmdHandler.dfgDoAddPort( GetBinding(), "", GetExec( "" ), "baseMeshTransform", FabricCore::DFGPortType_In, portSpec, "", "Math", metadata );
	m_baseMeshTransformArgName = res.toStdString();

	ParentClass::ResetPorts();
}

//////////////////////////////////////////////////////////////////////////
#define BASE_MESH_PORT_NAME		0x100
#define BASE_TRANS_PORT_NAME	0x200
#define IS_ENABLED_NAME			0x400

bool FabricWSModifier::CloneFabricData( ParentClass* pMyClone )
{
  FabricWSModifier* pMyCloneWSM = static_cast<FabricWSModifier*>(pMyClone);
  pMyCloneWSM->m_baseMeshArgName = m_baseMeshArgName;
  pMyCloneWSM->m_baseMeshTransformArgName = m_baseMeshTransformArgName;
  return true;
}

IOResult FabricWSModifier::SaveImpData( ISave* isave )
{
	// Save additional values for derived values
	isave->BeginChunk(BASE_MESH_PORT_NAME);
	isave->WriteCString(m_baseMeshArgName.c_str());
	isave->EndChunk();

	isave->BeginChunk(BASE_TRANS_PORT_NAME);
	isave->WriteCString(m_baseMeshTransformArgName.c_str());
	isave->EndChunk();

	ULONG dontcare;
	bool isenabled = Modifier::IsEnabled();
	isave->BeginChunk( IS_ENABLED_NAME );
	isave->Write( &isenabled, sizeof( isenabled ), &dontcare );
	isave->EndChunk();

	return IO_OK;

}

IOResult FabricWSModifier::LoadImpData(ILoad* iload)
{
	IOResult result = IO_OK;
	while (IO_OK == (result = iload->OpenChunk()))
	{
		switch (iload->CurChunkID())
		{
		case BASE_MESH_PORT_NAME:
		{
			char *buff;
			if (iload->ReadCStringChunk(&buff) == IO_OK) {
				m_baseMeshArgName = buff;
			}
			break;
		}
		case BASE_TRANS_PORT_NAME:
		{
			char *buff;
			if (iload->ReadCStringChunk(&buff) == IO_OK) {
				m_baseMeshTransformArgName = buff;
			}
			break;
		}
		case IS_ENABLED_NAME:
		{
			bool isEnabled;
			ULONG dontcare;
			if (iload->Read( &isEnabled, sizeof( isEnabled ), &dontcare ) == IO_OK) {
				if (isEnabled)
					EnableMod();
				else
					DisableMod();
			}
			break;
		}
		}
		iload->CloseChunk();
	}
	return result;
}
