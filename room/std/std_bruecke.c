// std_schiff.c
//
// Letzte Aenderung:
//
// 09.12.2025 It@MagicMud              neu

#include "def.h"

inherit REGION_ROOM "std/std_schiff";

protected void create() {
  ::create();
  SetProp(P_INT_SHORT,"Auf der Bruecke der Proton");
  SetProp(P_INT_LONG, "Auf der Bruecke der Proton.");
  AddDetail(({"bruecke","schiffsbruecke"}),#'_query_int_long);
}
