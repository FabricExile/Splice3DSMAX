#include "StdAfx.h"
#include "MaxDFGCmdHandler.h"

#include <macrorec.h>

//////////////////////////////////////////////////////////////////////////
// defines

const MSTR s_PortTypeEnumOUT = _M("DFGPortOUT");
const MSTR s_PortTypeEnumIO = _M("DFGPortIO");
const MSTR s_PortTypeEnumIN = _M("DFGPortIN");

//////////////////////////////////////////////////////////////////////////

MaxDFGCmdHandler::MaxDFGCmdHandler(FabricTranslationFPInterface* pTranslation)
	: DFGUICmdHandler_QUndo(GetQtUndoStack())
	, m_pTranslationLayer(pTranslation)
{

}

MaxDFGCmdHandler::~MaxDFGCmdHandler()
{

}

#pragma region <T> -> MSTR converters

MSTR ToMSTR(const Point2& v) {
	MSTR r;
	r.printf(_M("[%f,%f]"), v.x, v.y);
	return r;
}

MSTR ToMSTR(const QPointF& v) {
	MSTR r;
	r.printf(_M("[%f,%f]"), v.x(), v.y());
	return r;
}
MSTR ToMSTR(const QSizeF& v) {
	MSTR r;
	r.printf(_M("[%f,%f]"), v.width(), v.height());
	return r;
}

MSTR ToMSTR(const FabricCore::RTVal& v) {
	FabricCore::RTVal cjson = v.getJSON();
	return  MSTR::FromACP(cjson.getStringCString());
}

MSTR ToMSTR(unsigned int v) {
	MSTR s;
	s.printf(_M("%i"), v);
	return s;
}

template<typename T>
MSTR ToMSTR(const FTL::ArrayRef<T>& v) {
	MSTR r;
	MSTR contents;
	for (int i = 0; i < v.size(); i++) {
		MSTR comma = _M("");
		if (i > 0)
			comma = _M(", ");
		MSTR item = comma + ToMSTR(v[i]);
		contents += item;
	}
	r.printf(_M("#(%s)"), contents.data());
	return r;
}

template<typename T>
MSTR ToMSTR(const std::vector<T>& v) {
	MSTR r;
	MSTR contents;
	for (int i = 0; i < v.size(); i++) {
		MSTR comma = _M("");
		if (i > 0)
			comma = _M(", ");
		MSTR item = comma + ToMSTR(v[i]);
		contents += item;
	}
	r.printf(_M("#(%s)"), contents.data());
	return r;
}

MSTR ToMSTR(const FTL::StrRef& v) {
	MSTR rv;
	rv.printf(_M("\"%s\""), MSTR::FromACP(v.data()).data());
	return rv;
}

class nothing {};
MSTR ToMSTR(nothing v) {
	return MSTR();
}

// Quickly convert FTL::CStrRef to MCHAR*
#define TO_MCHAR(x) ToMSTR(x).data()

template<typename T1, typename T2, typename T3, typename T4>
void doEmit(const MCHAR* fn, const T1& t1, const T2& t2, const T3& t3, const T4& t4, FTL::CStrRef& execPath)
{
	MSTR cmd;
	cmd.printf(_M("$.%s %s %s %s %s execPath:%s"), fn, TO_MCHAR(t1), TO_MCHAR(t2), TO_MCHAR(t3), TO_MCHAR(t4), TO_MCHAR(execPath));
	macroRecorder->ScriptString(cmd.data());
	macroRecorder->EmitScript();
}

#define EMIT1(fn, t1, path) doEmit(fn, t1, nothing(), nothing(), nothing(), execPath)
#define EMIT2(fn, t1, t2, path) doEmit(fn, t1, t2, nothing(), nothing(), execPath)
#define EMIT3(fn, t1, t2, t3, path) doEmit(fn, t1, t2, t3, nothing(), execPath)
#define EMIT4(fn, t1, t2, t3, t4, path) doEmit(fn, t1, t2, t3, t4, execPath)

