#ifndef _MSWMCreateMessageHandler_
#define _MSWMCreateMessageHandler_

#include "GUIMessageHandlerInterface.h"

namespace GUI
{
	namespace Message
	{
		class MSWMCreateMessageHandler: GUIMessageHandlerInterface
		{
		public:
			MSWMCreateMessageHandler(HWND handler, UINT msg, WPARAM wParam, LPARAM lParam):
				hWnd(handler),msg(msg),wParam(wParam),lParam(lParam)
			{}
			virtual MSWMCreateMessageHandler& handle();
		private:
			HWND hWnd;
			UINT msg;
			WPARAM wParam;
			LPARAM lParam;
		};
	}
}
#endif // !_MSWMCreateMessageHandler_



