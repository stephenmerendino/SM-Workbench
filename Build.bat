@echo off

SETLOCAL

set BaseFilename=Workbench
set MainDir=%~dp0
set SrcDir=%MainDir%Src\
set BuildDir=%MainDir%SM-Engine\Build\

set CompilerFlags=/Zi /Od /nologo /std:c++20

set FilesToCompile=%SrcDir%%BaseFilename%.cpp
REM set FilesToCompile=%FilesToCompile%" "%MainDir%SomeNewFile.cpp

set IncludeDirs=/ISrc /I%MainDir%/SM-Engine/Src

set DllOutput=%BuildDir%%BaseFilename%.dll
set PdbOutput=%BuildDir%%BaseFilename%.pdb
set ObjOutput=%BuildDir%%BaseFilename%.obj
set OutputFiles=/Fe%DllOutput% /Fd%PdbOutput% /Fo%ObjOutput%

set LinkerFlags=/LD /link /DLL

REM call %MainDir%SM-Engine\Build.bat
cl %CompilerFlags% %FilesToCompile% %IncludeDirs% %OutputFiles% %LinkerFlags%

ENDLOCAL

EXIT /b %ERRORLEVEL%
