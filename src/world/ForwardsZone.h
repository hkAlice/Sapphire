#ifndef _FORWARDS_H
#define _FORWARDS_H

#include <utility>
#include <memory>
#include <vector>
#include <functional>
#include "Common.h"

#define TYPE_FORWARD( x ) \
class x; \
typedef std::shared_ptr< x > x ## Ptr; \
typedef std::unique_ptr< x > x ## UPtr; \
template< typename...Args > \
x ## Ptr make_ ## x( Args &&...args ) { \
return std::make_shared< x >( std::forward< Args >( args ) ... ); }\
typedef std::vector< x > x ## PtrList;

namespace Sapphire
{
TYPE_FORWARD( Cell );
TYPE_FORWARD( Zone );
TYPE_FORWARD( HousingZone );
TYPE_FORWARD( House );
TYPE_FORWARD( InstanceContent );
TYPE_FORWARD( Item );
TYPE_FORWARD( ItemContainer );
TYPE_FORWARD( ZonePosition );
TYPE_FORWARD( Land );
TYPE_FORWARD( Linkshell );
TYPE_FORWARD( Framework );

namespace World
{
TYPE_FORWARD( Session );
}

namespace World::Territory::Housing
{
TYPE_FORWARD( HousingInteriorTerritory );
}

namespace Inventory
{
using InventoryContainerPair = std::pair< Common::InventoryType, uint8_t >;
using InventoryTypeList = std::vector< Common::InventoryType >;
TYPE_FORWARD( HousingItem );
}

namespace World::Manager
{
TYPE_FORWARD( HousingMgr );
}

namespace StatusEffect
{
TYPE_FORWARD( StatusEffect );
TYPE_FORWARD( StatusEffectContainer );
}

namespace Entity
{
TYPE_FORWARD( Actor );
TYPE_FORWARD( Chara );
TYPE_FORWARD( Player );
TYPE_FORWARD( EventObject );
TYPE_FORWARD( BNpcTemplate );
TYPE_FORWARD( BNpc );
TYPE_FORWARD( SpawnPoint );
TYPE_FORWARD( SpawnGroup );
}

namespace Event
{
TYPE_FORWARD( Director );
TYPE_FORWARD( EventHandler );
}

namespace Action
{
TYPE_FORWARD( Action );
TYPE_FORWARD( ActionTeleport );
TYPE_FORWARD( ActionCast );
TYPE_FORWARD( ActionMount );
TYPE_FORWARD( EventAction );
TYPE_FORWARD( EventItemAction );
}

namespace Network
{
TYPE_FORWARD( Hive );
TYPE_FORWARD( Acceptor );
TYPE_FORWARD( Connection );
TYPE_FORWARD( GameConnection );
TYPE_FORWARD( SessionConnection );
TYPE_FORWARD( CustomMsgClientConnection );

namespace Packets
{
TYPE_FORWARD( GamePacket );
TYPE_FORWARD( FFXIVPacketBase );
}
}

namespace ContentFinder
{
TYPE_FORWARD( ContentFinder );
}

namespace Scripting
{
class NativeScriptMgr;
}

typedef std::function< void( Entity::Player&, uint32_t, uint64_t ) > ActionCallback;

}


#endif
