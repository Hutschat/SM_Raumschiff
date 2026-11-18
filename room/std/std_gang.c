// std_schiff.c
//
// Letzte Aenderung:
//
// 09.12.2025 It@MagicMud              neu

#include "def.h"

inherit REGION_ROOM "std/std_schiff";

protected void create() {
  ::create();
  SetProp(P_INT_SHORT,"Ein Gang in der Proton");
  SetProp(P_INT_LONG, "Ein Gang in der Proton.");
  AddDetail(({"gang"}),#'_query_int_long);

  AddDetail(KEYS_FLOOR,
  ({
    "Der Boden besteht aus Metall. Es befindet sich etwas Wüstensand "
    "darauf.",
  }));

  AddDetail(KEYS_WALL,
  ({
    "Die Wände bestehn aus Metallplatten, die durch Nieten "
    "zusammengehalten werden.",
  }));
  
  
}
