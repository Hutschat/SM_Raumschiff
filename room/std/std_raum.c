// std_raum.c
//
// Letzte Aenderung:
//
// 09.12.2025 It@MagicMud              neu

#include "def.h"

inherit "/std/room";
inherit REGION_STD "funcs";

protected void create() {
  "*"::create();
  AddDetail(KEYS_ROOM,#'_query_int_long);

  AddDetail(KEYS_CEILING,
  "Die Decke ist eine einzige Fläche aus flackerndem Licht.");

}
