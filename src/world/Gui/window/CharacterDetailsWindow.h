#ifndef _CHARDETAILS_WINDOW
#define _CHARDETAILS_WINDOW

#include <memory>
#include <unordered_map>
#include <string>

#include <Logging/Logger.h>
#include <CommonGen.h>
#include <ForwardsZone.h>

#include "IWindow.h"
#include "../ClientControl.h"

namespace Sapphire::GUI::Window
{
   class CharacterDetailsWindow : public virtual IWindow
   {
   public:
      CharacterDetailsWindow( ClientControlPtr pClientControl );

      virtual ~CharacterDetailsWindow()
      {
         
      }

      virtual void render();

      virtual void init();

   private:
      void drawBasicInfo();

      void drawActionsInfo();

      void drawPositionInfo();

      void drawInventoryInfo();

      void drawInstanceInfo();

      // todo: rethink - store pPlayer in class, remove func args

      Entity::PlayerPtr m_pPlayer;

      ClientControlPtr m_pClientControl;

      ImGuiWindowFlags m_windowFlags;

   };


}

#endif