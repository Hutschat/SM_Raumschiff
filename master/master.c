// master.c - Der Artefakt-Master
//
//

#pragma no_clone,no_inherit,no_shadow

#include "def.h"

protected mapping project_map = ([]);

static void save_me() {
  save_object(REGION_SAVEDIR "master");
}

static void restore_me() {
  restore_object(REGION_SAVEDIR "master");
}

protected void create() {
  seteuid(getuid(ME));

  if(file_size(REGION_SAVEDIR "master") == -1) {
    save_me();
  }
  restore_me();
}