#pragma endregion

void MaxDFGCmdHandler::dfgDoRemoveNodes(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::ArrayRef<FTL::StrRef> nodeNames)
{
	EMIT1(_M("DFGRemoveNodes"), nodeNames, execPath);
	DFGHoldActions hold(_M("DFG Remove Nodes"));
	__super::dfgDoRemoveNodes(binding, execPath, exec, nodeNames);
	m_pTranslationLayer->InvalidateAll();
}

void MaxDFGCmdHandler::dfgDoConnect(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef srcPath, FTL::CStrRef dstPath)
{
	EMIT2(_M("DFGConnect"), srcPath, dstPath, execPath);
	DFGHoldActions hold(_M("DFG Connect"));
	__super::dfgDoConnect(binding, execPath, exec, srcPath, dstPath);
	m_pTranslationLayer->InvalidateAll();
}

void MaxDFGCmdHandler::dfgDoDisconnect(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef srcPath, FTL::CStrRef dstPath)
{
	EMIT2(_M("DFGDisconnect"), srcPath, dstPath, execPath);
	DFGHoldActions hold(_M("DFG Disconnect"));
	__super::dfgDoDisconnect(binding, execPath, exec, srcPath, dstPath);
	m_pTranslationLayer->InvalidateAll();
}

std::string MaxDFGCmdHandler::dfgDoAddGraph(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef title, QPointF pos)
{
	EMIT2(_M("DFGAddGraph"), title, pos, execPath);
	DFGHoldActions hold(_M("DFG Add Graph"));
	return __super::dfgDoAddGraph(binding, execPath, exec, title, pos);
}

std::string MaxDFGCmdHandler::dfgDoAddFunc(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef title, FTL::CStrRef initialCode, QPointF pos)
{
	EMIT3(_M("DFGAddFunc"), title, initialCode, pos, execPath);
	DFGHoldActions hold(_M("DFG Add Function"));
	return __super::dfgDoAddFunc(binding, execPath, exec, title, initialCode, pos);
}

std::string MaxDFGCmdHandler::dfgDoInstPreset(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef presetPath, QPointF pos)
{
	EMIT2(_M("DFGInstPreset"), presetPath, pos, execPath);
	DFGHoldActions hold(_M("DFG Load Preset"));
	return __super::dfgDoInstPreset(binding, execPath, exec, presetPath, pos);
}

std::string MaxDFGCmdHandler::dfgDoAddVar(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef desiredNodeName, FTL::CStrRef dataType, FTL::CStrRef extDep, QPointF pos)
{
	EMIT4(_M("DFGAddVar"), desiredNodeName, dataType, extDep, pos, execPath);
	DFGHoldActions hold(_M("DFG Add Var"));
	return __super::dfgDoAddVar(binding, execPath, exec, desiredNodeName, dataType, extDep, pos);
}

std::string MaxDFGCmdHandler::dfgDoAddGet(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef desiredNodeName, FTL::CStrRef varPath, QPointF pos)
{
	EMIT3(_M("DFGAddGet"), desiredNodeName, varPath, pos, execPath);
	DFGHoldActions hold(_M("DFG Add Get"));
	return __super::dfgDoAddGet(binding, execPath, exec, desiredNodeName, varPath, pos);
}

std::string MaxDFGCmdHandler::dfgDoAddSet(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef desiredNodeName, FTL::CStrRef varPath, QPointF pos)
{
	EMIT3(_M("DFGAddSet"), desiredNodeName, varPath, pos, execPath);
	DFGHoldActions hold(_M("DFG Add Set"));
	return __super::dfgDoAddSet(binding, execPath, exec, desiredNodeName, varPath, pos);
}

