// holoraum.c - Von hier aus kann man die Holodecks betreten
//
// Letzte Aenderung:
//
// 08.12.2025 It@Efferdland            neu
// 18.11.2026 It@Efferdland            Holodeck-Konsole

#include "def.h"

inherit "/std/room";

protected void create() {
  ::create();
  SetProp(P_LIGHT, 1);
  SetProp(P_INT_SHORT, "Das Holodeck");
  SetProp(P_INT_LONG, break_string(
    "Ein grosser, leerer Raum. Waende, Boden und Decke sind von einem "
    "gelben Gitternetz auf schwarzem Grund ueberzogen. Hier werden die "
    "Programme der Schiffsbesatzung zum Leben erweckt. Neben dem "
    "Eingang steht eine Konsole.", 78));

  AddDetail(({"gitter", "gitternetz", "netz", "waende", "wand", "boden",
              "decke"}),
    "Gelbe Linien auf schwarzem Grund, exakt rechtwinklig. Sobald ein "
    "Programm laeuft, verschwinden sie.\n");

  AddItem("/d/raumschiff/obj/holokonsole", REFRESH_DESTRUCT);
}
