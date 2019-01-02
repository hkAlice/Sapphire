#include <imgui.h>

#include <ServerMgr.h>

#include <Network/GamePacketNew.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include <Util/UtilMath.h>

#include "Framework.h"
#include "CharacterDetailsWindow.h"
#include "../context/MainContext.h"
#include "../ClientStyle.h"
#include "../ClientLocale.h"

#include "Session.h"
#include "Actor/Player.h"
#include "Inventory/ItemContainer.h"
#include "Inventory/Item.h"

using namespace Sapphire::GUI;

Window::CharacterDetailsWindow::CharacterDetailsWindow( ClientControlPtr pClientControl )
   : m_pClientControl( pClientControl )
{
   m_windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
}

void Window::CharacterDetailsWindow::init()
{
   
}

void Window::CharacterDetailsWindow::render()
{
  auto pServerZone = m_pClientControl->m_pFramework->get< Sapphire::World::ServerMgr >();
  auto pSession = pServerZone->getSession( m_pClientControl->mainCtx->getSelectedCharacter() );

  std::string windowTitle = "Character Details";

  ImGui::SetNextWindowSize( ImVec2( m_pClientControl->clientWidth * 0.35f, m_pClientControl->clientHeight ),
    ImGuiCond_Always );
  ImGui::SetNextWindowPos( ImVec2( m_pClientControl->clientWidth * 0.15f, 0 ), ImGuiCond_Always );
  bool view = false;

  if( ImGui::Begin( windowTitle.c_str(), &view, m_windowFlags ) )
  {
    if( pSession )
    {
      m_pPlayer = pSession->getPlayer();

      drawBasicInfo();
      ImGui::Separator();

      drawActionsInfo();
      ImGui::Separator();

      drawPositionInfo();
      drawInventoryInfo();
      drawInstanceInfo();
     
    }
  }

  ImGui::End();
}

void Window::CharacterDetailsWindow::drawBasicInfo()
{
  //ImGui::PushFont( ImGui::GetIO().Fonts->Fonts[1] );
  Style::pushFont( Style::FontStyle::Big );
  ImGui::TextColored( Style::COLOR_ACCENT_H, m_pPlayer->getName().c_str() );
  ImGui::PopFont();

  ImGui::Text( Locale::RaceName[m_pPlayer->getRace()] );

  std::string lvText = Locale::JobName[m_pPlayer->getClassAsInt()];
  lvText += " Lv " + std::to_string( m_pPlayer->getLevel() );

  ImGui::Text( lvText.c_str() );


  ImGui::Columns( 1 );

  // HP
  float hpPercentage = m_pPlayer->getHp() / static_cast<float>( m_pPlayer->getMaxHp() );

  char hpBuf[32];
  sprintf( hpBuf, "%d/%d HP", m_pPlayer->getHp(), m_pPlayer->getMaxHp() );
  Style::applyGroupedStyle( Style::GroupType::Plot, Style::StyleColor::Success );

  ImGui::ProgressBar( hpPercentage, ImVec2( -1.f, 0.f ), hpBuf );
  /*
  ImGui::SameLine( 0.0f );
  ImGui::Text( "HP" );*/

  ImGui::Columns( 2, "charstats", true );

  // MP

  float mpPercentage = m_pPlayer->getMp() / static_cast<float>( m_pPlayer->getMaxMp() );

  char mpBuf[32];
  sprintf( mpBuf, "%d/%d MP", m_pPlayer->getMp(), m_pPlayer->getMaxMp() );

  Style::applyGroupedStyle( Style::GroupType::Plot, Style::StyleColor::Main );
  ImGui::ProgressBar( mpPercentage, ImVec2( -1.f, 0.f ), mpBuf );
  /*
  ImGui::SameLine( 0.0f, 10 );
  ImGui::Text( "MP" );*/

  ImGui::NextColumn();

  // TP

  float tpPercentage = m_pPlayer->getTp() / 1000.f;

  char tpBuf[32];
  sprintf( tpBuf, "%d/%d TP", m_pPlayer->getTp(), 1000 );

  Style::applyGroupedStyle( Style::GroupType::Plot, Style::StyleColor::Accent );
  ImGui::ProgressBar( tpPercentage, ImVec2( -1.f, 0.f ), tpBuf );

  ImGui::Columns( 1, "charstats", true );
}

