//////////////////////////////////////////////////////////////////////////
// The SpliceMesh allows Splice to generate procedural geometry and send it to Max.
// This class has the very dubious design decision to inherit directly from
// GeomObject, rather than the SimpleObject helper class.  This decision
// was made as an optimization - if we derived from SimpObj, it would require
// duplicating the Mesh cached on SpliceTranslationLayer onto the Mesh
// held by GeomObject.  The downside is of course we need to manually re-implement
// the functions in SimpleObject (not a big deal, the class is included in the
// SDK) and update it for changes over years (including Nitrous etc support).
//
// If, one day, things start breaking, and a max expert isn't on hand to update
// things, the easiest fix for most problems would be to change the superclass
// to SimpleObject2, and remove _only_ the mesh-related functions (ie Display/Hittest
// Convert* etc).  Do NOT replace the *Reference/*ParamBlock functions, we require the Splice
// implementations of these functions.

#include "StdAfx.h"
#include <object.h>
#include <ParticleFlow/OneClickCreateCallback.h>
#include "mnmesh.h"
#include "Graphics/IDisplayManager.h"

#define SpliceMesh_CLASS_ID	Class_ID(0x2ebd61e9, 0x33da121d)

class SpliceMesh : public SpliceTranslationLayer<GeomObject, Mesh>
{
public:

	//Constructor/Destructor
	SpliceMesh(BOOL loading);
	virtual ~SpliceMesh();	

	// From BaseObject
	virtual CreateMouseCallBack* GetCreateMouseCallBack() override;
	virtual int Display(TimeValue t, INode* inode, ViewExp *vpt, int flags) override;
	virtual int HitTest(TimeValue t, INode* inode, int type, int crossing, int flags, IPoint2 *p, ViewExp *vpt) override;
	virtual void Snap(TimeValue t, INode* inode, SnapInfo *snap, IPoint2 *p, ViewExp *vpt) override;
	
	// Return the name that will appear in the history browser (modifier stack)
	virtual const TCHAR *GetObjectName() override { return GetString(IDS_SPLICEMESH_CLASS_NAME); }
	
	virtual void GetWorldBoundBox(TimeValue t, INode *mat, ViewExp *vpt, Box3& box ) override;
	virtual void GetLocalBoundBox(TimeValue t, INode *mat, ViewExp *vpt, Box3& box ) override;

	virtual void GetDeformBBox(TimeValue t, Box3& box, Matrix3 *tm, BOOL useSel ) override;
	// Return the default name of the node when it is created.
	virtual void InitNodeName(TSTR& s) override { s = GetString(IDS_SPLICEMESH_CLASS_NAME); }
	
	// From Object
	virtual BOOL HasUVW() override;
	virtual void SetGenUVW(BOOL sw) override;
	virtual int CanConvertToType(Class_ID obtype) override;
	virtual Object* ConvertToType(TimeValue t, Class_ID obtype) override;
	virtual void GetCollapseTypes(Tab<Class_ID> &clist,Tab<TSTR*> &nlist) override;
	virtual int IntersectRay(TimeValue t, Ray& ray, float& at, Point3& norm) override;
	virtual ObjectState Eval(TimeValue t) override { return ObjectState(this); };		
	virtual Interval ObjectValidity(TimeValue t) override { return m_valid; }

	// Nitrous support
#if MAX_VERSION_MAJOR < 17 // Max 2015 is ver 17
	virtual bool UpdateDisplay(
		const MaxSDK::Graphics::MaxContext& maxContext, 
		const MaxSDK::Graphics::UpdateDisplayContext& displayContext) override;
#else
	MaxSDK::Graphics::IMeshDisplay2* GetMeshDisplay(const MaxSDK::Graphics::UpdateDisplayContext& updateDisplayContext, MaxSDK::Graphics::GenerateMeshRenderItemsContext& GenerateMeshRenderItemsContext);
	bool UpdatePerNodeItems(
		const MaxSDK::Graphics::UpdateDisplayContext& updateDisplayContext,
		MaxSDK::Graphics::UpdateNodeContext& nodeContext,
		MaxSDK::Graphics::IRenderItemContainer& targetRenderItemContainer) override;
	
