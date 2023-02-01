#pragma once

namespace AndrewEngine
{
    class AppState;
    struct AppConfig
    {
        std::wstring appName;
        uint32_t winWidth = 1200;
        uint32_t winHeigth = 720;
        uint32_t debugDrawLimit = 100000;
    };

    class App final
    {
    public:
        template <class StateType>
        void AddState(size_t stateID)
        {
            static_assert(std::is_base_of_v<AppState, StateType>, "AddState must be of the type AppState");
            std::string test = "a";
            auto [iter, success] = mAppStates.try_emplace(stateID, nullptr);
            if (success)
            {
                auto& ptr = iter->second;
                ptr = std::make_unique<StateType>();
                if (mCurrentState == nullptr)
                {
                    LOG("APP -- CurrentState: %d", iter->first );
                    mCurrentState = ptr.get();
                }
            }
        }
        void ChangeState(size_t stateID);

        //[Depricated] use of Run() function
        void Run();
        void Run(const AppConfig& config);
        void Quit();

    private:
        using AppStateMap = std::map<size_t, std::unique_ptr<AppState>>;

        AppStateMap mAppStates;
        AppState* mCurrentState = nullptr;
        AppState* mNextState = nullptr;

        bool mRunning = false;
    };


}