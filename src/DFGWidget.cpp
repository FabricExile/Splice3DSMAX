#include "StdAfx.h"

#include "DFGWidget.h"
#include "plugin.h"


//std::string DFGWidget::s_currentUINodeName;
//std::map<DFGWidget*, FabricDFGBaseInterface*> DFGWidget::s_widgets;

DFGWidget::DFGWidget(QWidget * parent, FabricCore::Client& client, FabricServices::DFGWrapper::Binding& binding, FabricServices::DFGWrapper::Host* host)
	: DFG::DFGCombinedWidget(parent)
	, m_host(host)
{
	//m_baseInterfaceName = s_currentUINodeName;

	//FabricDFGBaseInterface * interf = FabricDFGBaseInterface::getInstanceByName(m_baseInterfaceName.c_str());

	//if(interf)
	{
		//s_widgets.insert(std::pair<DFGWidget*, FabricDFGBaseInterface*>(this, interf));

		//m_mayaClient = interf->getCoreClient();
		// create a host for Canvas
		//m_host = new DFGWrapper::Host(m_client);

		//FabricServices::ASTWrapper::KLASTManager * manager = pOwner->getASTManager();
		//FabricServices::DFGWrapper::Host * host = pOwner->getDFGHost();

		//DFGWrapper::Binding binding = interf->getDFGBinding();

		ASTWrapper::KLASTManager* manager = ASTWrapper::KLASTManager::retainGlobalManager(&client);
		DFGWrapper::GraphExecutablePtr graph = DFGWrapper::GraphExecutablePtr::StaticCast(binding.getExecutable());

		init(&client, manager, host, binding, graph, nullptr, false);
	}
}

DFGWidget::~DFGWidget()
{
}

//QWidget * DFGWidget::creator(QWidget * parent, const QString & name)
//{
//	return new DFGWidget(parent);
//}

//void DFGWidget::setCurrentUINodeName(const char * node)
//{
//  if(node)
//    s_currentUINodeName = node;
//}

//void DFGWidget::closeWidgetsForBaseInterface(FabricDFGBaseInterface * interf)
//{
//  std::map<DFGWidget*, FabricDFGBaseInterface*>::iterator it;
//  for(it = s_widgets.begin(); it != s_widgets.end(); it++)
//  {
//    if(it->second == interf)
//    {
//      s_widgets.erase(it);
//
//      QWidget * parent = (QWidget*)it->first->parent();
//
//      // layout widget
//      if(parent)
//        parent = (QWidget*)parent->parent();
//
//      // dock widget
//      if(parent)
//        parent = (QWidget*)parent->parent();
//
//      if(parent)
//      {
//        parent->close();
//        parent->deleteLater();
//      }
//      break;
//    }
//  }
//}

void DFGWidget::onRecompilation()
{
	//FabricDFGBaseInterface * interf = FabricDFGBaseInterface::getInstanceByName(m_baseInterfaceName.c_str());
	//if(interf)
	//{
	//  interf->invalidateNode();
	//}
}

void DFGWidget::onPortRenamed(QString path, QString newName)
{
	// ignore ports which are not args
	if (path.indexOf('.') > 0)
		return;

	//FabricDFGBaseInterface * interf = FabricDFGBaseInterface::getInstanceByName(m_baseInterfaceName.c_str());
	//if(!interf)
	//  return;

	//MFnDependencyNode thisNode(interf->getThisMObject());
	//MPlug plug = thisNode.findPlug(path.toUtf8().constData());
	//if(plug.isNull())
	//  return;

	//MString cmdStr = "renameAttr \"";
	//cmdStr += thisNode.name() + "." + MString(path.toUtf8().constData());
	//cmdStr += "\" \"" + MString(newName.toUtf8().constData()) + "\";";
	//MGlobal::executeCommandOnIdle(cmdStr, false);
}

//void DFGWidget::mayaLog(const char * message)
//{
//  mayaLogFunc(message);
//}