std::string MaxDFGCmdHandler::dfgDoAddPort(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef desiredPortName, FabricCore::DFGPortType portType, FTL::CStrRef typeSpec, FTL::CStrRef portToConnect, FTL::StrRef extDep, FTL::CStrRef metaData)
{
	MSTR cmd;
	MSTR portTypeEnum = _M( "#" );
	switch (portType)
	{
		case FabricCore::DFGPortType_Out:
			portTypeEnum.Append(s_PortTypeEnumOUT);
			break;
		case FabricCore::DFGPortType_In:
			portTypeEnum.Append(s_PortTypeEnumIN);
			break;
		case FabricCore::DFGPortType_IO:
			portTypeEnum.Append(s_PortTypeEnumIO);
			break;
	}
	cmd.printf(_M("$.%s %s %s %s portToConnect:%s extDep:%s metaData:%s execPath:%s"),
		_M("DFGAddPort"),
		TO_MCHAR(desiredPortName),
		portTypeEnum.data(),
		TO_MCHAR(typeSpec),
		TO_MCHAR(portToConnect),
		TO_MCHAR(extDep),
		TO_MCHAR(metaData),
		TO_MCHAR(execPath));
	macroRecorder->ScriptString(cmd.data());
	macroRecorder->EmitScript();

	DFGHoldActions hold(_M("DFG Add Port"));

	bool isPossibleMaxPort = portType != FabricCore::DFGPortType_Out && execPath.empty();

	std::string res = __super::dfgDoAddPort(binding, execPath, exec, desiredPortName, portType, typeSpec, portToConnect, extDep, metaData);
	// I think that the issue with the boolean input is located here. I'm not sure what it is exactly...
	if (isPossibleMaxPort)
	{
		// It appears that the result will be NULL if called from MxS, and non-NULL
		// if called from the UI.  It's very difficult to tell what the reason for this
		// difference is, so here we just detect if the call returned the new ports name
		const char* resPortName = res.empty() ? desiredPortName.data() : res.c_str();
		// If we have add a new 'in' port, by default we create a matching 3ds max port.
		m_pTranslationLayer->SyncMetaDataFromPortToParam( resPortName );
	}
	return res;
}

std::string MaxDFGCmdHandler::dfgDoEditPort(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::StrRef oldPortName, FTL::StrRef desiredNewPortName, FTL::StrRef typeSpec, FTL::StrRef extDep, FTL::StrRef uiMetadata)
{
	MSTR cmd;
	cmd.printf(_M("$.%s %s desiredNewPortName:%s typeSpec:%s extDep:%s metadata:%s execPath:%s"),
		_M("DFGEditPort"),
		TO_MCHAR(oldPortName),
		TO_MCHAR(desiredNewPortName),
		TO_MCHAR(typeSpec),
		TO_MCHAR(extDep),
		TO_MCHAR(uiMetadata),
		TO_MCHAR(execPath));
	macroRecorder->ScriptString(cmd.data());
	macroRecorder->EmitScript();

	DFGHoldActions hold(_M("DFG Edit Port"));
	std::string res = __super::dfgDoEditPort(binding, execPath, exec, oldPortName, desiredNewPortName, typeSpec, extDep, uiMetadata);

	FabricCore::DFGPortType portMode = const_cast<FabricCore::DFGExec&>(exec).getExecPortType(res.c_str());
	bool isPossibleMaxPort = portMode != FabricCore::DFGPortType_Out && execPath.empty();
	if (isPossibleMaxPort)
	{
		// If we have add a new 'in' port, by default we create a matching 3ds max port.
		m_pTranslationLayer->SyncMetaDataFromPortToParam(res.c_str());
	}
	return res;
}

void MaxDFGCmdHandler::dfgDoRemovePort(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef portName)
{
	EMIT1(_M("DFGRemovePort"), portName, execPath);

	DFGHoldActions hold(_M("DFG Remove Port"));
	if (!theHold.RestoreOrRedoing())
	{
		int pid = GetPortParamID(exec, portName.c_str());
		if (pid >= 0)
		{
			m_pTranslationLayer->SetMaxTypeForArg(MSTR::FromACP(portName.c_str()), -1);
		}
	}

	__super::dfgDoRemovePort(binding, execPath, exec, portName);

	m_pTranslationLayer->InvalidateAll();
}

