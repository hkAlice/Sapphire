#ifndef _MAIN_CTX
#define _MAIN_CTX

#include <vector>
#include <memory>

#include "../ClientControl.h"
#include "../window/CharacterSelectWindow.h"
#include "../window/WindowManager.h"

//TODO: Type forward

namespace Sapphire::GUI::Context
{
   class MainContext
   {
   public:
      MainContext( ClientControlPtr clientControl );
      ~MainContext();

      void createNewChar();

      uint32_t getSelectedCharacter() const;

      void setSelectedCharacter( uint32_t playerId );

      ItemPtr openItemEditor( Entity::Player pPlayer, ItemPtr pItem = nullptr );

   private:
      void init();

      ClientControlPtr m_pClientControl;

      std::shared_ptr< Window::CharacterSelectWindow > m_pCharSelectWindow;

      std::vector< uint32_t > m_ownedWindows;

      uint32_t m_selectedPlayerID;

      template< class IWindow, typename... Args >
      void createContextWindow( Args... args )
      {
         auto pWindow = std::make_shared< IWindow >( args... );
         auto windowID = m_pClientControl->windowManager.addWindow( pWindow );

         m_ownedWindows.emplace_back( windowID );
      }
   };
}

#endif