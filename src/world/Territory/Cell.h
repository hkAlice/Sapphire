#pragma once
#include <cstdint>

#include "ForwardsZone.h"
#include <set>

namespace Sapphire {

typedef std::set< Entity::GameObjectPtr > ActorSet;

class Cell
{
  friend class Territory;

private:
  bool m_bForcedActive;
  uint16_t m_posX;
  uint16_t m_posY;
  ActorSet m_actors;
  bool m_bActive;

  uint16_t m_playerCount;

public:
  Cell();

  ~Cell();

  void init( uint32_t x, uint32_t y );

  void addActor( Entity::GameObjectPtr pAct );

  void removeActorFromCell( Entity::GameObjectPtr pAct );

  bool hasActor( Entity::GameObjectPtr pAct )
  {
    return ( m_actors.find( pAct ) != m_actors.end() );
  }

  bool hasPlayers() const
  {
    return m_playerCount > 0;
  }

  size_t getActorCount() const
  {
    return m_actors.size();
  }

  void removeActors();

  ActorSet::iterator begin()
  {
    return m_actors.begin();
  }

  ActorSet::iterator end()
  {
    return m_actors.end();
  }

  void setActivity( bool state );

  bool isActive() const
  {
    return m_bActive;
  }

  void unload();

  bool isForcedActive() const
  {
    return m_bForcedActive;
  }

  uint16_t getPosX() const
  {
    return m_posX;
  }

  uint16_t getPosY() const
  {
    return m_posY;
  }
};

}
