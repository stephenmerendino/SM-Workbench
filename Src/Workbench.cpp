#include <stdio.h>

#include "SM/Engine.h"

SM::EngineApi Engine;

GAME_BIND_ENGINE
{
    Engine = engineApi;
}

GAME_INIT
{
    Engine.EngineLog("GameInit\n");
}

GAME_UPDATE
{
    //Engine.EngineLog("GameUpdate\n");
}

GAME_RENDER
{
    //Engine.EngineLog("GameRender\n");
}
