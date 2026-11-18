// Letzte Aenderung:
//
//
// 09.12.2025 It@MagicMud              neu

#include "def.h"

inherit ROOM "std/std_raum";

static status wunsch;

#define MAX_CHAIR_USER   2

static mapping  Chair_user;   // Personen auf der Insel

static int personen = 0;
static int opfer    = 0;

/* ------------------------------------------------------------------------- */
private int chair_is_empty() {
/**  Prueft, ob die Insel leer ist. Falls ja, wird WAHR zurueckgegeben */
  return(sizeof(Chair_user) == 0 );
}

/* ------------------------------------------------------------------------- */
private int chair_is_full() {
/**  Prueft, ob die Insel voll besetzt ist. Falls ja, wird WAHR zurueck
 **  gegeben */
  return (sizeof(Chair_user) == MAX_CHAIR_USER);
}

/* ------------------------------------------------------------------------- */
private int num_of_chair_user() {
/**  Gibt die Anzahl der Leute zurueck, die auf der Insel sind. */
  return (sizeof(Chair_user));
}

/* ------------------------------------------------------------------------- */
private object* chair_user() {
/**  Gibt die Leute zurueck, die auf der Insel sind. */
  return ( m_indices( Chair_user));
}

/* ------------------------------------------------------------------------- */
private int pl_is_lazy(object pl) {
/**  Prueft, ob der der uebergebene Spieler auf der Insel ist (ob pl in der
 **  Liste der Spieler Chair_user enthalten ist). Falls ja, wird WAHR
 **  zurueck gegeben */
  return ( member( Chair_user, pl));
}

/* ------------------------------------------------------------------------- */
private string pl_name(object pl) {
/**  Gibt den Namen des uebergebenen Spielers zurueck bzw 'Du', falls der 
 **  handelnde Spieler uebergeben wird. */
  if (pl == this_player()) {
    return "Du";
  }
  return pl->Name( WER);
}

/* ------------------------------------------------------------------------- */
private void add_user(object u) {
/**  Spieler zur Liste der in der Wanne Sitzenden hinzufuegen. */
  if (pl_is_lazy( u) || chair_is_full())
    return;

  Chair_user = Chair_user + ([ u: 1]);
}

/* ------------------------------------------------------------------------- */
private void remove_user(object u) {
/**  Spieler aus der Liste der in der Wanne Sitzenden loeschen. */
  Chair_user = Chair_user - ([ u ]);
}

/* ------------------------------------------------------------------------- */
private int trage_prop_ein(object pl, string prop_s, string max_prop_s,
                            int min_wert, int aend) {
  int  wert, max_wert;

  max_wert = pl->QueryProp(max_prop_s);
  wert     = pl->QueryProp(prop_s);
  wert     = wert + aend;
  
  if (wert > max_wert) {
    wert = max_wert;
  }
  if (wert < min_wert) {
    wert = min_wert;
  }
  pl->SetProp(prop_s, wert);

  return wert;
}

void BecomesNetDead(object player) {
  personen -= 1;
  player->move((ROOM "see"),M_GO,"",
                "schwimmt netztot davon",
                "schwimmt netztot von der Insel runter");
}

void init() {
  ::init();
   personen += 1;

  if(personen >= 3) {
    write(break_string("Du schwimmst zu der kleinen Insel hin. Ein gutes "
    "Stueck davor siehst du, dass schon zwei Personen dort Platz genommen "
    "haben. Da du ja nicht stoeren moechtest, schwimmst du wieder "
    "zurueck."));

    this_player()->move(ROOM "raum1", M_GO|M_SILENT|M_NO_SHOW);
  }
  if(personen <= 2) {
    write(break_string("Du schwimmst zu der Insel und stellst mit Erstaunen "
    "fest, dass es nur ein Felsen ist, der aus dem Wasser ragt. Hastig "
    "kletters du hinauf."));
  }
}

varargs void exit() {
  ::exit();

  personen -= 1;
}


protected void reset() {
  ::reset();

  wunsch = 0;

  // random(100) = 0 bis 99
  if (random(100) < 50) {
    tell_room(this_object(),break_string(
      "Ploetzlich zieht ein Silberstreifen am Himmel entlang. Eine "
      "Sternschnuppe!"));
    
    wunsch = 1;
  }
}

