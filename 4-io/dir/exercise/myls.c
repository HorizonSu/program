#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>


#define ERROR(_errmesg_)	error(EXIT_FAILURE, errno, "%s:%d->%s\n", \
		__FILE__, __LINE__ - 1, _errmesg_)

struct file_stat {
	char mode[12];
	int nlink;
	char uname[32];
	char gname[32];
	int size;
	char time[32];
	char fname[256];
	char color[32];
};

int getfilestat(char *filename, struct file_stat *strfstat);
int showfilestat(struct file_stat *strfstat);

int main(int argc, char **argv)
{
	int f_isphidden = 1;
	struct file_stat *strfstat = NULL;
	char *filename = NULL;
	struct stat *statbuff = NULL;
	DIR *dirp = NULL;
	struct dirent *entry = NULL;
	
	if (1 == argc)
		filename = ".";
	else if (2 == argc)
		filename = argv[1];
	else {
		puts("invalid argment");
		exit(EXIT_FAILURE);
	}

	strfstat = (struct file_stat *)malloc(sizeof(struct file_stat));
	statbuff = (struct stat *)malloc(sizeof(struct stat));
	
	if (-1 == lstat(filename, statbuff))
		ERROR("lstat");

	if (S_ISDIR(statbuff->st_mode)) {
		chdir(filename);
		if (NULL == (dirp = opendir(filename)))
			ERROR("opendir");
		while (NULL != (entry = readdir(dirp))) {
			if ('.' != entry->d_name[0] || f_isphidden) {
				getfilestat(entry->d_name, strfstat);	
				showfilestat(strfstat);
			}
		}
	}else {
		getfilestat(filename, strfstat);	
		showfilestat(strfstat);
	}

	free(strfstat);
	free(statbuff);

	return 0;
}

int getfilestat(char *filename, struct file_stat *strfstat)
{
	struct stat *statbuff = NULL;
	int f_isx = 0;
	int namelen = 0;
	
	statbuff = (struct stat *)malloc(sizeof(struct stat));
	
	if (-1 == lstat(filename, statbuff))
		ERROR("lstat");
	
	memset(strfstat->mode, '-', sizeof(strfstat->mode));
	/*      get file mode    */
	if (statbuff->st_mode & S_IRUSR)
		strfstat->mode[1] = 'r';
	if (statbuff->st_mode & S_IWUSR)
		strfstat->mode[2] = 'w';
	if (statbuff->st_mode & S_IXUSR)
		strfstat->mode[3] = 'x', f_isx = 1;
	if (statbuff->st_mode & S_IRGRP)
		strfstat->mode[4] = 'r';
	if (statbuff->st_mode & S_IWGRP)
		strfstat->mode[5] = 'w';
	if (statbuff->st_mode & S_IXGRP)
		strfstat->mode[6] = 'x', f_isx = 1;
	if (statbuff->st_mode & S_IROTH)
		strfstat->mode[7] = 'r';
	if (statbuff->st_mode & S_IWOTH)
		strfstat->mode[8] = 'w';
	if (statbuff->st_mode & S_IXOTH)
		strfstat->mode[9] = 'x', f_isx = 1;
	
	/*         get file type         */
	if (S_ISBLK(statbuff->st_mode)) {
		strfstat->mode[0] = 'b';
		strcpy(strfstat->color, "\e[40;33;01m");
	}
	else if (S_ISCHR(statbuff->st_mode)) {
		strfstat->mode[0] = 'c';
		strcpy(strfstat->color, "\e[40;33;01m");
	}
	else if (S_ISDIR(statbuff->st_mode)) {
		strfstat->mode[0] = 'd';
		strcpy(strfstat->color, "\e[01;34m");
	}
	else if (S_ISLNK(statbuff->st_mode)) {
		strfstat->mode[0] = 'l';
		strcpy(strfstat->color, "\e[01;36m");
	}
	else if (S_ISSOCK(statbuff->st_mode)) {
		strfstat->mode[0] = 's';
		strcpy(strfstat->color, "\e[01;35m");
	}
	else if (S_ISFIFO(statbuff->st_mode)) {
		strfstat->mode[0] = 'p';
		strcpy(strfstat->color, "\e[40;33m");
	}else if (S_ISREG(statbuff->st_mode)) {
		if(f_isx)
			strcpy(strfstat->color, "\e[01;32m");
		else
			strfstat->color[0] = '\0';
	}
	strfstat->mode[10] = '\0';

	/*     get file nlink  */
	strfstat->nlink = statbuff->st_nlink;

	/*   get owner name   */
	strcpy(strfstat->uname, getpwuid(statbuff->st_uid)->pw_name);
	/*    get owner group name      */
	strcpy(strfstat->gname, getgrgid(statbuff->st_gid)->gr_name);
	/**  get file size  **/
	strfstat->size = statbuff->st_size;
	/*     get file time     */
	strcpy(strfstat->time, 4 + ctime(&statbuff->st_mtime));
	strfstat->time[strlen(strfstat->time)-1] = '\0';
	/*     get file name     */
	strcpy(strfstat->fname, filename);
	if (strfstat->mode[0] == 'l') {
		strcat(strfstat->fname, " -> ");
		namelen = strlen(strfstat->fname);
		namelen += readlink(filename, strfstat->fname + namelen, 256 - namelen);
		strfstat->fname[namelen] = '\0';
	}

	free(statbuff);

	return 0;
}

int showfilestat(struct file_stat *strfstat)
{
	printf("%s%3d %s %s %6d %s ",strfstat->mode, strfstat->nlink,
			strfstat->uname, strfstat->gname, strfstat->size, strfstat->time);
	printf("%s%s\e[0m\n", strfstat->color, strfstat->fname);

	return 0;
}
