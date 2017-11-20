#include <Server_Zone/Actor/Player.h>

#include "Group.h"

Core::Group::Group( Core::Entity::PlayerPtr groupLeaderPtr  ) : // Just get player ID instead?
  m_groupLeaderId( groupLeaderPtr->getId() )
{

}

uint64_t Core::Group::getId() const
{
   return m_groupId;
}

uint64_t Core::Group::getGroupLeaderId() const
{
   return m_groupLeaderId;
}

const std::set< uint64_t >& Core::Group::getMemberIdList() const
{
   return m_memberIds;
}

std::set< uint64_t >& Core::Group::getMemberIdList()
{
   return m_memberIds;
}

uint8_t Core::Group::getGroupMemberCount()
{
   return m_memberIds.size();
}

void Core::Group::addMember( uint64_t memberId )
{
   m_memberIds.insert( memberId );
}

void Core::Group::removeMember( uint64_t memberId )
{
   m_memberIds.erase( memberId );
}

void Core::Group::setGroupLeader( uint64_t memberId )
{
   m_groupLeaderId = memberId;
}