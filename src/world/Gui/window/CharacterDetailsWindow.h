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
      void drawBasicInfo( Entity::PlayerPtr pPlayer );

      void drawActionsInfo( Entity::PlayerPtr pPlayer );

      void drawPositionInfo( Entity::PlayerPtr pPlayer );

      void drawInventoryInfo( Entity::PlayerPtr pPlayer );

      ClientControlPtr m_pClientControl;

      ImGuiWindowFlags m_windowFlags;

   };


}

#endif