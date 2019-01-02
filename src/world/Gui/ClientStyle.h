#ifndef _CLIENTSTYLE
#define _CLIENTSTYLE

#include <functional>
#include <unordered_map>

#include <imgui.h>

#include "FontData.h"

namespace Sapphire::GUI
{
   namespace Style
   {
      static const ImVec4 COLOR_TEXT = ImVec4( 1.f, 1.f, 1.f, 1.f );

      static const ImVec4 COLOR_APPBG = ImVec4( 0.05f, 0.05f, 0.05f, 1.f );
      static const ImVec4 COLOR_BG = ImVec4( 0.08f, 0.08f, 0.08f, 1.f );
      static const ImVec4 COLOR_BG_ACCENT = ImVec4( 0.12f, 0.12f, 0.12f, 1.f );
      static const ImVec4 COLOR_SHADOW = ImVec4( 0.f, 0.f, 0.f, 0.f );

      static const ImVec4 COLOR_MAIN_N = ImVec4( 0.21f, 0.34f, 0.78f, 0.75f );
      static const ImVec4 COLOR_MAIN_L = ImVec4( 0.21f, 0.34f, 0.78f, 0.35f );
      static const ImVec4 COLOR_MAIN_H = ImVec4( 0.21f, 0.34f, 0.78f, 1.f );

      static const ImVec4 COLOR_ACCENT_N = ImVec4( 0.65f, 0.91f, 0.99f, 0.8f );
      static const ImVec4 COLOR_ACCENT_L = ImVec4( 0.65f, 0.91f, 0.99f, 0.3f );
      static const ImVec4 COLOR_ACCENT_H = ImVec4( 0.65f, 0.91f, 0.99f, 1.f );

      static const ImVec4 COLOR_SUCCESS_N = ImVec4( 0.16f, 0.4f, 0.24f, 0.8f );
      static const ImVec4 COLOR_SUCCESS_L = ImVec4( 0.16f, 0.4f, 0.24f, 0.6f );
      static const ImVec4 COLOR_SUCCESS_H = ImVec4( 0.16f, 0.4f, 0.24f, 1.f );

      static ImFont* FONT_DEFAULT;
      static ImFont* FONT_BIG;

      enum class StyleColor
      {
         Main = 1,
         Accent,
         Success
      };

      enum class GroupType
      {
         Frame = 1,
         Title,
         Scrollbar,
         Button,
         Header,
         Separator,
         Resize,
         Plot
      };

      static std::unordered_map< GroupType, const ImGuiCol_ > groupStyleMap =
      {
         { GroupType::Button,    ImGuiCol_Button },
         { GroupType::Header,    ImGuiCol_Header },
         { GroupType::Separator, ImGuiCol_Separator },
         { GroupType::Plot,      ImGuiCol_PlotHistogram }
      };

      static std::unordered_map< StyleColor, const std::vector< ImVec4 > > styleColorMap =
      {
         { StyleColor::Main,    { COLOR_MAIN_L, COLOR_MAIN_N, COLOR_MAIN_H } },
         { StyleColor::Accent,  { COLOR_ACCENT_L, COLOR_ACCENT_N, COLOR_ACCENT_H } },
         { StyleColor::Success, { COLOR_SUCCESS_L, COLOR_SUCCESS_N, COLOR_SUCCESS_H } }
      };

      ImVec4 inline transformStyleAlpha( const ImVec4 color, float transparency )
      {
         return ImVec4( color.x, color.y, color.z, transparency );
      }

      void inline applyGroupedStyle( GroupType groupType, StyleColor styleColor )
      {
         ImGuiStyle* style = &ImGui::GetStyle();
         ImVec4* colors = style->Colors;

         auto firstStyleEntry = groupStyleMap[groupType];
         const auto& styleColorVec = styleColorMap[styleColor];

         int styleEntry = static_cast< int >( firstStyleEntry );

         for( auto& color : styleColorVec )
         {
            colors[styleEntry] = color;
            styleEntry++;
         }
      }

