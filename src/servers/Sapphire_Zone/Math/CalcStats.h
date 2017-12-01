#ifndef _CALCSTATS_H
#define _CALCSTATS_H

#include <Common/Common.h>
#include <Sapphire_Zone/Actor/Actor.h>

using namespace Core::Entity;

namespace Core {
namespace Math {
   
   class CalcStats
   {
   public:
      static float calculateBaseStat( PlayerPtr pPlayer );
      static uint32_t calculateMaxMp( PlayerPtr pPlayer );
      static uint32_t calculateMaxHp( PlayerPtr pPlayer );

   private:

   };

}
}

#endif