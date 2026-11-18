// [-3+0+0].c
//
// Letzte Aenderung:
//
// 14.12.2025 It@Efferdland            neu

#include "def.h"

inherit REGION_ROOM "std/std_gang";

protected void create() {
  if(!clonep()) {
    set_next_reset(-1);
    return;
  }
  ::create();
}
