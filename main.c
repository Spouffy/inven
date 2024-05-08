#include <stdio.h>
#include "string.h"
#include "sqlite3.h"

int dbInit(sqlite3 *db, char *dbName) {
  int rc = sqlite3_open(strcat(dbName, ".db"), &db);

  if (rc != SQLITE_OK) {
    return 1;
  }

  // Creating users table.
  char *sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT)";
  rc = sqlite3_exec(db, sql, NULL, NULL, NULL);

  if (rc != SQLITE_OK) {
    printf("Error creating users table\n");
    return 1;
  }
  return 0;
}

int main (int argc, char *argv[]) {
  sqlite3 *db;
  printf("argv[0] = %d\n", *argv[1]);
  dbInit(db, argv[1] /*Hopefully, the db name*/);


  sqlite3_close(db);
  return 0;
}


