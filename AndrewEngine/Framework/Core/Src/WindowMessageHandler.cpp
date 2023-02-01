#include "Precompiled.h"
#include "../Inc/DebugUtil.h"
#include "../Inc/WindowMessageHandler.h"

using namespace AndrewEngine::Core;


void WindowMessageHandler::Hook(HWND window, Callback cb)
{
    mWindow = window;
    mPreviousCallback = (Callback)GetWindowLongPtrA(window, GWLP_WNDPROC);
    SetWindowLongPtrA(window, GWLP_WNDPROC, (LONG_PTR)cb);
}

void WindowMessageHandler::Unhook()
{
    SetWindowLongPtrA(mWindow, GWLP_WNDPROC, (LONG_PTR)mPreviousCallback);
    mWindow = nullptr;
}

LPARAM WindowMessageHandler::ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    ASSERT(mPreviousCallback, "WindowMessageHandler -- No Callback is hooked");
    return CallWindowProcA((WNDPROC)mPreviousCallback, window, message, wParam, lParam);

}