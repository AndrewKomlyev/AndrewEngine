#include <AndrewEngine/Inc/AndrewEngine.h>
#include "GameState.h"

enum class States : size_t
{
    GameState = 0,
};

int WINAPI  WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    AndrewEngine::App& mainApp = AndrewEngine::MainApp();
    mainApp.AddState<GameState>((size_t)States::GameState);
    AndrewEngine::AppConfig config;
    config.appName = L"Hello Editor";
    config.winWidth = 1200;
    config.winHeigth = 720;

    mainApp.Run(config);

    return 0;
}