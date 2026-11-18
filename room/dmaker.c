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
       "Diese Säule ist die Antmateriekammer der Proton. In ihrem Inneren "
       "schwebt ein dunkler, scheinbar leerer Bereich, umgeben von mehreren "
       "schmalen Lichtringen. Die Ringe pulsieren regelmässig und halten die "
       "darin eingeschlossene Antimaterie in einer unsichtbaren magnetischen "
       "Falle. Rings um die Säule verläuft eine Konsole.");
       
    o->NewDoor("norden",REGION_ROOM "[+0-1+0]",KEYS_DOOR,
    ([
      D_NAME          : "automatische Tuer",
      D_GENDER        : FEMALE,
      D_SHORT         : "Eine %se automatische Tuer befindet sich im "
                        "Norden.",
      D_LONG          : "",
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
       "Metallwände in kurzen Abständen aufleuchten. Der geschlossen Tür im "
       "Süden vibriert leicht, als würden dahinter noch immer mächtige "
       "Maschinen arbeiten.");
    
    o->NewDoor("sueden",REGION_ROOM "[+0-2+0]",KEYS_DOOR,
    ([
      D_NAME          : "automatische Tuer",
      D_GENDER        : FEMALE,
      D_SHORT         : "Eine %se automatische Tuer befindet sich im "
                        "Sueden.",
      D_LONG          : "",
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

    o->AddItem(REGION_OBJ "terminal_win",REFRESH_DESTRUCT);
      
    o->NewDoor("norden",REGION_ROOM "[+0+2+0]",KEYS_DOOR,
    ([
      D_NAME          : "automatische Tuer",
      D_GENDER        : FEMALE,
      D_SHORT         : "Eine %se automatische Tuer befindet sich im "
                        "Norden.",
      D_LONG          : "",
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
    o->SetProp(P_INT_SHORT, "Die Bruecke der Protom");
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
    "Auf einem antrazitfarbenen Microfaser-Teppichboden liegt ein "
    "hellblauer Laeufer, der von der Tuer aus zur Sitzbank fuehrt, "
    "auf der der Kaptain normalerweise sitzt."); 

    o->AddDetail(KEYS_WALL,
    "Die Nordwand des Raumes sind in schlichtem Weinrot gehalten. Die "
    "uebrigen Waende bestehen aus elektrochromen Fenstern, die zum einen "
    "den Ausblick in die Wueste freigeben, zum anderen aber auch als "
    "Projektionsschirm fuer den Schiffscomputer dienen.");

    o->AddDetail(({"fenster"}),
    "Das Suedfenster bietet einen faszinierenden Ausblick in Wueste. "
    "Derzeit wird auf dem Westfenster ein Schadensbericht des "
    "Raumschiffs dargestellt und auf dem Ostfenster eine Sternenkarte.");

    o->AddDetail(KEYS_COMPUTER_SHIP+({"wunderwerk"}),
    "Ein ueberwaeltigendes Wunderwerk der Technik. Es gibt eigentlich "
    "nichts, was dieser Computer nicht kann. Er ist zuestaendig fuer "
    "die Navigation, das Sicherheitssystem, die Kommunikation an Bord "
    "und die Ueberwachung und der Antriebssysteme.");

    o->NewDoor("sueden",REGION_ROOM "[+0+1+0]",KEYS_DOOR,
    ([
      D_NAME          : "automatische Tuer",
      D_GENDER        : FEMALE,
      D_SHORT         : "Eine %se automatische Tuer befindet sich im "
                        "Sueden.",
      D_LONG          : "",
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
