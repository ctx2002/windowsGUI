#include "MSWMCreateMessageHandler.h"

namespace GUI
{
	namespace Message
	{
		MSWMCreateMessageHandler& MSWMCreateMessageHandler::handle()
		{
			::MessageBox(this->hWnd, TEXT("Window has been successfully created"), TEXT("Succes"), MB_OK);
			return (*this);
		}
	}
}