protected void create() {
  ::create();
  SetProp(P_INT_SHORT,"Eine Felseninsel");
  SetProp(P_INT_LONG,
    "Du befindest dich auf einem Felsen der aus dem Wasser heraus ragt. "
    "Rings um dich herum ist der See. Es ist Nacht und der Himmel ist mit "
    "Sternen uebersaet. Der Mond leuchtet kalt am Himmel. Das Ufer ist "
    "ein ganzes Stueck entfernt.");

  SetProp(P_ENVIRONMENT,([
    ENV_TEMPERATURE:15,
    ENV_ENVSPEED   : 2,
    ENV_ENVSPEED   : 6,
  ]));
  SetProp(P_LIGHT,1);
  SetProp(P_INDOORS,0);
  SetProp(P_TERRAIN,T_AT_WATER);
  SetProp(P_T_WATERTEMP,TW_COLD);
  SetProp(P_T_WATERTYPE,TW_LAKE);
  
  wunsch = 0;

  /* Mapping der Personen vorbereiten, die spaeter in der Wanne sitzen werden
   * (Wannennutzer). */
  Chair_user = ([]);

  AddDetail(({"grund","seegrund"}),
  "Den Grund kannst du bei diesem Licht nicht erkennen.");
  
  AddDetail(({"welle","wellen"}),
  "Nein, hier gibt es nicht eine einzige Welle, die die Bilder der Sterne "
  "und des Mondes wanken laesst. Sei froh darueber. Solch ein Anblick ist "
  "selten zu finden!");
  
  AddDetail("wasseroberflaeche",
  "Sie ist voellig ruhig und klar. Nicht eine einzige Welle laesst die "
  "Bilder der Sterne und des Mondes, die sich darauf spiegeln, erzittern.");
  
  AddDetail(([
              "ruhiges#klares#dunkles#blaues#dunkelblaues":
              ({"wasser","seewasser","suesswasser","trinkwasser"})
            ]),
  "Das Wasser des Sees liegt hier ganz ruhig und klar vor dir. Keine "
  "Welle stoert die Ruhe die das Bild der Wasseroberflaeche dir bietet. "
  "Bis auf den Grund kannst du leider nicht sehen, dafuer spiegeln sich "
  "der Mond und die zahlreichen Sterne auf der Wasseroberflaeche.");
  
  AddDetail(([
              "himmlische":
              ({"ruhe"}),
            ]),
  "Eine himmlische Ruhe, du geniesst sie einfach.");
  
  AddDetail(([
              "naechtliches":
              ({"blau"})
            ]),
  "Das Wasser schimmert im naechtlichen Blau.");
  
  AddDetail(({"wal","wale","oval","vorbild"}), 
  "Trotz seines grossen Vorbilds im Wasser der Welt, ist das Sternenbild "
  "doch klein. Fuenf Sterne bilden ein kleines Oval.");
  
  AddDetail(({"efferdland","welt"}),
  "Die Welt... das Efferdland...");
  
  AddDetail(({"orkkind","orkkinder","kind","kinder"}), 
  "Kein anderes Sternenbild ist so kompakt wie dieses. Eine riesige "
  "Anzahl von Sternen formen sich zu einem Orkkind.");
  
  AddDetail(([
              "riesige#gewaltige#unzaehlbare":
              ({"zahl","anzahl"}),
            ]),
  "Gewaltig, riesig, unzaehlbar.");
  
  AddDetail(({"sonne"}),
  "Die Sonne sieht man selten bis gar nicht in der Nacht!");
  
  AddDetail(({"schlange","schlangen","schleife"}), 
  "Wie eine Schleife windet sich die Schlange ueber eine grosse Strecke "
  "des Himmels. Ihre Sterne leuchten in einem matten Weiss.");

  AddDetail(([
              "mattes#schoenes#kaltes":
              ({"weiss"}),
            ]),
  "Ein kaltes, schoenes, mattes Weiss.");
  
  AddDetail(([
              "grosse":
              ({"strecke","strecken"}),
              "kosmische":
              ({"massstaebe"}),
              "kosmischen":
              ({"masstab"}),
            ]),
  "In kosmischen Massstaeben ist diese Strecke einfach gigantisch. Von "
  "hier aus sieht sie alledings nur gross aus.");
  
  AddDetail(({"orion"}), 
  "Der Orion ist das hellste Sternenbild. Seine acht Sterne leuchten hell "
  "am naechtlichen Himmel.");

  AddDetail(({"bilder","sternenbilder", "sternenbild","bild"}),
  "Die meisten Sterne kannst du keinem Sternenbild zuordnen. Doch bei "
  "manchen erinnerst du dich. Als da waeren: Der Wal, das Orkkind, die "
  "weisse Schlange sowie der Orion.");

  AddDetail(({"stern","sterne"}),
  "Der ganze naechtliche Himmel ist mit Sternen uebersaeht. So gewaltig "
  "hast du diesen Anblick noch nie wahrgenommen. In manchen glaubst du "
  "dir bekannte Sternenbilder zu erkennen.");
  
  AddDetail(([
              "schwarzen#dunklen#klaren#sternenklaren":
              ({"himmel"}),
            ]),
  "Der Himmel bietet dir einen einmalig schoenen Anblick. Dominiert wird "
  "er von einem kalt leuchtenden Mond, umgeben von unzaehligen Sternen, "
  "von denen manche heller und andere wieder dunkler leuchten.");
  
  AddDetail(({"zwinkern","zwinker"}),
  "Als du genauer hinschaust siehst du tatsaechlich ein Zwinkern. Was ist "
  "das nur fuer ein seltsamer Ort, denkst du dir...");
  
  AddDetail(({"auge","augen"}),
  "Zwei ungleichfoermige Augen sehen auf dich hinab. Dir kommt es so vor, "
  "als haben sie dir gerade zugezwinkert.");

  AddDetail("mund",
  "Ein langer, breiter Mund, der anscheinend laechelt, zieht sich "
  "ueber den Mond.");
  
  AddDetail(({"nase","nasen"}),
  "Das was du fuer eine Nase gehalten hast ist tatsaechlich eine. "
  "Unwillkuerlich fragst du dich wie der Mond denn zu einer Nase kommt.");
  
  AddDetail(({"gesicht","mondgesicht"}),
  "Nase, Mund und Augen, all das siehst du. Insgesamt koennte man mit etwas "
  "Phantasie es fuer ein Laecheln halten. Oder ist es nur Einbildung?");

  AddDetail(({"laecheln"}),
  "Dieser Mond wird dir so langsam sympathisch.");
  
  AddDetail(({"fantasie","phantasie"}),
  "Die scheinst du zu haben.");
  
  AddDetail(({"einbildung"}),
  "Ist es wirklich eine?");
  
  AddDetail(([
              "hellen#leuchtenden":
              ({"mond"}),
            ]),
  "Der Mond leuchte kalt hoch oben am Himmel in seiner ganzen Pracht. Es "
  "scheint so, als will er dich glauben machen, sein Gesicht haette dir "
  "zugezwinkert. Aber das kann natuerlich nicht sein. Monde zwinkern "
  "nicht.");
  
  AddDetail(([
              "ganze#schoene#wunderschoene":
              ({"pracht"}),
              "":
              ({"anblick"}),
            ]),
  "Einfach wunderschoen...");
  
  AddDetail(([
              "tiefe#dunkle#schwarze#klare":
              ({"nacht"}),
            ]),
  "Es ist tiefste dunkle Nacht. Nein, nicht ganz, denn der Mond steht "
  "kalt leuchtend am Himmel und spendet Licht, so dass du sehen kannst.");
  
  AddDetail(([
              "klares#reines#kaltes#helles#kaltes":
              ({"licht","mondlicht","leuchten"}),
            ]),
  "Klar und rein spendet der Mond sein Licht zu dir herunter. Es reicht aus, "
  "um zu sehen, jedoch ist es nicht besonders hell. Genau die richtige "
  "Helligkeit fuer diese entspannende Gegend.");
  
  AddDetail("helligkeit",
  "Besonders hell ist es nicht gerade.");
  
  AddDetail(({"gegend","raum","ort","umgebung"}),
  "Die Gegend ist schlicht und ergreifend ueberwaeltigend. Nicht mehr und "
  "nicht weniger.");
  
  AddDetail(({"ufer","seeufer","stueck","ganzes stueck"}),
  "Du schaetzt den Durchmesser des Sees auf ungefaehr 2000 Schritte. Da der "
  "Felsen so etwa in der Mitte des Sees ist, duerfte das andere Ufer gute "
  "1000 Schritte von dir entfernt sein. Sehen kannst du das Ufer zwar "
  "schon, jedoch etwas genaueres zu erkennen ist dir nicht moeglich.");
  
  AddDetail(({"durchmesser"}),
  "2000 Schritte.");
  
  AddDetail(({"mitte","seemitte"}),
  "In der Mitte des Sees befindet sich ein Felsen und darauf stehst du "
  "momentan.");
  
  AddDetail(({"schritte","schritt"}),
  "Du machst einen Schritt und weisst nun ziemlich genau, wie lang der "
  "ist.");
  
  AddDetail(({"schwaene","schwan","gruppe"}),
  "Da draussen auf dem See schwimmt eine kleine Gruppe von Schwaenen ueber "
  "den See. Sind Schwaene wirklich so stolz wie ihr Anblick? Von dir "
  "scheinen sie keine weitere Notiz zu nehmen. Gemaechlich schwimmen sie "
  "mit einigem Abstand um den Felsen herum.");
  
  AddDetail(({"notiz"}),
  "Die Schwaene ignorieren dich. Wahrscheinlich bist du ihnen nicht "
  "wichtig genug.");
  
  AddDetail("see",
  "Der See, der den Felsen umschliesst, liegt ruhig vor dir. Sein Wasser "
  "schimmert in einem dunklen Blau und kaum eine Welle zieht ihren Weg "
  "durch die Wasseroberflaeche. In einiger Entfernung siehst du wie ein "
  "paar Schwaene ueber den See schwimmen.");
  
  AddDetail(({"weg","wege"}),
  "Ein Weg? Hier auf diesen Felsen? Traeum weiter...");
  
  AddDetail(({"entfernung","entfernungen","abstand","abstaende"}),
  "Zu weit weg, um sie mit der Hand zu erreichen.");
  
  AddDetail(({"hand","haende"}),
  "Deine Haende werden gemeint sein und die kennst du bereits...");
  
  AddDetail(({"plattform","halt","platz"}),
  "Die kleine Plattform ist dicht am Wasser. Auf ihr koennen bis zu zwei "
  "Personen Platz finden und einer davon bist gerade du. Etwas Halt "
  "bietet die Plattform schon, aber aufpassen solltest du schon ein "
  "bischen, dass du nicht wieder ins Wasser faellst.");
  
  AddDetail(({"person","personen"}),
  "Personen wie du...");
  
  AddDetail(({"stein","gestein","gesteins"}), 
  "Natuerlich besteht der Felsen aus Gestein. Welches Gestein das ist, "
  "kannst du mit deinen Kenntnissen nicht herausbekommen. Es sieht "
  "jedenfalls ziemlich alt aus.");

  AddDetail("kenntnisse",
  "Du untersuchst deine Kenntnisse genau, findest allerdings nichts neues. "
  "Woran das wohl liegen mag?");
  
  AddDetail(({"fels","felsen","boden","fussboden"}), 
  "Der Felsen ragt ca. vier Meter aus dem See hervor. Seine Oberflaeche "
  "ist glatt und rutschig. An einigen Stellen des Gesteins siehst du "
  "Risse. Auf einer kleinen Plattform ist Platz fuer zwei Personen. Auf "
  "dieser befindest du dich gerade.");

  AddDetail(({"sand"}), 
  "Der Sand in den Rissen ist wohl sicherlich vom Wasser, wenn es denn mal "
  "den Felsen ueberdeckt, angeschwemmt worden. Der Sand hat sich in den "
  "Rissen abgelagert.");

  AddDetail( ({ "riss","risse" }), 
  "Die Risse sind nicht besonders tief. Sie sind mit nassem Sand gefuellt.");

  AddDetail( ({ "stelle","stellen" }), 
  "Einige wenige Risse ziehen sich durch den Felsen.");

  AddDetail(({"flaeche","oberflaeche"}),
  "Die Oberflaeche des Felsen ist glatt und rutschig. An einigen Stellen "
  "hat die Oberflaeche schon Risse, die vermutlich auf ein sehr hohes "
  "Alter deuten lassen.");

  AddDetail(({"alter"}),
  "Du kannst das Alter nicht einmal schaetzen, schliesslich bist du kein "
  "Fachmann.");
  
  AddDetail(({"fachmann"}),
  "Bist du nicht.");
  
  AddDetail(({"wolke","wolken"}),
  "Der Himmel ist sternenklar. Also scheinen dort oben keine Wolken zu "
  "sein.");
  
  AddSound(({"rauschen","welle","wellenrauschen","wellen"}),
  "Wo keine Wellen sind koennen Wellen auch kein Laerm machen.");

  AddSound(({"wind","hauch","windhauch"}),
  "Nicht der geringste Windhauch ist zu hoeren, geschweige denn "
  "ein Wellenrauschen.");
  
  AddSound(({DEFAULT_SOUND,"raum","ort","umgebung"}),
  "Absolute Stille umgibt dich. Du hoerst nicht den leisesten Windhauch "
  "pfeiffen.");
  
  AddSmell("frische",
  "Tief atmest du die Frische in deine Nase ein. Du vergisst fuer einen "
  "kurzen Moment alles um ich herum und schwebst auf einer kleinen Wolke.");
  
  AddSmell(({"luft","meeresluft","meer","see","sternensee"}),
  "Die Luft riecht so frisch wie Meeresluft nur sein kann, nur, wo ist das "
  "Meer? Es ist schon seltsam wie ein kleiner See riechen kann. "
  "Jedenfalls wird deine Nase mit einer Frische umworben, wie sie dir "
  "nur aus alten Geschichten bekannt ist, da wo Held sowieso mit "
  "Prinzessin sowieso verliebt ueber die Wiese reiten.");
  
  AddSmell(({DEFAULT_SMELL,"raum","ort","umgebung"}),
    "Frische umwirbt deine Nase.");


  AddCmd( ({"schwimm","schwimme"}), "cmd_schwimmen" );
  AddCmd( ({"fuetter","fuettere"}), "cmd_fuettern" );
  AddCmd( ({"zaehl", "zaehle"}), "cmd_zaehlen" );
  AddCmd( ({"spring", "springe"}), "cmd_springen");
  AddCmd( ({"plansch", "plansche", "planschen"}), "cmd_planschen");
  AddCmd( ({"spritz", "spritze", "spritzen"}), "cmd_spritzen");
  AddCmd( ({"trinke", "trink","sauf","saufe"}), "cmd_trinken");
  AddCmd( ({"kletter", "kletter","klettre"}), "cmd_klettern");
  AddCmd( ({"tauchen", "tauche"}), "cmd_tauchen");
  AddCmd( ({"wuensch", "wuensche"}), "cmd_wuenschen");
}

