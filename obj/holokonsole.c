// holokonsole.c - Holodeck-Konsole fuer alle
//
//   projekte [frei|<schuljahr>]          Liste mit Team und Zutritt
//   lade <projekt> [<schuljahr>]         Deck betreten
//
// Nur Teammitglieder (aktuelles Schuljahr):
//   einladen <name> [in <projekt>]       Charakter als Gast zulassen
//   ausladen <name> [aus <projekt>]      Gast entfernen (fliegt raus)
//   gaeste [<projekt>]                   Gaesteliste
//
// Jedes Deck ist fuer andere geschlossen, bis das Team jemanden einlaedt.
// Lehrerbefehle: siehe lehrerkonsole.c
//
// Letzte Aenderung:
//
// 18.11.2026 It@Efferdland            neu
// 19.11.2026 It@Efferdland            Gaeste, Lehrerbefehle ausgelagert

#pragma strong_types
#pragma save_types
#pragma rtt_checks

#include "../region.h"
#include <moving.h>

inherit "/std/thing";

#define START_RAUM    "/room/raum1"
#define KOMMUNIKATOR  "/d/raumschiff/obj/kommunikator"
#define HOLORAUM      "/d/raumschiff/room/[-3+0-1]"

static string hilfe() {
  return
  "Holodeck-Konsole:\n"
  "  projekte [frei|<schuljahr>]       Programme mit Team und Zutritt\n"
  "  lade <projekt> [<schuljahr>]      Programm starten\n"
  "Fuer Teammitglieder:\n"
  "  einladen <name> [in <projekt>]    Charakter auf dein Deck lassen\n"
  "  ausladen <name> [aus <projekt>]   Einladung zuruecknehmen\n"
  "  gaeste [<projekt>]                Wer ist eingeladen?\n";
}

static string konsole_long() {
  return break_string(
    "Eine schraeg gestellte Konsole mit leuchtenden Schaltflaechen. Ueber "
    "ihr steht in grossen Lettern 'HOLODECK'.", 78) + hilfe();
}

// Projekte des aktuellen Schuljahres, in denen pl im Team ist
static string *meine_projekte(object pl) {
  mapping liste = HOLODECKD->query_projekte(HOLODECKD->query_jahr());
  string *ret   = ({});

  foreach (string name, mixed *p : liste) {
    if (member(p[0], getuid(pl)) != -1) {
      ret += ({ name });
    }
  }
  return ret;
}

