#ifndef _MSWMDestroyMessageHandler_
#define _MSWMDestroyMessageHandler_

#include "GUIMessageHandlerInterface.h"

namespace GUI
{
	namespace Message
	{
		class MSWMDestroyMessageHandler : GUIMessageHandlerInterface
		{
		public:
			MSWMDestroyMessageHandler(HWND handler, UINT msg, WPARAM wParam, LPARAM lParam) :
				hWnd(handler), msg(msg), wParam(wParam), lParam(lParam)
			{}
			virtual MSWMDestroyMessageHandler& handle() override;
		private:
			HWND hWnd;
			UINT msg;
			WPARAM wParam;
			LPARAM lParam;
		};
	}
}

#endif // !_MSWMDestroyMessageHandler_



