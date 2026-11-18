// metallkiste.c
//
// Letzte Aenderung:
//
// 30.12.2021 It@Efferdland            neu

#include "def.h"

inherit REGION_OBJ "metallschrank";

protected void create() {
  if(!clonep()) {
    set_next_reset(-1);
    return;
  }
  "*"::create();
  SetProp(P_IDS,({}));
  SetProp(P_SHORT,"Eine verbeulte Metallkiste");
  SetProp(P_LONG,
  "Das ist eine grosse, verbeulte, rostige Metallkiste. Was die hier wohl "
  "zu suchen hat?");

  SetProp(P_NAME,"Metallkiste");
  SetProp(P_GENDER,FEMALE);
  SetProp(P_CNT_STATUS,CNT_STATUS_CLOSED);
  SetProp(P_SIZE,100);
  SetProp(P_WEIGHT,80000);
  SetProp(P_NOGET,"Die Metallkiste scheint mit dem Boden verschraubt zu "
                  "sein.\n");

  AddId(([
          "rostige#verbeulte":
          ({"kiste","metallkiste","eisenkiste"}),
        ]));
}
