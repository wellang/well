#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"
#include "../log.h"

struct welldb_table table;
struct DB_DUMPDATA dumpdata;
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

        sqlite3_exec(table.db, "PRAGMA synchronous = OFF;", callback, 0, &errmsg);
        sqlite3_exec(table.db, time_table, callback, 0, &errmsg);
        return table;
    }

}

void welldb_dump_db(char *TABLE, int print) {
    char buf[0x100];
    snprintf(buf, sizeof(buf), "SELECT * FROM %s", TABLE);
    sqlite3_prepare_v2(table.db, buf, 256, &table.res, &table.tail);

    int i;
    if(print == 1) {
        log_info("DUMPING TABLE %s:", TABLE);
    }
    for(i = 0; i < 512; i++) {
        sqlite3_step(table.res);
        dumpdata.data[i] = sqlite3_column_text(table.res, 0);
        if(dumpdata.data[i] == NULL) {
           break;
        }
        if(print == 1) {
            log_info("%d | %s", i, dumpdata.data[i]);
        }
    }

    sqlite3_finalize(table.res);
}

/* table_name = "COMPILE_TIMES";
 * items = "FINAL_COMPILE_TIME REAL, "\
 *         "FILENAME CHAR(256)"
 * */
void welldb_create_table(char *table_name, char *items) {
    char buf[0x100];
    snprintf(buf, sizeof(buf), "CREATE TABLE %s(" \
    "%s );",
    table_name, items);
    sqlite3_exec(table.db, buf, callback, 0, &errmsg);
}

/*welldb_add_data("COMPILE_TIMES (FINAL_COMPILE_TIME,FILENAME)", "0.013245,'filename.well'");*/
void welldb_add_data(char *TABLE_NAME, char *db_value) {

    sqlite3_exec(table.db, "BEGIN;", callback, 0, &errmsg);
    char buf[0x100];
    snprintf(buf, sizeof(buf), "INSERT INTO %s " \
    "VALUES (%s);", TABLE_NAME, db_value);

    sqlite3_exec(table.db, buf, callback, 0, &errmsg);

}

void welldb_drop_table(char *table_name) {
    char buf[0x100];
    snprintf(buf, sizeof(buf), "DROP TABLE %s", table_name);
    sqlite3_exec(table.db, buf, callback, 0, &errmsg);
}

void close_db() {
    /*welldb_dump_db("DROPABLES");
    int i;
    for(i = 0; i < sizeof(dumpdata.data); i++) {
        if(dumpdata.data[i] == NULL) {
            break;
        }
        char buf[0x100];
        snprintf(buf, sizeof(buf), "DROP TABLE %s", dumpdata.data[i]);
        sqlite3_exec(table.db, buf, callback, 0, &errmsg);
    }*/
    sqlite3_exec(table.db, "COMMIT;", callback, 0, &errmsg);
    sqlite3_close(table.db);

}