void MaxDFGCmdHandler::dfgDoResizeBackDrop(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef backDropNodeName, QPointF newTopLeftPos, QSizeF newSize)
{
	EMIT3(_M("DFGResizeBackDrop"), backDropNodeName, newTopLeftPos, newSize, execPath);
	DFGHoldActions hold(_M("DFG Resize Back Drop"));
	return __super::dfgDoResizeBackDrop(binding, execPath, exec, backDropNodeName, newTopLeftPos, newSize);
}

void MaxDFGCmdHandler::dfgDoMoveNodes(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::ArrayRef<FTL::StrRef> nodeNames, FTL::ArrayRef<QPointF> newTopLeftPoss)
{
	EMIT2(_M("DFGMoveNodes"), nodeNames, newTopLeftPoss, execPath);
	DFGHoldActions hold(_M("DFG Move Nodes"));
	return __super::dfgDoMoveNodes(binding, execPath, exec, nodeNames, newTopLeftPoss);
}

std::string MaxDFGCmdHandler::dfgDoImplodeNodes(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::ArrayRef<FTL::StrRef> nodeNames, FTL::CStrRef desiredNodeName)
{
	EMIT2(_M("DFGImplodeNodes"), nodeNames, desiredNodeName, execPath);
	DFGHoldActions hold(_M("DFG Implode Nodes"));
	return __super::dfgDoImplodeNodes(binding, execPath, exec, nodeNames, desiredNodeName);
}

std::vector<std::string> MaxDFGCmdHandler::dfgDoExplodeNode(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef nodeName)
{
	EMIT1(_M("DFGExplodeNode"), nodeName, execPath);
	DFGHoldActions hold(_M("DFG Explode Nodes"));
	return __super::dfgDoExplodeNode(binding, execPath, exec, nodeName);
}

void MaxDFGCmdHandler::dfgDoAddBackDrop(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef title, QPointF pos)
{
	EMIT2(_M("DFGAddBackDrop"), title, pos, execPath);
	DFGHoldActions hold(_M("DFG Add BackDrop"));
	return __super::dfgDoAddBackDrop(binding, execPath, exec, title, pos);
}

void MaxDFGCmdHandler::dfgDoSetTitle(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef newTitle)
{
	EMIT1(_M("DFGSetTitle"), newTitle, execPath);
	DFGHoldActions hold(_M("DFG Set Title"));
	return __super::dfgDoSetTitle(binding, execPath, exec, newTitle);
}

void MaxDFGCmdHandler::dfgDoSetNodeComment(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef nodeName, FTL::CStrRef comment)
{
	EMIT2(_M("DFGSetNodeComment"), nodeName, comment, execPath);
	DFGHoldActions hold(_M("DFG Set Node Comment"));
	__super::dfgDoSetNodeComment(binding, execPath, exec, nodeName, comment);
}

void MaxDFGCmdHandler::dfgDoSetCode(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef code)
{
	EMIT1(_M("DFGSetCode"), code, execPath);
	DFGHoldActions hold(_M("DFG Set Code"));
	__super::dfgDoSetCode(binding, execPath, exec, code);
	m_pTranslationLayer->InvalidateAll();
}

std::string MaxDFGCmdHandler::dfgDoRenamePort(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef oldName, FTL::CStrRef desiredNewName)
{
	EMIT2(_M("DFGRenamePort"), oldName, desiredNewName, execPath);
	DFGHoldActions hold(_M("DFG Rename Port"));
	std::string res = __super::dfgDoRenamePort(binding, execPath, exec, oldName, desiredNewName);
	m_pTranslationLayer->SyncMetaDataFromPortToParam(res.c_str());
	return res;
}

std::vector<std::string> MaxDFGCmdHandler::dfgDoPaste(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef json, QPointF cursorPos)
{
	EMIT2(_M("DFGPaste"), json, cursorPos, execPath);
	DFGHoldActions hold(_M("DFG Paste"));
	return __super::dfgDoPaste(binding, execPath, exec, json, cursorPos);
}

