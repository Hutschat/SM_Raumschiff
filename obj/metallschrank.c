// metallschrank.c
//
// Letzte Aenderung:
//
// 30.12.2021 It@Efferdland            neu

#include "def.h"

inherit "/obj/container";
inherit "/std/room/items";

protected void create() {
  if(!clonep()) {
    set_next_reset(-1);
    return;
  }
  "*"::create();

  SetProp(P_SHORT,"Ein rostiger Metallschrank");
  SetProp(P_LONG,
  "Es rostiger Schrank aus Metall. Er ist ungefaher sechs Fuss hoch "
  "und fuenf breit und mit Beulen nur so uebersaet.");

  SetProp(P_NAME,"Metallschrank");
  SetProp(P_GENDER,MALE);
  SetProp(P_SIZE,180);
  SetProp(P_WEIGHT,300000);
  SetProp(P_NAME_ADJ,"rostig");
  SetProp(P_MATERIAL,MAT_IRON);
  SetProp(P_NOGET,"Der Metallschrank bewegt sich kein Stueck.\n");
  AddId(([
          "rostigen#verbeulten":
          ({"schrank","metallschrank","eisenschrank"})
        ]));

  AddDetail(([
              "rostiges":
              ({"metall"}),
            ]),
  "Das wird wohl Eisen oder so etwas sein.");

  AddDetail(([
              "rostiges":
              ({"eisen"}),
            ]),
  "Was rostet sonst, ausser Eisen? Dann wird es wohl auch Eisen sein.");

  AddDetail(([
              "rauen#roetlichen#basigen":
              ({"rost"}),
            ]),
  "Der Rost ist sehr blasig, rau und roetlich.");

  AddDetail(({"beule","beulen"}),
  "Der ganze Schrank ist mit Beulen nur so uebersaet. Da muss einiges "
  "drauf gefallen sein...");
}
