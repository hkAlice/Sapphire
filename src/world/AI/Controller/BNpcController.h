#pragma once

#include <cstdint>

#include "ForwardsZone.h"

namespace Sapphire::World::AI
{
  /**
   * Owns the autonomous behaviour of a single BNpc.
   *
   * The split update hooks preserve BNpc's existing update order: aggro
   * acquisition occurs before position synchronization, while the legacy FSM
   * runs afterwards. Controllers that do not require both phases may leave
   * either hook unused.
   */
  class BNpcController
  {
  public:
    virtual ~BNpcController() = default;

    virtual void initialize( Entity::BNpc& ) {}

    virtual void updateBeforePositionSync( Entity::BNpc&, uint64_t ) {}

    virtual void updateAfterPositionSync( Entity::BNpc&, uint64_t ) {}

    virtual void onTick( Entity::BNpc& ) {}

    virtual void onActionHostile( Entity::BNpc&, Entity::CharaPtr, int32_t ) {}

    virtual void onDetach( Entity::BNpc& ) {}

    virtual bool usesNavigation( const Entity::BNpc& owner ) const = 0;

    virtual float getMovementSpeed( const Entity::BNpc& owner ) const = 0;
  };
}// namespace Sapphire::World::AI
