#ifndef _WINDOWMGR
#define _WINDOWMGR

#include <unordered_map>
#include <memory>

#include "IWindow.h"

namespace Sapphire::GUI::Window
{
   class WindowManager
   {
   public:
      WindowManager();
      ~WindowManager();

      WindowManager( WindowManager const& ) = delete;
      WindowManager& operator=( WindowManager const& ) = delete;

      const uint32_t addWindow( IWindowPtr pWindow );
      void removeWindow( IWindowPtr pWindow );
      void removeWindow( const uint32_t windowID );

      void updateWindows();

   private:
      uint32_t m_idIncr;
      std::unordered_map< uint32_t, IWindowPtr > m_windows;
      std::unordered_map< IWindowPtr, uint32_t > m_windowIndex;
   };

   using WindowManagerPtr = std::shared_ptr< WindowManager >;
}

#endif