#ifndef CORE_PARTYMGR_H
#define CORE_PARTYMGR_H

#include <boost/shared_ptr.hpp>
#include <map>

namespace Core {
namespace Social { 

class Group;
using boost::shared_ptr< Group > GroupPtr;

class GroupMgr
{
private:
   std::map< uint32_t, PartyPtr > m_partyIdMap;

   PartyPtr getPartyById( uint64_t lsId );

public:
   PartyMgr();
};

}
}
#endif //CORE_PARTYMGR_H
