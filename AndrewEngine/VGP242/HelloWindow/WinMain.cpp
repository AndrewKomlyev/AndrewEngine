#include <Core/Inc/Core.h>
#include <AndrewEngine/Inc/AndrewEngine.h>

enum class States : size_t
{
    GameState = 0
};

class GameState: public  AndrewEngine::AppState
{
public:
    virtual ~GameState() = default;

};

int WINAPI  WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    AndrewEngine::App& mainApp = AndrewEngine::MainApp();

    mainApp.AddState<GameState>((size_t)States::GameState);
    mainApp.Run();

    return 0;
}