// std_schiff.c
//
// Letzte Aenderung:
//
// 09.12.2025 It@MagicMud              neu

#include "def.h"

inherit REGION_ROOM "std/std_raum";

public int cant_open_door() {
  write(break_string(CTSA("Das ist eine automatische Tür! Sie öffnet sich, "
        "sobald du sie durschreiten willst!"));

  return 1;
}

public void close_sound() {
  tell_room(ME,CTSA("Die automatische Tür schließt sich wieder mit "
               "einem '"+SND_DOOR+"'.\n"));
   
}

public int door_sound() {
  write("\n"+break_string(CTSA("Die automatische Tür öffnet sich mit "
        "einem '"+SND_DOOR+"' und du gehst hindurch. Hinter dir schließt sie "
        "sich wieder."))+"\n");
  
  tell_room(ME,break_string(CTSA("Die automaische Tür öffnet sich mit einem "
               "'"+SND_DOOR+"'.")),({PL}));
  
  call_out("close_sound",0);
  return 0;
} 

// D_TESTFUNC der Tuer zur Kapitaenskajuete: nur Lehrer kommen hinein
public int lehrer_tuer() {
  if (!PL || !IS_TEACHER(PL)) {
    write(break_string(CTSA("Die automatische Tür bleibt geschlossen. Eine "
          "freundliche Computerstimme sagt: 'Zutritt nur für Lehrer.'")));
    return 1;
  }
  return door_sound();
}

protected void create() {
  ::create();
  SetProp(P_TERRAIN,T_CONSTRUCT);
  SetProp(P_LIGHT,1);
  SetProp(P_INDOORS,1);
  SetProp(P_INT_SHORT,"Im Raumschiff Proton");
  SetProp(P_INT_LONG, "Im Raumschiff Proton.");
  AddDetail(({"schiff","raumschiff","proton"}),#'_query_int_long);
}