private int check_inventory( object pl)

/**  Testet, ob der Spieler, der auf der Insel sitzen moechte, etwas traegt
 **  oder eine Waffe gezueckt hat.
 **  Rueckgabewerte:   0  Keine Kleidung, keine Waffe
 **                   -1  Spieler traegt Ruestung
 **                   -2  Waffe gezueckt.  */
{
  int     i1, anz_inv;
  object  *inv;

  inv = all_inventory( pl);
  for (i1 = 0; i1 < sizeof( inv); ++i1)
  {
    if (inv[i1]->QueryProp( P_WORN) != 0)
    {
      /*  Ringe, Amulette und Ketten zulassen */
      if (!inv[i1]->id( "ring")     &&
          !inv[i1]->id( "ehering")  &&
          !inv[i1]->id( "amulett")  &&
          !inv[i1]->id( "kette"))
      {
        return -1;
      }
    }
    if (inv[i1]->QueryProp( P_WIELDED) != 0)
    {
      return -2;
    }
  }

  return 0;
}

/* ------------------------------------------------------------------------- */
private int check_users()

/**  Testet, ob die Spieler, die im Mapping stehen, tatsaechlich noch da
 **  sind. Falls, nicht, werden sie aus dem Mapping entfernt. */
{
  int     i1, anz_user;
  object  *user;

  anz_user = num_of_chair_user();
  user     = m_indices( Chair_user);

  for (i1 = anz_user-1; i1 >= 0 ; --i1)
  {
    if (!present( user[i1]))
    {
      Chair_user = Chair_user - ([ user[i1] ]);
    }
  }

  return 1;
}

