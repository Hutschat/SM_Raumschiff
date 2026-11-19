// lehrerkonsole.c - Lehrerpult in der Kapitaenskajuete (nur Dekoration)
//
// Die Befehle zur Verwaltung der Holodeck-Projekte haben Lehrer jetzt
// immer dabei: projekt / projekte (/std/shells/modules/mod_mag_holodeck.c).
//
// Letzte Aenderung:
//
// 19.11.2026 It@Efferdland            aus holokonsole.c ausgelagert
// 19.11.2026 It@Efferdland            Ausgaben mit /std/util/anzeige
// 19.11.2026 It@Efferdland            Befehle in die Lehrer-Shell verlegt

#pragma strong_types
#pragma save_types
#pragma rtt_checks

#include "../region.h"

inherit "/std/thing";

static string pult_long() {
  if (PL && IS_TEACHER(PL)) {
    return break_string("Ein schmales Pult mit einem Schild: 'Nur fuer "
           "Lehrer'. Die Holodeck-Projekte verwaltest Du von ueberall "
           "mit den Befehlen 'projekte' und 'projekt' ('projekt' allein "
           "zeigt die Hilfe).", 78);
  }
  return "Ein schmales Pult mit einem Schild: 'Nur fuer Lehrer'.\n";
}

protected void create() {
  if (!clonep()) {
    set_next_reset(-1);
    return;
  }
  thing::create();
  SetProp(P_NAME, "Lehrerpult");
  SetProp(P_GENDER, NEUTER);
  SetProp(P_SHORT, "Ein Lehrerpult");
  Set(P_LONG, #'pult_long, F_QUERY_METHOD);
  SetProp(P_NOGET, "Das Pult ist fest im Boden verankert.\n");
  SetProp(P_WEIGHT, 100000);
  AddId(({"pult", "lehrerpult", "lehrerkonsole"}));
}