	bool PrepareDisplay(const MaxSDK::Graphics::UpdateDisplayContext& updateDisplayContext) override;
#endif

	// From GeomObject
	// For some incredibly strange reason, View is resolving to FabricServices::DFGWrapper::View, instead
	// of the Max View class. Very strange, as we are 'using' FabricServices, but not DFGWrapper...
	virtual Mesh* GetRenderMesh(TimeValue t, INode *inode, ::View& view, BOOL& needDelete) override;

	//From Animatable
	virtual Class_ID ClassID() override {return SpliceMesh_CLASS_ID;}		
	virtual void GetClassName(TSTR& s) override {s = GetString(IDS_SPLICEMESH_CLASS_NAME);}

	// Free anything that can be rebuilt (Our mesh is generated by Splice)
	virtual void FreeCaches() override { ParentClass::m_value.FreeAll(); }

private:
	// From SpliceTranslationLayer
	int GetValueType() { return TYPE_MESH; }

	bool CloneSpliceData(ParentClass* pMyClone) { return true; }
};

class SpliceMeshClassDesc: public DynPBCustAttrClassDesc {
	public:
	void *			Create(BOOL loading = FALSE) { return new SpliceMesh(loading); }
	const MCHAR *	ClassName() { static MSTR className = GetString(IDS_SPLICEMESH_CLASS_NAME); return className.data(); }
	SClass_ID		SuperClassID() { return GEOMOBJECT_CLASS_ID; }
	Class_ID		ClassID() { return SpliceMesh_CLASS_ID; }
	const TCHAR*	InternalName() {return _T("SpliceMesh");}
};

DynPBCustAttrClassDesc* SpliceMesh::ParentClass::GetClassDesc() 
{ 
	static SpliceMeshClassDesc spliceMeshDesc;
	return &spliceMeshDesc; 
}


//--- SpliceMesh -------------------------------------------------------

SpliceMesh::SpliceMesh(BOOL loading)
	: ParentClass(loading)
{
	if (!loading)
		ResetPorts();
}

SpliceMesh::~SpliceMesh()
{
}
//From Object
BOOL SpliceMesh::HasUVW() 
{ 
	return TRUE; 
}

void SpliceMesh::SetGenUVW(BOOL sw) 
{  
	if (sw==HasUVW()) return;
}

//From BaseObject
CreateMouseCallBack* SpliceMesh::GetCreateMouseCallBack() 
{
	return OneClickCreateCallBack::Instance();
}

// Nitrous has changed a lot for 2015
#if MAX_VERSION_MAJOR < 17 // Max 2015 is ver 17
// Adding Nitrous support
bool SpliceMesh::UpdateDisplay(
	const MaxSDK::Graphics::MaxContext& maxContext, 
	const MaxSDK::Graphics::UpdateDisplayContext& displayContext)
{
	TimeValue t = displayContext.GetDisplayTime();
	//if (!OKtoDisplay(t))
	//{
	//	mRenderItemHandles.ClearAllRenderItems();
	//	return true;
	//}

	using namespace MaxSDK::Graphics;
	using namespace MaxGraphics;

	Interval ivDontCare;
	const Mesh& mesh = Evaluate(t, ivDontCare);
	Mesh* pMeshNoConst = const_cast<Mesh*>(&mesh);

	GenerateMeshRenderItemsContext generateRenderItemsContext;
	generateRenderItemsContext.GenerateDefaultContext(displayContext);

	pMeshNoConst->GenerateDeferredRenderItems(mRenderItemHandles,generateRenderItemsContext);

	return true;
}
#else

MaxSDK::Graphics::IMeshDisplay2* SpliceMesh::GetMeshDisplay(const MaxSDK::Graphics::UpdateDisplayContext& updateDisplayContext, MaxSDK::Graphics::GenerateMeshRenderItemsContext& generateRenderItemsContext) {
	using namespace MaxSDK::Graphics;
	using namespace MaxGraphics;

	TimeValue t = updateDisplayContext.GetDisplayTime();

	Interval ivDontCare;
	const Mesh& mesh = Evaluate(t, ivDontCare);
	Mesh* pMeshNoConst = const_cast<Mesh*>(&mesh);
	IMeshDisplay2* pMeshDisplay = static_cast<IMeshDisplay2*>(pMeshNoConst->GetInterface(IMesh_DISPLAY2_INTERFACE_ID));
	if (NULL == pMeshDisplay)
	{
		return false;
	}
	generateRenderItemsContext.GenerateDefaultContext(updateDisplayContext);
	return pMeshDisplay;
}

