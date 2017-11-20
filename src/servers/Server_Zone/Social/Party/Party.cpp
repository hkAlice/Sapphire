#include "Party.h"
#include <Server_Zone/Actor/Player.h>

Core::Party::Party( Core::Entity::PlayerPtr partyLeaderPtr  ) : // Just get player ID instead?
  m_partyLeaderId( partyLeaderPtr->getId() )
{

}

uint64_t Core::Party::getId() const
{
   return m_partyId;
}

uint64_t Core::Party::getPartyLeaderId() const
{
   return m_partyLeaderId;
}

const std::set< uint64_t >& Core::Party::getMemberIdList() const
{
   return m_memberIds;
}

std::set< uint64_t >& Core::Party::getMemberIdList()
{
   return m_memberIds;
}

uint8_t Core::Party::getPartyMemberCount()
{
   return m_memberIds.size();
}

void Core::Party::addMember( uint64_t memberId )
{
   m_memberIds.insert( memberId );
}

void Core::Party::removeMember( uint64_t memberId )
{
   m_memberIds.erase( memberId );
}

void Core::Party::setPartyLeader( uint64_t memberId )
{
   m_partyLeaderId = memberId;
}