/*
** EPITECH PROJECT, 2019
** my_ls
** File description:
** stock files in a chain list
*/

#include <dirent.h>
#include "my.h"
#include "my_ls.h"

static struct stat get_filepath_stats(char *path, char *name)
{
    struct stat st;
    char *filepath = my_strndup(path, my_strlen(path)
                + my_strlen(name) + 1);

    my_strcat(filepath, "/");
    my_strcat(filepath, name);
    lstat(filepath, &st);
    free(filepath);
    return st;
}

static file_t *fill_file(char *path, char *name, file_t *next,
                        bool get_allfiles)
{
    file_t *file;

    if (name[0] != '.' || get_allfiles) {
        file = malloc(sizeof(file_t));
        if (file == NULL)
            exit(EXIT_ERROR);
        file->name = my_strdup(name);
        file->st = get_filepath_stats(path, name);
        file->next = next;
        if (file->next != NULL)
            file->next->prev = file;
        return file;
    }
    return next;
}

file_t *get_files(char *path, bool get_allfiles)
{
    DIR *dir = opendir(path);
    struct dirent *d_file = dir != NULL ? readdir(dir) : NULL;
    file_t *files = NULL;

    if (dir == NULL || d_file == NULL)
        exit(EXIT_ERROR);
    while (d_file != NULL) {
        files = fill_file(path, d_file->d_name, files, get_allfiles);
        d_file = readdir(dir);
    }
    closedir(dir);
    files->prev = NULL;
    return files;
}