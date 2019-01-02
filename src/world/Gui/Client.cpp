#include "Client.h"
#include "context/MainContext.h"

#include <Logging/Logger.h>

#include "renderer/NullRenderer.h"
#include "renderer/SDLRenderer.h"

Sapphire::GUI::Client::Client( Sapphire::FrameworkPtr pFw ) :
  BaseManager( pFw )
{
   m_pClientControl = std::make_shared< ClientControl >( pFw, m_windowManager );
}

// TODO: use struct Status for control instead of sending single bool
// helps for delta etc as well

// HACK: It makes NO sense for backend to handle things the way it does now!!
// Either 1. move events and remove backend render completely, or
// move window management to backend!

void Sapphire::GUI::Client::run()
{
   Logger::info( "Initializing renderer" );
   m_pRenderer = std::make_shared< Renderer::SDLRenderer >();
   m_pRenderer->init( m_pClientControl );

   Logger::info( "Initializing main context" );
   m_pClientControl->mainCtx = std::make_shared< Context::MainContext >( m_pClientControl );

   m_pClientControl->isRunning = true;
}

void Sapphire::GUI::Client::render()
{
   m_pRenderer->render();

   if( !m_pClientControl->isRunning )
     stop();
}

void Sapphire::GUI::Client::stop()
{
   m_pClientControl->isRunning = false;
   m_pRenderer->dispose();
}

void Sapphire::GUI::Client::setClientControl()
{
   
}

bool Sapphire::GUI::Client::isRunning() const
{
  return m_pClientControl->isRunning;
}