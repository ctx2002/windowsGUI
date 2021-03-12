#include "MSWMDestroyMessageHandler.h"

namespace GUI
{
	namespace Message
	{
		MSWMDestroyMessageHandler& MSWMDestroyMessageHandler::handle()
		{
			::PostQuitMessage(0);
			return (*this);
		}
	}
}
