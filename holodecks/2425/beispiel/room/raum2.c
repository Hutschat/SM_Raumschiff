// raums.c
//
// Letzte Aenderung:
//
// 09.12.2025 It@MagicMud              neu

#include "def.h"

inherit ROOM "std/std_raum";

static mapping blumen = ([
  "orkveilchen"      : 1,
  "himmelsschluessel": 1,
  "kaiserknopf"      : 1,
  "wiesenschaumkraut": 1,
]);

static int wunsch = time()+60;

static void reset_objects() {
  blumen = ([
    "orkveilchen"      : 1,
    "himmelsschluessel": 1,
    "kaiserknopf"      : 1,
    "wiesenschaumkraut": 1,
  ]);
}

protected void reset() {
  ::reset();
  reset_objects();

  if (random(100) < 50) {
    tell_room(this_object(),break_string("Ploetzlich zieht ein Silberstreifen "
              "am Himmel entlang. Eine Sternschnuppe!"));
    
    wunsch = time()+60;
  }
}

protected void create() {
  ::create();
  reset_objects();

  SetProp(P_LIGHT,1);
  SetProp(P_INDOORS,0);
  SetProp(P_INT_SHORT,"Am Sternensee");
  SetProp(P_INT_LONG,
  "Du stehst auf einer gruenen Wiese am Ufer eines grossen Sees. Es ist "
  "ploetzlich Nacht und keine Wolke ist am Himmel. Abertausende von Sternen "
  "uebersaeen den Himmel. Inmitten der Sterne leuchtet der Mond in seiner "
  "ganzen Pracht. Auf der Wiese wachsen die verschiedensten Blumen. Ihr Duft "
  "streichelt deine Nase. In einiger Entfernung schwimmt eine Gruppe "
  "Schwaene auf dem See. In der Mitte des Sees liegt eine kleine Insel.");  

  SetProp(P_TERRAIN,T_PLAIN|T_MEADOW|T_AT_WATER);
  
  SetProp(P_T_WATERTEMP,TW_COLD);
  SetProp(P_T_WATERTYPE,TW_LAKE);
  
  AddItem(POOL_NPC_ANIMAL "frosch", REFRESH_DESTRUCT);
  
  AddDetail(({"boden","fussboden"}),
  "Der Boden besteht aus weichem Gras.");

  AddDetail("nacht",
  "Es ist Nacht und der Himmel ist wolkenlos. Durch das helle Leuchten "
  "des Mondes kannst du jedoch sehen.");
  
  AddDetail(({"wolke","wolken"}),
  "Es sind keine Wolken zu sehen. Der Himmel ist sternenklar.");

  AddDetail("stengel",
  "Der Stengel ist lang und duenn.");
  
  AddDetail("blaetter",
  "Die Blaetter des Wiesenschaumkrauts und des Himmelsschluessels sind "
  "sich einander gar nicht aehnlich.");
  
  AddDetail(({"oberflaeche","wasseroberflaeche"}), 
  "Die Wasseroberflaeche ist ziemlich ruhig. Die Sterne und der Mond "
  "spiegeln sich darauf. Ein himmlischer Anblick.");

  AddDetail(({"felsen","fels"}), 
  "Du siehst zwar das es ein Felsen ist, der dort aus dem See ragt, jedoch, "
  "um mehr zu sehen muesstest du schon hinschwimmen.");

  AddDetail(({"ufer","seeufer"}), 
  "Das Ufer der kleinen Insel ist von hier zwar zu erkennen, aber mehr auch "
  "nicht.");
  
  AddDetail(({"wal","oval"}), 
  "Trotz seines grossen Vorbilds im Wasser der Welt, ist das Sternbild "
  "doch klein. Drei Sterne bilden ein kleines Oval.");

  AddDetail(({"vorbild"}),
  "Den Wal.");

  AddDetail(({"duft","geruch"}),
  "Den Duft sieht man nicht, man kann ihn aber deutlich riechen.");
  
  AddDetail(({"welt"}),
  "Diese Welt ist gemeint...");
  
  AddDetail(({"orkkind","kind"}), 
  "Kein anderes Sternbild ist so kompakt wie das Orkkind. Eine riesige "
  "Anzahl von Sternen formen sich zu einem Orkkind.");

  AddDetail(({"schlange","schleife"}), 
  "Wie eine Schleife windet sich die Schlange ueber eine grosse Strecke "
  "des Himmels. Ihre Sternen leuchten in einem matten Weiss.");

  AddDetail(({"orion"}), 
  "Der Orion ist das hellste Sternbild. Seine acht Sterne leuchten hell am "
  "naechtlichen Himmel.");
  
  AddDetail(({"kontur","konturen"}), 
  "Die Konturen der Spiegelbilder sind nicht ganz klar, da kleine Wellen "
  "sie verzerren.");

  AddDetail(({"bewegung"}), 
  "Ja, sie bewegen sich tatsaechlich, zumindestens sieht es so aus.");

  AddDetail(({"wellen","welle"}), 
  "Kleine Wellen bewegen sich ueber das Wasser.");

  AddDetail(({"spiegelbild","spiegelbilder"}), 
  "Im Wasser spiegeln sich der Mond und die vielen Sterne. Kleine Wellen "
  "verzerren das Bild ein wenig, jedoch erkennst du die Konturen genau.");

  AddDetail(({"grashalm","halm","grashalme","halme"}), 
  "Jeder einzelne Grashalm ist ein Bestandteil der Wiese. Zusammen ergeben "
  "sie ein dunkles, kraeftiges Gruen.");

  AddDetail(({"gras","graeser"}), 
  "Das Gras der Wiese ist kraeftig und gruen. Viele Grashalme winden sich "
  "gen Himmel.");

  AddDetail(({"gruen"}), 
  "Das Gras der Wiese ist ein kraeftiges Gruen. Jeder einzelne Grashalm "
  "scheint im Gruen zu schwelgen.");

  AddDetail(({"rand","rande"}), 
  "Der Rand zum grossen See. Von hier kannst du ganz bequem in das Wasser "
  "gehen und schwimmen.");

  AddDetail(({"see","sternensee"}),
  "Ruhig liegt der Sternensee vor Dir. Das Wasser ist klar und kalt, "
  "aber nicht eisig. Moeglicherweise koenntest Du darin schwimmen. Etwa "
  "in der Mitte des Sees befindet sich eine sehr kleine Insel. Du "
  "schaetzt die Entfernung zum anderen Ufer auf etwa 1000 Schritte.");

  AddDetail("mitte",
  "Ungefaehr in der Mitte des Sternensees siehst du eine kleine Insel.");

  AddDetail("insel",
  "Die Insel liegt in etwa der Mitte des Sees und ein Felsen ragt in den "
  "Himmel empor. Genaueres kannst du von hier leider nicht erkennen. Dafuer "
  "musst du dich schon hinbegeben.");
  
  AddDetail("himmel",
  "Eine ganze Menge Sterne sind am Himmel zu sehen, und natuerlich der "
  "Mond. Ein ueberragender Anblick ist das.");

  AddDetail(({"bilder","sternbilder","sternbild","bild"}),
  "Viele Sternbilder kommen Dir merkwuerdigerweise voellig unbekannt "
  "vor, andere hingegen sind dir sehr vertraut. Da waeren der Orion, "
  "der Wal, das Orkkind und die weisse Schlange.");

  AddDetail("sterne",
  "Eine riesige Menge an Sternen siehst du dort oben am Himmel. Manche "
  "fuegen sich zu Sternbildern zusammen und andere sind einfach nur da.");

  AddDetail("wasser",
  "Es ist klar und kalt. Die Oberflaeche ist so ruhig, dass sich die "
  "Sterne und der Mond ganz deutlich darin spiegeln. Den Grund kannst "
  "du leider nicht sehen.");

  AddDetail("grund",
  "Du bemuehst dich den Grund des Sees zu sehen, doch mehr als das "
  "schwarze, spiegelde Wasser siehst du nicht.");

  AddDetail("mond",
  "Fast hast du den Eindruck, als wenn dich von dort oben jemand anzwinkern "
  "wuerde. Aber das ist wohl nur eine Taeuschung. Du bist dir aber sicher, "
  "dass du ein Gesicht erkennen kannst.");

  AddDetail("gesicht",
  "Ein Gesicht wie aus dem Bilderbuch starrt dich an. Zwinkert es dir gar zu?");

  AddDetail("wiese",
  "Eine kraeftig gruene Wiese mit allerlei verschiedenen Graesern und "
  "Blumen. Du atmest tief durch und geniesst den frischen Duft.");

  AddDetail(({"farbe","farben"}),
  "Viele Farben siehst du hier. Leicht ueberwiegend ist jedoch Blau und "
  "gruen vertreten.");

  AddDetail(({"blumen","blume","sorte","sorten"}),
  "Eine unueberblickbare Vielfalt von Blumen macht sich hier auf der "
  "Wiese breit. Du erkennst Wiesenschaumkraut, Himmelsschluessel, "
  "Kaiserknoepfe und Orkveilchen, aber die meisten anderen Sorten sind "
  "Dir voellig unbekannt.");

  AddDetail(({"orkveilchen","veilchen"}),
  "Die Orkveilchen sind blau-schwarzer Farbe. Ihre Blaetter scheinen dich "
  "verfuehreisch anzuhimmeln.");

  AddDetail(({"blau","blautoene","blauton","azurblau","dunkles blau"}),
  "Vom Azurblau bis hin zum dunklen Blau ist alles vertreten.");

  AddDetail(({"wiesenschaumkraut","kraut","schaumkraut"}),
  "Kleine, weisse sich nach oben kraeuselnde Blaetter gaben dieser Blume "
  "ihren Namen. Einen beruhigenden Anblick bietet diese zarte Blume.");

  AddDetail(({"himmelsschluessel","kelch"}),
  "Ein langer Stengel mit sich nach oben hin zu einem Kelch formende Blaetter "
  "machen den Reiz dieser Blume aus. Die Blaetter sind in allen moeglichen "
  "Blautoenen aufzufinden.");

  AddDetail(({"kaiserknoepfe", "kaiserknopf","pilz","kuppel"}),
  "Wie ein Pilz ragen die Kaiserknoepfe aus der Wiese empor. Ein dicker "
  "Stengel, nicht besonders lang, und stabile, in allen Farbtoenen leuchtende "
  "Blaetter, die sich zu einer flachen Kuppel formen bilden ein "
  "majestaetischen Anblick.");

  AddDetail(({"schwan","schwaene","gruppe"}),
  "Eine kleine Gruppe von Schwaenen schwimmt langsam und wuerdevoll ueber "
  "den See. Ab und zu mustert Dich einer von ihnen, aber ansonsten "
  "scheinen sie sich nicht weiter fuer Dich zu interessieren.");

  AddSound(DEFAULT_SOUND,
  "Du hoerst nur ein leises Zirpen. Seltsam, normalerweise gibts aus auf "
  "einer solchen Wiese viele Toene.");

  AddSound(({"zirpen","zirpe"}),
  "Genau orten kannst du das Zirpen nicht, aber du hoerst es. So leise "
  "wie es ist, muss es schon ein ganzes Stueck entfernt sein.");

  AddSmell(({DEFAULT_SMELL,"duft","geruch"}),
  "Die meisten Blumen riechen wuerzig und erfrischend. Vereinzelt "
  "wachsen jedoch auch blau-schwarze Orkveilchen, die einen fauligen "
  "Geruch ausstroemen.");

  AddSmell("kaiserknoepfe",
  "Als du versuchst dich einem Kaiserknopf zu naehern, um dessen Geruch "
  "aufzusaugen, bemerkst du wie sich die Bluete der Blume dir zuwendet. "
  "Rasch entfernst du dich wieder.");

  AddSmell(({"himmelsschluessel","schluessel"}),
  "Sanft umschmeichelt der zarte Geruch deine Nase. Du versinkst im Land "
  "der Traeume: Hoch oben ueber den Wolken schwebst du dahin und siehst "
  "die schoensten Bilder deines Lebens.");

  AddSmell(({"wiesenschaumkraut","schaumkraut","kraut"}),
  "Suess, fast so wie Honig, steigt dir der Geruch in die Nase.");
  
  AddSmell(({"blumen","blume"}),
  "Die meisten Blumen riechen wuerzig und erfrischend. Vereinzelt wachsen "
  "jedoch auch blau-schwarze Orkveilchen, die einen fauligen Geruch "
  "ausstroemen.");

  AddSmell(({"orkveilchen","veilchen"}),
  "Vor dieser blau-schwarzen, verfuehrerisch aussehenden Pflanze hat man "
  "Dich frueher immer gewarnt. Vorsichtig schnupperst Du an der Bluete und "
  "der scharfe, faulige Geruch stroemt Dir in die Nase.");

  AddCmd(({"schwimm","schwimme"}), "cmd_schwimmen" );
  AddCmd(({"fuetter","fuettere"}), "cmd_fuettern" );
  AddCmd(({"zaehl","zaehle"}), "cmd_zaehlen" );
  AddCmd(({"trampel","trample","zertrample","zertrampel","zertrete",
           "zertritt"}), "cmd_trampeln");
  AddCmd(({"pfluecke","pfluecke"}), "cmd_pfluecken");
  AddCmd(({"wuensch","wuensche"}), "cmd_wuenschen");
  
  AddExit("nordosten", ROOM "raum1");
}

