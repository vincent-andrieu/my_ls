/*
** EPITECH PROJECT, 2019
** my_ls
** File description:
** flag l
*/

#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/sysmacros.h>
#include "my.h"
#include "my_ls.h"

static char get_file_type(struct stat st)
{
    if (S_ISREG(st.st_mode))
        return '-';
    if (S_ISDIR(st.st_mode))
        return 'd';
    if (S_ISLNK(st.st_mode))
        return 'l';
    if (S_ISFIFO(st.st_mode))
        return 'p';
    if (S_ISSOCK(st.st_mode))
        return 's';
    if (S_ISBLK(st.st_mode))
        return 'b';
    if (S_ISCHR(st.st_mode))
        return 'c';
    return 0;
}

static void put_file_permissions(struct stat st)
{
    my_putchar((st.st_mode & S_IRUSR) ? 'r' : '-');
    my_putchar((st.st_mode & S_IWUSR) ? 'w' : '-');
    my_putchar((st.st_mode & S_IXUSR) ? 'x' : '-');
    my_putchar((st.st_mode & S_IRGRP) ? 'r' : '-');
    my_putchar((st.st_mode & S_IWGRP) ? 'w' : '-');
    my_putchar((st.st_mode & S_IXGRP) ? 'x' : '-');
    my_putchar((st.st_mode & S_IROTH) ? 'r' : '-');
    my_putchar((st.st_mode & S_IWOTH) ? 'w' : '-');
    my_putchar((st.st_mode & S_IXOTH) ? 'x' : '-');
    my_putstr(". ");
}

static void put_month(struct stat st)
{
    int i = 0;
    char *date;

    time(&st.st_mtime);
    date = ctime(&st.st_mtime);
    for (; date[0] != ' ' && date[0] != '\0'; date++);
    if (date[0] == '\0')
        return;
    date++;
    for (; date[i] != ':' && date[i] != '\0'; i++);
    for (i++; date[i] != ':' && date[i] != '\0'; i++);
    date[i] = '\0';
    my_putstr(date);
    my_putchar(' ');
}

static void put_details(struct stat st, char *filename)
{
    my_putchar(get_file_type(st));
    put_file_permissions(st);
    my_put_nbr(st.st_nlink);
    my_putchar(' ');
    my_putstr(getpwuid(st.st_uid)->pw_name);
    my_putchar(' ');
    my_putstr(getgrgid(st.st_gid)->gr_name);
    my_putchar('\t');
    my_put_nbr(st.st_size);
    my_putchar('\t');
    put_month(st);
    my_putstr(filename);
    my_putchar('\n');
}

void flag_l(options_t *options, char **argv, int argc)
{
    DIR *dir = opendir(argv[0]);
    struct dirent *d_file = dir != NULL ? readdir(dir) : NULL;
    struct stat st;
    char *filepath;

    if (dir == NULL || d_file == NULL)
        exit(EXIT_ERROR);
    while (d_file != NULL) {
        if (d_file->d_name[0] != '.') {
            filepath = my_strndup(argv[0], my_strlen(argv[0])
                        + my_strlen(d_file->d_name) + 1);
            my_strcat(filepath, "/");
            my_strcat(filepath, name);
            lstat(filepath, &st);
            free(filepath);
            put_details(st, d_file->d_name);
        }
        d_file = readdir(dir);
    }
    closedir(dir);
}