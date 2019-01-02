#include "MainContext.h"

#include "../ClientControl.h"
#include "../window/WindowManager.h"
#include "../window/CharacterSelectWindow.h"
#include "../window/CharacterDetailsWindow.h"

#include "Actor/Player.h"

#include <Logging/Logger.h>

using namespace Sapphire::GUI;

Context::MainContext::MainContext( ClientControlPtr pClientControl )
   : m_pClientControl( pClientControl )
{
   init();
}

Context::MainContext::~MainContext()
{
   for( auto& windowID : m_ownedWindows )
      m_pClientControl->windowManager.removeWindow( windowID );
}

void Context::MainContext::init()
{
   // Build our character list, main frame, and sidebar for party etc

   createContextWindow< Window::CharacterSelectWindow >( m_pClientControl );
   createContextWindow< Window::CharacterDetailsWindow >( m_pClientControl );
}

void Context::MainContext::setSelectedCharacter( uint32_t playerId )
{
  m_selectedPlayerID = playerId;
}

uint32_t Context::MainContext::getSelectedCharacter() const
{
  return m_selectedPlayerID;
}

void Context::MainContext::createNewChar()
{

}

// HACK: Due to item creation depending on a player existing, we cannot split responsibility
Sapphire::ItemPtr Context::MainContext::openItemEditor( Sapphire::Entity::Player pPlayer, Sapphire::ItemPtr pItem )
{
  return nullptr;
}