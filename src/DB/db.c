#include <stdio.h>
#include <stdlib.h>
#include "db.h"
#include "../log.h"

struct welldb_table table;
char *errmsg = 0;

static int callback() {
    return 0;
}

struct welldb_table init_db() {

    int check;
#if defined _WIN32 | defined _WIN64 | defined __WIN32__
    check = sqlite3_open(".welldb.db", &table.db);
#endif

#if defined __gnu_linux__ | defined __linux__ | defined linux \
    | __FreeBSD__ | defined __NetBSD__ | defined __OpenBSD__
    check = sqlite3_open(".welldb.db", &table.db);
#endif

    if(check != SQLITE_OK) {
        wlog_fatal("welldb.db", 0, "Could not open Wellang database!\n");
        exit(1);
    } else {
        char *time_table = "CREATE TABLE COMPILE_TIMES(" \
                           "FINAL_COMPILE_TIME REAL, " \
                           "FILENAME           CHAR(256) );";

        sqlite3_exec(table.db, time_table, callback, 0, &errmsg);
        return table;
    }

}

void dump_db(char *argv_value_to_dump) {

    exit(0);
}

/*welldb_add_data("COMPILE_TIMES (FINAL_COMPILE_TIME,FILENAME)", "0.013245,'filename.well'");*/
void welldb_add_data(char *TABLE_NAME, char *db_value) {

    char buf[0x100];
    snprintf(buf, sizeof(buf), "INSERT INTO %s " \
    "VALUES (%s);", TABLE_NAME, db_value);

    sqlite3_exec(table.db, buf, callback, 0, &errmsg);

}

void close_db() {
    sqlite3_close(table.db);
}