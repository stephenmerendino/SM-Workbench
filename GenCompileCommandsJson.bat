@echo off

setlocal EnableDelayedExpansion

set ScriptDir=%~dp0
set CodeRootDir=Src
set OutputFile=%ScriptDir%compile_commands.json

set Directory=%CD%
set "Directory=!Directory:\=/!"
set IncludeDirs=/ISrc /ISM-Engine/Src

echo [ > %OutputFile%

set "FoundFile="
for /r "%ScriptDir%" %%f in (*.cpp *.c) do (
    if not "!FoundFile!"=="" (
        echo Found file: !FoundFile!

        echo   { >> %OutputFile%
        echo     "directory": "%Directory%", >> %OutputFile%
        echo     "command": "cl.exe %IncludeDirs% !FoundFile!", >> %OutputFile%
        echo     "file": "!FoundFile!" >> %OutputFile%
        echo   }, >> %OutputFile%
    )

    set "FoundFile=%%f"
    set "FoundFile=!FoundFile:%CD%\=!"
    set "FoundFile=!FoundFile:\=/!"
)

if not "!FoundFile!"=="" (
    echo Found file: !FoundFile!

    echo   { >> %OutputFile%
    echo     "directory": "%Directory%", >> %OutputFile%
    echo     "command": "cl.exe %IncludeDirs% !FoundFile!", >> %OutputFile%
    echo     "file": "!FoundFile!" >> %OutputFile%
    echo   } >> %OutputFile%
)

echo ] >> %OutputFile%
