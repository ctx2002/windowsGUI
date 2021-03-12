#include "MSGUI.h"
#include <tchar.h>
#include "GUIMessageHandlerInterface.h"

namespace GUI
{
    boolean MSWINClass::setup()
    {
        this->wcex.lpszClassName = this->className;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = 0;
        wcex.lpfnWndProc = WinProc::proc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = this->hInstance;
        wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH) ::GetStockObject(COLOR_BTNFACE);
        wcex.lpszMenuName = NULL;
        wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        if (!RegisterClassEx(&wcex))
        {
            return false;
        }

        return true;
    }

    boolean MSWINCreate::setup()
    {
        this->hWnd = ::CreateWindow
        (
            this->registeredClass.exposeWndClass().lpszClassName,
            this->title,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            500, 100,
            NULL,
            NULL,
            this->registeredClass.getHInstance(),
            &(this->proc)
        );

        if (!this->hWnd)
        {
            return false;
        }
        return true;
    }

    boolean MSWINShowWindow::setup()
    {
        ::ShowWindow(this->create.getWindowHandler(), this->nCmdShow);
        ::UpdateWindow(this->create.getWindowHandler());
        return true;
    }

    boolean MSWINMsgLoop::setup()
    {
        int status;
        while ((status = ::GetMessage(&(this->msg), 0, 0, 0)) != 0)
        {
            if (status == -1) {
                // handle the error, break
                break;
            }
            ::TranslateMessage(&(this->msg));
            ::DispatchMessage(&(this->msg));
        }

        return true;
    }

    MSWINClass MSGUI::registerWinClass()
    {
        MSWINClass wndClass{ this->hInstance, _T("MSGUI") };
        boolean result = wndClass.setup();

        if (result == false) {
            this->showError();
            throw "Call to RegisterClassEx failed!";
        }

        return wndClass;
    }

    MSWINCreate MSGUI::createWindow(MSWINClass& winClass)
    {
        
        MSWINCreate create { winClass, _T("MS GUI"), this->proc };
        boolean result = create.setup();

        if (result == false) {
            this->showError();
            throw "Call to create Window failed!";
        }

        return create;
    }

    MSWINShowWindow MSGUI::showWindow(MSWINCreate& create)
    {
        MSWINShowWindow show{ create, this->nCmdShow };
        show.setup();
        return show;
    }

    MSG& MSGUI::MSGLoop(MSWINShowWindow& window)
    {
        MSWINMsgLoop loop{ window };
        loop.setup();
        return loop.getMsg();
    }

    void MSGUI::start()
    {
        auto reg = this->registerWinClass();
        auto create = this->createWindow(reg);
        auto show = this->showWindow(create);
        this->MSGLoop(show);
    }

    void MSGUI::showError()
    {
        void* lpBuffer;

        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            ::GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
            (LPTSTR)&lpBuffer,
            0,
            NULL);

        MessageBox(NULL,
            (LPCTSTR)lpBuffer,
            _T("MS GUI"),
            NULL
        );
    }

    LRESULT CALLBACK WinProc::proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        WinProc* wnd = 0;
        if (message == WM_NCCREATE) {
            CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
            wnd = (WinProc*)pcs->lpCreateParams;

            ::SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR)wnd);
        }
        else {
            wnd = (WinProc*) ::GetWindowLongPtrA(hwnd, GWLP_USERDATA);
        }

        if (wnd) {
            return wnd->actualProc(hwnd, message, wParam, lParam);
        }
        else {
            // for messages that arrive prior to WM_NCCREATE
            return ::DefWindowProc(hwnd, message, wParam, lParam);
        }
    }

    LRESULT CALLBACK WinProc::actualProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        if (this->functions.find(message) != this->functions.end()) {
            return (this->functions[message])(hwnd, message, wParam, lParam);
        }
        else {
            return ::DefWindowProc(hwnd, message, wParam, lParam);
        }
    }

    void WinProc::on(UINT message, std::function<LRESULT(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)> func)
    {
        //see WinProcBuilder.cpp to find out how to use this function
        this->functions[message] = func;
    }
}
