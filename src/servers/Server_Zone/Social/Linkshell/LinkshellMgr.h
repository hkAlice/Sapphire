#ifndef CORE_LINKSHELLMGR_H
#define CORE_LINKSHELLMGR_H

#include <Server_Zone\Social\GroupMgr.h>
#include <boost/shared_ptr.hpp>
#include <map>

namespace Core {
namespace Social {

class Linkshell;

class LinkshellMgr : public GroupMgr
{
private:

public:
   LinkshellMgr();

   bool loadLinkshells();
};

}
}
#endif //CORE_LINKSHELLMGR_H
