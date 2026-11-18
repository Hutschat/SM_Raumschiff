// himmelsschluessel.c
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
  SetProp( P_SHORT, "Ein Himmelsschluessel" );
  SetProp( P_LONG, 
  "Ein langer Stengel mit sich nach oben hin zu einem Kelch "
  "formende Blaetter machen den Reiz des Himmelsschluessels aus. Die "
  "Blaetter zeigen sich dir in allen moeglichen Blautoenen.");

  AddId(({"himmelsschluessel","blume"}));
  AddClass(({CL_PLANT,CL_FLOWER}));
  SetProp(P_NAME, "Himmelsschluessel");
  SetProp(P_GENDER, MALE);
  SetProp(P_WEIGHT, 2);
  SetProp(P_NOBUY,1);
  SetProp(P_BUY_VALUE,10);
  SetProp(P_SIZE,20);
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
      write(break_string(
      "Du schnupperst am Himmelsschluessel und dir oeffnen sich saemtliche "
      "Himmelspforten. Ein zarter Geruch spielt mit deiner Nase, der dich "
      "fuer einen kurzen Moment auf den Wolken fliegen laesst."));
      
      say(this_player()->Name(WER,2) + " steckt die Nase in einen "
      "Himmelsschluessel.\n");
    
      return 1;
    }
  }
  return 0;
}