static int cmd_schwimmen(string s)  {
  notify_fail("Wohin moechtest du schwimmen?\n");
  
  if(!s) {
    return 0;
  }
  if(member(combine_mapping(([
             "zur#zu":
             ({"insel","felsen","fels"}),
             "zum":
             ({"ufer"}),
            ])),s) != -1) {

    this_player()->move((ROOM "raum3.c"),M_GO,
                              "zur Insel", "schwimmt","kommt an");
    return 1;
  }
  if(member(combine_mapping(([
              "in":
              ({"wasser","see","sterensee"}),
            ])),s) != -1) {
    
    say(break_string(this_player()->Name(WER)+" schwimmt eine Weile im See "
        "herum."));
 
    write(break_string("Du springst in das ziemlich kuehle Wasser und "
          "schwimmst ein wenig. Manchmal kommt einer der Schwaene etwas "
          "naeher und schaut dich mit großen Augen an, als ob er etwas von "
          "dir will. Als du endlich wieder herauskommst, ist dir ganz kalt. "
          "Hast du etwas zum Aufwaermen dabei?"));
    
    return 1;
  }
  return 0;
}

static int cmd_fuettern(string s) {
  notify_fail("Wen moechtest Du fuettern?\n");
  
  if(!s) {
    return 0;
  }
  if(member(({"schwan","schwaene"}),s) != -1) {
    say(break_string(this_player()->Name(WER)+" fuettert die Schwaene."));
    
    write(break_string("Du nimmst ein Stueck Brot und haeltst es "
          "auffordernd in Richtung der Schwaene. Ein besonders grosses "
          "Mitglied der Gruppe laesst sich nicht lange bitten, schwimmt "
          "herbei und nimmt dir dankbar das Brot ab. Anmutig schwimmt er "
          "zurueck zum See."));
    
    return 1;
  }
  return 0;
}

