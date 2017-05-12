#pragma once


#include <FabricUI/DFG/DFGUICmdHandler_QUndo.h>

class FabricTranslationFPInterface;

class MaxDFGCmdHandler : public FabricUI::DFG::DFGUICmdHandler_QUndo
{
private:

	FabricTranslationFPInterface* m_pTranslationLayer;

public:
	MaxDFGCmdHandler(FabricTranslationFPInterface* pTranslation);
	~MaxDFGCmdHandler();

virtual void dfgDoRemoveNodes(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QStringList nodeNames
    ) override;

  virtual void dfgDoConnect(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QStringList srcPortPaths, 
    QStringList dstPortPaths
    ) override;

  virtual void dfgDoDisconnect(
	  FabricCore::DFGBinding const &binding,
	  QString execPath,
	  FabricCore::DFGExec const &exec,
	  QStringList srcPaths,
	  QStringList dstPaths
  ) override;

  virtual QString dfgDoAddGraph(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString title,
    QPointF pos
    ) override;

  virtual QString dfgDoAddFunc(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString title,
    QString initialCode,
    QPointF pos
    ) override;

  virtual QString dfgDoInstPreset(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString presetPath,
    QPointF pos
    ) override;

  virtual QString dfgDoAddVar(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString desiredNodeName,
    QString dataType,
    QString extDep,
    QPointF pos
    ) override;

  virtual QString dfgDoAddGet(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString desiredNodeName,
    QString varPath,
    QPointF pos
    ) override;

  virtual QString dfgDoAddSet(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString desiredNodeName,
    QString varPath,
    QPointF pos
    ) override;

  virtual QString dfgDoAddPort(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString desiredPortName,
    FabricCore::DFGPortType portType,
    QString typeSpec,
    QString portToConnect,
    QString extDep,
    QString metaData
    ) override;

/* r3d
  virtual QString dfgDoCreatePreset(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString nodeName,
    QString presetDirPath,
    QString presetName
    ) override;
*/

  virtual QString dfgDoEditPort(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString oldPortName,
    QString desiredNewPortName,
	FabricCore::DFGPortType portType,
    QString typeSpec,
    QString extDep,
    QString uiMetadata
    ) override;

  virtual void dfgDoRemovePort(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QStringList portNames
    ) override;

  virtual void dfgDoResizeBackDrop(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString backDropNodeName,
    QPointF newTopLeftPos,
    QSizeF newSize
    ) override;
  
  virtual void dfgDoMoveNodes(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QStringList nodeNames,
    QList<QPointF> newTopLeftPoss
    ) override;

  virtual QString dfgDoImplodeNodes(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QStringList nodeNames,
    QString desiredNodeName
    ) override;

  virtual QStringList dfgDoExplodeNode(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString nodeName
    ) override;

  virtual QString dfgDoAddBackDrop(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString title,
    QPointF pos
    ) override;

  virtual void dfgDoSetNodeComment(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString nodeName,
    QString comment
    ) override;

  virtual void dfgDoSetCode(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString code
    ) override;

/* r3d
  virtual QString dfgDoEditNode(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString oldNodeName,
    QString desiredNewNodeName,
    QString nodeMetadata,
    QString execMetadata
    ) override;
*/
  virtual QString dfgDoRenamePort(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString portPath,
    QString desiredNewPortName
    ) override;

  virtual QStringList dfgDoPaste(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString json,
    QPointF cursorPos
    ) override;

  virtual void dfgDoSetArgValue(
    FabricCore::DFGBinding const &binding,
    QString argName,
    FabricCore::RTVal const &value
    ) override;

  virtual void dfgDoSetPortDefaultValue(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString portOrPinPath,
    FabricCore::RTVal const &value
    ) override;

  virtual void dfgDoSetRefVarPath(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QString refName,
    QString varPath
    ) override;

  virtual void dfgDoReorderPorts(
	FabricCore::DFGBinding const &binding,
	QString execPath,
	FabricCore::DFGExec const &exec,
	QString itemPath,
	QList<int> indices
	) override;

  virtual void dfgDoSetExtDeps(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec,
    QStringList extDeps
    ) override;

  virtual void dfgDoSplitFromPreset(
    FabricCore::DFGBinding const &binding,
    QString execPath,
    FabricCore::DFGExec const &exec
    ) override;

/* r3d
  virtual void dfgDoDismissLoadDiags(
    FabricCore::DFGBinding const &binding,
    QList<int> diagIndices
    ) override;
*/    

  virtual QString dfgDoEditNode( FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString oldNodeName, QString desiredNewNodeName, QString nodeMetadata, QString execMetadata ) override;

  virtual void dfgDoDismissLoadDiags( FabricCore::DFGBinding const &binding, QList<int> diagIndices ) override;

  virtual QString dfgDoCreatePreset( FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString nodeName, QString presetDirPath, QString presetName, bool updateOrigPreset ) override;


  virtual QString dfgDoAddInstPort( FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString instName, QString desiredPortName, FabricCore::DFGPortType portType, QString typeSpec, QString pathToConnect, FabricCore::DFGPortType connectType, QString extDep, QString metaData ) override;

  virtual QString dfgDoAddInstBlockPort( FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString instName, QString blockName, QString desiredPortName, QString typeSpec, QString pathToConnect, QString extDep, QString metaData ) override;

  virtual QString dfgDoAddBlock( FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString desiredName, QPointF pos ) override;

  virtual QString dfgDoAddBlockPort( FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString blockName, QString desiredPortName, FabricCore::DFGPortType portType, QString typeSpec, QString pathToConnect, FabricCore::DFGPortType connectType, QString extDep, QString metaData ) override;

};


extern const MSTR s_PortTypeEnumOUT;
extern const MSTR s_PortTypeEnumIO;
extern const MSTR s_PortTypeEnumIN;
