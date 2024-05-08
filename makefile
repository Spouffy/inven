inven: main.c
	gcc -L./sqlite/sqlite3.so -lsqlite3 -I./sqlite/ main.c -o inven

cleandbs:
	rm -rf ./dbs/*.db
