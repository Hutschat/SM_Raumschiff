// holokonsole.c - Holodeck-Konsole fuer alle
//
//   projekte [frei|<schuljahr>]          Liste mit Team und Zutritt
//   lade <nr|projekt> [<schuljahr>]      Deck betreten
//
// Nur Teammitglieder (aktuelles Schuljahr):
//   einladen <name> [in <nr|projekt>]    Charakter als Gast zulassen
//   ausladen <name> [aus <nr|projekt>]   Gast entfernen (fliegt raus)
//   gaeste [<nr|projekt>]                Gaesteliste
//
// Jedes Deck ist fuer andere geschlossen, bis das Team jemanden einlaedt.
// Lehrerbefehle: projekt/projekte in der Lehrer-Shell (mod_mag_holodeck.c)
//
// Letzte Aenderung:
//
// 18.11.2026 It@Efferdland            neu
// 19.11.2026 It@Efferdland            Gaeste, Lehrerbefehle ausgelagert
// 19.11.2026 It@Efferdland            Ausgaben mit /std/util/anzeige

#pragma strong_types
#pragma save_types
#pragma rtt_checks

#include "../region.h"
#include <moving.h>
#include <anzeige.h>

inherit "/std/thing";
inherit "/std/util/anzeige";

#define START_RAUM    "/room/raum1"
#define KOMMUNIKATOR  "/d/raumschiff/obj/kommunikator"
#define HOLORAUM      "/d/raumschiff/room/[-3+0-1]"

#define SP_HILFE ({ ({ 32, "<" }), ({ 0, "<" }) })

static string hilfe() {
  return
    linie_voll()
  + rahmen_titel("Holodeck-Konsole", "")
  + tabellen_linie(SP_HILFE)
  + tabellen_kopf(SP_HILFE, ({ "Befehl", "Bedeutung" }))
  + tabellen_linie(SP_HILFE)
  + tabellen_zeile(SP_HILFE, ({ "projekte [frei|<schuljahr>]",
                                "Programme mit Team und Zutritt" }))
  + tabellen_zeile(SP_HILFE, ({ "lade <nr> [<schuljahr>]",
                                "Programm starten" }))
  + tabellen_linie(SP_HILFE)
  + rahmen_titel("Fuer Teammitglieder", "")
  + tabellen_linie(SP_HILFE)
  + tabellen_kopf(SP_HILFE, ({ "Befehl", "Bedeutung" }))
  + tabellen_linie(SP_HILFE)
  + tabellen_zeile(SP_HILFE, ({ "einladen <name> [in <nr>]",
                                "Charakter auf dein Deck lassen" }))
  + tabellen_zeile(SP_HILFE, ({ "ausladen <name> [aus <nr>]",
                                "Einladung zuruecknehmen" }))
  + tabellen_zeile(SP_HILFE, ({ "gaeste [<nr>]",
                                "Wer ist eingeladen?" }))
  + tabellen_linie(SP_HILFE);
}

// P_LONG wird nicht ueber schreibe() ausgegeben
static string konsole_long() {
  return break_string(
    "Eine schraeg gestellte Konsole mit leuchtenden Schaltflaechen. Ueber "
    "ihr steht in grossen Lettern 'HOLODECK'.", 78)
    + anzeige_text(hilfe());
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
    projekt = HOLODECKD->projekt_name(HOLODECKD->query_jahr(), projekt)
              || lower_case(projekt);

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

// Nummer und Projekt in einer Spalte: Tabellenspalten sind mindestens
// 6 Zeichen breit, die Nummer braucht nur 3 ("%3s projekt").
#define SP_PROJEKTE ({ ({ 24, "<" }), ({ 7, "<" }), ({ 8, "<" }), \
                       ({ 0, "<" }) })

// Projektnamen nach Nummer sortiert
static int nr_groesser(string a, string b, mapping liste) {
  return liste[a][3] > liste[b][3];
}

