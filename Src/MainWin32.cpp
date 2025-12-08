#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Workbench.cpp"

int WINAPI WinMain(HINSTANCE app, 
				   HINSTANCE prevApp, 
				   LPSTR args, 
				   int show)
{
    WorkbenchRun();
    return 0;
}
