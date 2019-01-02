#ifndef _TYPE_FORWARD
#define _TYPE_FORWARD

#include <memory>

namespace Sapphire::GUI
{
   struct ClientControl;
   using ClientControlPtr = std::shared_ptr< ClientControl >;

   namespace Window
   {
      class IWindow;

      class CharacterSelectWindow;
      class CharacterSelectWindowPtr;
   }
}

#endif