/* ------------------------------------------------------------------------- */

static int cmd_schwimmen(string s)  {
  notify_fail("Wohin moechtest Du schwimmen?\n");
  
  if(!s) {
    return 0;
  }
  switch(s) {
    case "ufer":
    case "land":
    case "festland":
    case "zum ufer":
      say(break_string(this_player()->Name(WER)+" schwimmt von dem Felsen "
      "weg."));
  
      this_player()->move((ROOM "raum2"),M_GO|M_SILENT);
      
      say(break_string(this_player()->Name(WER)+" kommt an."));
      
      return 1;
      break;

    case "see":
    case "sernensee":
    case "in see":
    case "in sternensee":
      say(break_string(this_player()->Name(WER)+" schwimmt eine Weile im See "
      "herum."));
  
      write(break_string(
      "Du springst in das doch recht kuehle Wasser und schwimmst ein "
      "bischen herrum. Manchmal kommt einer der Schwaene etwas naeher zu "
      "dir heran und schaut dich mit grossen Augen an, so als wolle er etwas "
      "von dir. Als du schliesslich wieder heraus kommst ist dir ziemlich "
      "kalt. Hast du denn etwas zum Aufwaermen dabei?"));
      return 1;
      break;
  }
  return 0;
}

static int cmd_fuettern(string s) {
  notify_fail("Wen moechtest Du fuettern?\n");

  if ((s!="schwan") && (s!="schwaene")) {
    return 0;
  }
  say(break_string(this_player()->Name(WER)+" fuettert die Schwaene."));
  
  write(break_string(
  "Du holst ein Stueck Brot hervor und haeltst es auffordernd in die "
  "Richtung der Schwaene. Ein besonders grosses Mitglied der Gruppe "
  "laesst sich nicht lange bitten, schwimmt herbei und nimmt dir das "
  "Brot dankbar ab. Gemessen schwimmt er zurueck auf den See."));

  return 1;
}

