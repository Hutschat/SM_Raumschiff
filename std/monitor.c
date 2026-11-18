// monitor.c - Ein scrollender Bildschirm fuer Terminals
//
// Letzte Aenderung:
//
// 02.01.2022 It@Efferdland            neu

#include <properties.h>
#include <ansi.h>
#include <defines.h>
#include "def.h"
#include REGION_SYS "monitor.h"

static int   breite  = 65;
static int    hoehe  = 22;
static string modus  = "ansi";

static string *schirm,*schirm_orig;

static mapping cols = ([
  "rahmen"     : ANSI_BG_GREEN,
  "schirm"     : MON_ANSI_GREEN_BLACK,
  "schrift"    : ANSI_FG_WHITE,
]);

static void set_colors(mapping col) {
  
  if(col["rahmen"]) {
     cols["rahmen"] = col["rahmen"];
  }
  if(col["schirm"]) {
    cols["schirm"] = col["schirm"];
  }
  if(col["schrift"]) {
    cols["schrift"] = col["schrift"];
  }
}

static string get_color(string col) {
  return cols[col];
}

static void set_display(string *str) {
  schirm = schirm_orig = str;
}

string make_line(<string|closure> line) {
  if(closurep(line)) {
    line = funcall(line);
  }
  string ret = "";
  int sz     = sizeof(line);
  int i;
  
  if(sz < breite) {
    for(i=sz;i<breite;i++) {
      line += " ";
    }
  }
  line = " "+line;

  if(modus == "simple") {
    ret += line;
  }
  else if(modus == "ansi") {
/*
    ret += cols["rahmen"]+" "+ANSI_NORMAL+
           cols["schirm"]+line+ANSI_NORMAL+
           cols["rahmen"]+"  "+ANSI_NORMAL;
*/
dtell("it",cols["schrift"]+line);
    ret += cols["rahmen"]+" "+ANSI_NORMAL+
           cols["schirm"]+cols["schrift"]+line+ANSI_NORMAL+
           cols["rahmen"]+" "+ANSI_NORMAL;
  }
  else {
    ret += "| "+line+" |";
  }
  return ret;
}

static string schirm_det() {
  int i;
  string ret = "\n";

  string base = "";
  
  if(PL->QueryProp(P_SIMPLE_MODE)) {
    modus = "simple";
  }
  else if(PL->QueryProp(P_TTY) == "ansi") {
    modus = "ansi";
  }
  else {
    modus = "vt100";
  }

  if(modus == "simple") {
    base = base;
  }
  else if(modus == "ansi") {
    base += cols["rahmen"]+sprintf("%|' ':"+(breite+3)+"s", "")+
            ANSI_NORMAL+"\n";
  }
  else {
    base += sprintf(" %|'-':"+(breite+3)+"s\n", "");
  }
  ret += base;

  foreach(string line:schirm) {
    ret += make_line(line)+"\n";
    i++;
  }
  if(i<hoehe) {
    for(i=i;i<=hoehe;i++) {
      ret += make_line("")+"\n";
    }
  }
  ret += base;

  return ret;
}

static void ringbuffer(<string|string*> str) {
  string *tmp;
  int i;

  if(pointerp(str)) {
    for(i=0;i<sizeof(str);i++) {
      if(sizeof(str[i]) > breite) {
        str[i] = break_string(str[i],breite-1,"",BS_LEAVE_MY_LFS);
      }
      str[i] = trim(str[i],2,"\n");
    }
    str = implode(str,"\n");
  }
  else if(stringp(str)) {
    // Keine \n im String, daher evtl. fuer eine Zeile zu lang.
    if(!regmatch(str,"\n")) {
      str = break_string(str,breite-1);
    }
  }
  else {
    return;
  }
  tmp = explode(str,"\n");

  foreach(string s:tmp) {
    if(sizeof(schirm) >= hoehe) {
      schirm = schirm[1..<1];
    } 
    schirm += ({ s });
  }
}

protected void create() {
  if(!clonep()) {
    set_next_reset(-1);
    return;
  }
  ME->SetProp(P_NAME,"Computer");
  ME->SetProp(P_SHORT,
  "Ein Terminal");
  ME->SetProp(P_LONG,
  "Irgendein Terminal");
  ME->Set(P_LONG,#'schirm_det,F_QUERY_METHOD);
  ME->SetProp(P_GENDER,NEUTER);
  ME->SetProp(P_SIZE,300);
  ME->SetProp(P_INFO,
      "Auf der Tastatur kann man etwas tippen. Syntax: 'tippe <text>'.\n");
  ME->SetProp(P_WEIGHT,150000);
  ME->AddId(({"terminal","computer","kasten","monitor","bildschirm",
              "schirm","termlink","\nmonitor"}));
  ME->SetProp(P_NOGET,"Das Ding ist irgendwie befestigt.\n");
}

protected void reset() {
}
