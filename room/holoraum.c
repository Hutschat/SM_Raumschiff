// holoraum.c - Von hier aus kann man die Holodecks betreten
//
// Letzte Aenderung:
//
// 08.12.2025 It@Efferdland            neu
// 18.11.2026 It@Efferdland            Holodeck-Konsole
// 19.11.2026 It@Efferdland            virtueller Raum [-3+0-1]

#include "def.h"

inherit "/std/room";

protected void create() {
  if (!clonep()) {
    set_next_reset(-1);
    return;
  }
  ::create();
  SetProp(P_LIGHT, 1);
  SetProp(P_INDOORS, 1);
  SetProp(P_TERRAIN, T_CONSTRUCT);
  SetProp(P_INT_SHORT, "Das Holodeck");
  SetProp(P_INT_LONG, break_string(
    "Ein grosser, leerer Raum. Waende, Boden und Decke sind von einem "
    "gelben Gitternetz auf schwarzem Grund ueberzogen. Hier werden die "
    "Programme der Schiffsbesatzung zum Leben erweckt. Neben dem "
    "Eingang steht eine Konsole.", 78));

  AddDetail(({"raum", "holodeck", "ort", "umgebung"}), #'_query_int_long);

  AddDetail(({"gitter", "gitternetz", "netz", "linien", "linie"}),
    "Gelbe Linien auf schwarzem Grund, exakt rechtwinklig. Sobald ein "
    "Programm laeuft, verschwinden sie.\n");

  AddDetail(KEYS_WALL + KEYS_FLOOR + KEYS_CEILING,
    "Ueberall das gleiche gelbe Gitternetz. Wo die Wand aufhoert und die "
    "Decke anfaengt, ist kaum zu erkennen.\n");

  AddDetail(({"grund", "schwarz"}),
    "Tiefschwarz. Das Gitternetz wirkt darauf fast, als wuerde es "
    "schweben.\n");

  AddDetail(({"programm", "programme"}),
    "Welche Programme gespeichert sind, zeigt dir die Konsole mit "
    "'projekte'.\n");

  AddDetail(({"schiffsbesatzung", "besatzung"}),
    "Von der Besatzung ist niemand zu sehen. Die Programme hat sie aber "
    "hiergelassen.\n");

  AddDetail(({"leben"}),
    "Erstaunlich, wie echt die Programme wirken.\n");

  AddDetail(({"eingang", "durchgang"}),
    "Ein schlichter, offener Durchgang.\n");

  AddItem("/d/raumschiff/obj/holokonsole", REFRESH_DESTRUCT);
}
