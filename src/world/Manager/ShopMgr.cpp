#include "ShopMgr.h"

#include <Framework.h>
#include <Exd/ExdDataGenerated.h>
#include <Actor/Player.h>
#include <Common.h>

using namespace Sapphire;

Sapphire::World::Manager::ShopMgr::ShopMgr( FrameworkPtr pFw ) :
  BaseManager( pFw )
{

}

bool Sapphire::World::Manager::ShopMgr::purchaseGilShopItem( Entity::Player& player, uint32_t shopId, uint16_t itemId, uint32_t quantity )
{
  auto exdData = framework()->get< Data::ExdDataGenerated >();
  if( !exdData )
    return false;

  auto gilShopItem = exdData->get< Data::GilShopItem >( shopId, itemId );
  if( !gilShopItem )
    return false;

  auto item = exdData->get< Data::Item >( gilShopItem->item );
  if( !item )
    return false;

  auto price = item->priceMid * quantity;

  if( player.getCurrency( Common::CurrencyType::Gil ) < price )
    return false;

  if( !player.addItem( gilShopItem->item, quantity ) )
    return false;

  player.removeCurrency( Common::CurrencyType::Gil, price );

  return true;
}
