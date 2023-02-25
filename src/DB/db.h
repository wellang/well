#ifndef WELL_DB_H
#define WELL_DB_H

#include "../../include/SQLite3/sqlite3.h"
#if defined __gnu_linux__ | defined __linux__ | defined linux \
    | __FreeBSD__ | defined __NetBSD__ | defined __OpenBSD__
#include <unistd.h>
#endif

#define WIN_DBLOC "C:\wesm\DB\welldb.db"

struct welldb_table {

    sqlite3 *db;
    char *username;

};

struct welldb_table init_db();
void dump_db(char *argv_value_to_dump);
void welldb_add_data(char *TABLE_NAME, char *db_value);
void close_db();

#endif
