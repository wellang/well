#include <stdio.h>
#include <stdlib.h>
#include "db.h"
#include "../log.h"

struct welldb_table table;

struct welldb_table init_db() {

    int check;
#if defined _WIN32 | defined _WIN64 | defined __WIN32__
    check = sqlite3_open(WIN_DBLOC, &table.db);
#endif

#if defined __gnu_linux__ | defined __linux__ | defined linux \
    | __FreeBSD__ | defined __NetBSD__ | defined __OpenBSD__
    check = sqlite3_open(UNIX_DBLOC, &table.db);
#endif

    if(check != SQLITE_OK) {
        wlog_fatal("welldb.db", 0, "Could not open Wellang database!\n");
        exit(1);
    } else {
        return table;
    }

}

void dump_db(char *argv_value_to_dump) {

    exit(0);
}