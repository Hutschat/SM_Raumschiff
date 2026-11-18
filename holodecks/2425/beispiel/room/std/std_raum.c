// std_raum
//
// Letzte Aenderung:
//
// 09.12.2025 It@MagicMud              neu

#include "def.h"

inherit "/std/room";

protected void create() {
  ::create();

  AddDetail(({"raum","ort","umgebung"}),#'_query_int_long);
}
