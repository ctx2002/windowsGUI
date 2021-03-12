#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#include "MSGUI.h"

#include "WinProcBuilder.h"
//#include "messages.h"

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
    )
{
    auto proc = GUI::WinProcBuilder::on();

    GUI::MSGUI gui{ hInstance ,lpCmdLine ,nCmdShow, proc };
    gui.start();

    return 0;
}