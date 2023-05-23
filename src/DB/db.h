#ifndef WELL_DB_H
#define WELL_DB_H

#if defined __arm__
#include <sqlite3.h>
#else
#include "../../include/SQLite3/sqlite3.h"
#endif

#if defined __gnu_linux__ | defined __linux__ | defined linux \
    | __FreeBSD__ | defined __NetBSD__ | defined __OpenBSD__
#include <unistd.h>
#endif

#define WIN_DBLOC "C:\wesm\DB\welldb.db"

struct welldb_table {

    sqlite3 *db;
    char *username;
    sqlite3_stmt *res;
    const char *tail;

};

struct DB_DUMPDATA {
    const char *data[512];
};

struct welldb_table init_db();
void welldb_create_table(char *table_name, char *items);
void welldb_dump_db(char *TABLE, int print);
void welldb_add_data(char *TABLE_NAME, char *db_value);
void welldb_drop_table(char *table_name);
void close_db();

#endif
