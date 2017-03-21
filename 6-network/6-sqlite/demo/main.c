#include "sqlite3.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define DATABASE_PATH	"mydb.db"
#define BUFF_SIZE		1024

int select_callback(void *arg, int argc, char **argv, char **cloname);
int pid;

int counter;

int main(int argc, char **argv)
{
	sqlite3 *db = NULL;
	char *errmsg = NULL;
	char *sql = NULL;
	char sql_buff[BUFF_SIZE];

	if (SQLITE_OK != sqlite3_open(DATABASE_PATH, &db)) {
		puts("database open error !");
		return -1;
	}

	sql = "create table if not exists student (name char, id int, score int)";
	if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg)) {
		printf("sqlite3_exec:%s\n", errmsg);
		sqlite3_free(errmsg);
		return -1;
	}

	sprintf(sql_buff, "insert into %s values ('%s', %d, %d)", "student", "james", 20131101, 100);
	if (SQLITE_OK != sqlite3_exec(db, sql_buff, NULL, NULL, &errmsg)) {
		printf("sqlite3_exec:%s\n", errmsg);
		sqlite3_free(errmsg);
		return -1;
	}

	sql = "insert into student values ('lucy', 20131102, 80)";
	if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg)) {
		printf("sqlite3_exec:%s\n", errmsg);
		sqlite3_free(errmsg);
		return -1;
	}

	/* SQL injection !! */
	/*	sprintf(sql_buff,"select * from student where name='%s'", "zhan' or '1'='1");
	 */

#if 0
	/* method 1. sqlite3_exec + callback*/
	sprintf(sql_buff,"select * from %s where name='%s'", "student", "james");
	if (SQLITE_OK != sqlite3_exec(db, sql_buff, select_callback, NULL, &errmsg)) {
		printf("sqlite3_exec:%s\n", errmsg);
		sqlite3_free(errmsg);
		return -1;
	}
#else 
	/* method 2. sqlite3_get_table */
	int row, column;
	char **resultp;
	int index;
	int i,j;
	
	sql = "select * from student";
	if (SQLITE_OK != sqlite3_get_table(db, sql, &resultp, &row, &column, &errmsg)) {
		printf("sqlite3_exec:%s\n", errmsg);
		sqlite3_free(errmsg);
		return -1;
	}

	/* show column names in table */
	for (i = 0; i < column; i ++)
		printf("  %-10s|",resultp[i]);
	puts("\b ");

	/* show column values in row */
	index = column;
	for (i = 0; i < row; i ++) {
		for (j = 0; j < column; j ++)
			printf("  %-10s|",resultp[index ++]);
		puts("\b ");
	}

#endif

	if (SQLITE_OK != sqlite3_close(db)) {
		puts("database close error !");
		return -1;	
	}
	return 0;
}

int select_callback(void *arg, int argc, char **argv, char **cloname)
{
	int index;

#if 0
	/* show column names in table */
	for (index  = 0; index < argc; index ++)
		printf("%-10s|", cloname[index]);
	puts("\b ");
#endif
	/* show column values in row */
	for (index  = 0; index < argc; index ++)
		printf("%-10s|", argv[index]);
	puts("\b ");

	return 0;
}
