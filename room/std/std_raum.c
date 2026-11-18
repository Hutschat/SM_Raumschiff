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

  AddDetail(({"licht","deckenlicht","beleuchtung"}),
  "Das Licht kommt direkt aus der Decke. Es ist kalt und weiß.");

  AddDetail(({"flaeche","lichtflaeche"}),
  "Die ganze Decke leuchtet. Wo genau das Licht herkommt, kannst du "
  "nicht erkennen.");

}
