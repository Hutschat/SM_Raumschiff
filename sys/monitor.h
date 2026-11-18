#ifndef _RAUMSCHIFF_ANSI_H__
#define _RAUMSCHIFF_ANSI_H__

#ifndef _ANSI
#include <ansi.h>
#endif

// gruener Hintergrund
#define MON_ANSI_BG_GREEN             ESC+"[48;5;40m"

// roter Hintergrund                  
#define MON_ANSI_BG_RED               ESC+"[48;5;160m"

// blauer Hintergrund
#define MON_ANSI_BG_BLUE              ESC+"[48;5;27m"

// hellblauer Hintergrund
#define MON_ANSI_BG_LIGHT_BLUE        ESC+"[48;5;75m"

// weisse Schrift, schwarzer Hintergrund
#define MON_ANSI_WHITE_BLACK          ESC+"[38;5;231m"+ESC+"[48;5;0m"

// gruene Schrift, weisser Hintergrund
#define MON_ANSI_GREEN_BLACK          ESC+"[38;5;40m"+ESC+"[48;5;0m"

// weisse Schrift, blauer Hintergrund
#define MON_ANSI_WHITE_BLUE           ESC+"[38;5;231m"+ESC+"[48;5;27m"

// blaue Schrift, weisser Hintergrund
#define MON_ANSI_BLUE_WHITE           ESC+"[38;5;27m"+ESC+"[48;5;231m"
#endif