static int cmd_zaehlen(string s) {
  notify_fail("Was moechtest du zaehlen?\n");
  
  if(!s) {
    return 0;
  }
  
  if(member(({"stern","sterne"}),s) != -1) {
    say(break_string(this_player()->Name(WER)+" schaut zum Himmel hoch "
  	"und scheint dort etwas zu suchen."));
  
    write(break_string("Du schaust in den Himmel und faengst an, die Sterne "
        "zu zaehlen. Eins, zwei, drei ... sechshundertachtvierzig ... "
        "eintausend und fuenf ... Nach einer Weile hoerst du auf, denn du "
        "bist erschoepft und hast dennoch nur einen kleinen Teil gezaehlt."));
  
    return 1;
  }
  return 0;
}

static int cmd_wuenschen(string s) {
  notify_fail("Wuensche haben wir alle.\n");
  
  if (wunsch > time()) {
    write(break_string("Du schliesst die Augen, drueckst die Daumen und "
          "wuenschst dir etwas. Ob er wohl in Erfuellung geht?"));

    say(break_string(this_player()->Name(WER)+ " schliesst die Augen "
       "fuer einen kurzen Moment."));
    
    return 1;
  }
  return 0;
}

static int cmd_trampeln(string s) {
  notify_fail("Was mochtest du zertrampeln?\n");

  if(member(({"blume","blumen","veilchen","knoepfe","wiesenschaumkaut",
              "orkveilchen","himmelsschluessel","kaiserknoepfe",
              "kaiserknopf"}),s) != -1) {
   
    write(break_string("Blumen zertrampeln... So etwas Unanstaendiges "
           "wuerdest du dir an diesem Ort nicht trauen."));
    return 1; 
  }
  return 0;
}

static int cmd_pfluecken (string s) {
  notify_fail("Was moechtest Du pfluecken?\n");
  
  if(!s) {
    return 0;
  }
  if(!member(blumen,s)) {
    write("Welche Blume noechtest du denn pfluecken?\n");
    return 1;
  }
  
  if(!blumen[s]) {
    write ("Da war wohl jemand schon vor dir da!\n");
    return 1;
  }
  else {
    object o = clone_object(OBJ+s);
    
    write(break_string("Du pflueckst "+o->name(WEN)+"."));
    
    say(break_string(this_player()->Name(WER)+" pflueckt "+o->name(WEN)+"."));

    if(o->move(this_player(),M_GET) == ME_TOO_HEAVY) {
      write("Da du die Blume nicht mehr tragen kannst, laesst du sie "
            "fallen.\n");

      o->move(this_object(),M_NOCHECK);
    }
    blumen[s] = 0;
    return 1;
  }
  return 0;
}
