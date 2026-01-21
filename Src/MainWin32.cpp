#include <cstring>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Workbench.cpp"

int WINAPI WinMain(HINSTANCE app, 
				   HINSTANCE prevApp, 
				   LPSTR args, 
				   int show)
{
    CommandLineArgs commandLineArgs;

    // parse args and store them for later use
    size_t argsLen = strlen(args);
    size_t curPos = 0;
    while(curPos < argsLen)
    {
        // we are searching for keys which by convention always start with a hyphen "-"
        if(args[curPos] != '-')
        {
            // Would be nice to have a message letting you know you passed an arg without a key

            // advance to next arg which are space delimited
            while(args[curPos] != ' ' && curPos < argsLen)
            {
                curPos++;
            }
            if(curPos == argsLen)
            {
                break;
            }

            args[curPos] = '\0';
            curPos++;
        }

        commandLineArgs.m_keys[commandLineArgs.m_numArgs] = &args[curPos + 1]; // don't store the hyphen
        args[curPos] = '\0';
        curPos++;

        // advance to next arg which are space delimited
        while(args[curPos] != ' ' && curPos < argsLen)
        {
            curPos++;
        }
        if(curPos == argsLen)
        {
            commandLineArgs.m_numArgs++;
            break;
        }

        args[curPos] = '\0';
        curPos++;

        if(args[curPos] != '-') // check it's an arg and not another key
        {
            commandLineArgs.m_values[commandLineArgs.m_numArgs] = &args[curPos];

            // advance to next arg which are space delimited
            while(args[curPos] != ' ' && curPos < argsLen)
            {
                curPos++;
            }
            if(curPos == argsLen)
            {
                commandLineArgs.m_numArgs++;
                break;
            }
        }

        commandLineArgs.m_numArgs++;
    }

    WorkbenchRun(commandLineArgs);
    return 0;
}
