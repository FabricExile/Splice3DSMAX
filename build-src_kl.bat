setlocal

SET MAX_DIR=%~dp0
REM It seems KL2EDK no longer works with non-local folders...
cd /D "%FABRIC_DIR%\Exts\Builtin\Math"
mkdir h
kl2edk Math.fpm.json -o h
rd /s /q "%MAX_DIR%\src_kl\"
mkdir "%MAX_DIR%\src_kl\h"
xcopy h "%MAX_DIR%\src_kl\h" /S /E
rmdir /S /q h
endlocal
