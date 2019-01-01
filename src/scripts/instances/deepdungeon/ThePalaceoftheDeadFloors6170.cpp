#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class ThePalaceoftheDeadFloors6170 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ThePalaceoftheDeadFloors6170() :
    Sapphire::ScriptAPI::InstanceContentScript( 60007 )
  {
  }

  void onInit( InstanceContentPtr instance ) override
  {
    instance->registerEObj( "sgvf_w_lvd_b0959", 2000608, 6521120, 4, { -300.000000f, 3.189805f, -241.061096f },
                            1.000000f, 0.000000f );
    // States -> vf_bextwall_on vf_bextwall_on2off vf_bextwall_off

  }

  void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};