// terminal_wint.c
//
// Letzte Aenderung:
//
// 06.01.2022 It@Efferdland            neu

#include "def.h"
#include REGION_SYS "monitor.h"

inherit "/std/thing";
inherit REGION_STD "monitor";

static string error_line() {
  return
  "Der schwere Ausnahmefehler 0E ist an der Adresse 00"+(10+random(10))+
  ":C0044"+(400+random(100));
}

static void setup_schirm() {
  set_display(
   ({ 
      "",
      "",
      "",
      "",
      "                                 Windows",
      "",
      #'error_line,
      "in der VXD-Datei VFAT(01) + 00002D6A aufgetreten. Die aktuelle ",
      "Anwendung wird beendet.",
      "",
      "*  Druecken Sie eine beliebige Taste, um die Anwendung",
      "abzubrechen.",
      "*  Druecken Sie Strg+Alt+Entf, um den Computer neu zu",
      "starten. Nichtgespeicherte Dateien gehen dabei verloren.",
      "",
      "                      Weiter mit beliebiger Taste. _",
   }));
}

protected void create() {
  if(!clonep()) {
    set_next_reset(-1);
    return;
  }
  "*"::create();
  SetProp(P_NAME,"Bildschirm");
  SetProp(P_SHORT,"In einer Wandnische steht ein Bildschirm mit einer Tastatur davor");
  Set(P_LONG,#'schirm_det,F_QUERY_METHOD);
  SetProp(P_GENDER,MALE);
  SetProp(P_SIZE,30);
  SetProp(P_WEIGHT,10000);
  AddId(({"terminal"}));

  AddCmd(({"tipp","tippe","druecke","drueck"}),"tippen_act");

  setup_schirm();

  set_colors(([
    "rahmen"     : ANSI_BG_WHITE,
    "schirm"     : ANSI_BG_BLUE,
    "schrift"    : ANSI_HFG_WHITE,
  ]));
}

static void restart() {
  setup_schirm();
}

static int tippen_act(string str) {
  mixed tmp;
  string verb = query_verb();
  
  notify_fail("Tippe was?\n");
  if(!str) {
    return 0;
  }
  str = lower_case(trim(str));

  if(verb=="drueck" || verb=="druecke") {
    if(member(({"beliebige taste","strg+alt+entf",
                "strg alt entf"}),str) != -1) {
      write("Du drueckst die Tasten. Mist, da tut sich nichts mehr!\n");
      return 1;
    }
  }
  write(schirm_det());  
  return 1;
}
