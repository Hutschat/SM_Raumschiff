                                                         
// virtual_compiler.c
//
// Letzte Aenderung:
// 
// 10.12.2025 It@MagicMud              1. Version

#pragma no_clone
#pragma no_inherit
#pragma no_shadow

#include "def.h"

inherit  "/std/virtual/it_compiler";

protected void create() {
  ::create();
  SetProp(P_VC_FILELIST,SCHIFF_RL);
  seteuid(getuid());
}
