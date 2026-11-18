// lehrerkonsole.c - Verwaltung der Holodeck-Projekte, nur fuer Lehrer
//
// Letzte Aenderung:
//
// 19.11.2026 It@Efferdland            aus holokonsole.c ausgelagert

#pragma strong_types
#pragma save_types
#pragma rtt_checks

#include "../region.h"

inherit "/std/thing";

static string lehrer_hilfe() {
  return
  "Lehrerpult (aktuelles Schuljahr: " + HOLODECKD->query_jahr() + "):\n"
  "  holo jahr <schuljahr>              Schuljahr wechseln (z.B. 2627)\n"
  "  holo neu <projekt>                 Projekt aus Vorlage anlegen\n"
  "  holo loesche <projekt>             Projekt aus der Verwaltung nehmen\n"
  "  holo team <projekt> + <name> ...   Schueler ins Team aufnehmen\n"
  "  holo team <projekt> - <name> ...   Schueler aus dem Team nehmen\n"
  "  holo klasse <projekt> <klasse>     ganze Klasse ins Team aufnehmen\n"
  "  holo sperre <projekt> an|aus       Schreibschutz fuer das Team\n"
  "Uebersicht und Gaeste: an der Holodeck-Konsole ('projekte', 'gaeste').\n";
}

static string pult_long() {
  if (PL && IS_TEACHER(PL)) {
    return lehrer_hilfe();
  }
  return "Ein schmales Pult mit einem Schild: 'Nur fuer Lehrer'.\n";
}

static int holo_cmd(string str) {
  string *arg, msg;

  if (!PL || !IS_TEACHER(PL)) {
    return 0;
  }
  arg = str ? explode(str, " ") - ({""}) : ({});

  if (!sizeof(arg) || arg[0] == "hilfe") {
    write(lehrer_hilfe());
    return 1;
  }
  switch (arg[0]) {
    case "jahr":
      if (sizeof(arg) == 2) {
        msg = HOLODECKD->set_jahr(arg[1]);
      }
      break;

    case "neu":
      if (sizeof(arg) == 2) {
        msg = HOLODECKD->projekt_neu(lower_case(arg[1]));
      }
      break;

    case "loesche":
      if (sizeof(arg) == 2) {
        msg = HOLODECKD->projekt_loeschen(lower_case(arg[1]));
      }
      break;

    case "team":
      if (sizeof(arg) < 4) {
        break;
      }
      if (arg[2] == "+") {
        msg = HOLODECKD->mitglied_add(lower_case(arg[1]), arg[3..]);
      }
      else if (arg[2] == "-") {
        msg = HOLODECKD->mitglied_del(lower_case(arg[1]), arg[3..]);
      }
      break;

    case "klasse":
      if (sizeof(arg) == 3) {
        msg = HOLODECKD->klasse_add(lower_case(arg[1]), arg[2]);
      }
      break;

    case "sperre":
      if (sizeof(arg) == 3 && member(({"an", "aus"}), arg[2]) != -1) {
        msg = HOLODECKD->set_gesperrt(lower_case(arg[1]), arg[2] == "an");
      }
      break;
  }
  if (!msg) {
    write(lehrer_hilfe());
    return 1;
  }
  write(break_string("Computer: " + msg, 78));
  return 1;
}

protected void create() {
  if (!clonep()) {
    set_next_reset(-1);
    return;
  }
  ::create();
  SetProp(P_NAME, "Lehrerpult");
  SetProp(P_GENDER, NEUTER);
  SetProp(P_SHORT, "Ein Lehrerpult");
  Set(P_LONG, #'pult_long, F_QUERY_METHOD);
  SetProp(P_NOGET, "Das Pult ist fest im Boden verankert.\n");
  SetProp(P_WEIGHT, 100000);
  AddId(({"pult", "lehrerpult", "lehrerkonsole"}));

  AddCmd("holo", "holo_cmd");
}
