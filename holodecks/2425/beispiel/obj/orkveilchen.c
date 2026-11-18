// orkveilchen.c
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
  SetProp( P_SHORT, "Ein Orkveilchen" );
  SetProp( P_LONG, break_string(
        "Ein richtig schoenes blaufarbende Orkveilchen."));
  AddId(({"veilchen","blume", "orkveilchen"}));
  SetProp(P_NAME, "Orkveilchen");
  SetProp(P_GENDER, NEUTER);
  SetProp(P_WEIGHT, 2);
  SetProp(P_NOBUY,1);
  SetProp(P_SIZE,8);
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
      write(break_string("Du schnupperst am Orkveilchen und ein starker "
      "Geruch von Faeulnis zieht in deine Nase. Puhhhhhh!"));
      
      say (this_player()->Name(WER,2) + " steckt die Nase in ein "
      "Orkveilchen.\n");
      
      return 1;
    }
  }
  return 0;
}
