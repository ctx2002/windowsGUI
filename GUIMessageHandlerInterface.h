#ifndef _GUIMessageHandlerInterface_
#define _GUIMessageHandlerInterface_

#include <Windows.h>

namespace GUI
{
	namespace Message 
	{
		class GUIMessageHandlerInterface
		{
		public:
			virtual GUIMessageHandlerInterface& handle() = 0;
			virtual ~GUIMessageHandlerInterface()
			{

			}
		};
	}
}

#endif // !_GUIMessageHandlerInterface_

