#include "sqlite/sqlite3.h"
#include "sqlite3.h"
#include "string.h"
#include <stdio.h>

int dbInit(sqlite3 *db, char *dbName) {

  char *filename = strcat(dbName, ".db");
  int rc = sqlite3_open(filename, &db);

  if (rc != SQLITE_OK) {
    return 1;
  }

  // Creating users table.
  char *sql =
      "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT)";
  rc = sqlite3_exec(db, sql, NULL, NULL, NULL);

  if (rc != SQLITE_OK) {
    printf("Error creating users table\n");
    return 1;
  }
  return 0;
}

void prompt(char *str, int n, char msg[]) {
  printf(msg, "");
  fgets(str, n, stdin);
  int i = 0;
  while (str[i] != '\n' && str[i] != '\0')
    i++;
  if (str[i] == '\n')
    str[i] = '\0';
}

static int callback(void *data, int argc, char **argv, char **azColName) {
  int i;
  fprintf(stderr, "%s: ", (const char *)data);

  for (i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }

  printf("\n");
  return 0;
}

int main(int argc, char *argv[]) {
  sqlite3_initialize();
  sqlite3 *db;
  char *err;
  char *data = "Callback function called";

  char userin[15];
  prompt(userin, sizeof(userin), "Enter database name (15 chars max): \n");

  dbInit(db, userin /*Hopefully, the db name*/);

  // TODO: Get DB Tables names and print it then prompt for which table to
  // print.

  char *sql = "INSERT INTO users (name) VALUES ('frominven')";
  int rc = sqlite3_exec(db, sql, callback, (void *)data, &err);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s.\n", err);
    sqlite3_free(err);
  } else {
    fprintf(stdout, "Operation Successful");
  }

  sqlite3_close(db);
  sqlite3_shutdown();
  return 0;
}
