#include <Server_Common/Database/Database.h>
#include <Server_Common/Logging/Logger.h>
#include <boost/make_shared.hpp>

#include "PartyMgr.h"
#include "Party.h"

extern Core::Logger g_log;
extern Core::Db::Database g_database;

Core::PartyMgr::PartyMgr()
{

}

Core::PartyPtr Core::PartyMgr::getPartyById( uint64_t partyId )
{
   auto it = m_partyIdMap.find( partyId );
   if( it == m_partyIdMap.end() )
      return nullptr;
   else
      return it->second;
}
