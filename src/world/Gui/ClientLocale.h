#ifndef _CLIENTLOCALE
#define _CLIENTLOCALE

#include <unordered_map>
#include <string>

#include <CommonGen.h>

namespace Sapphire::GUI::Locale
{
  // todo: commongen Common::Race is not constqual

  static const constexpr char* const RaceName[] =
  {
    "Invalid",
    "Hyur",
    "Elezen",
    "Lalafell",
    "Miqo'te",
    "Roegadyn",
    "Au'Ra"
  };

  static const constexpr char* const JobName[] =
  {
    "Adventurer",
    "Gladiator",
    "Pugilist",
    "Marauder",
    "Lancer",
    "Archer",
    "Conjurer",
    "Thaumaturge",
    "Carpenter",
    "Blacksmith",
    "Armorer",
    "Goldsmith",
    "Leatherworker",
    "Weaver",
    "Alchemist",
    "Culinarian",
    "Miner",
    "Botanist",
    "Fisher",
    "Paladin",
    "Monk",
    "Warrior",
    "Dragoon",
    "Bard",
    "White Mage",
    "Black Mage",
    "Arcanist",
    "Summoner",
    "Scholar",
    "Rogue",
    "Ninja",
    "Machinist",
    "Dark Knight",
    "Astrologian",
    "Samurai",
    "Red Mage"
  };
  /*
  static std::unordered_map< const uint8_t, const std::string > RaceName =
  {
      { 1, "Hyur" },
      { 2, "Elezen" },
      { 3, "Lalafell" },
      { 4, "Miqo'te" },
      { 5, "Roegadyn" },
      { 6, "Au'Ra" }
  };

  static std::array< std::string, 2 > RaceTest = {
    "Test",
    "2"
  }
  
  static std::unordered_map< uint8_t, std::string > JobName =
  {
      { Common::ClassJob::Adventurer, "Adventurer" },
      { Common::ClassJob::Gladiator, "Gladiator" }
  };*/
}

#endif