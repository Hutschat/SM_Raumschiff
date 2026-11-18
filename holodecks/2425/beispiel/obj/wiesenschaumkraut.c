// wiesenschaumkraut.c
//
// Letzte Aenderung:
//
// 09.12.2015 It@MagicMud             neu

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
  SetProp( P_SHORT, "Ein Wiesenschaumkraut" );
  SetProp( P_LONG, 
  "Kleine, weisse sich nach oben kraeuselnde Blaetter gaben dieser Blume "
  "ihren Namen. Einen beruhigenden Anblick bietet diese zarte Blume.");
  AddId(({"kraut","blume", "wiesenschaumkraut"}));
  SetProp(P_NAME, "Wiesenschaumkraut");
  SetProp(P_GENDER, NEUTER);
  SetProp(P_WEIGHT, 2);
  SetProp(P_NOBUY,1);
  SetProp(P_SIZE,5);
  AddClass(({CL_PLANT,CL_FLOWER}));
  SetProp(P_BUY_VALUE,10);
  AddCmd(({"riech","rieche","schnupper","schnuppere"}), "riechen");
}

int riechen(string str)
{
  string woran;
  
  notify_fail("Woran moechtest Du denn schnuppern?\n");
  
  if (!str) return 0;
  
  if(sscanf(str,"an %s",woran) == 1 ||
     sscanf(str,"%s",woran) == 1)
  {
    if(id(woran))
    {
      write(break_string("Du schnupperst am Wiesenschaumkraut und ein sanfter "
      "honiger Geruch steigt dir in die Nase."));
      
      say (this_player()->Name(WER,2) + " steckt seine die in ein "
      "Wiesenschaumkraut.\n");
   
      return 1;
    }
  }
  return 0;
}
