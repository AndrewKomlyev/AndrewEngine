#include <AndrewEngine/Inc/AndrewEngine.h>
#include "GameState.h"

enum class States : size_t
{
    GameState = 0,
    Triangle =1,
    Square=2,
    Diamond=3,

};

int WINAPI  WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    AppConfig config;
    config.appName = L"Hello Simple Draw";
    config.winWidth = 1200;
    config.winHeigth = 720;

    AndrewEngine::App& mainApp = AndrewEngine::MainApp();
    mainApp.AddState<GameState>((size_t)States::GameState);
    mainApp.Run(config);

    return 0;
}