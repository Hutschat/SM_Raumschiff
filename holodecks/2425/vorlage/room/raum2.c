// raum2.c - Eine Wiese vor der Huette, mit Hannes dem Hirten

#include "def.h"

inherit "/std/room";

protected void create() {
  ::create();

  SetProp(P_INT_SHORT, "Auf einer Wiese");

  SetProp(P_INT_LONG,
    "Du stehst auf einer grossen Wiese voller Blumen. Im Norden steht eine "
    "kleine Huette, ringsum wachsen hohe Baeume. Am Himmel scheint die "
    "Sonne.");

  // Wird an die Langbeschreibung angehaengt, nach den Ausgaengen
  SetProp(P_INT_LONG_EXT,
    "Ein leichter Wind streicht ueber das Gras.");

  // Draussen: hier gibt es Himmel, Sonne und Wetter
  SetProp(P_INDOORS, 0);
  SetProp(P_LIGHT, 1);

  // Gelaende fuer draussen, siehe /sys/room/terrain.h
  SetProp(P_TERRAIN, T_PLAIN | T_MEADOW);

  AddDetail("wiese",
    "Die Wiese ist gross und voller Blumen. Das Gras reicht Dir bis zu den "
    "Knien.");

  AddDetail(({"knie", "knien"}),
    "Deine Knie sind im Gras verschwunden.");

  AddDetail(({"gras", "boden", "fussboden"}),
    "Weiches, gruenes Gras bedeckt den Boden.");

  AddDetail(({"blume", "blumen"}),
    "Rote, gelbe und blaue Blumen wachsen ueberall. Riech doch mal daran.");

  AddDetail(({"huette", "norden"}),
    "Im Norden steht eine kleine Huette aus Holz. Ihre Tuer steht offen.");

  AddDetail("holz",
    "Die Huette ist aus dunklem Holz gebaut.");

  AddDetail("tuer",
    "Durch die Tuer kommst Du zurueck in die Huette.");

  AddDetail(({"baum", "baeume"}),
    "Hohe Baeume umgeben die Wiese. Weiter kommst Du hier nicht.");

  AddDetail("himmel",
    "Der Himmel ist blau. Nur ein paar Wolken ziehen vorbei.");

  AddDetail(({"wolke", "wolken"}),
    "Kleine, weisse Wolken. Eine sieht aus wie ein Schaf.");

  AddDetail("schaf",
    "Nur eine Wolke, kein echtes Schaf.");

  AddDetail("sonne",
    "Die Sonne scheint warm auf die Wiese.");

  AddDetail("wind",
    "Der Wind bewegt das Gras wie Wellen.");

  AddDetail(({"welle", "wellen"}),
    "Das Gras wogt hin und her.");

  AddSmell(DEFAULT_SMELL,
    "Es duftet nach Blumen und frischem Gras.");

  AddSmell(({"blume", "blumen"}),
    "Die Blumen duften suess.");

  AddSound(DEFAULT_SOUND,
    "Bienen summen, und der Wind rauscht in den Baeumen.");

  AddSound(({"baum", "baeume"}),
    "Die Blaetter rascheln leise im Wind.");

  AddExit("norden", ROOM "raum1");

  // Der NPC kommt beim Laden und bei jedem Reset wieder, wenn er fehlt
  AddItem(NPC "hirte", REFRESH_DESTRUCT);
}
