#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

#define DB_TALBE_NAME	"student"
#define DB_SQL_LEN		1024
#define BUFF_SIZE		1024

struct student {
	char name[32];
	int num;
	int ch;
	int ma;
	int en;
};

int parse_student_info(char *buff, struct student *stu);

int main(int argc, const char **argv)
{
	FILE *fp = NULL;
	const char *fname = argv[1];
	const char *dbname = argv[2];
	sqlite3 *dbp = NULL;
	char sql[DB_SQL_LEN];
	char *errmsg = NULL;
	char buff[BUFF_SIZE];
	struct student stu;

	/* check arguments */
	if (argc != 3) {
		puts("invalid arguments !");
		exit(EXIT_FAILURE);
	}

	/* open file */
	if (NULL == (fp = fopen(fname, "r"))) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	
	/* open database */
	if (SQLITE_OK != sqlite3_open(dbname, &dbp)) {
		printf("sqlite3_open:%s\n", sqlite3_errmsg(dbp));
		exit(EXIT_FAILURE);
	}
	
	/*   create_table */
	sprintf(sql, "CREATE TABLE IF NOT EXISTS %s \
			(name char, num int, ch int, ma int, en int)", DB_TALBE_NAME);
	if (SQLITE_OK != sqlite3_exec(dbp, sql, NULL, NULL, &errmsg)) {
		puts(errmsg);
		sqlite3_free(errmsg);
		exit(EXIT_FAILURE);
	}

	while (1) {
		if (NULL == fgets(buff, BUFF_SIZE, fp))
			break;
		
		if (0 != parse_student_info(buff, &stu))
			continue;

		printf("%10s%10d%5d%5d%5d\n", 
				stu.name, stu.num, stu.ch, stu.ma, stu.en);

#if 1
		/* insert_database */
		sprintf(sql, "INSERT INTO %s VALUES ('%s', %d, %d, %d, %d)",
				DB_TALBE_NAME, stu.name, stu.num, stu.ch, stu.ma, stu.en);
		if (SQLITE_OK != sqlite3_exec(dbp, sql, NULL, NULL, &errmsg)) {
			puts(errmsg);
			sqlite3_free(errmsg);
			break;
		}
#endif
	}

	fclose(fp);
	sqlite3_close(dbp);

	return 0;
}


#if 0
int parse_student_info(char *buff, struct student *stu)
{
	char *p = NULL;

	if (NULL == (p = strtok(buff, ":")))
		return -1;
	strcpy(stu->name, p);

	if (NULL == (p = strtok(NULL, ":")))
		return -1;
	stu->num = atoi(p);

	if (NULL == (p = strtok(NULL, ":")))
		return -1;
	stu->ch = atoi(p);

	if (NULL == (p = strtok(NULL, ":")))
		return -1;
	stu->ma = atoi(p);
	
	if (NULL == (p = strtok(NULL, ":")))
		return -1;
	stu->en = atoi(p);

	return 0;
}
#else

int parse_student_info(char *buff, struct student *stu)
{
	char *p = NULL;
	int i = 0;
	int *data = &stu->num;

	if (NULL == (p = strtok(buff, ":")))
		return -1;
	strcpy(stu->name, p);

	while (NULL != (p = strtok(NULL, ":")))
		data[i++] = atoi(p);
	
	return 0;
}

#endif
