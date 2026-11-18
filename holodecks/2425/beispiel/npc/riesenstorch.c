// riesenstorch.c
//
// Letzte Aenderung:
//
// 09.12.2025 It@MagicMud            neu

#include "def.h"

inherit "/std/npc";

// Wenn eine Lebewesen (Spieler oder NPC) sich in die Naehe des Storches 
// bewegt, also den Raum betritt, wird diese Funktion aufgerufen:
varargs void init() {
  ::init();
  // Greift an, wenn this_player() (Spieler oder NPC) ein Frosch ist
  // oder sich mit "untersuche maus" untersuchen lässt. Greift keine
  // Programmierer an: !IS_LEARNING()
  
  if (this_player() && (this_player()->QueryProp(P_FROG)
	  || this_player()->id("maus")) && (!IS_LEARNING(this_player()))) {
  
      // Der Storch greift den Spieler sofort an
      Kill(this_player());
  
      // Der Stroch wird in die Feindesliste des Spielers eingetragen
      this_player()->AddPursuer(this_object());
  }
}


protected void create() {
  if (!clonep()) {
    set_next_reset(-1);
    return;
  }
  ::create();
  // Erstellt Standartwerte für den NPC: 20 = Stufe und 150 = Lebespunkte
  create_default_npc(20,150);
  
  // Wenn man "schau" im Raum eingibt, sieht man dies
  SetProp(P_SHORT, "Ein Riesenstorch");
  
  // Und wenn man den Storch mit "untersuche Storch" betrachtet, dann dies:
  SetProp(P_LONG,
  "Dieser Riesenstorch freut sich auch heute auf jeden Frosch, den er sieht. "
  "Und wenn er keine Froesche findet, frisst er zur Not auch Elfen, Zwerge "
  "und sonstiges Gesocks.");
  
  SetProp(P_INFO, break_string("Froesche ueberrascht der Storch am liebsten "
                  "aus dem Hinterhalt."));

  SetProp(P_NAME, "Riesenstorch");

  SetProp(P_GENDER, MALE);

  AddId(({"storch","riesenstorch","tier","vogel"}) );

  SetProp(P_MSGIN,"stelzt herein");

  // Ergibt z.B.: Ein Riesenstorch stolziert nach Norden.
  SetProp(P_MSGOUT,  "stolziert");
  
  // Ergibt, wenn der NPC den Raum betritt: Ein Riesenstorch landet.
  SetProp(P_MMSGIN,  "landet");
  
  // Das Gewicht des Storchs in Gramm. 15000 Gramm = 15 Kilo
  SetProp(P_WEIGHT, 15000);
  
  // Die Groesse des Storchs in Zentimeter: 150 Zentimeter = 1,50 Meter
  SetProp(P_SIZE,150);

  // Die Klassen. Siehe: "man AddClass" und /sys/class.h
  AddClass(({
    CL_ANIMAL,     // Er ist ein Tier
    CL_FEATHERS,   // Er hat Federn
    CL_BIRD,       // Er ist ein Vogel
    CL_STORK,      // Er ist ein Storch
    CL_FLYING,     // Er fliegt
    CL_BREATH_AIR, // Er atmet Luft
  }));
  
  SetProp(P_RACE,CL_BIRD);  // Ist von der Rasse her ein Vogel
  
  // Ist heilig: +1500, ist satanisch: -1500. Hier +800 er ist ziemlich nett
  SetProp(P_ALIGN, 800);
  
  // Schanden und Meldung, wenn er ohne Waffen angreift:
  // Zu Schadentypen wie Stich etc. siehe: /sys/combat.h
  //                  Die Meldung                 Schadenshöhe  Stiche
  SetProp(P_HANDS,({" mit seinem Klapperschnabel",80+random(20),DT_PIERCE}) );
  
  SetProp(P_MAX_HANDS, 3);
  
  // Resistentzen gegen Schaeden wie in /sys/combat.h definiert.
  // Siehe auch: man P_RESISTANCE
  SetProp(P_RESISTANCE,
  ([
    DT_WATER : -0.1, 
    DT_AIR : -0.5 
  ]) );
  
  // Raummeldungen, die der Storch ab und zu macht. Siehe auch: man SetChats
  SetChats(2,
  ({
    "Der Storch klappert mit seinem Schnabel.\n"
  }));
  
  // Wenn der Stoch stirbt, kommt dieses Meldung:
  SetProp( P_DIE_MSG, " klappt den Schnabel fuer immer zu.\n" );
  
  // Wenn man dem Storch etwas fragt, dann kommt diese Meldung
  
  SetProp(P_DEFAULT_INFO," klappert mit dem Schnabel.\n");
  
  // Wenn man dem Storch etwas gibt, gibt er es wieder zurueck an den
  // Spieler. Für weitere Einstellungen siehe "man P_REJECT"
  SetProp(P_REJECT, ({ REJECT_GIVE,
                       "Der Storch ist schon satt.\n"
                    }) );
}
