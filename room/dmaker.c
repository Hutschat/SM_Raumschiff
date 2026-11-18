#pragma no_clone
#pragma no_inherit
#pragma no_shadow

#include "def.h"

inherit "/std/virtual/it_compiler_dmaker";

static mixed tmp;

public varargs void create_room(string file,object o) {
  object mon;
  
  if(!::create_room(file,o,SCHIFF_RL)) {
    return;
  }
  o->SetProp(P_NOMAP,0);

  switch(file) {
// Deck 1
    case "[-3+0+0]":
    o->SetProp(P_INT_LONG,
    ([
      INT_LONG_HEADER:
      "Du befindest dich in einem Gang des Raumschiffs Proton, das vor "
      "langer Zeit in der Wüste Kurma abgestürzt ist. Das Schiff scheint "
      "seitdem verlassen zu sein. In der Decke leuchtet ein kaltes, weißes "
      "Licht, das unregelmäßig flackert. Nach",
         
      "osten":
      "Westen gelangst du zurück in die zerstörte Schleuse und nach "
      "Osten fuehrt der Gang weiter in Schiff hinein. ",
         
      INT_LONG_DEFAULT:
      "Osten führt der Gang wieder weiter ins Schiff hinein während "
      "sich im Westen eine zerstörte Schleuse befindet.",
         
      INT_LONG_FOOTER:
      "An der südlichen Wand ist ein Schild angebracht.",
    ]));
    
    o->AddDetail(({"schild","flagge"}),
         function() {
           if(PL->QueryProp(P_SIMPLE_MODE)) {
             return "Auf dem Schild steht: BRS PROTON\n";
           }
           if(PL->QueryProp(P_TTY) != "ansi") {
             return "+------------+\n"
                    "|            |\n"
                    "| BRS PROTON |\n"
                    "|            |\n"
                    "+------------+\n";
           }
           return "\n"+o->make_emblem_1(PL);
         }
       );
    
    o->AddDetail(({"schleuse"}),
       "Dort siehst du nur noch Trümmer aus Metall, die kreuz und quer "
       "herum liegen.");

    o->AddDetail(KEYS_CEILING,
       "Die Decke ist eine einzige Fläche aus flackerndem Licht.");

    o->AddDetail(({"truemmer","truemmerteile"}),
       "Verbogenes, zerrissenes Metall. Durch die Schleuse kommt hier "
       "niemand mehr hinaus.");

    o->AddDetail(({"wueste","kurma","wueste kurma"}),
       "Die Wüste Kurma liegt draußen vor dem Schiff. Von hier drinnen "
       "siehst du davon nur den Sand auf dem Boden.");

    o->AddDetail(({"zeit"}),
       "Wie lange das Schiff schon hier liegt, weiß niemand. Es muss aber "
       "sehr lange her sein.");

    o->AddDetail(({"brs","buchstaben"}),
       "Was die drei Buchstaben bedeuten, weiß heute niemand mehr.");

    o->AddExit("osten",   REGION_ROOM "[-2+0+0]");
    break;
    
    case "[-2+0+0]":
    o->SetProp(P_INT_LONG,
       ([
         INT_LONG_HEADER:
         "Du läufst den Gang des abgestürzten Raumschiffs Proton in",
         
         "osten":
         "östlicher",
         
         INT_LONG_DEFAULT:
         "westlicher",
         
         INT_LONG_FOOTER:
         "Richtung entlang. Eine Wandplatte hat sich aus ihrer Verankerung "
         "gelöst und liegt achtlos auf dem Boden. Aus der offenen Wand "
         "ragen Kabel, die unregelmaessig zischen und Funken versprühen. "
         "Der Gang verläuft hier gerade in westlicher und östlicher "
         "Richtung.",
       ]));

    o->AddDetail(({"wandplatte","wandplatten"}),
       "Die Wandplatte liegt verbogen auf dem Boden. Ein paar abgerissene "
       "Nieten liegen daneben.");

    o->AddDetail(({"verankerung","halterung"}),
       "Wo die Wandplatte einmal befestigt war, ragen nur noch abgerissene "
       "Nieten aus der Wand.");

    o->AddDetail(({"kabel","kabelstrang","kabelstraenge"}),
       "Bunte Kabel hängen aus der offenen Wand. Ab und zu springen zischend "
       "Funken über. Besser nicht anfassen!");

    o->AddDetail(({"funken","funke"}),
       "Kleine, blaue Funken. Sie zischen und erlöschen sofort wieder.");

    o->AddDetail(({"richtung"}),
       "Der Gang führt nur nach Westen oder nach Osten.");

    o->AddExit("osten",   REGION_ROOM "[-1+0+0]");
    o->AddExit("westen",  REGION_ROOM "[-3+0+0]");
    break;
    
    case "[-1+0+0]":
    o->SetProp(P_INT_LONG,
       "Der Gang des Raumschiffs Proton führt hier nach Westen und Osten. "
       "Das Licht an der Decke ist schwach und flackert unregelmäßig, als "
       "würde die Energieversorgung jeden Augenblick zusammenbrechen. Von "
       "der südlichen Wand dringt dagegen das stetige rote Leuchten einer "
       "quadratischen Alarmlampe. Ihr Licht taucht den Gang in einen "
       "düsteren roten Schein. Der Alarm scheint seit dem Absturz nicht "
       "abgeschaltet worden zu sein.");

    o->AddDetail(({"alarmlampe","lampe","alarmleuchte"}),
       "Eine quadratische Lampe in der Wand. Sie leuchtet ununterbrochen "
       "rot.");

    o->AddDetail(({"alarm"}),
       "Der Alarm ist stumm. Nur die Alarmlampe zeigt, dass er noch immer "
       "läuft.");

    o->AddDetail(({"leuchten","schein"}),
       "Das rote Leuchten lässt den Gang unheimlich wirken.");

    o->AddDetail(({"energieversorgung","energie","strom"}),
       "Die Energieversorgung liegt wohl irgendwo tief im Schiff. Hier "
       "merkst du nur, dass sie nicht mehr richtig funktioniert.");

    o->AddDetail(({"absturz"}),
       "Vom Absturz zeugen hier vor allem das flackernde Licht und der "
       "Alarm.");

    o->AddDetail(({"augenblick"}),
       "Jetzt? Oder jetzt? Hm, noch hält die Energieversorgung.");

    o->AddExit("osten",   REGION_ROOM "[+0+0+0]");
    o->AddExit("westen",  REGION_ROOM "[-2+0+0]");
    break;
    
    case "[+0-2+0]":
    o->SetProp(P_MAP_SYMBOL,"m");
    o->SetProp(P_INT_SHORT,"Der Maschinenraum der Proton");
    o->SetProp(P_INT_LONG,
       "Dies ist der Maschinenraum des Raumschiffs Proton. In der Mitte des "
       "Raumes steht eine hohe, leuchtende Säule, die in regelmässigen "
       "Abständen schwach pulsiert. Rings um die Säule verläuft eine "
       "halbkreisförmige Konsole mit zahlreichen Anzeigen, Schaltern, "
       "Reglern und Knöpfen. An den Wänden befinden sich weitere Geräte "
       "und Leitungen, deren Kontrollleuchten noch immer in "
       "unterschiedlichen Farben leuchten. Ein tiefes, gleichmässiges "
       "Summen erfüllt den Raum.");

    o->AddDetail(({"säule"}),
       "Diese Säule ist die Antimateriekammer der Proton. In ihrem Inneren "
       "schwebt ein dunkler, scheinbar leerer Bereich, umgeben von mehreren "
       "schmalen Lichtringen. Die Ringe pulsieren regelmässig und halten die "
       "darin eingeschlossene Antimaterie in einer unsichtbaren magnetischen "
       "Falle. Rings um die Säule verläuft eine Konsole.");

    o->AddSpecialDetail(({"maschinenraum"}),"_query_int_long");

    o->AddDetail(KEYS_FLOOR,
       "Der Boden vibriert leicht, sobald die Säule pulsiert.");

    o->AddDetail(KEYS_WALL,
       "An den Wänden hängen Geräte und Leitungen, dicht an dicht.");

    o->AddDetail(({"antimateriekammer","kammer"}),
       "Die Antimateriekammer ist die hohe, leuchtende Säule in der Mitte "
       "des Raumes.");

    o->AddDetail(({"antimaterie"}),
       "Antimaterie kann man nicht sehen. Man erkennt nur den dunklen "
       "Bereich im Inneren der Säule. Gut, dass sie dort eingeschlossen "
       "bleibt.");

    o->AddDetail(({"bereich","innere","inneres"}),
       "Ein dunkler, scheinbar leerer Bereich. Wenn du länger hinsiehst, "
       "wird dir schwindelig.");

    o->AddDetail(({"lichtring","lichtringe","ring","ringe"}),
       "Die schmalen Ringe aus Licht pulsieren gleichmäßig.");

    o->AddDetail(({"falle","magnetfalle"}),
       "Eine unsichtbare magnetische Falle. Sehen kannst du sie nicht, aber "
       "es kribbelt, wenn du der Säule zu nahe kommst.");

    o->AddDetail(({"konsole","halbkreis"}),
       "Die halbkreisförmige Konsole ist übersät mit Anzeigen, Schaltern, "
       "Reglern und Knöpfen. Welcher davon was bewirkt, weißt du nicht.");

    o->AddDetail(({"anzeige","anzeigen"}),
       "Darauf flimmert es ständig. Lesen kannst du davon nichts.");

    o->AddDetail(({"schalter","regler","knopf","knoepfe"}),
       "Unzählige Schalter, Regler und Knöpfe. Lieber nichts anfassen, bevor "
       "hier noch etwas explodiert.");

    o->AddDetail(({"geraet","geraete"}),
       "Kästen mit blinkenden Kontrollleuchten, verbunden durch dicke "
       "Leitungen.");

    o->AddDetail(({"leitung","leitungen"}),
       "Dicke Leitungen verbinden die Geräte mit der Säule.");

    o->AddDetail(({"kontrollleuchte","kontrollleuchten","leuchte",
                   "leuchten"}),
       "Kleine rote, grüne und gelbe Leuchten. Die meisten blinken.");

    o->AddDetail(({"farbe","farben"}),
       "Rot, grün und gelb.");

    o->AddDetail(({"summen","brummen"}),
       "Ein tiefes Summen, das du eher spürst als hörst.");

    o->AddDetail(({"mitte"}),
       "In der Mitte steht die Säule.");

    o->AddDetail(({"abstand","abstaende"}),
       "Die Säule pulsiert gleichmäßig und ruhig.");

    o->NewDoor("norden",REGION_ROOM "[+0-1+0]",KEYS_DOOR,
    ([
      D_NAME          : "automatische Tuer",
      D_GENDER        : FEMALE,
      D_SHORT         : "Eine %se automatische Tuer befindet sich im "
                        "Norden.",
      D_LONG          : "Die automatische Tuer ist %s. Sie oeffnet sich "
                        "von selbst, sobald man hindurchgehen will.\n",
      D_RESET_MSG     : "Die automatische Tuer schliesst sich mit "
                        "einem '"+SND_DOOR+"'.\n",
      D_FLAGS         : DOOR_CLOSED|DOOR_RESET_CL,
      D_OPENTESTFUNC  : "cant_open_door",
      D_TESTFUNC      : "door_sound",
      D_OPEN_WITH_MOVE: 1,
    ]));
       
    break;

    case "[+0-1+0]":
    o->SetProp(P_INT_LONG,
       "Du stehst in einem Gang der Proton, der nach Norden zur "
       "zentralen Kreuzung führt. Im Süden vernimmt man deutlich ein "
       "Summen. Das schwache Deckenlicht flackert unruhig und lässt die "
       "Metallwände in kurzen Abständen aufleuchten. Die geschlossene Tür im "
       "Süden vibriert leicht, als würden dahinter noch immer mächtige "
       "Maschinen arbeiten.");

    o->AddDetail(({"deckenlicht","licht"}),
       "Das Licht an der Decke flackert unruhig.");

    o->AddDetail(({"kreuzung"}),
       "Die Kreuzung liegt im Norden.");

    o->AddDetail(({"maschine","maschinen"}),
       "Die Maschinen kannst du von hier aus nicht sehen. Hören aber schon.");

    o->AddDetail(({"summen"}),
       "Ein tiefes Summen dringt durch die Tür im Süden.");

    o->AddDetail(({"abstand","abstaende"}),
       "Mal schneller, mal langsamer.");

    o->NewDoor("sueden",REGION_ROOM "[+0-2+0]",KEYS_DOOR,
    ([
      D_NAME          : "automatische Tuer",
      D_GENDER        : FEMALE,
      D_SHORT         : "Eine %se automatische Tuer befindet sich im "
                        "Sueden.",
      D_LONG          : "Die automatische Tuer ist %s. Sie oeffnet sich "
                        "von selbst, sobald man hindurchgehen will.\n",
      D_RESET_MSG     : "Die automatische Tuer schliesst sich mit "
                        "einem '"+SND_DOOR+"'.\n",
      D_FLAGS         : DOOR_CLOSED|DOOR_RESET_CL,
      D_OPENTESTFUNC  : "cant_open_door",
      D_TESTFUNC      : "door_sound",
      D_OPEN_WITH_MOVE: 1,
    ]));
       
    o->AddExit("norden", REGION_ROOM "[+0+0+0]");
    break;
    
    case "[+0+0+0]":
    o->SetProp(P_INT_LONG,
       "Hier kreuzen sich die wichtigsten Gänge des Raumschiffs Proton. "
       "Die Decke ist an dieser Stelle höher. Über der "
       "Kreuzung blinkt eine rote Warnleuchte und taucht die Umgebung in "
       "einen unsteten roten Schein. Nach Norden führt der Gang zur "
       "Brücke, nach Süden geht es zum Maschinenraum. Im Osten führt "
       "eine Treppe auf eine weitere Ebene des Schiffes.");
    
    o->SetProp(P_INT_LONG_EXT,
       "Ein großes Emblem prangt auf dem Boden.\n");
    
    o->AddDetail(({"emblem","symbol"}),
         function() {
           string txt = read_file(REGION_TEXT+"symbol.txt");
           
           if(PL->QueryProp(P_TTY) == "ansi") {
             txt = ANSI_HFG_WHITE+ANSI_BG_BLUE+txt+ANSI_NORMAL;
           }
           return txt;
         }
       );

    o->AddDetail(({"kreuzung"}),
       "Hier treffen sich die Gänge des Schiffes.");

    o->AddDetail(({"gaenge"}),
       "Die Gänge führen nach Norden, Süden und Westen.");

    o->AddDetail(({"warnleuchte","leuchte"}),
       "Eine rote Warnleuchte hängt unter der Decke und blinkt unermüdlich.");

    o->AddDetail(({"schein"}),
       "Rot, dunkel, rot, dunkel. Das macht ganz schön nervös.");

    o->AddDetail(({"stelle"}),
       "Genau hier, über der Kreuzung, ist die Decke höher.");

    o->AddDetail(({"bruecke"}),
       "Die Brücke liegt im Norden.");

    o->AddDetail(({"maschinenraum"}),
       "Der Maschinenraum liegt im Süden.");

    o->AddDetail(({"treppe","stufen"}),
       "Eine schmale Treppe führt im Osten auf eine weitere Ebene des "
       "Schiffes. Leider ist sie eingestürzt.");

    o->AddDetail(({"ebene","deck"}),
       "Was auf der oberen Ebene liegt, kannst du von hier aus nicht "
       "erkennen.");

    o->AddExit("norden",      REGION_ROOM "[+0+1+0]");
    o->AddExit("sueden",      REGION_ROOM "[+0-1+0]");
    o->AddExit("westen",      REGION_ROOM "[-1+0+0]");
    break;

    case "[+0+1+0]":
    o->SetProp(P_INT_LONG,
       "Dies ist ein Gang im Raumschiff Proton. Im Norden befindet sich "
       "die geschlossene automatische Tür zur Brücke. Die Beleuchtung an "
       "der Decke ist vollständig ausgefallen. Nur ein Bildschirm in einer "
       "Nische der westlichen Wand funktioniert noch und taucht den "
       "ansonsten dunklen Gang in ein kaltes, bläuliches Licht. Nach Süden "
       "führt der Gang zurück zur zentralen Kreuzung.");


    o->AddDetail(({"nische","wandnische"}),
       "Die Wandnische befindet sich in der westlichen Wand des Ganges. Sie "
       "ist ungefaehr 80cm hoch und breit. In der Nische steht ein "
       "Bildschirm mit einer Tastatur davor. Eindeutig ein Terminal.");

    o->AddDetail(({"beleuchtung","licht","deckenlicht"}),
       "Die Beleuchtung an der Decke ist ausgefallen. Nur der Bildschirm in "
       "der Nische spendet noch etwas bläuliches Licht.");

    o->AddDetail(({"bildschirm","terminal"}),
       "Der Bildschirm steht in der Nische der westlichen Wand.");

    o->AddDetail(({"tastatur"}),
       "Eine alte, abgegriffene Tastatur.");

    o->AddDetail(({"kreuzung"}),
       "Die Kreuzung liegt im Süden.");

    o->AddDetail(({"bruecke"}),
       "Die Brücke liegt hinter der Tür im Norden.");

    o->AddItem(REGION_OBJ "terminal_win",REFRESH_DESTRUCT);
      
    o->NewDoor("norden",REGION_ROOM "[+0+2+0]",KEYS_DOOR,
    ([
      D_NAME          : "automatische Tuer",
      D_GENDER        : FEMALE,
      D_SHORT         : "Eine %se automatische Tuer befindet sich im "
                        "Norden.",
      D_LONG          : "Die automatische Tuer ist %s. Sie oeffnet sich "
                        "von selbst, sobald man hindurchgehen will.\n",
      D_RESET_MSG     : "Die automatische Tuer schliesst sich mit "
                        "einem '"+SND_DOOR+"'.\n",
      D_FLAGS         : DOOR_CLOSED|DOOR_RESET_CL,
      D_OPENTESTFUNC  : "cant_open_door",
      D_TESTFUNC      : "door_sound",
      D_OPEN_WITH_MOVE: 1,
    ]));

    o->AddExit("sueden",      REGION_ROOM "[+0+0+0]");

//    o->AddExit("norden",      REGION_ROOM "[+0+2+0]");
    break;

    case "[+0+2+0]":
    o->SetProp(P_MAP_SYMBOL,"b");
    o->SetProp(P_INT_SHORT, "Die Bruecke der Proton");
    o->SetProp(P_INT_LONG,
       "Dies ist die Brücke und damit die Kommandozentrale des Raumschiffs "
       "Proton. Vor dir erstreckt sich ein weitläufiges Bedienpult mit "
       "einer kaum überschaubaren Anzahl an Anzeigen, Schaltern und "
       "Kontrollleuchten. Hinter dem Pult befinden sich mehrere Stationen "
       "für die Steuerung und Navigation des Schiffes. In der Mitte der "
       "Brücke steht die Zentraleinheit des Schiffscomputers, daneben "
       "befindet sich ein grosser Projektionsschirm. Trotz des Alters des "
       "Schiffes sind noch zahlreiche Systeme aktiv.");

    o->AddSpecialDetail(({"bruecke","zentrale","kommandobruecke",
                          "kommandozentrale"}),"_query_int_long");
  
    o->AddDetail(KEYS_FLOOR,
    "Auf einem anthrazitfarbenen Mikrofaser-Teppichboden liegt ein "
    "hellblauer Laeufer, der von der Tuer aus zur Sitzbank fuehrt, "
    "auf der der Kapitaen normalerweise sitzt."); 

    o->AddDetail(KEYS_WALL,
    "Die Nordwand des Raumes ist schlicht weinrot gestrichen. Die "
    "uebrigen Waende bestehen aus elektrochromen Fenstern, die zum einen "
    "den Ausblick in die Wueste freigeben, zum anderen aber auch als "
    "Projektionsschirm fuer den Schiffscomputer dienen.");

    o->AddDetail(({"fenster"}),
    "Das Suedfenster bietet einen faszinierenden Ausblick in die Wueste. "
    "Derzeit wird auf dem Westfenster ein Schadensbericht des "
    "Raumschiffs dargestellt und auf dem Ostfenster eine Sternenkarte.");

    o->AddDetail(KEYS_COMPUTER_SHIP+({"wunderwerk"}),
    "Ein ueberwaeltigendes Wunderwerk der Technik. Es gibt eigentlich "
    "nichts, was dieser Computer nicht kann. Er ist zustaendig fuer "
    "die Navigation, das Sicherheitssystem, die Kommunikation an Bord "
    "und die Ueberwachung der Antriebssysteme.");

    o->AddDetail(({"bedienpult","pult","pulte"}),
    "Ein weitlaeufiges Pult voller Anzeigen, Schalter und "
    "Kontrollleuchten.");

    o->AddDetail(({"anzeige","anzeigen","schalter","kontrollleuchte",
                   "kontrollleuchten"}),
    "Es blinkt, leuchtet und flimmert ueberall. Die meisten Systeme "
    "scheinen tatsaechlich noch zu arbeiten.");

    o->AddDetail(({"anzahl"}),
    "Mehr, als du zaehlen kannst.");

    o->AddDetail(({"station","stationen","sitz","sitze"}),
    "Mehrere Sitze mit eigenen kleinen Pulten. Eine Station fuer die "
    "Steuerung, eine fuer die Navigation.");

    o->AddDetail(({"steuerung"}),
    "Wer hier sitzt, lenkt das Schiff. Theoretisch zumindest, denn so "
    "bald fliegt die Proton nirgendwo mehr hin.");

    o->AddDetail(({"navigation"}),
    "Die Navigation zeigt immer noch denselben Ort an: mitten in der "
    "Wueste.");

    o->AddDetail(({"wueste","ausblick","sand"}),
    "Durch das Suedfenster siehst du die Wueste. Sand, nichts als Sand.");

    o->AddDetail(({"suedfenster"}),
    "Durch das Suedfenster schaust du hinaus in die Wueste.");

    o->AddDetail(({"westfenster","schadensbericht","bericht"}),
    "Auf dem Westfenster steht ein Schadensbericht. Er ist lang, und fast "
    "alles darin ist rot markiert.");

    o->AddDetail(({"ostfenster"}),
    "Auf dem Ostfenster ist eine Sternenkarte zu sehen.");

    o->AddDetail(({"sternenkarte","karte"}),
         function() {
           return read_file(REGION_TEXT+"sternenkarte.txt");
         }
       );

    o->AddDetail(({"projektionsschirm","schirm"}),
    "Der grosse Projektionsschirm ist dunkel. Offenbar zeigt der "
    "Schiffscomputer lieber alles auf den Fenstern an.");

    o->AddDetail(({"mitte"}),
    "In der Mitte der Bruecke steht die Zentraleinheit des "
    "Schiffscomputers.");

    o->AddDetail(({"alter"}),
    "Die Proton ist alt, sehr alt. Trotzdem funktioniert hier erstaunlich "
    "viel.");

    o->AddDetail(({"system","systeme","sicherheitssystem","antriebssystem",
                   "antriebssysteme"}),
    "Viele Systeme laufen noch. Welche genau, verraet dir der "
    "Schadensbericht auf dem Westfenster.");

    o->AddDetail(({"kommunikation","funk"}),
    "Die Kommunikation scheint zu funktionieren. Nur meldet sich niemand.");

    o->AddDetail(({"ueberwachung"}),
    "Der Schiffscomputer ueberwacht alles, auch dich.");

    o->AddDetail(({"technik"}),
    "Technik, die du nicht verstehst. Aber beeindruckend ist sie.");

    o->AddDetail(({"bord"}),
    "An Bord der Proton ist es erstaunlich still.");

    o->AddDetail(({"teppich","teppichboden","mikrofaser"}),
    "Ein weicher, dunkelgrauer Teppich. Erstaunlich weich fuer ein "
    "Raumschiff.");

    o->AddDetail(({"laeufer"}),
    "Ein hellblauer Laeufer, ziemlich abgetreten.");

    o->AddDetail(({"sitzbank","bank"}),
    "Eine bequeme, gepolsterte Bank. Hier sass der Kapitaen.");

    o->AddDetail(({"kapitaen","kaptain"}),
    "Der Kapitaen ist nicht da. Wo er wohl geblieben ist?");

    o->AddDetail(({"nordwand"}),
    "Die Nordwand ist weinrot gestrichen. Sonst ist sie voellig "
    "schmucklos.");

    o->NewDoor("sueden",REGION_ROOM "[+0+1+0]",KEYS_DOOR,
    ([
      D_NAME          : "automatische Tuer",
      D_GENDER        : FEMALE,
      D_SHORT         : "Eine %se automatische Tuer befindet sich im "
                        "Sueden.",
      D_LONG          : "Die automatische Tuer ist %s. Sie oeffnet sich "
                        "von selbst, sobald man hindurchgehen will.\n",
      D_RESET_MSG     : "Die automatische Tuer schliesst sich mit "
                        "einem '"+SND_DOOR+"'.\n",
      D_FLAGS         : DOOR_CLOSED|DOOR_RESET_CL,
      D_OPENTESTFUNC  : "cant_open_door",
      D_TESTFUNC      : "door_sound",
      D_OPEN_WITH_MOVE: 1,
    ]));
    break;
  }
}
