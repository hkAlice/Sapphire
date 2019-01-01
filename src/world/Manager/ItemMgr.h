#ifndef SAPPHIRE_ITEMMGR_H
#define SAPPHIRE_ITEMMGR_H

#include <Common.h>
#include "ForwardsZone.h"
#include "BaseManager.h"

namespace Sapphire::World::Manager
{

  class ItemMgr : public BaseManager
  {
  public:
    ItemMgr( FrameworkPtr pFw );

    ItemPtr loadItem( uint64_t uId );

    uint32_t getNextUId();

    /*! check if weapon category qualifies the weapon as onehanded */
    static bool isOneHandedWeapon( Common::ItemUICategory weaponCategory );
    static bool isArmory( uint16_t containerId );
    static bool isEquipment( uint16_t containerId );
    static uint16_t getCharaEquipSlotCategoryToArmoryId( uint8_t slotId );
    static Common::ContainerType getContainerType( uint32_t containerId );
  };

}

#endif //SAPPHIRE_ITEMMGR_H