// Projekt aus der Eingabe oder automatisch, wenn man nur in einem Team ist
static string welches_projekt(string projekt) {
  string *meine = meine_projekte(PL);

  if (projekt) {
    projekt = lower_case(projekt);

    if (member(meine, projekt) == -1 && !IS_TEACHER(PL)) {
      write("Computer: Du bist nicht im Team von '" + projekt + "'.\n");
      return 0;
    }
    return projekt;
  }
  if (sizeof(meine) == 1) {
    return meine[0];
  }
  if (!sizeof(meine)) {
    write("Computer: Du gehoerst zu keinem Team.\n");
  }
  else {
    write("Computer: Welches Projekt? Du bist in: "
          + implode(sort_array(meine, #'>), ", ") + "\n");
  }
  return 0;
}

/* ------------------------------------------------------------------ */
/* Anzeigen und Betreten                                               */
/* ------------------------------------------------------------------ */

static string zutritt(mixed *p) {
  string uid = getuid(PL);

  if (member(p[0], uid) != -1) {
    return "Team";
  }
  if (member(p[1], uid) != -1) {
    return "Gast";
  }
  if (IS_TEACHER(PL)) {
    return "Lehrer";
  }
  return "-";
}

static int projekte_cmd(string str) {
  string jahr = HOLODECKD->query_jahr();
  int nur_frei;
  mapping liste;
  string ret;

  if (str == "frei") {
    nur_frei = 1;
  }
  else if (str) {
    jahr = str;
  }
  liste = HOLODECKD->query_projekte(jahr);

  if (!sizeof(liste)) {
    write("Computer: Fuer das Schuljahr " + jahr
          + " sind keine Programme gespeichert.\n");
    return 1;
  }
  ret = sprintf("Holodeck-Programme im Schuljahr %s:\n\n"
                "  %-18s %-7s %-9s %s\n", jahr,
                "Projekt", "Zutritt", "Status", "Team");

  foreach (string name : sort_array(m_indices(liste), #'>)) {
    mixed *p = liste[name];
    string z = zutritt(p);

    if (nur_frei && z == "-") {
      continue;
    }
    ret += sprintf("  %-18s %-7s %-9s %s\n", name, z,
                   p[2] ? "gesperrt" : "",
                   sizeof(p[0]) ? implode(map(p[0], #'capitalize), ", ")
                                : "-");
  }
  write(ret + "\nStarten mit: lade <projekt>\n");
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
    write("Computer: Zugriff verweigert. Dafuer brauchst du eine Einladung "
          "vom Team.\n");
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
/* Gaeste (nur Team)                                                   */
/* ------------------------------------------------------------------ */

// Gast, der gerade im Deck steht, zurueck ins Holodeck schicken
static void rauswerfen(string gast, string jahr, string projekt) {
  object pl  = find_player(gast);
  string dir = HOLODECKD->query_projekt_dir(jahr, projekt);
  string wo;

  if (!pl || !environment(pl) || !dir) {
    return;
  }
  wo = object_name(environment(pl));

  if (sizeof(wo) && wo[0] != '/') {
    wo = "/" + wo;
  }
  if (wo[0..sizeof(dir)] != dir + "/") {
    return;
  }
  tell_object(pl, break_string("Computer: Deine Einladung fuer das Programm "
              + projekt + " wurde zurueckgenommen. Die Umgebung loest sich "
              "auf und du stehst wieder im Holodeck.", 78));
  pl->move(load_object(HOLORAUM), M_TPORT | M_NOCHECK);

  if (present_clone(KOMMUNIKATOR, pl)) {
    present_clone(KOMMUNIKATOR, pl)->remove();
  }
}

static int einladen_cmd(string str) {
  string gast, projekt, jahr = HOLODECKD->query_jahr();
  mixed res;
  object pl;

  notify_fail("Syntax: einladen <name> [in <projekt>]\n");

  if (!str) {
    return 0;
  }
  if (sscanf(str, "%s in %s", gast, projekt) != 2) {
    gast = str;
  }
  if (!(projekt = welches_projekt(projekt))) {
    return 1;
  }
  res = HOLODECKD->gast_add(jahr, projekt, gast);

  if (stringp(res)) {
    write("Computer: " + res + "\n");
    return 1;
  }
  write("Computer: " + capitalize(gast) + " darf jetzt das Programm "
        + projekt + " betreten.\n");

  if (pl = find_player(lower_case(gast))) {
    tell_object(pl, break_string(capitalize(getuid(PL)) + " hat dich auf "
                "das Holodeck-Programm " + projekt + " eingeladen. Starten "
                "kannst du es an der Holodeck-Konsole mit 'lade " + projekt
                + "'.", 78));
  }
  return 1;
}

static int ausladen_cmd(string str) {
  string gast, projekt, jahr = HOLODECKD->query_jahr();
  mixed res;

  notify_fail("Syntax: ausladen <name> [aus <projekt>]\n");

  if (!str) {
    return 0;
  }
  if (sscanf(str, "%s aus %s", gast, projekt) != 2) {
    gast = str;
  }
  if (!(projekt = welches_projekt(projekt))) {
    return 1;
  }
  gast = lower_case(gast);
  res  = HOLODECKD->gast_del(jahr, projekt, gast);

  if (stringp(res)) {
    write("Computer: " + res + "\n");
    return 1;
  }
  write("Computer: " + capitalize(gast) + " ist nicht mehr eingeladen.\n");
  rauswerfen(gast, jahr, projekt);
  return 1;
}

static int gaeste_cmd(string str) {
  string projekt;
  mixed *p;

  if (!(projekt = welches_projekt(str))) {
    return 1;
  }
  p = HOLODECKD->query_projekte(HOLODECKD->query_jahr())[projekt];

  if (!p) {
    write("Computer: Das Programm '" + projekt + "' gibt es nicht.\n");
    return 1;
  }
  write("Gaeste von " + projekt + ": "
        + (sizeof(p[1]) ? implode(map(sort_array(p[1], #'>), #'capitalize),
                                  ", ")
                        : "keine")
        + "\n");
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
  AddCmd("einladen", "einladen_cmd");
  AddCmd("ausladen", "ausladen_cmd");
  AddCmd("gaeste", "gaeste_cmd");
}
