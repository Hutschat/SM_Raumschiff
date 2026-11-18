// holokonsole.c - Steuerkonsole fuer die Holodecks
//
// Spieler:  projekte [<schuljahr>]
//           lade <projekt> [<schuljahr>]
// Lehrer:   holo ...   (siehe 'holo hilfe')
//
// Rechte und Teams verwaltet /secure/daemon/holodeckd.
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

#define START_RAUM    "/room/raum1"
#define KOMMUNIKATOR  "/d/raumschiff/obj/kommunikator"

static string lehrer_hilfe() {
  return
  "Lehrerbefehle der Holodeck-Konsole (aktuelles Schuljahr: "
    + HOLODECKD->query_jahr() + "):\n"
  "  holo jahr <schuljahr>              Schuljahr wechseln (z.B. 2627)\n"
  "  holo neu <projekt>                 Projekt aus Vorlage anlegen\n"
  "  holo loesche <projekt>             Projekt aus der Verwaltung nehmen\n"
  "  holo team <projekt> + <name> ...   Schueler ins Team aufnehmen\n"
  "  holo team <projekt> - <name> ...   Schueler aus dem Team nehmen\n"
  "  holo klasse <projekt> <klasse>     ganze Klasse ins Team aufnehmen\n"
  "  holo besuch <projekt> an|aus       Besuch durch andere erlauben\n"
  "  holo sperre <projekt> an|aus       Schreibschutz fuer das Team\n";
}

static string konsole_long() {
  string ret =
    "Eine schraeg gestellte Konsole mit leuchtenden Schaltflaechen. Ueber "
    "ihr steht in grossen Lettern 'HOLODECK'. Mit 'projekte' zeigt sie "
    "dir die verfuegbaren Programme, mit 'lade <projekt>' startest du eins.";

  ret = break_string(ret, 78);

  if (PL && IS_TEACHER(PL)) {
    ret += "\n" + lehrer_hilfe();
  }
  return ret;
}

/* ------------------------------------------------------------------ */
/* Spielerbefehle                                                      */
/* ------------------------------------------------------------------ */

static int projekte_cmd(string str) {
  string jahr = str ? str : HOLODECKD->query_jahr();
  mapping liste = HOLODECKD->query_projekte(jahr);
  string ret;

  if (!sizeof(liste)) {
    write("Computer: Fuer das Schuljahr " + jahr
          + " sind keine Programme gespeichert.\n");
    return 1;
  }
  ret = "Holodeck-Programme im Schuljahr " + jahr + ":\n\n"
      + sprintf("  %-20s %-8s %s\n", "Projekt", "Status", "Team");

  foreach (string name : sort_array(m_indices(liste), #'>)) {
    mixed *p = liste[name];

    ret += sprintf("  %-20s %-8s %s\n", name,
                   p[2] ? "gesperrt" : (p[1] ? "offen" : "privat"),
                   sizeof(p[0]) ? implode(map(p[0], #'capitalize), ", ")
                                : "-");
  }
  write(ret + "\nWeitere Schuljahre: "
        + implode(HOLODECKD->query_schuljahre(), ", ") + "\n");
  return 1;
}

static int lade_cmd(string str) {
  string projekt, jahr, dir, err;
  object raum, kom;

  notify_fail("Syntax: lade <projekt> [<schuljahr>]\n");

  if (!str) {
    return 0;
  }
  if (sscanf(str, "%s %s", projekt, jahr) != 2) {
    projekt = str;
    jahr    = HOLODECKD->query_jahr();
  }
  projekt = lower_case(projekt);

  if (!(dir = HOLODECKD->query_projekt_dir(jahr, projekt))) {
    write("Computer: Das Programm '" + projekt + "' ist nicht gespeichert.\n");
    return 1;
  }
  if (!HOLODECKD->darf_betreten(PL, jahr, projekt)) {
    write("Computer: Zugriff verweigert. Dieses Programm ist nur fuer "
          "sein Team freigegeben.\n");
    return 1;
  }
  if (err = catch(raum = load_object(dir + START_RAUM); publish)) {
    write("Computer: Programmfehler! Das Programm kann nicht geladen "
          "werden.\n");

    if (IS_TEACHER(PL) || HOLODECKD->ist_im_team(getuid(PL), jahr, projekt)) {
      write("Fehler in " + dir + START_RAUM + ":\n" + err);
    }
    return 1;
  }
  if (!(kom = present_clone(KOMMUNIKATOR, PL))) {
    kom = clone_object(KOMMUNIKATOR);
    kom->move(PL, M_NOCHECK);
  }
  kom->set_heimat(environment());

  write(break_string("Du sagst laut: 'Computer, Programm " + projekt
        + " starten.' Ein Arch mit leuchtenden Rahmen erscheint vor dir, "
        "die Tueren gleiten zur Seite und du trittst hindurch.", 78));
  say(break_string(PL->Name() + " startet das Programm " + projekt
      + " und verschwindet durch das Arch.", 78));

  PL->move(raum, M_TPORT | M_NOCHECK);
  return 1;
}

/* ------------------------------------------------------------------ */
/* Lehrerbefehle                                                       */
/* ------------------------------------------------------------------ */

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
      if (sizeof(arg) != 2) {
        break;
      }
      msg = HOLODECKD->set_jahr(arg[1]);
      break;

    case "neu":
      if (sizeof(arg) != 2) {
        break;
      }
      msg = HOLODECKD->projekt_neu(lower_case(arg[1]));
      break;

    case "loesche":
      if (sizeof(arg) != 2) {
        break;
      }
      msg = HOLODECKD->projekt_loeschen(lower_case(arg[1]));
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
      if (sizeof(arg) != 3) {
        break;
      }
      msg = HOLODECKD->klasse_add(lower_case(arg[1]), arg[2]);
      break;

    case "besuch":
    case "sperre":
      if (sizeof(arg) != 3 || member(({"an", "aus"}), arg[2]) == -1) {
        break;
      }
      if (arg[0] == "besuch") {
        msg = HOLODECKD->set_besuch(lower_case(arg[1]), arg[2] == "an");
      }
      else {
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
  SetProp(P_NAME, "Konsole");
  SetProp(P_GENDER, FEMALE);
  SetProp(P_SHORT, "Die Holodeck-Konsole");
  Set(P_LONG, #'konsole_long, F_QUERY_METHOD);
  SetProp(P_NOGET, "Die Konsole ist fest im Boden verankert.\n");
  SetProp(P_WEIGHT, 200000);
  AddId(({"konsole", "holodeck-konsole", "holokonsole", "computer"}));

  AddCmd("projekte", "projekte_cmd");
  AddCmd("lade", "lade_cmd");
  AddCmd("holo", "holo_cmd");
}
