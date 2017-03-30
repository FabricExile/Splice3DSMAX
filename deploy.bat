set batdir=%~dp0
set FabricStageDir=%batdir%stage
set FabricFinalDir=%batdir%../../../stage/Windows/x86_64/Release/DCCIntegrations
xcopy "%FabricStageDir%"  "%FabricFinalDir%" /e /i /y
RMDIR "%FabricStageDir%" /S /Q

