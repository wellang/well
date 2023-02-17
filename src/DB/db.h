#ifndef WELL_DB_H
#define WELL_DB_H

#include <sqlite3.h>

#define UNIX_DBLOC "/usr/include/wellang/DB/welldb.db"
#define WIN_DBLOC "C:\wesm\DB\welldb.db"

struct welldb_table {

    sqlite3 *db;

};

struct welldb_table init_db();
void dump_db(char *argv_value_to_dump);

#endif
