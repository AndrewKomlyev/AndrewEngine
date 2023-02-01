#include <AndrewEngine/Inc/AndrewEngine.h>
#include "GameState.h"

enum class States : size_t
{
    GameState = 0,
    Triangle,
    Square,
    Diamond
};

int WINAPI  WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    AndrewEngine::App& mainApp = AndrewEngine::MainApp();

    mainApp.AddState<GameState>((size_t)States::GameState);
    mainApp.AddState<Triangle>((size_t)States::Triangle);
    mainApp.AddState<Square>((size_t)States::Square);
    mainApp.AddState<Diamond>((size_t)States::Diamond);
    mainApp.Run();

    return 0;
}