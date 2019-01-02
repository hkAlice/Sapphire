#include "WindowManager.h"

#include <Logging/Logger.h>

using namespace Sapphire::GUI;

Window::WindowManager::WindowManager()
   : m_idIncr( 0 )
{
   Logger::info( "Window Manager stack starting up" );
}

Window::WindowManager::~WindowManager()
{
   
}

const uint32_t Window::WindowManager::addWindow( IWindowPtr pWindow )
{
   Logger::info( "Added window" );
   m_idIncr++;
   m_windows.emplace( m_idIncr, pWindow );
   m_windowIndex.emplace( pWindow, m_idIncr );
   pWindow->setID( m_idIncr );

   return m_idIncr;
}

void Window::WindowManager::removeWindow( IWindowPtr pWindow )
{
   auto windowID = m_windowIndex[pWindow];

   if( pWindow )
   {
      Logger::info( "Removing window " + std::to_string( windowID ) );
      m_windows.erase( windowID );
      //m_windowIndex.erase( pWindow );
   }
}
void Window::WindowManager::removeWindow( const uint32_t windowID )
{
   auto pWindow = m_windows[windowID];

   if( pWindow )
   {
      Logger::info( "Removing window " + std::to_string( windowID ) );
      m_windows.erase( windowID );
      m_windowIndex.erase( pWindow );
   }
}

void Window::WindowManager::updateWindows()
{
   for( auto&[key, entry] : m_windows )
   {
      entry->render();
   }
}