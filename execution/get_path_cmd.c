#include "../mini_shell.h"

char *split_path(char *path, char *cmd)
{
    char *splitted_path;
    char **paths;
    char *complete_path;
    int i;

    splitted_path = ft_substr(path, 5, ft_strlen(path) - 5);
    paths = ft_split(splitted_path, ':');
    cmd = ft_strjoin("/", cmd);
    free(splitted_path);
    i = 0;
    while (paths[i])
    {
        complete_path = ft_strjoin(paths[i], cmd);
        if (access(complete_path, F_OK | X_OK) != -1)
                return (free_double(paths), free(cmd), complete_path);
        free(complete_path);
        i++;
	}
	return (free_double(paths), free(cmd), NULL);
}

char *get_path_cmd(char *cmd, t_listt *env)
{
    while (env)
    {
        if (!ft_strncmp(env->content, "PATH=", 5))
            return (split_path(env->content, cmd));
        env = env->next;
    }
    return (NULL);
}