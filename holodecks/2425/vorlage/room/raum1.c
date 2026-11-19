// raum1.c - Startraum: Hier landet man, wenn das Programm geladen wird.
//
// Zurueck ins Holodeck geht es jederzeit mit "ende programm".

#include "def.h"

inherit "/std/room";

protected void create() {
  ::create();

  // Kurzbeschreibung: steht im Kurzmodus und bei "wo bin ich"
  SetProp(P_INT_SHORT, "In einer kleinen Huette");

  // Langbeschreibung: kommt beim Betreten und bei "schau"
  SetProp(P_INT_LONG,
    "Du stehst in einer kleinen Huette aus Holz. Durch ein Fenster faellt "
    "helles Licht auf einen Tisch, auf dem ein Zettel liegt. Durch die Tuer "
    "im Sueden kommst Du hinaus auf eine Wiese.");

  // Der Raum ist innen (Regen, Sonne usw. gibt es hier nicht)
  SetProp(P_INDOORS, 1);

  // Es ist hell. 0 waere dunkel, dann braucht man eine Fackel.
  SetProp(P_LIGHT, 1);

  // Details: was man mit "untersuche <wort>" sieht.
  // Mehrere Woerter in ({ }) zeigen alle denselben Text.
  AddDetail(({"huette", "raum"}),
    "Die Huette ist klein, aber gemuetlich. Ausser dem Tisch steht hier "
    "nichts.");

  AddDetail("holz",
    "Dunkles, altes Holz. Es knarrt, wenn Du darauf trittst.");

  AddDetail(({"boden", "fussboden"}),
    "Der Boden besteht aus breiten Brettern aus Holz.");

  AddDetail(({"brett", "bretter", "brettern"}),
    "Die Bretter sind abgetreten und knarren leise.");

  AddDetail(({"wand", "waende"}),
    "Die Waende sind aus dicken Balken gebaut.");

  AddDetail(({"balken"}),
    "Dicke, dunkle Balken aus Holz.");

  AddDetail("decke",
    "Die Decke ist niedrig. Fast stoesst Du mit dem Kopf daran.");

  AddDetail("kopf",
    "Pass auf, dass Du ihn Dir nicht stoesst!");

  AddDetail("fenster",
    "Durch das Fenster siehst Du die Wiese im Sueden.");

  AddDetail("licht",
    "Das Licht faellt warm durch das Fenster.");

  AddDetail("tisch",
    "Ein einfacher Tisch aus Holz. Auf ihm liegt ein Zettel.");

  AddDetail("zettel",
    "Ein Zettel mit ein paar Zeilen. Du kannst ihn lesen.");

  AddDetail(({"zeile", "zeilen"}),
    "Lies den Zettel, dann weisst Du, was dort steht.");

  AddDetail("tuer",
    "Die Tuer steht offen. Draussen siehst Du eine Wiese.");

  AddDetail(({"wiese", "sueden"}),
    "Im Sueden liegt eine Wiese voller Blumen.");

  AddDetail(({"blume", "blumen"}),
    "Von hier aus siehst Du nur bunte Punkte.");

  AddDetail(({"punkt", "punkte"}),
    "Geh hinaus, dann siehst Du mehr.");

  // Lesbare Details: was man mit "lies <wort>" sieht.
  AddReadDetail("zettel",
    "Auf dem Zettel steht: 'Willkommen in unserem Programm! Geh nach "
    "Sueden und sprich mit Hannes.'");

  // Gerueche: "rieche" allein ergibt DEFAULT_SMELL, "rieche tisch" den
  // Text zu "tisch".
  AddSmell(DEFAULT_SMELL,
    "Es riecht nach altem Holz.");

  AddSmell("tisch",
    "Der Tisch riecht ein wenig nach Brot.");

  // Geraeusche: "lausche" allein ergibt DEFAULT_SOUND.
  AddSound(DEFAULT_SOUND,
    "Draussen zwitschern Voegel.");

  // Ausgang: Richtung und Raum. ROOM steht in def.h.
  AddExit("sueden", ROOM "raum2");
}
