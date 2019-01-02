#ifndef _IWINDOW_H
#define _IWINDOW_H

#include <memory>
#include <string>

namespace Sapphire::GUI::Window
{
   class IWindow
   {
   public:
      IWindow()
      {
      };
      virtual ~IWindow() {};

      virtual void render() = 0;
      virtual void init() = 0;

      void setID( uint32_t id )
      {
         m_id = id;
      }

      uint32_t getID() const
      {
         return m_id;
      }

      bool& isViewable()
      {
         return m_view;
      }

      const std::string& getName() const
      {
         return m_name;
      }

   protected:
      uint32_t m_id{ 0xFFFFFFFF };
      bool m_view = true;
      std::string m_name;
   };

   using IWindowPtr = std::shared_ptr< Window::IWindow >;
}

#endif