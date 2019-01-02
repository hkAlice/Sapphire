#include <imgui.h>

#include <ServerMgr.h>
#include "Framework.h"
#include "CharacterSelectWindow.h"
#include "../context/MainContext.h"
#include "../ClientStyle.h"

#include "Session.h"
#include "Actor/Player.h"

using namespace Sapphire::GUI;

Window::CharacterSelectWindow::CharacterSelectWindow( ClientControlPtr pClientControl )
   : m_pClientControl( pClientControl )
{
   m_windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
}

void Window::CharacterSelectWindow::init()
{
   
}

void Window::CharacterSelectWindow::render()
{
   auto pServerZone = m_pClientControl->m_pFramework->get< Sapphire::World::ServerMgr >();
   auto sessions = pServerZone->getAllSessions();

   ImGui::SetNextWindowSize( ImVec2( m_pClientControl->clientWidth * 0.15f, m_pClientControl->clientHeight ), 
                             ImGuiCond_Always );
   ImGui::SetNextWindowPos( ImVec2( 0, 0 ), ImGuiCond_Always );
   bool view = false;

   std::string windowTitle = std::to_string( sessions.size() ) + " player(s) connected";

   if( ImGui::Begin( windowTitle.c_str(), &view, m_windowFlags ) )
   {
      ImGui::Columns( 2, "options", false );

      Style::applyGroupedStyle( Style::GroupType::Button, Style::StyleColor::Success );
      if( ImGui::Button( "+ New Character" ) )
         m_pClientControl->mainCtx->createNewChar();

      ImGui::NextColumn();

      Style::applyGroupedStyle( Style::GroupType::Button, Style::StyleColor::Accent );
      if( ImGui::Button( "? Settings" ) )
         nullptr;

      ImGui::Columns( 1 );

      ImGui::Spacing();

      ImGui::Separator();

      static int selectedCharacter = 0;

      for( auto const& it : sessions )
      {
        auto pPlayer = it.second->getPlayer();
        std::string itemHeader = pPlayer->getName() + " [" + std::to_string( pPlayer->getId() ) + "]";
        if( ImGui::Selectable( itemHeader.c_str(), selectedCharacter == it.first ) )
          selectedCharacter = it.first;

        ImGui::Columns( 2, "charinfo", false );

        std::string levelText = "Lv " + std::to_string( pPlayer->getLevel() );

        auto level = pPlayer->getLevel();

        ImGui::Text( levelText.c_str() );
        ImGui::NextColumn();

        std::string zoneText = "Zone " + std::to_string( pPlayer->getZoneId() );

        ImGui::TextWrapped( zoneText.c_str() );

        ImGui::Columns(1);
        ImGui::Separator();
      }
      /*
      for( auto& character : m_session.getCharacters() )
      {
         if( ImGui::Selectable( character->getName().c_str(), selectedCharacter == character->getID() ) )
            selectedCharacter = character->getID();

         ImGui::Columns( 2, "charinfo", false );

         ImGui::Text( "White Mage Lv75" );
         ImGui::NextColumn();
         
         ImGui::TextWrapped( "Randall HQ" );

         ImGui::Columns( 1 );
         ImGui::Separator();
      }

      m_session.setActiveCharacterID( selectedCharacter );*/

      if( selectedCharacter != m_pClientControl->mainCtx->getSelectedCharacter() )
        m_pClientControl->mainCtx->setSelectedCharacter( selectedCharacter );
   }

   ImGui::End();
}