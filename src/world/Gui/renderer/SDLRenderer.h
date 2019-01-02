#ifndef _BACKEND_H
#define _BACKEND_H

#include <SDL.h>
#include <SDL_opengl.h>

#include <imgui.h>
#include <examples/imgui_impl_sdl.h>
#include <examples/imgui_impl_opengl2.h>

#include "IRenderer.h"
#include "../FontData.h"
#include "../ClientControl.h"

namespace Sapphire::GUI::Renderer
{
   class SDLRenderer : public virtual IRenderer
   {
   public:
      SDLRenderer();
      virtual ~SDLRenderer();

      SDLRenderer( SDLRenderer const& ) = delete;
      SDLRenderer& operator=( SDLRenderer const& ) = delete;

      virtual void init( ClientControlPtr clientControl );
      virtual void render();
      virtual void dispose();

   private:
      void internalDraw();

      ClientControlPtr m_pClientControl;

      uint32_t m_lastTick;
      const uint32_t m_minDeltaTime = 1000 / 6;

      ImVec4 m_background;

      SDL_Window* m_pSDLWindow;
      SDL_GLContext m_SDLGLContext;
      ImGuiIO m_ImGuiIO;

      FontData m_fontData;
   };
}

#endif