
#include "shell.h"

/**
 * is_cmd - checks if a file is an executable command
 * @path: path to the file
 *
 * Return: 1 if it's an executable command, 0 otherwise
 */
int is_cmd(char *path)
{
    struct stat st;

    if (!path || stat(path, &st) == -1)
        return 0;

    return S_ISREG(st.st_mode);
}

/**
 * find_cmd_in_path - finds a command in the PATH
 * @info: the info struct
 * @cmd: the command to find
 *
 * Return: full path of the command if found, NULL otherwise
 */
char *find_cmd_in_path(info_t *info, char *cmd)
{
    char *pathstr = _getenv(info, "PATH");
    if (!pathstr)
        return NULL;

    char *token = strtok(pathstr, ":");
    while (token)
    {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", token, cmd);

        if (is_cmd(path))
            return strdup(path);

        token = strtok(NULL, ":");
    }

    return NULL;
}

