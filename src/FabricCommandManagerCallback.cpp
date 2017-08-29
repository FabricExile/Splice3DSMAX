//
// Copyright (c) 2010-2017, Fabric Software Inc. All rights reserved.
//
#include "StdAfx.h"

#include "MaxDFGCmdHandler.h"
#include <FabricUI/Util/RTValUtil.h>
#include "FabricCommandManagerCallback.h"
#include <FabricUI/Commands/CommandHelpers.h>
#include <FabricUI/Commands/KLCommandManager.h>
#include <FabricUI/Commands/KLCommandRegistry.h>
#include <FabricUI/Commands/BaseScriptableCommand.h>
#include <FabricUI/Dialog/DialogCommandRegistration.h>
#include <FabricUI/Commands/BaseRTValScriptableCommand.h>
#include <FabricUI/Application/FabricApplicationStates.h>
#include <FabricUI/OptionsEditor/Commands/OptionEditorCommandRegistration.h>

// Uncomment the following to have stdout and stderr printed into files (else these will not
// be seen in the Maya console)
//
// #include <stdlib.h>
// #include <stdio.h>
// #include <iostream>

using namespace FabricCore;
using namespace FabricUI::Util;
using namespace FabricUI::Commands;

bool FabricCommandManagerCallback::s_instanceFlag = false;
FabricCommandManagerCallback* FabricCommandManagerCallback::s_cmdManagerMayaCallback = 0;

FabricCommandManagerCallback::FabricCommandManagerCallback()
  : QObject()  
{
}

FabricCommandManagerCallback::~FabricCommandManagerCallback()
{
  s_instanceFlag = false;
}

FabricCommandManagerCallback *FabricCommandManagerCallback::GetManagerCallback()
{
  if(!s_instanceFlag)
  {
    s_cmdManagerMayaCallback = new FabricCommandManagerCallback();
    s_instanceFlag = true;
  }
  return s_cmdManagerMayaCallback;
}

inline void encodeArg(
  QString const&arg,
  std::stringstream &cmdArgs)
{
  cmdArgs << ' ';
  cmdArgs << arg.toUtf8().constData();
}
 
void FabricCommandManagerCallback::onCommandDone(
  BaseCommand *cmd,
  bool canUndo)
{
  MAXSPLICE_CATCH_BEGIN;

  if(cmd->canLog())
  {
    BaseScriptableCommand *scriptCmd = qobject_cast<BaseScriptableCommand*>(cmd);

    QMap<QString, QString> cmdArgs;

    if(scriptCmd)
    {
      BaseRTValScriptableCommand *rtValScriptCmd = qobject_cast<BaseRTValScriptableCommand*>(cmd);
      
      foreach(QString key, scriptCmd->getArgKeys())
      {
        if(!scriptCmd->hasArgFlag(key, CommandArgFlags::DONT_LOG_ARG))
        {          
          if( rtValScriptCmd ) {
            QString path = rtValScriptCmd->getRTValArgPath( key ).toUtf8().constData();
            
            if( !path.isEmpty() ) 
              cmdArgs[key] = CommandHelpers::encodeJSON( CommandHelpers::castToPathValuePath( path ) );
            
            else
            {
              RTVal val = rtValScriptCmd->getRTValArgValue( key );
              cmdArgs[key] = CommandHelpers::encodeJSON( RTValUtil::toJSON( val ) );
            }
          }

          else
            cmdArgs[key] = scriptCmd->getArg(key);
        }
      }
    }
 
    MaxDFGCmdHandler::fabricCommand(
      cmd->getName(), 
      cmdArgs,
      false, 
      canUndo);
  }

  MAXSPLICE_CATCH_END;
}

void FabricCommandManagerCallback::init(
  FabricCore::Client client)
{
  MAXSPLICE_CATCH_BEGIN;

  if(!CommandManager::isInitalized())
  {
    // Uncomment the following to have stdout and stderr printed into files (else these will not
    // be seen in the Maya console)
    //
    // freopen( "C:\\Users\\Julien\\Documents\\Dev\\SceneGraph\\stage\\Windows\\x86_64\\Release\\DCCIntegrations\\Fabric3dsmax2017\\3dsMaxLog.txt", "a", stdout );
    // freopen( "C:\\Users\\Julien\\Documents\\Dev\\SceneGraph\\stage\\Windows\\x86_64\\Release\\DCCIntegrations\\Fabric3dsmax2017\\3dsMaxError.txt", "a", stderr );
    // std::cout << "\n\n----- initializePlugin -----\n\n" << std::endl;
 
    new FabricUI::Application::FabricApplicationStates(client);
    
    KLCommandRegistry *registry = new KLCommandRegistry();
    registry->synchronizeKL();
    
    KLCommandManager *manager = new KLCommandManager();
    
    QObject::connect(
      manager,
      SIGNAL(commandDone(FabricUI::Commands::BaseCommand*, bool)),
      this,
      SLOT(onCommandDone(FabricUI::Commands::BaseCommand*, bool))
      );

    FabricUI::OptionsEditor::OptionEditorCommandRegistration::RegisterCommands();
    FabricUI::Dialog::DialogCommandRegistration::RegisterCommands();
  }
  MAXSPLICE_CATCH_END;
}

void FabricCommandManagerCallback::clear()
{  
  MAXSPLICE_CATCH_BEGIN;

  if(CommandManager::isInitalized())
  {
    CommandManager::getCommandManager()->clear();

    FabricUI::Application::FabricApplicationStates *appStates = FabricUI::Application::FabricApplicationStates::GetAppStates();
    delete appStates;
    appStates = 0;

    CommandManager *manager = CommandManager::getCommandManager();
    delete manager;
    manager = 0;

    CommandRegistry *registry =  CommandRegistry::getCommandRegistry();
    delete registry;
    registry = 0;
  }

  MAXSPLICE_CATCH_END;
}

void FabricCommandManagerCallback::reset()
{
  MAXSPLICE_CATCH_BEGIN;

  CommandManager::getCommandManager()->clear();

  KLCommandRegistry *registry = qobject_cast<KLCommandRegistry*>(
    CommandRegistry::getCommandRegistry());
  registry->synchronizeKL();
  
  MAXSPLICE_CATCH_END;
}