static int cmd_zaehlen(string s) {
  notify_fail("Was moechtest du zaehlen?\n");

  if ((s!="sterne") && (s!="stern")) {
    return 0;
  }
  say(break_string(this_player()->Name(WER)+" scheint am Himmel "
  "etwas zu suchen."));
  
  write(break_string(
  "Du schaust zum Himmel hoch und faengst an, die Sterne zu zaehlen. Eins, "
  "zwei, drei ... sechshundertachtundvierzig ... eintausend und fuenf ... "
  "Nach einer ganzen Weile hoerst du wieder auf, denn du bist langsam "
  "erschoepft und hast nur einen ganz kleinen Teil durchzaehlen koennen."));

  return 1;
}

static int cmd_springen( string s) {
  int     check;
  object  tp;

  check_users();
  tp = this_player();

  notify_fail("Wohin moechtest Du springen?\n");

  if(!s || member(combine_mapping(([
                                    "in":
                                    ({"see","sternensee","wasser"})
                                  ])),s) == -1) {
    return 0;
  }
  check = check_inventory(tp);
  
  if (tp->QueryProp( P_GHOST) != 0) {
    write(break_string( "Als Geist hast du mit Wasser nicht viel am Hut."));
  }
  else if (check == -1) {
    write( break_string( "Seit wann springt man denn angezogen ins Wasser?"));
  }
  else if (check == -2) {
    write( break_string( "Mit einer Waffe ins Wasser springen wollen... "
    "Jaja, aber nicht hier du..."));
  }
  else {
    add_user(tp);
   
    write( break_string( "Du springst in das kuehle Nass und schwimmst ein "
    "paar Runden im See. Nach einer kurzen Weile wird dir kalt und du "
    "kletters wieder auf den Felsen hinauf."));
    
    say( break_string( MakeString( "##NamU1n## springt ploetzlich in den See "
    "und spritzt dich dabei voellig nass. Dann schwimmt ##pron1n## "
    "ein paar Runden und kommt mit blauen Lippen wieder auf den Felsen "
    "geklettert.", tp)));
  }

  return 1;
}

