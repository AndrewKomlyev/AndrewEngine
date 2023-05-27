#include <AndrewEngine/Inc/AndrewEngine.h>
#include "GameState.h"

enum class States : size_t
{
    GameState = 0,
    Cube = 1,
    Rectangle = 2,
    Plane = 3,
    Cylinder = 4,
    Sphere = 5
};

int WINAPI  WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    AndrewEngine::App& mainApp = AndrewEngine::MainApp();
    mainApp.AddState<GameState>((size_t)States::GameState);
    AndrewEngine::AppConfig config;
    config.appName = L"Hello Animation";
    config.winWidth = 1200;
    config.winHeigth = 720;

    mainApp.Run(config);

    return 0;
}