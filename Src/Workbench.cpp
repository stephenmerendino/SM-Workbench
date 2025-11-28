#include <stdio.h>

#include "SM/Engine.h"

sm::EngineApi Engine;

SM_DLL_EXPORT void GameLoaded(sm::EngineApi engineApi)
{
    Engine = engineApi;
}

SM_DLL_EXPORT void GameUpdate()
{
    Engine.EngineLog("GameUpdate\n");
}

SM_DLL_EXPORT void GameRender()
{
    Engine.EngineLog("GameRender\n");
}