bool SpliceMesh::UpdatePerNodeItems(
	const MaxSDK::Graphics::UpdateDisplayContext& updateDisplayContext,
	MaxSDK::Graphics::UpdateNodeContext& nodeContext,
	MaxSDK::Graphics::IRenderItemContainer& targetRenderItemContainer)
{
	using namespace MaxSDK::Graphics;
	using namespace MaxGraphics;

	GenerateMeshRenderItemsContext generateRenderItemsContext;
	IMeshDisplay2* pMeshDisplay = GetMeshDisplay(updateDisplayContext, generateRenderItemsContext);
	generateRenderItemsContext.RemoveInvisibleMeshElementDescriptions(nodeContext.GetRenderNode());

	pMeshDisplay->GetRenderItems(generateRenderItemsContext,nodeContext,targetRenderItemContainer);
	return true;
}

bool SpliceMesh::PrepareDisplay(const MaxSDK::Graphics::UpdateDisplayContext& updateDisplayContext)
{
	using namespace MaxSDK::Graphics;
	using namespace MaxGraphics;

	GenerateMeshRenderItemsContext generateRenderItemsContext;
	IMeshDisplay2* pMeshDisplay = GetMeshDisplay(updateDisplayContext, generateRenderItemsContext);
	pMeshDisplay->PrepareDisplay(generateRenderItemsContext);
	return true;
}

#endif

bool IsNitrousGraphicsEnabled() {
	MaxSDK::Graphics::IDisplayManager* pGraphicsManager = MaxSDK::Graphics::GetIDisplayManager();
	return NULL != pGraphicsManager && pGraphicsManager->IsRetainedModeEnabled();
}

int SpliceMesh::Display(TimeValue t, INode* inode, ViewExp* vpt, int flags)
{
	if (!IsNitrousGraphicsEnabled())
	{
		GraphicsWindow *gw = vpt->getGW();
		Matrix3 mat = inode->GetObjectTM(t);	 
		gw->setTransform(mat);

		Interval ivDontCare;
		const Mesh& mesh = Evaluate(t, ivDontCare);
		Mesh* pMeshNoConst = const_cast<Mesh*>(&mesh);
		pMeshNoConst->render(gw, inode->Mtls(), (flags&USE_DAMAGE_RECT) ? &vpt->GetDammageRect() : NULL, COMP_ALL, inode->NumMtls());
	}
	return(0);
}

int SpliceMesh::HitTest(TimeValue t, INode* inode, int type, int crossing, 
	int flags, IPoint2* p, ViewExp* vpt)
{
	Interval ivDontCare;
	const Mesh& mesh = Evaluate(t, ivDontCare);
	Mesh* pMeshNoConst = const_cast<Mesh*>(&mesh);

	HitRegion hitRegion;
	GraphicsWindow *gw = vpt->getGW();  
	gw->setTransform(inode->GetObjectTM(t));
	MakeHitRegion(hitRegion, type, crossing, 4, p);
	return pMeshNoConst->select(gw, inode->Mtls(), &hitRegion, flags & HIT_ABORTONHIT, inode->NumMtls());
}

void SpliceMesh::Snap(TimeValue t, INode* inode, SnapInfo* snap, IPoint2* p, ViewExp* vpt)
{
	Interval ivDontCare;
	const Mesh& mesh = Evaluate(t, ivDontCare);
	Mesh* pMeshNoConst = const_cast<Mesh*>(&mesh);

	Matrix3 tm = inode->GetObjectTM(t);
	GraphicsWindow *gw = vpt->getGW();  
	gw->setTransform(tm);
	pMeshNoConst->snap(vpt->getGW(), snap, p, tm);
}

void SpliceMesh::GetWorldBoundBox(TimeValue t, INode* pNode, ViewExp* /*vpt*/, Box3& box )
{
	GetDeformBBox(t, box, &pNode->GetObjectTM(t), FALSE);
}