      void inline applyAppStyle()
      {
         ImGuiStyle* style = &ImGui::GetStyle();
         ImVec4* colors = style->Colors;

         colors[ImGuiCol_Text] = COLOR_TEXT;
         colors[ImGuiCol_TextDisabled] = transformStyleAlpha( COLOR_TEXT, 0.5f );
         colors[ImGuiCol_WindowBg] = COLOR_BG;
         colors[ImGuiCol_ChildBg] = transformStyleAlpha( COLOR_BG, 0.75f );
         colors[ImGuiCol_PopupBg] = COLOR_BG;
         colors[ImGuiCol_Border] = COLOR_MAIN_L;
         colors[ImGuiCol_BorderShadow] = COLOR_SHADOW;
         colors[ImGuiCol_FrameBg] = COLOR_BG_ACCENT;
         colors[ImGuiCol_FrameBgHovered] = COLOR_BG_ACCENT;
         colors[ImGuiCol_FrameBgActive] = COLOR_BG_ACCENT;
         colors[ImGuiCol_TitleBg] = COLOR_BG_ACCENT;
         colors[ImGuiCol_TitleBgActive] = COLOR_BG_ACCENT;
         colors[ImGuiCol_TitleBgCollapsed] = COLOR_BG_ACCENT;
         colors[ImGuiCol_MenuBarBg] = COLOR_BG_ACCENT;
         colors[ImGuiCol_ScrollbarBg] = COLOR_BG;
         colors[ImGuiCol_ScrollbarGrab] = COLOR_BG_ACCENT;
         colors[ImGuiCol_ScrollbarGrabHovered] = COLOR_BG_ACCENT;
         colors[ImGuiCol_ScrollbarGrabActive] = COLOR_BG_ACCENT;
         colors[ImGuiCol_CheckMark] = COLOR_ACCENT_H;
         colors[ImGuiCol_SliderGrab] = COLOR_MAIN_N;
         colors[ImGuiCol_SliderGrabActive] = COLOR_MAIN_H;
         colors[ImGuiCol_ResizeGrip] = COLOR_MAIN_L;
         colors[ImGuiCol_ResizeGripHovered] = COLOR_MAIN_N;
         colors[ImGuiCol_ResizeGripActive] = COLOR_MAIN_H;
         colors[ImGuiCol_PlotLines] = COLOR_ACCENT_N;
         colors[ImGuiCol_PlotLinesHovered] = COLOR_ACCENT_H;
         colors[ImGuiCol_PlotHistogram] = COLOR_ACCENT_N;
         colors[ImGuiCol_PlotHistogramHovered] = COLOR_ACCENT_H;
         colors[ImGuiCol_TextSelectedBg] = ImVec4( 0.26f, 0.59f, 0.98f, 0.35f );
         colors[ImGuiCol_DragDropTarget] = ImVec4( 1.00f, 1.00f, 0.00f, 0.90f );
         colors[ImGuiCol_NavHighlight] = ImVec4( 0.26f, 0.59f, 0.98f, 1.00f );
         colors[ImGuiCol_NavWindowingHighlight] = ImVec4( 1.00f, 1.00f, 1.00f, 0.70f );
         colors[ImGuiCol_NavWindowingDimBg] = ImVec4( 0.80f, 0.80f, 0.80f, 0.20f );
         colors[ImGuiCol_ModalWindowDimBg] = ImVec4( 0.80f, 0.80f, 0.80f, 0.35f );

         applyGroupedStyle( GroupType::Button, StyleColor::Accent );
         applyGroupedStyle( GroupType::Header, StyleColor::Main );
         applyGroupedStyle( GroupType::Separator, StyleColor::Main );

         style->FrameRounding = 0.f;
         style->WindowRounding = 0.f;
         style->ChildRounding = 0.f;
         style->GrabRounding = 0.f;
         style->PopupRounding = 0.f;
         style->ScrollbarRounding = 0.f;
      }

      void inline setFont( const std::string& fontPath, int sizeDefault, int sizeBig, FontData& fontData )
      {
        ImGuiIO& io = ImGui::GetIO();

        ImFontConfig config;

        FONT_DEFAULT = io.Fonts->AddFontFromFileTTF( fontPath.c_str(), sizeDefault, &config );
        FONT_BIG = io.Fonts->AddFontFromFileTTF( fontPath.c_str(), sizeBig, &config );

        if( !FONT_DEFAULT || !FONT_BIG )
          return;

        io.Fonts->GetTexDataAsRGBA32( &fontData.pixels, &fontData.width, &fontData.height, &fontData.bpp );
        //ImGui::PushFont( appFont );
      }
   }
}

#endif