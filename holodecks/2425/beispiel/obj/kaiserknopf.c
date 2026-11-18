// kaiserknopf.c
//
// Letzte Aenderung:
//
// 09.12.2025 It@MagicMud            neu

#include "def.h"

inherit "std/thing";

protected void create()
{
  if(!clonep())
  {
    set_next_reset(-1);
    return;
  }
  ::create();
  AddMaterial(MAT_PLANT);
  SetProp( P_SHORT, "Ein Kaiserknopf" );
  SetProp( P_LONG,
  "Ein dicker Stengel, nicht besonders lang, und stabile in allen "
  "Farbtoenen leuchtende Blaetter, die sich zu einer flachen Kuppel "
  "formen, bilden einen majestaetischen Anblick.");
  AddId(({"kaiserknopf","blume"}));
  SetProp(P_NAME, "Kaiserknopf");
  SetProp(P_GENDER, MALE);
  SetProp(P_WEIGHT, 2);
  SetProp(P_NOBUY,1);
  SetProp(P_SIZE,15);
  AddClass(({CL_PLANT,CL_FLOWER}));
  SetProp(P_BUY_VALUE,10);
  AddCmd(({"riech","rieche","schnupper","schnuppere"}), "riechen");
}

static int riechen(string str)
{
   string woran;
   
   notify_fail("Woran moechtest Du denn schnuppern?\n");
   
   if (!str) return 0;
   
   if(sscanf(str,"an %s",woran) == 1 ||
      sscanf(str,"%s",woran) == 1)
   {
     if(id(woran))
     {
       write(break_string("Der Geruch dieser Blume fegt dich quasi hinfort. "
       "Ueberwaeltigend und betoerend huellt diese Kraft dich ein. Du kannst "
       "deine Nase fast nicht mehr losreissen..."));
       
       say (this_player()->Name(WER,2) + " steckt die Nase in einen "
       "Kaiserknopf.\n");
       
       return 1;
     }
  }
  return 0;
}
