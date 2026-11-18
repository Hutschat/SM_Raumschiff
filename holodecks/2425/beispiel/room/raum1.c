// raum1.c
//
// Letzte Aenderung:
//
// 09.12.2025 It@MagicMud              neu

#include "def.h"

inherit ROOM "std/std_raum";

static string my_long() {
  string ret;
  
  if (this_player()->QueryProp(P_FROG)) {
    if(present_clone(NPC "riesenstorch")) {
      ret = "Eine entzueckende, saftiggruene Wie... AU WEIA! Da...dada.... "
            "dadada steht... EIN STORCH!!! HUEPFE UM DEIN LEBEN!!!";
    }
    else { 
      ret = "Eine entzueckende, saftiggruene Wiese, die wie "
            "geschaffen fuer kleine, gruene Froesche scheint. Leise summen "
            "fette Fliegen ueber dem Morast, und auch die eine oder andere "
            "tiefe Pfuetze zum entspannen findest du.";
    }
  }
  else {
   ret = "Eine saftiggruene Wiese, die obendrein noch von matschigen "
         "Pfuetzen durchsetzt ist. Gottseidank kannst du im Suedosten wieder "
         "auf die trockene Strasse gehen.";
  }
  return break_string(ret+" Im Suedwesten der Wiese ist es erstaunlich "
         "dunkel, als wenn dort Nacht herrschen wuerde. Merkwuerdig!");
}

static int nacht_ex() {
  tell_object(this_player(),"\nPloetzlich setzt die Nacht ein!\n");
  
  this_player()->move(ROOM "raum2",M_GO);
  
  return 1;
}

static int wand_ex() {
  tell_object(this_player(),break_string(
  "\nDONG! Du rennst gegen die Wand der Holodecks! Verdammt! Dort "
  "entlang geht es nicht weiter!!"));
  return 1;
}

protected void create() {
  ::create();
  SetProp(P_INT_SHORT, "Die Storchenwiese");
  Set(P_INT_LONG,#'my_long,F_QUERY_METHOD);
  
  // Licht an. siehe: "man P_LIGHT"
  SetProp(P_LIGHT,1);

  // siehe: /sys/room/terrain.h und "man P_TERRAIN"
  SetProp(P_TERRAIN,T_PLAIN|T_MEADOW);

  AddDetail(({"wiese","storchenwiese"}),
  "Du stehst mitten drin. Im Matsch. Denn hier steht fast alles unter "
  "Wasser!");

  AddDetail(({"fliege","fliegen"}),
  "Die Fliegen hier sind wirklich nervig. Die scheinen sich auf dieser "
  "nassen Wiese richtig wohl zu fuehlen.");

  AddDetail(({"matsch","morast"}),
  "Platsch! Platsch! Du huepfst im Matsch! Ach, das ist spassig!");
  
  AddDetail(({"nacht"}),
  "Im Suedwesten scheint Nacht zu sein. Wie das wo moeglich ist?");

  AddDetail(({"himmel"}),
  "Hier hat es wohl kuerzlich geregnet. Jetzt ist der Himmel aber wieder "
  "blau und wolkenlos.");

  AddDetail(({"regen"}),
  "Der ist vorbei!");

  AddDetail(({"pfuetze","pfuetzen"}),
  "Eigentlich ist die gesamte Wiese eine einzige Pfuetze, in der einige "
  "wenige Inseln aus Gras wachsen. Froesche muessten sich hier sehr wohl "
  "fuehlen.");
  
  AddDetail(({"boden","fussboden"}),
  "HIer steht alles unter Wasser. Nur ein paar Grasinseln schauen heraus.");

  AddDetail(({"wasser"}),
  "Das Wasser sieht ziemlich schlammig aus ist koechelhoch.");

  AddDetail(({"sonne"}),
  "Die Sonne steht hoch am Himmel.");

  AddDetail(({"wolke","wolken"}),
  "Es sind gerade keine Wolken zu sehen.");

  AddDetail(({"insel","inseln","gras","grashalm","grashalme","halme",
              "grasinsel","grasinseln"}),
  "Hier wachsen viele vereinzelte Inseln aus Gras in einer riesigen "
  "Pfuetze. Dadurch, dass die Grashalme bogenfoermig von der Wurzel zur "
  "Seite wachsen, sieht man jedoch nur das Wasser, in dem man steht. Etwas "
  "weiter weg ist es durch das ewiggruene Gras verdeckt.");
  
  AddDetail(({"wurzel", "wurzeln"}),
  "Du kannst keine Wurzel sehen. Oder hast du Roentgenaugen?");
  
  AddDetail(({"auge","augen","roentgenauge","roentgenaugen"}),
  "Deine Augen schmerzen sehr, als du versuchst, dir mit der rechten Pupille "
  "in die linke Pupille zu schauen. Du bist gewarnt.");
  
  AddDetail(({"strasse","weg","pfad","allee"}),
  "Was auch immer, es ist im Suedosten.");
  
  AddItem(NPC "riesenstorch", REFRESH_DESTRUCT);

  AddSpecialExit("suedwesten", "nacht_ex");
  AddSpecialExit("suedosten",  "wand_ex");
}