static int cmd_planschen( string str) {
  check_users();
  
  write(break_string("Du planschst mit den Fuessen im kalten Wasser."));
  
  say(break_string( MakeString( "##NamU1n## planscht mit den Fuessen im "
      "kalten Wasser.", this_player())));
  
  return 1;
}

static int cmd_tauchen(string s) {
  check_users();

  notify_fail("Wohin moechtest du tauchen?\n");

  if(!s || member(combine_mapping(([
                                    "in":
                                    ({"wasser","see","sernensee"})
                                  ])),s) == -1) {
    return 0;
  }
  write(break_string(
  "Du springst in das kalte Wasser des Sees und tauchst unter. Die"
  "Sicht unter Wasser ist durch das klare Wasser maessig gut, aber es"
  "reicht um ein bischen zu sehen. Du tauchst so tief hinunter wie du"
  "kannst, wobei die Sicht immer schlechter wird. Ploetzlich spuerst du"
  "auf deinem Arm eine erstaunlich warme Beruehrung. Huch! Was das wohl sein "
  "mag? Erstaunt schaust du zur Seite und hinter dich, aber was du da siehst "
  "beruhigt dich gar nicht... Ein seltsames Wesen, anscheinend aus Wasser "
  "bestehend, sich dauernd veraendernd, schaut dich an. Der Blick strahlt "
  "unsagbar viel Gelassenheit aus. Langsam wirst du etwas ruhiger, denn "
  "anscheinend will dieses Wesen dir nichts boeses antun. Als du voellig "
  "zur Ruhe gekommen bist und gar nicht mehr merkst wie die Zeit "
  "verstreicht, redet es zu dir")+
  
  "\nIch habe auf dich gewartet. Ich bin hier, um dir etwas "
  "auszurichten...\n\n"+
  
  "VERSUCH DEIN GLUECK!\n\n"+
  
  "Das ist alles was ich zu sagen habe.\n\n"+
  
  break_string(
  "So ploetzlich wie das Wesen gekommen ist, ist es auch wieder "
  "verschwunden. Du spuerst wieder das kalte Wasser auf deiner Haut und so "
  "langsam wird dir klar, was dich eben besucht hat, eine Undine. Das war "
  "aber knapp... Schnell tauchst du wieder auf und kletterst auf den "
  "Felsen."));

  say(break_string(MakeString("##NamU1n## springt in den See hinein und "
     "kommt nach einer kurzen Weile wieder auf den Felsen geklettert.",
     this_player())));

  return 1;
}

