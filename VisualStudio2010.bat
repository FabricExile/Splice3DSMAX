@echo OFF

set REPODIR=%~dp0
set SLN=%REPODIR%/FabricSplice3dsmax.sln

IF NOT DEFINED FABRIC_DIR (
  SET FABRIC_DIR=%REPODIR%..\..\..\stage\Windows\x86_64\Release\
  ECHO Setting Fabric at %FABRIC_DIR%
  SET FABRIC_EXTS_PATH=%FABRIC_EXTS_PATH%;%FABRIC_DIR%\Exts
) ELSE ECHO Fabric found at %FABRIC_PATH%

echo Allow the system to load FabricCore dll
SET PATH=%FABRIC_DIR%/lib;%PATH%

IF NOT DEFINED BOOST_DIR ( 
  set BOOST_DIR=%REPODIR%..\..\..\ThirdParty\PreBuilt\Windows\x86_64\Release\boost\1.55.0\lib
)

set DISTDIR=%FABRIC_DIR%\SpliceIntegrations\FabricSplice3dsmax2014\
set SCINTILLANETDIR=%DISTDIR%ScintillaNET\

echo Starting VS Launcher
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE\devenv.exe" "%SLN%"


echo on