void SpliceMesh::GetLocalBoundBox(TimeValue t, INode *mat, ViewExp * /*vpt*/, Box3& box )
{
	Interval ivDontCare;
	const Mesh& mesh = Evaluate(t, ivDontCare);
	Mesh* pMeshNoConst = const_cast<Mesh*>(&mesh);
	box = pMeshNoConst->getBoundingBox();
}

void SpliceMesh::GetDeformBBox(TimeValue t, Box3& box, Matrix3* tm, BOOL useSel )
{
	GetLocalBoundBox(t, NULL, NULL, box);
	if (tm)
		box = box * *tm;
}

//#if MAX_VERSION_MAJOR < 17
Mesh* SpliceMesh::GetRenderMesh(TimeValue t, 
						INode *inode, ::View& view, BOOL& needDelete)
{
	needDelete = FALSE;
	Interval ivDontCare;
	const Mesh& mesh = Evaluate(t, ivDontCare);
	return const_cast<Mesh*>(&mesh);
}
//#endif

Object* SpliceMesh::ConvertToType(TimeValue t, Class_ID obtype)
{
	// Code lifted from SimpleObject
	if (obtype==defObjectClassID||obtype==triObjectClassID||obtype==mapObjectClassID) {
		TriObject *pTriObj = CreateNewTriObject();
		Interval ivDontCare;
		pTriObj->GetMesh() = Evaluate(t, ivDontCare);
		pTriObj->SetChannelValidity(TOPO_CHAN_NUM,ObjectValidity(t));
		pTriObj->SetChannelValidity(GEOM_CHAN_NUM,ObjectValidity(t));		
		return pTriObj;
	}
#ifndef NO_PATCHES
	if (obtype == patchObjectClassID) {
		PatchObject *patchob = new PatchObject();
		Interval ivDontCare;
		const Mesh& mesh = Evaluate(t, ivDontCare);
		Mesh* pMeshNoConst = const_cast<Mesh*>(&mesh);
		patchob->patch = *pMeshNoConst;		// Handy Mesh->PatchMesh conversion
		patchob->SetChannelValidity(TOPO_CHAN_NUM,ObjectValidity(t));
		patchob->SetChannelValidity(GEOM_CHAN_NUM,ObjectValidity(t));		
		return patchob;
	}
#endif
	if (Object::CanConvertToType (obtype)) {
		return Object::ConvertToType(t,obtype);
	}
	if (CanConvertTriObject(obtype)) {
		TriObject *triob = CreateNewTriObject ();
		Interval ivDontCare;
		triob->GetMesh() = Evaluate(t, ivDontCare);
		triob->SetChannelValidity(TOPO_CHAN_NUM,ObjectValidity(t));
		triob->SetChannelValidity(GEOM_CHAN_NUM,ObjectValidity(t));		
		Object *ob = triob->ConvertToType (t, obtype);
		if (ob != triob) triob->DeleteThis ();	// (ob should never = tob.)
		return ob;
	}
	return NULL;
}

int SpliceMesh::CanConvertToType(Class_ID obtype)
{
	if (obtype==defObjectClassID) return TRUE;
	if (obtype==mapObjectClassID) return TRUE;
	if (obtype==triObjectClassID) return TRUE;
#ifndef NO_PATCHES
	if (obtype==patchObjectClassID) return TRUE;
#endif
	if (Object::CanConvertToType(obtype)) return TRUE;
	// need way to find out if Mesh can be converted to type...
	if (CanConvertTriObject(obtype)) return TRUE;
	return FALSE;
}

// From Object
int SpliceMesh::IntersectRay(
		TimeValue t, Ray& ray, float& at, Point3& norm)
{
	Interval ivDontCare;
	const Mesh& mesh = Evaluate(t, ivDontCare);
	Mesh* pMeshNoConst = const_cast<Mesh*>(&mesh);
	return pMeshNoConst->IntersectRay(ray,at,norm);
}

void SpliceMesh::GetCollapseTypes(Tab<Class_ID> &clist,Tab<TSTR*> &nlist)
{
    Object::GetCollapseTypes(clist, nlist);
	//#pragma message(TODO("Append any any other collapse type the plugin supports"))
}
