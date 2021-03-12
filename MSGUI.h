#ifndef _MSGUI_
#define _MSGUI_

#include <Windows.h>
#include <map>
#include <functional>
#include "GUI.h"
#include "GUIMessageHandlerInterface.h"

namespace GUI {

	class WinProc
	{
	public:
		WinProc() = default;
		static LRESULT CALLBACK proc(HWND, UINT, WPARAM, LPARAM);
		LRESULT CALLBACK actualProc(HWND, UINT, WPARAM, LPARAM);
		void on(UINT message, std::function<LRESULT(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)> func);
	protected:
		std::map<UINT, std::function<LRESULT(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)>> functions;
	};

	
	class MSWINClass
	{
	public:
		MSWINClass(HINSTANCE hInstance, const TCHAR* className):
		hInstance(hInstance),className(className){}

		boolean setup();
		HINSTANCE getHInstance() const
		{
			return this->hInstance;
		}

		WNDCLASSEX& exposeWndClass(void)
		{
			return this->wcex;
		}

		const TCHAR* getClassName()
		{
			return this->className;
		}
	private:
		HINSTANCE hInstance;
		WNDCLASSEX wcex{};
		const TCHAR* className;
	};

	class MSWINCreate
	{
	public:
		MSWINCreate(MSWINClass& registeredClass, const TCHAR* title, WinProc& proc):
			registeredClass(registeredClass), title(title), proc(proc)
		{
		}
		boolean setup();
		HWND getWindowHandler() const
		{
			return this->hWnd;
		}
		~MSWINCreate()
		{
			this->hWnd = 0;
		}
	private:
		HWND hWnd{};
		MSWINClass registeredClass;
		const TCHAR* title;
		WinProc& proc;
	};

	class MSWINShowWindow
	{
	public:
		MSWINShowWindow(MSWINCreate create, int nCmdShow):
			create(create), nCmdShow(nCmdShow)
		{}
		boolean setup();
	private:
		MSWINCreate create;
		int nCmdShow;
	};

	class MSWINMsgLoop
	{
	public:
		MSWINMsgLoop(MSWINShowWindow window):
		    window(window)
		{}
		boolean setup();
		MSG& getMsg()
		{
			return this->msg;
		}
	private:
		MSWINShowWindow window;
		MSG msg = { 0 };
	};
	
	class MSGUI :
		public GUI
	{
	public:
		MSGUI(
			HINSTANCE hInstance,
			LPSTR     lpCmdLine,
			int       nCmdShow,
			WinProc& proc
		):
			hInstance(hInstance), lpCmdLine(lpCmdLine), nCmdShow(nCmdShow), proc(proc)
		{}
		
		void start();

		void showError();

		~MSGUI()
		{

		}
	protected:
		MSWINClass registerWinClass();
		MSWINCreate createWindow(MSWINClass& winClass);
		MSWINShowWindow showWindow(MSWINCreate& create);
		MSG& MSGLoop(MSWINShowWindow& window);
	private:
		HINSTANCE hInstance;
		LPSTR     lpCmdLine;
		int       nCmdShow;
		WinProc& proc;
	};
};
#endif;

