#ifndef _PacketContainer_H_
#define _PacketContainer_H_

#include <vector>

#include "src/servers/Common/Common.h"
#include "CommonNetwork.h"
#include "GamePacket.h"

namespace Core {
namespace Network {
namespace Packets {

class GamePacket;

class PacketContainer
{
public:
   PacketContainer( void );
   ~PacketContainer( void );

   void addPacket( GamePacket pEntry );

   FFXIVARR_PACKET_HEADER m_ipcHdr;

   std::vector<GamePacket> m_entryList;

   std::string toString();

   void fillSendBuffer( std::vector< uint8_t >& sendBuffer );

};

}
}
}

#endif
