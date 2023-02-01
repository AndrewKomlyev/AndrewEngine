#include "Precompiled.h"
#include "AndrewEngine.h"

AndrewEngine::App& AndrewEngine::MainApp()
{
    static App sApp;
    return sApp;
}