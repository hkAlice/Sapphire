#pragma once

#include "BNpcController.h"

namespace Sapphire::World::AI
{
  /**
   * Preserves the existing combat, roaming, retreat, and server-path BNpc
   * behaviour behind the controller interface.
   */
  class CombatBNpcController final : public BNpcController
  {
  public:
    void initialize( Entity::BNpc& owner ) override;

    void updateBeforePositionSync( Entity::BNpc& owner, uint64_t tickCount ) override;

    void updateAfterPositionSync( Entity::BNpc& owner, uint64_t tickCount ) override;

    void onTick( Entity::BNpc& owner ) override;

    void onActionHostile( Entity::BNpc& owner, Entity::CharaPtr pSource, int32_t aggro ) override;

    bool usesNavigation( const Entity::BNpc& owner ) const override;

    float getMovementSpeed( const Entity::BNpc& owner ) const override;

  private:
    Fsm::StateMachinePtr m_pFsm;
  };
}// namespace Sapphire::World::AI
