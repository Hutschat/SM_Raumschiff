// kommunikator.c - Wird beim Laden eines Holodeck-Programms ausgehaendigt.
//
// 'computer, ende' bzw. 'ende programm' bringt zurueck zum Holodeck.
//
// Letzte Aenderung:
//
// 18.11.2026 It@Efferdland            neu

#pragma strong_types
#pragma save_types
#pragma rtt_checks

#include "../region.h"
#include <moving.h>

inherit "/std/thing";

#define HOLO_DIR  "/d/raumschiff/holodecks/"
#define HOLORAUM  "/d/raumschiff/room/[-3+0-1]"

private object heimat;

public void set_heimat(object ob) {
  heimat = ob;
}

private int im_holodeck(object ob) {
  string name = ob ? object_name(ob) : "";

  if (sizeof(name) && name[0] != '/') {
    name = "/" + name;
  }
  return name[0..sizeof(HOLO_DIR)-1] == HOLO_DIR;
}

static int ende_cmd(string str) {
  object ziel;

  if (query_verb() == "computer,") {
    if (str != "ende" && str != "programm ende") {
      return 0;
    }
  }
  else if (str != "programm") {
    notify_fail("Meinst du 'ende programm'?\n");
    return 0;
  }
  ziel = heimat || load_object(HOLORAUM);

  write(break_string("Du sagst: 'Computer, Programm beenden.' Die Umgebung "
        "flackert, loest sich in ein gelbes Gitternetz auf und du stehst "
        "wieder im Holodeck.", 78));

  if (environment(PL)) {
    tell_room(environment(PL), break_string(PL->Name()
              + " loest sich flackernd in Luft auf.", 78), ({PL}));
  }
  PL->move(ziel, M_TPORT | M_NOCHECK);
  remove();
  return 1;
}

// Ausserhalb der Holodecks verschwindet der Kommunikator
void reset() {
  ::reset();

  if (environment() && !im_holodeck(environment(environment()))) {
    remove();
  }
}

protected void create() {
  if (!clonep()) {
    set_next_reset(-1);
    return;
  }
  ::create();
  SetProp(P_NAME, "Kommunikator");
  SetProp(P_GENDER, MALE);
  SetProp(P_SHORT, "Ein Kommunikator");
  SetProp(P_LONG, break_string(
    "Ein kleines Abzeichen, das du an der Brust traegst. Mit "
    "'ende programm' oder 'computer, ende' kehrst du ins Holodeck "
    "zurueck.", 78));
  SetProp(P_NODROP, "Den Kommunikator brauchst du noch.\n");
  SetProp(P_NEVERDROP, 1);
  SetProp(P_WEIGHT, 10);
  AddId(({"kommunikator", "abzeichen", "\nholo_kommunikator"}));

  AddCmd("ende", "ende_cmd");
  AddCmd("computer,", "ende_cmd");
}
