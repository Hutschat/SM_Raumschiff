// [+0-2+0].c - Der Maschinenraum
//
// Letzte Aenderung:
//
// 14.12.2025 It@MagicMud              neu

#include "def.h"

inherit REGION_ROOM "std/std_schiff";

protected void create() {
  if(!clonep()) {
    set_next_reset(-1);
    return;
  }
  ::create();
}