void MaxDFGCmdHandler::dfgDoSetArgType(FabricCore::DFGBinding const &binding, FTL::CStrRef argName, FTL::CStrRef typeName)
{
	macroRecorder->FunctionCall(_M("$.DFGSetArgType"), 2, 0,
		mr_string, TO_MCHAR(argName),
		mr_string, TO_MCHAR(typeName)
		);

	DFGHoldActions hold(_M("DFG Set Arg Type"));

	if (binding.getExec().getExecPortType(argName.c_str()) == FabricCore::DFGPortType_In)
	{
		int type = m_pTranslationLayer->GetMaxTypeForArg(argName.c_str());
		// Attempt to set the same type back.  If the max type is no
		// longer legitimate, the type will be reset to default.
		m_pTranslationLayer->SetMaxTypeForArg(argName.c_str(), type);
	}
	return __super::dfgDoSetArgType(binding, argName, typeName);
}

void MaxDFGCmdHandler::dfgDoSetArgValue(FabricCore::DFGBinding const &binding, FTL::CStrRef argName, FabricCore::RTVal const &value)
{
	macroRecorder->FunctionCall(_M("$.DFGSetArgValue"), 2, 0,
		mr_string, TO_MCHAR(argName),
		mr_string, TO_MCHAR(value)
		);

	DFGHoldActions hold(_M("DFG Set Arg Value"));

	__super::dfgDoSetArgValue(binding, argName, value);

	m_pTranslationLayer->InvalidateAll();
}

void MaxDFGCmdHandler::dfgDoSetPortDefaultValue(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef portOrPinPath, FabricCore::RTVal const &value)
{
	EMIT2(_M("DFGSetPortDefaultValue"), portOrPinPath, value, execPath);
	DFGHoldActions hold(_M("DFG Set Def Value"));
	__super::dfgDoSetPortDefaultValue(binding, execPath, exec, portOrPinPath, value);

	// If we have a period '.' in our port name, or our execPath is non-empty, then
	// the port is not a max parameter, and there is no need to sync
	if (!(portOrPinPath.contains('.') || execPath.size() > 1))
		m_pTranslationLayer->SyncMetaDataFromPortToParam(portOrPinPath.c_str());

	// Whatever happens though, we need to re-evaluate
	m_pTranslationLayer->InvalidateAll();
}

void MaxDFGCmdHandler::dfgDoSetRefVarPath(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::CStrRef refName, FTL::CStrRef varPath)
{
	EMIT2(_M("DFGSetRefVarPath"), refName, varPath, execPath);
	DFGHoldActions hold(_M("DFG Set Ref Path"));
	return __super::dfgDoSetRefVarPath(binding, execPath, exec, refName, varPath);
}

void MaxDFGCmdHandler::dfgDoReorderPorts(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, const std::vector<unsigned int> & indices)
{
	EMIT1(_M("DFGReorderPorts"), indices, execPath);
	DFGHoldActions hold(_M("DFG Re-order Ports"));
	return __super::dfgDoReorderPorts(binding, execPath, exec, indices);
}

void MaxDFGCmdHandler::dfgDoSetExtDeps(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec, FTL::ArrayRef<FTL::StrRef> extDeps)
{
	EMIT1(_M("DFGSetExtDeps"), extDeps, execPath);
	DFGHoldActions hold(_M("DFG Set External Dependencies"));
	return __super::dfgDoSetExtDeps(binding, execPath, exec, extDeps);
}

void MaxDFGCmdHandler::dfgDoSplitFromPreset(FabricCore::DFGBinding const &binding, FTL::CStrRef execPath, FabricCore::DFGExec const &exec)
{
	doEmit(_M("DFGSplitFromPreset"), nothing(), nothing(), nothing(), nothing(), execPath);
	DFGHoldActions hold(_M("DFG Split From Preset"));
	return __super::dfgDoSplitFromPreset(binding, execPath, exec);
}
