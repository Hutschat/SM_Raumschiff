// hirte.c - Hannes, ein freundlicher Hirte auf der Wiese

#include "def.h"

inherit "/std/npc";

protected void create() {
  // Die Blaupause (nicht geclonte Datei) braucht nichts zu tun
  if (!clonep()) {
    set_next_reset(-1);
    return;
  }
  ::create();

  // Stufe 5 und 80 Lebenspunkte. Setzt auch Werte wie Kraft und Ruestung.
  create_default_npc(5, 80);

  // Name und Geschlecht. Bei Eigennamen gibt es keinen Artikel.
  SetProp(P_NAME, "Hannes");
  SetProp(P_ARTICLE, 0);
  SetProp(P_GENDER, MALE);

  // Mit diesen Woertern kann man ihn ansprechen: "unt hannes", "frage hirte"
  AddId(({"hannes", "hirte", "mann", "mensch"}));

  // Steht in der Raumbeschreibung
  SetProp(P_SHORT, "Hannes, der Hirte");

  // Was man bei "untersuche hannes" sieht
  SetProp(P_LONG,
    "Hannes ist ein alter Hirte mit einem grauen Bart und einem breiten "
    "Hut. In der Hand haelt er einen langen Stab. Er laechelt Dich "
    "freundlich an. Frag ihn doch mal nach seinen Schafen.");

  // Details am NPC: "untersuche bart an hannes"
  AddDetail("bart",
    "Ein langer, grauer Bart. Ein paar Grashalme haengen darin.");
  AddDetail(({"grashalm", "grashalme"}),
    "Hannes hat wohl im Gras geschlafen.");
  AddDetail("hut",
    "Ein breiter Hut aus Stroh, gegen die Sonne.");
  AddDetail("hand",
    "In der Hand haelt er seinen Stab.");
  AddDetail(({"schaf", "schafe", "schafen"}),
    "Schafe siehst Du hier keine. Wo die wohl sind?");
  AddDetail("stab",
    "Ein langer Hirtenstab aus Holz, oben gebogen.");

  // Groesse in Zentimetern, Gewicht in Gramm
  SetProp(P_SIZE, 175);
  SetProp(P_WEIGHT, 70000);

  // Rasse und Klasse, siehe /sys/class.h
  SetProp(P_RACE, CL_HUMAN);
  AddClass(CL_HUMAN);

  // Gesinnung: positiv = gut, negativ = boese
  SetProp(P_ALIGN, 500);

  // Wie er kommt und geht: "Hannes schlendert nach Norden."
  SetProp(P_MSGIN,  "schlendert herein");
  SetProp(P_MSGOUT, "schlendert");

  // Infos: "frage hannes nach schafe". "sagt: " steht vor der Antwort.
  AddInfo(({"schaf", "schafe", "herde"}),
    "Meine Schafe sind heute weggelaufen. Vielleicht findest Du sie?",
    "sagt: ");
  AddInfo(({"wiese"}),
    "Das ist die schoenste Wiese weit und breit.", "sagt: ");
  AddInfo(({"huette"}),
    "Da wohne ich. Auf dem Tisch liegt ein Zettel fuer Gaeste.", "sagt: ");
  AddInfo(({"name", "hannes"}),
    "Ich bin Hannes, der Hirte.", "sagt: ");

  // Antwort, wenn er zu einem Thema nichts weiss
  SetProp(P_DEFAULT_INFO,
    "kratzt sich am Kopf und zuckt mit den Schultern.\n");

  // Was er ab und zu von sich aus tut: 2 = Wahrscheinlichkeit in Prozent
  SetChats(2, ({
    "Hannes pfeift ein Lied.\n",
    "Hannes schaut sich suchend nach seinen Schafen um.\n",
  }));

  // Meldung, wenn er stirbt
  SetProp(P_DIE_MSG, " sinkt seufzend ins Gras.\n");
}
