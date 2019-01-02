#ifndef _NULL_RENDERER
#define _NULL_RENDERER

#include <memory>

#include "IRenderer.h"

namespace Sapphire::GUI::Renderer
{
   class NullRenderer : public virtual IRenderer
   {
   public:
      NullRenderer();
      virtual ~NullRenderer();

      NullRenderer( NullRenderer const& ) = delete;
      NullRenderer& operator=( NullRenderer const& ) = delete;

      virtual void init( ClientControlPtr clientControl );
      virtual void render();
      virtual void dispose();

   private:
      ClientControlPtr m_pClientControl;
   };

}

#endif
