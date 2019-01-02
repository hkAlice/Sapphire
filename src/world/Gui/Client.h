#ifndef _CLIENT
#define _CLIENT

#include <memory>

#include "GUITypeForward.h"

#include "../Manager/BaseManager.h"
#include "renderer/IRenderer.h"
#include "window/WindowManager.h"
#include "context/MainContext.h"

namespace Sapphire::GUI
{
   class Client : public World::Manager::BaseManager
   {

   public:
      Client( FrameworkPtr pFw );
      ~Client() = default;

      Client( Client const& ) = delete;
      Client& operator=( Client const& ) = delete;

      void run();
      void stop();

      void render();

      bool isRunning() const;

   private:
      void setClientControl();

      ClientControlPtr m_pClientControl;

      Renderer::IRendererPtr m_pRenderer;
      Window::WindowManager m_windowManager;

   };
}

#endif