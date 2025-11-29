#include <stdio.h>

#include "SM/Engine.h"

SM::EngineApi Engine;

GAME_LOADED
{
    Engine = engineApi;
}

GAME_UPDATE
{
    //Engine.EngineLog("GameUpdate\n");
}

GAME_RENDER
{
    //Engine.EngineLog("GameRender\n");
}
