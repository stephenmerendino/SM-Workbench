@echo off

SETLOCAL

set BaseFilename=Main
set MainDir=%~dp0
set SrcDir=%MainDir%Src\
set BuildDir=%MainDir%Build\

call %MainDir%sm-engine\Build.bat

mkdir %BuildDir% >nul 2>&1

set ExeOutput=%BuildDir%%BaseFilename%.exe
set PdbOutput=%BuildDir%%BaseFilename%.pdb
set ObjOutput=%BuildDir%%BaseFilename%.obj

set FilesToCompile=%SrcDir%%BaseFilename%.cpp
REM set FilesToCompile=%FilesToCompile%" "%MainDir%SomeNewFile.cpp

cl /Zi /Od %FilesToCompile% /Fe%ExeOutput% /Fd%PdbOutput% /Fo%ObjOutput%

ENDLOCAL
