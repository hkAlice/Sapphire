#ifndef CORE_GROUP_H
#define CORE_GROUP_H

#include <Server_Zone/Actor/Player.h>
#include <set>

namespace Core {
namespace Social {

class Group
{
private:
   /*! unique ID of the group */
   uint64_t m_groupId;
   /*! ID of the group leader */
   uint64_t m_groupLeaderId;
   /*! ID list of all group members */
   std::set< uint64_t > m_memberIds;

public:
   Group( Core::Entity::PlayerPtr groupLeaderPtr );

   uint64_t getId() const;

   uint64_t getGroupLeaderId() const;

   const std::set< uint64_t >& getMemberIdList() const;
   std::set< uint64_t >& getMemberIdList();

   void addMember( uint64_t memberId );
   void removeMember( uint64_t memberId );

   void setGroupLeader( uint64_t memberId );

   uint8_t getGroupMemberCount();
};

}
}
#endif //CORE_GROUP_H
