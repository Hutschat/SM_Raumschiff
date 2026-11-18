// mech.c - Std File fuer mechanische Wesen
//
// Letzte Aenderung:
//
// 14.08.2018 It@Efferdland             neu

#pragma no_clone

#include "def.h"

inherit POOL_STD "corpse_npc";
inherit REGION_STD "funcs";

varargs void die(int bla,int ex) {
  ::die(bla,ex,POOL_CONTAINER "schrott");
}

protected void create() {
  if(!clonep()) {
    set_next_reset(-1);
    return;
  }
  "*"::create();
  create_default_npc(2,100);
  SetProp(P_SHORT,"Ein Mech");
  SetProp(P_LONG, "Ein Mech.");
  SetProp(P_ALIGN,100);
  SetProp(P_DIE_MSG," zerfaellt zu Schrott.\n");
  SetProp(P_CLASS,({CL_CONSTRUCT}));
  SetProp(P_RACE,CL_CONSTRUCT);
  AddId(({"maschine"}));
}