void Window::CharacterDetailsWindow::drawActionsInfo()
{
  static int selectedCharacter = 0;

  ImGui::Columns( 2, "actions" );

  {
    ImGui::Text( "Players nearby" );
    ImGui::BeginChild( "Players nearby", ImVec2( -1.f, 100.f ), false );

    for( const auto& pActor : m_pPlayer->getInRangeActors() )
    {
      if( pActor->isPlayer() )
      {
        auto pNearbyPlayer = pActor->getAsPlayer();
        if( ImGui::Selectable( pNearbyPlayer->getName().c_str(), selectedCharacter == pNearbyPlayer->getId() ) )
          selectedCharacter = pNearbyPlayer->getId();
      }

    }

    ImGui::EndChild();
  }

  ImGui::NextColumn();

  {
    ImGui::Text( "Operations" );
    ImGui::BeginChild( "Operations", ImVec2( -1.f, 100.f ), false );

    ImGui::Columns( 2, "operations", false );

    if( ImGui::Button( "Kill", ImVec2( -1.0f, 0.0f ) ) )
      m_pPlayer->takeDamage( m_pPlayer->getMaxHp() );

    ImGui::NextColumn();

    if( ImGui::Button( "Kick", ImVec2( -1.0f, 0.0f ) ) )
      m_pPlayer->setMarkedForRemoval();

    ImGui::EndChild();
  }

  ImGui::Columns( 1 );

  m_pClientControl->mainCtx->setSelectedCharacter( selectedCharacter );
}

void Window::CharacterDetailsWindow::drawPositionInfo()
{
  if( ImGui::CollapsingHeader( "Position" ) )
  {
    bool updatePos = false;

    // TODO: 1. sapphire doesn't do pitch/yaw/roll
    // 2. imgui does not provide sliderangle3, use sliderfloat3

    m_pPlayer->getRot();
    float v[3] = { m_pPlayer->getPos().x, m_pPlayer->getPos().y, m_pPlayer->getPos().z };
    float rot = m_pPlayer->getRot();
    int zoneId = m_pPlayer->getZoneId();

    if( ImGui::InputInt( "Zone", &zoneId, ImGuiInputTextFlags_EnterReturnsTrue ) )
      m_pPlayer->setZone( zoneId );

    if( ImGui::InputFloat3( "X / Y / Z", v, "%.4f", ImGuiInputTextFlags_EnterReturnsTrue ) )
      updatePos = true;

    if( ImGui::SliderAngle( "Rotation", &rot ) )
      updatePos = true;

    if( updatePos )
    {
      Common::FFXIVARR_POSITION3 playerPos = { v[0], v[1], v[2] };
      m_pPlayer->setPos( playerPos );

      m_pPlayer->setRot( rot );

      auto setActorPosPacket = Network::Packets::makeZonePacket< Network::Packets::Server::FFXIVIpcActorSetPos >( m_pPlayer->getId() );
      setActorPosPacket->data().x = playerPos.x;
      setActorPosPacket->data().y = playerPos.y;
      setActorPosPacket->data().z = playerPos.z;
      setActorPosPacket->data().r16 = Util::floatToUInt16Rot( rot );

      m_pPlayer->queuePacket( setActorPosPacket );
    }

  }
}

void Window::CharacterDetailsWindow::drawInventoryInfo()
{
  if( ImGui::CollapsingHeader( "Inventory" ) )
  {
    int i = 0;
    auto pInventoryMap = m_pPlayer->getInventoryMap();
    std::string itemName = "";

    if( ImGui::TreeNode( "Bag" ) )
    {
      ImGui::Columns( 2, "bagInv", true );

      using InvType = Common::InventoryType;

      int blockSize = (ImGui::GetContentRegionAvailWidth() / 5) - 5;

      for( auto iType : { InvType::Bag0, InvType::Bag1, InvType::Bag2, InvType::Bag3 } )
      {
        auto pItemMap = pInventoryMap[iType]->getItemMap();

        for( int i = 0; i < 35; ++i )
        {
          itemName = "-";

          ItemPtr pItem;
          if( i < pItemMap.size() )
          {
            pItem = pItemMap[i];
            if( pItem )
              itemName = std::to_string( pItem->getId() );
          }

          bool itemExists = pItem != nullptr;

          if( ImGui::Selectable( itemName.c_str(), &itemExists, 0, ImVec2( blockSize, blockSize ) ) )
          {

          }
          if( (i % 5) < 4 ) ImGui::SameLine();
        }

        ImGui::NextColumn();

        if( iType == InvType::Bag1 )
          ImGui::Separator();
      }
      ImGui::TreePop();
    }

  }
}

void Window::CharacterDetailsWindow::drawInstanceInfo()
{
  if( ImGui::CollapsingHeader( "Instance" ) )
  {
    
  }
}