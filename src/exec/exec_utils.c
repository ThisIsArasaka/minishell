#include "minishell.h"

void	init_fds_and_redirections(t_cmd_list *current_cmd, t_fd *fds)
{
    init_fds(fds); // Initialisation des fds
    if (current_cmd->next) 
    {
        if (pipe(fds->pipes) == -1)
            exit(1);
    }
    //apply_redirections(current_cmd, &fds->redir[0], &fds->redir[1]);
    set_fds(fds); // Appliquer les fds
}

int	is_dir(const char *path)
{
    struct stat	path_stat;

    if (stat(path, &path_stat) != 0)
        return (0);
    return (S_ISDIR(path_stat.st_mode));
}

void	execute_process(t_data *data, t_cmd_list *current_cmd, t_fd *fds)
{
	printf("execu/ execute process\n");
    pid_t	pid;

    pid = fork();
    if (pid == -1)
    {
        close_all_fds(fds);
        exit(0);
    }
    else if (pid == 0)
    {
        if (is_builtin(current_cmd)) // Commande builtin
        {
            builtin(data);
            close_all_fds(fds);
            exit(0);
        }
        else
            execute_child(data, current_cmd, fds);
    }
}

// void	run_builtins(t_data *data, t_cmd_list *cmd, t_fd *fds)
// {
//     child_builtins(fds);
//     if (ft_strncmp(cmd->cmd, "echo", 4) == 0 && ft_strlen(cmd->cmd) == 4)
//         ft_echo(data, cmd, fds->output, fds);
//     else if (ft_strncmp(cmd->cmd, "env", 3) == 0 && ft_strlen(cmd->cmd) == 3)
//         bi_env(data, cmd, fds->output, fds);
//     else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0 && ft_strlen(cmd->cmd) == 3)
//         bi_pwd(data, cmd, fds->output, fds);
// }

void	child_builtins(t_fd *fds)
{
    if (fds->input != -2)
        close(fds->input);
    if (fds->output == -2)
        fds->output = dup(STDOUT_FILENO);
    if (fds->output == -1)
        (close_all_fds(fds), exit(0));
}



// char	*get_cmd_path(t_data *data, t_cmd_list *cmd, t_fd *fds, char **envp)
// {
//     if (ft_strchr(cmd->cmd, '/') != NULL)
//     {
//         if (is_dir(cmd->cmd))
//         {
//             ft_putstr_fd(cmd->cmd, STDOUT_FILENO);
//             ft_putstr_fd(": Is a directory\n", STDOUT_FILENO);
//             data->excode = 126;
//             free_envp(envp);
//             close_all_fds(fds);
//             exit;
//         }
//         else if (access(cmd->cmd, F_OK | X_OK) == 0)
//             return (ft_strdup(cmd->cmd));
//     }
//     else
//     {
//         data->excode = 126;
//         return (find_cmd_path(cmd->cmd));
//     }
//     return (NULL);
// }

void	free_envp(char **envp)
{
    int	i;

    i = 0;
    while (envp[i])
    {
        free(envp[i]);
        i++;
    }
    free(envp);
}

void	execute_child(t_data *data, t_cmd_list *cmd, t_fd *fds)
{
	printf("execu/ execute child\n");
    if (fds->pipes[0] != -2)
        close(fds->pipes[0]);
    if (fds->input != -2)
        if (dup2(fds->input, STDIN_FILENO) == -1)
            (close_all_fds(fds), exit(1));
    if (fds->output != -2)
        if (dup2(fds->output, STDOUT_FILENO) == -1)
            (close_all_fds(fds), exit(1));
    close_all_fds(fds);
    exec_cmd(data, cmd, NULL); // Exécution de la commande
}


void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}