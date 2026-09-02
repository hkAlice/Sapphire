#include "CombatBNpcController.h"

#include "Actor/BNpc.h"
#include "AI/Fsm/Condition.h"
#include "AI/Fsm/StateCombat.h"
#include "AI/Fsm/StateDead.h"
#include "AI/Fsm/StateFollowPath.h"
#include "AI/Fsm/StateIdle.h"
#include "AI/Fsm/StateMachine.h"
#include "AI/Fsm/StateResumePath.h"
#include "AI/Fsm/StateRetreat.h"
#include "AI/Fsm/StateRoam.h"
#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

#include <Service.h>

using namespace Sapphire;
using namespace Sapphire::World;

void AI::CombatBNpcController::initialize( Entity::BNpc& owner )
{
  using namespace Fsm;

  m_pFsm = make_StateMachine();

  auto stateIdle = make_StateIdle();
  auto stateCombat = make_StateCombat();
  auto stateDead = make_StateDead();

  auto& territoryMgr = Common::Service< Manager::TerritoryMgr >::ref();
  auto pTerritory = territoryMgr.getTerritoryByGuId( owner.getTerritoryId() );
  auto pInfo = owner.getInstanceObjectInfo();

  if( pInfo && pInfo->ServerPathId != 0 && pTerritory && pTerritory->getServerPath( pInfo->ServerPathId ) )
  {
    auto statePath = make_StateFollowPath();
    auto stateResumePath = make_StateResumePath();
    statePath->addTransition( stateCombat, make_HateListHasEntriesCondition() );
    statePath->addTransition( stateDead, make_IsDeadCondition() );

    stateCombat->addTransition( stateDead, make_IsDeadCondition() );
    stateCombat->addTransition( stateResumePath, make_HateListEmptyCondition() );
    stateResumePath->addTransition( statePath, make_RoamTargetReachedCondition() );

    m_pFsm->addState( statePath );
    m_pFsm->setCurrentState( statePath );
  }
  else
  {
    if( !owner.hasFlag( Entity::Immobile ) && !owner.hasFlag( Entity::NoRoam ) )
    {
      auto stateRoam = make_StateRoam();
      stateIdle->addTransition( stateRoam, make_RoamNextTimeReachedCondition() );
      stateRoam->addTransition( stateIdle, make_RoamTargetReachedCondition() );
      stateRoam->addTransition( stateCombat, make_HateListHasEntriesCondition() );
      stateRoam->addTransition( stateDead, make_IsDeadCondition() );
      m_pFsm->addState( stateRoam );
    }

    stateIdle->addTransition( stateCombat, make_HateListHasEntriesCondition() );
    stateIdle->addTransition( stateDead, make_IsDeadCondition() );
    stateCombat->addTransition( stateDead, make_IsDeadCondition() );
    m_pFsm->addState( stateIdle );

    if( !owner.hasFlag( Entity::NoDeaggro ) )
    {
      auto stateRetreat = make_StateRetreat();
      stateCombat->addTransition( stateRetreat, make_SpawnPointDistanceGtMaxDistanceCondition() );
      stateCombat->addTransition( stateRetreat, make_HateListEmptyCondition() );
      stateRetreat->addTransition( stateIdle, make_RoamTargetReachedCondition() );
    }

    m_pFsm->setCurrentState( stateIdle );
  }
}

void AI::CombatBNpcController::updateBeforePositionSync( Entity::BNpc& owner, uint64_t )
{
  owner.checkAggro();
}

void AI::CombatBNpcController::updateAfterPositionSync( Entity::BNpc& owner, uint64_t tickCount )
{
  if( m_pFsm )
    m_pFsm->update( owner, tickCount );
}

void AI::CombatBNpcController::onTick( Entity::BNpc& owner )
{
  if( owner.getState() == Entity::BNpcState::Retreat )
    owner.restHp();
}

void AI::CombatBNpcController::onActionHostile( Entity::BNpc& owner, Entity::CharaPtr pSource, int32_t aggro )
{
  if( !owner.isAlive() )
    return;

  owner.hateListUpdate( pSource, aggro );

  if( owner.getCanSwapTarget() )
    owner.updateAggroTarget();

  if( !owner.getOwner() )
    owner.setOwner( pSource );
}

bool AI::CombatBNpcController::usesNavigation( const Entity::BNpc& owner ) const
{
  return !owner.hasFlag( Entity::Immobile );
}

float AI::CombatBNpcController::getMovementSpeed( const Entity::BNpc& owner ) const
{
  return owner.getDefaultMovementSpeed();
}
