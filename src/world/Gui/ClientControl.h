#ifndef _CLIENTCONTROL
#define _CLIENTCONTROL

#include <memory>
#include <imgui.h>

#include <Manager/BaseManager.h>
#include "Framework.h"

namespace Sapphire::GUI
{
   // TODO: Forward Decl
   namespace Window
   {
      class WindowManager;
   }

   namespace Context
   {
      class MainContext;
      using MainContextPtr = std::shared_ptr< MainContext >;
   }

   // TODO: maybe a class with getters as to not allow invalid states/values for ptrs
   // TODO: ClientControl is not really needed with pGuiClient now being in Framework
   struct ClientControl
   {
      ClientControl( Sapphire::FrameworkPtr pFramework, Window::WindowManager& windowMgrRef )
         : m_pFramework( pFramework ), windowManager( windowMgrRef )
      {

      }

      bool isRunning = false;
      uint32_t clientWidth = 1920;
      uint32_t clientHeight = 1080;

      Window::WindowManager& windowManager;
      Context::MainContextPtr mainCtx;
      Sapphire::FrameworkPtr m_pFramework;

   };

   using ClientControlPtr = std::shared_ptr< ClientControl >;
}

#endif