static int cmd_trinken(string s) {
  check_users();

  notify_fail("Was moechtest du trinken?\n");

  if(!s || member(combine_mapping(([
                                    "aus#wasser aus":
                                    ({"see","sternensee"}),
                                    "":
                                    ({"wasser"})
                                  ])),s) == -1) {
    return 0;
  }
  say(break_string( MakeString( "##NamU1n## beugt sich hinunter "
  "und trinkt einen Schluck Wasser aus dem See. Es scheint ##NamU1n## "
  "gut zu schmecken.", this_player())));

  write(break_string(
  "Du beugst dich nach vorne und schoepfst mit deinen Haenden eine "
  "Handvoll Wasser aus dem See. Genuesslich trinkst du es. "
  "Einmalig schmeckt es dir."));
  
  return 1;
}

static int cmd_klettern(string s) {
  check_users();

  notify_fail("Wohin moechtest du klettern?\n");

  if(!s || member(combine_mapping(([
                    "nach":
                    ({"oben"}),
                    "auf":
                    ({"fels","felsen","spitze","felsspitze"}),
                    "":
                    ({"hoch","rauf","hinauf"}),
                  ])),s) == -1) {
    return 0;
  }
  say(break_string( MakeString( "##NamU1n## klettert auf den Felsen hoch und "
      "kommt mit enttaeuschter Miene wieder herunter.", this_player())));

  write(break_string("Du kletterst auf den Felsen hoch. Dort oben findest du "
        "jedoch nichts besonderes und kletterst enttaeuscht wieder "
        "herunter."));

  return 1;
}

static int cmd_spritzen(string str) {
  object pl;

  check_users();

  if (!str) {
    write( break_string("Du spritzt etwas herum."));
    say(break_string(MakeString("##NamU1n## spritzt etwas herum.",
                                this_player())));
  }
  else {
    pl = find_player( str);

    if (!pl || environment( pl) != environment( this_player())) {
      write( break_string( "Diese Person kannst Du hier nicht sehen."));
    }
    else {
      write( break_string( MakeString( "Du spritzt ##namB1a## voll.", pl)));
      
      say(break_string( MakeString( "##NamU1n## spritzt ##namU2d## voll.",
          this_player(), pl)), pl);
      
      tell_object(pl,break_string( MakeString( "##NamU1n## spritzt Dich"
                     " voll.", this_player())));
    }
  }
  return 1;
}

static int cmd_wuenschen(string s) {
  if (wunsch==1) {
    write(break_string("Du machst die Augen zu, drueckst dir selbst die "
          "Daumen und wuenschst dir etwas. Ob es wohl in Erfuellung gehen "
          "mag?"));
    
    say(break_string(this_player()->name(WER)+ " schliesst die Augen "
        "fuer einen kurzen Moment."));

    wunsch = 0;
  }
  else {
    write(break_string("Wuensche haben wir alle."));
  }
  return 1;
}
