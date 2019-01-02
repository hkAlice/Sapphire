#ifndef _CHARSELECT_WINDOW
#define _CHARSELECT_WINDOW

#include <memory>

#include "IWindow.h"
#include <Logging/Logger.h>
#include "../ClientControl.h"

namespace Sapphire::GUI::Window
{
   class CharacterSelectWindow : public virtual IWindow
   {
   public:
      CharacterSelectWindow( ClientControlPtr pClientControl );

      virtual ~CharacterSelectWindow()
      {
         
      }

      virtual void render();

      virtual void init();

   private:
      ClientControlPtr m_pClientControl;

      ImGuiWindowFlags m_windowFlags;
   };


}

#endif