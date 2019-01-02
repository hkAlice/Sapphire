#ifndef _IRENDERER
#define _IRENDERER

#include <memory>

#include "../GUITypeForward.h"

namespace Sapphire::GUI::Renderer
{
   class IRenderer
   {
   public:
      IRenderer() {};
      virtual ~IRenderer() {};

      IRenderer( IRenderer const& ) = delete;
      IRenderer& operator=( IRenderer const& ) = delete;

      virtual void init( ClientControlPtr clientControl ) = 0;
      virtual void render() = 0;
      virtual void dispose() = 0;

   private:

      ClientControlPtr m_pClientControl;
   };

   using IRendererPtr = std::shared_ptr< IRenderer >;
}

#endif

