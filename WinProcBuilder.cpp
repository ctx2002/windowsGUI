#include <Windows.h>
#include "MSGUI.h"
#include "messages.h"
#include "WinProcBuilder.h"

namespace GUI
{
    WinProc WinProcBuilder::on(void)
    {
        WinProc proc{};

        proc.on(WM_CREATE, [](HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
            Message::MSWMCreateMessageHandler handler(hwnd, message, wParam, lParam);
            handler.handle();
            return 0;
        });

        proc.on(WM_DESTROY, [](HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
            Message::MSWMDestroyMessageHandler handler(hwnd, message, wParam, lParam);
            handler.handle();
            return 0;
        });

        return proc;
    }
}

