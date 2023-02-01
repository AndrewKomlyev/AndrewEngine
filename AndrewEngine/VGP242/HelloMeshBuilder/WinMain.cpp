#include <AndrewEngine/Inc/AndrewEngine.h>
#include "GameState.h"

enum class States : size_t
{
    GameState = 0,
    Cube =1,
    Rectangle=2,
    Plane=3,
    Cylinder=4,
    Sphere=5
};

int WINAPI  WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    AndrewEngine::App& mainApp = AndrewEngine::MainApp();

    mainApp.AddState<GameState>((size_t)States::GameState);
    mainApp.AddState<GameState>((size_t)States::Cube);
    mainApp.AddState<GameState>((size_t)States::Rectangle);
    mainApp.AddState<GameState>((size_t)States::Plane);
    mainApp.AddState<GameState>((size_t)States::Cylinder);
    mainApp.AddState<GameState>((size_t)States::Sphere);

    mainApp.Run();

    return 0;
}