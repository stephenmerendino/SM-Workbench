@echo off

SETLOCAL

set BaseFilename=MainWin32
set MainDir=%~dp0
set SrcDir=%MainDir%Src\
set BuildDir=%MainDir%\Build\
set EngineDir=%~dp0SM-Engine\

set CompilerFlags=/Zi /Od /nologo /std:c++20 /EHsc

set FilesToCompile=%SrcDir%%BaseFilename%.cpp
REM set FilesToCompile=%FilesToCompile%" "%MainDir%SomeNewFile.cpp

set IncludeDirs=/ISrc\ /I%MainDir%SM-Engine\Src\

set EngineLibDir=%MainDir%SM-Engine\Build\
set Libs=SM-Engine.lib

set ExeOutput=%BuildDir%Workbench.exe
set PdbOutput=%BuildDir%Workbench.pdb
set ObjOutput=%BuildDir%Workbench.obj
set OutputFiles=/Fe%ExeOutput% /Fd%PdbOutput% /Fo%ObjOutput%

set LibsPath=/LIBPATH:%EngineDir%Build\ /LIBPATH:%EngineDir%Libs\
set LinkerFlags=/link %libs% %LibsPath%

mkdir %BuildDir% >nul 2>&1

call %MainDir%SM-Engine\EngineBuild.bat
@echo on
cl %CompilerFlags% %FilesToCompile% %IncludeDirs% %OutputFiles% %LinkerFlags%
@echo off

ENDLOCAL

EXIT /b %ERRORLEVEL%
