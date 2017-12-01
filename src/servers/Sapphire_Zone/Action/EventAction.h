#ifndef _EVENTACTION_H_
#define _EVENTACTION_H_

#include <src/servers/Common/Common.h>

#include "src/servers/Sapphire_Zone/Forwards.h"
#include "src/servers/Sapphire_Zone/Action/Action.h"

namespace Core { namespace Action {

   class EventAction : public Action 
   {

   public:
      EventAction();
      ~EventAction();
      
      EventAction( Entity::ActorPtr pActor, uint32_t eventId, uint16_t action,
                   ActionCallback finishRef, ActionCallback interruptRef, uint64_t additional );

      void onStart() override;
      void onFinish() override;
      void onInterrupt() override;

   private:
      uint32_t m_eventId;
      uint64_t m_additional;
      
      ActionCallback m_onActionFinishClb;
      ActionCallback m_onActionInterruptClb;

   };

}
}

#endif