static string *nach_nummer(mapping liste) {
  return sort_array(m_indices(liste), #'nr_groesser, liste);
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
  ret = linie_voll()
      + rahmen_titel(nur_frei ? "Holodeck-Programme mit Zutritt"
                              : "Holodeck-Programme",
                     "Schuljahr " + jahr)
      + tabellen_linie(SP_PROJEKTE)
      + tabellen_kopf(SP_PROJEKTE, ({ " Nr Projekt", "Zutritt",
                                       "Status", "Team" }))
      + tabellen_linie(SP_PROJEKTE);

  foreach (string name : nach_nummer(liste)) {
    mixed *p = liste[name];
    string z = zutritt(p);

    if (nur_frei && z == "-") {
      continue;
    }
    ret += tabellen_zeile(SP_PROJEKTE, ({
             sprintf("%3s %s", to_string(p[3]), name),
             z == "-" ? FARBE_ROT + z + FARBE_AUS
                      : FARBE_GRUEN + z + FARBE_AUS,
             p[2] ? FARBE_GELB "gesperrt" FARBE_AUS : " ",
             sizeof(p[0]) ? implode(map(p[0], #'capitalizeAfterDot), ", ") : "-" }));
  }
  schreibe(ret
           + tabellen_linie(SP_PROJEKTE)
           + rahmen_text("Starten mit: lade <nr>, z.B. lade 1")
           + linie_voll());
  return 1;
}

// Jede Zeile rot markieren (Farbe nur bei ANSI, siehe anzeige_text)
static string rot_zeile(string zeile) {
  return sizeof(zeile) ? FARBE_ROT + zeile + FARBE_AUS : zeile;
}

static string rot(string text) {
  return implode(map(explode(text, "\n"), #'rot_zeile), "\n");
}

static int lade_cmd(string str) {
  string projekt, jahr, dir, err;
  object raum, kom;

  notify_fail("Syntax: lade <nr> [<schuljahr>]\n");

  if (!str) {
    return 0;
  }
  if (sscanf(str, "%s %s", projekt, jahr) != 2) {
    projekt = str;
    jahr    = HOLODECKD->query_jahr();
  }
  projekt = HOLODECKD->projekt_name(jahr, projekt) || lower_case(projekt);

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

  // Hinweis VOR dem move, damit er ueber der Raumbeschreibung steht
  tell_object(PL, anzeige_text(rot(break_string("ZURUECK INS HOLODECK "
              "KOMMST DU JEDERZEIT MIT DEINEM KOMMUNIKATOR: 'ENDE PROGRAMM' "
              "ODER 'COMPUTER, ENDE'."))) + "\n");

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

  notify_fail("Syntax: einladen <name> [in <nr>]\n");

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
  write("Computer: " + capitalizeAfterDot(gast) + " darf jetzt das Programm "
        + projekt + " betreten.\n");

  if (pl = find_player(lower_case(gast))) {
    tell_object(pl, break_string(capitalizeAfterDot(getuid(PL)) + " hat dich auf "
                "das Holodeck-Programm " + projekt + " eingeladen. Starten "
                "kannst du es an der Holodeck-Konsole mit 'lade " + projekt
                + "'.", 78));
  }
  return 1;
}

static int ausladen_cmd(string str) {
  string gast, projekt, jahr = HOLODECKD->query_jahr();
  mixed res;

  notify_fail("Syntax: ausladen <name> [aus <nr>]\n");

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
  write("Computer: " + capitalizeAfterDot(gast) + " ist nicht mehr eingeladen.\n");
  rauswerfen(gast, jahr, projekt);
  return 1;
}

// "C.hansen, M.meyer"
static string namen_liste(string *namen) {
  return implode(map(sort_array(namen, #'>), #'capitalizeAfterDot), ", ");
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
  schreibe(linie_voll()
           + rahmen_titel(projekt + " (Nr. " + to_string(p[3]) + ")",
                          "Schuljahr " + HOLODECKD->query_jahr())
           + linie_voll()
           + rahmen_text("Team (" + sizeof(p[0]) + "):   "
                         + (sizeof(p[0]) ? namen_liste(p[0]) : "-"))
           + rahmen_text("Gaeste (" + sizeof(p[1]) + "): "
                         + (sizeof(p[1]) ? namen_liste(p[1])
                                         : "noch niemand eingeladen"))
           + linie_voll());
  return 1;
}

protected void create() {
  if (!clonep()) {
    set_next_reset(-1);
    return;
  }
  thing::create();
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
