#include <stdio.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
        for(int i = 0; i < argc; i++) {
                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
}

int main(int argc, char* argv[]) {
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        char *sql;
        rc = sqlite3_open("test.db", &db);
        if(rc) {
                fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
                return 0;
        } else {
                fprintf(stderr, "Opened database successfully\n");
        }

        sql = "INSERT INTO COMPANY (ID, NAME, AGE, ADDRESS, SALARY) VALUES" \
        "(1, 'Paul', 32, 'California', 20000.00 )," \
        "(2, 'Allen', 25, 'Texas', 15000.00),"\
        "(3, 'Teddy', 23, 'Norway', 20000.00),"\
        "(4, 'Mark', 25, 'Rich-Mand ', 65000.00);";

        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

        if (rc != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
        } else {
                fprintf(stdout, "Table created successfully\n");
        }

        sqlite3_close(db);
}
