// lehrerkonsole.c - Verwaltung der Holodeck-Projekte, nur fuer Lehrer
//
// Steht in der Kapitaenskajuete [-1+2+0] und im Workroom der Lehrer:
//   AddItem("/d/raumschiff/obj/lehrerkonsole", REFRESH_DESTRUCT);
//
// Letzte Aenderung:
//
// 19.11.2026 It@Efferdland            aus holokonsole.c ausgelagert
// 19.11.2026 It@Efferdland            Ausgaben mit /std/util/anzeige

#pragma strong_types
#pragma save_types
#pragma rtt_checks

#include "../region.h"

#include <anzeige.h>
#include <moving.h>

inherit "/std/thing";
inherit "/std/util/anzeige";

#define SP_HILFE  ({ ({ 34, "<" }), ({ 0, "<" }) })
#define SP_LISTE  ({ ({ 16, "<" }), ({ 8, "<" }), ({ 20, "<" }), \
                     ({ 0, "<" }) })

static string lehrer_hilfe() {
  return
    linie_voll()
  + rahmen_titel("Lehrerpult", "Schuljahr " + HOLODECKD->query_jahr())
  + tabellen_linie(SP_HILFE)
  + tabellen_kopf(SP_HILFE, ({ "Befehl", "Bedeutung" }))
  + tabellen_linie(SP_HILFE)
  + tabellen_zeile(SP_HILFE, ({ "holo liste [<schuljahr>]",
                                "Projekte mit Team und Gaesten" }))
  + tabellen_zeile(SP_HILFE, ({ "holo jahr <schuljahr>",
                                "Schuljahr wechseln (z.B. 2627)" }))
  + tabellen_zeile(SP_HILFE, ({ "holo neu <projekt>",
                                "Projekt aus Vorlage anlegen" }))
  + tabellen_zeile(SP_HILFE, ({ "holo loesche <projekt>",
                                "Projekt samt Dateien loeschen" }))
  + tabellen_zeile(SP_HILFE, ({ "holo team <projekt> + <name> ...",
                                "Schueler ins Team aufnehmen" }))
  + tabellen_zeile(SP_HILFE, ({ "holo team <projekt> - <name> ...",
                                "Schueler aus dem Team nehmen" }))
  + tabellen_zeile(SP_HILFE, ({ "holo klasse <projekt> <klasse>",
                                "ganze Klasse ins Team aufnehmen" }))
  + tabellen_zeile(SP_HILFE, ({ "holo sperre <projekt> an|aus",
                                "Schreibschutz fuer das Team" }))
  + tabellen_linie(SP_HILFE);
}

// P_LONG wird nicht ueber schreibe() ausgegeben
static string pult_long() {
  if (PL && IS_TEACHER(PL)) {
    return anzeige_text(lehrer_hilfe());
  }
  return "Ein schmales Pult mit einem Schild: 'Nur fuer Lehrer'.\n";
}

static string liste(string jahr) {
  mapping l = HOLODECKD->query_projekte(jahr);
  string ret;

  ret = linie_voll()
      + rahmen_titel("Holodeck-Projekte", "Schuljahr " + jahr);

  if (!sizeof(l)) {
    return ret
         + linie_voll()
         + rahmen_text("Keine Projekte in diesem Schuljahr.")
         + linie_voll();
  }
  ret += tabellen_linie(SP_LISTE)
       + tabellen_kopf(SP_LISTE, ({ "Projekt", "Status", "Team",
                                     "Gaeste" }))
       + tabellen_linie(SP_LISTE);

  foreach (string name : sort_array(m_indices(l), #'>)) {
    mixed *p = l[name];

    ret += tabellen_zeile(SP_LISTE, ({
             name,
             p[2] ? FARBE_GELB "gesperrt" FARBE_AUS : " ",
             sizeof(p[0]) ? implode(map(p[0], #'capitalizeAfterDot), ", ") : "-",
             sizeof(p[1]) ? implode(map(p[1], #'capitalizeAfterDot), ", ") : "-" }));
  }
  return ret
       + tabellen_linie(SP_LISTE)
       + rahmen_text("Schuljahre: "
                     + implode(HOLODECKD->query_schuljahre(), ", "))
       + linie_voll();
}

#define HOLORAUM  "/d/raumschiff/room/[-3+0-1]"

// Wer gerade im Projekt steht, kommt zurueck ins Holodeck
static void deck_raeumen(string dir) {
  foreach (object pl : users()) {
    string wo;

    if (!environment(pl)) {
      continue;
    }
    wo = object_name(environment(pl));

    if (sizeof(wo) && wo[0] != '/') {
      wo = "/" + wo;
    }
    if (wo[0..sizeof(dir)] == dir + "/") {
      tell_object(pl, break_string("Computer: Dieses Programm wird "
                  "geloescht. Die Umgebung loest sich auf und du stehst "
                  "wieder im Holodeck.", 78));
      pl->move(load_object(HOLORAUM), M_TPORT | M_NOCHECK);
    }
  }
}

static void loesche_antwort(string antwort, string projekt) {
  string dir;

  if (!PL || !IS_TEACHER(PL)) {
    return;
  }
  if (lower_case(antwort || "") != "ja") {
    write("Computer: Abgebrochen, nichts geloescht.\n");
    return;
  }
  if (dir = HOLODECKD->query_projekt_dir(HOLODECKD->query_jahr(), projekt)) {
    deck_raeumen(dir);
  }
  write(break_string("Computer: "
        + HOLODECKD->projekt_loeschen(projekt), 78));
}

static int loesche_fragen(string projekt) {
  string dir = HOLODECKD->query_projekt_dir(HOLODECKD->query_jahr(), projekt);

  if (!dir) {
    write("Computer: Das Projekt " + projekt + " gibt es nicht.\n");
    return 1;
  }
  write(break_string("ACHTUNG: Das Projekt " + projekt + " wird samt ALLEN "
        "Dateien in " + dir + " geloescht. Das laesst sich nicht "
        "rueckgaengig machen.", 78)
        + "Wirklich loeschen? (ja/nein) ");
  input_to("loesche_antwort", 0, projekt);
  return 1;
}

static int holo_cmd(string str) {
  string *arg, msg;

  if (!PL || !IS_TEACHER(PL)) {
    return 0;
  }
  arg = str ? explode(str, " ") - ({""}) : ({});

  if (!sizeof(arg) || arg[0] == "hilfe") {
    schreibe(lehrer_hilfe());
    return 1;
  }
  switch (arg[0]) {
    case "liste":
      schreibe(liste(sizeof(arg) > 1 ? arg[1] : HOLODECKD->query_jahr()));
      return 1;

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
        return loesche_fragen(lower_case(arg[1]));
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
    schreibe(lehrer_hilfe());
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
  thing::create();
  SetProp(P_NAME, "Lehrerpult");
  SetProp(P_GENDER, NEUTER);
  SetProp(P_SHORT, "Ein Lehrerpult");
  Set(P_LONG, #'pult_long, F_QUERY_METHOD);
  SetProp(P_NOGET, "Das Pult ist fest im Boden verankert.\n");
  SetProp(P_WEIGHT, 100000);
  AddId(({"pult", "lehrerpult", "lehrerkonsole"}));

  AddCmd("holo", "holo_cmd");
}
