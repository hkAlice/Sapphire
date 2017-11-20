#ifndef CORE_PARTY_H
#define CORE_PARTY_H

#include <Server_Zone/Actor/Player.h>
#include <set>

namespace Core {
namespace Social {

class Party
{
private:
   /*! unique ID of the party */
   uint64_t m_partyId;
   /*! ID of the party leader */
   uint64_t m_partyLeaderId;
   /*! ID list of all party members */
   std::set< uint64_t > m_memberIds;

public:
   Party( Core::Entity::PlayerPtr partyLeaderPtr );

   uint64_t getId() const;

   uint64_t getPartyLeaderId() const;

   const std::set< uint64_t >& getMemberIdList() const;
   std::set< uint64_t >& getMemberIdList();

   void addMember( uint64_t memberId );
   void removeMember( uint64_t memberId );

   void setPartyLeader( uint64_t memberId );

   uint8_t getPartyMemberCount();
};

}
}
#endif //CORE_PARTY_H
