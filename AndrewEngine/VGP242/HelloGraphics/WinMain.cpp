#include <AndrewEngine/Inc/AndrewEngine.h>
#include "GameState.h"

enum class States : size_t
{
    GameState = 0
};

int WINAPI  WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    AndrewEngine::App& mainApp = AndrewEngine::MainApp();
    mainApp.AddState<GameState>((size_t)States::GameState);
    mainApp.Run();

    return 0;
}