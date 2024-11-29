#include "minishell.h"

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

// Fonction pour exécuter la commande
void	exec_cmd(t_data *data, t_cmd_list *cmd, char **envp)
{
	if (!cmd || !cmd->cmd)
		return ;
	envp = env_to_array(data->env);
	if (!cmd || !cmd->cmd || cmd->cmd[0] == '\0')
	{
		free_envp(envp);
		data->excode = 1;
		exit_free(data);
	}
	cmd->cmd_path = get_env_exec(data->env, cmd->cmd);
	if (execve(cmd->cmd_path, cmd->args, envp) == -1)
	{
		free_envp(envp);
		error_msg(NO_CMD, cmd->cmd);
		data->excode = 127;
		exit_free(data);
	}
}

int	is_builtin_command(t_data *data, t_cmd_list *cmd)
{
	if (ft_strncmp(cmd->cmd, "exit\0", 5) == 0 && data->cmd_list == cmd
		&& !cmd->next)
	{
		ft_exit(data, cmd);
		return (1);
	}
	if (ft_strncmp(cmd->cmd, "cd\0", 3) == 0)
	{
		ft_cd(cmd, data);
		return (1);
	}
	if (ft_strncmp(cmd->cmd, "unset\0", 6) == 0)
	{
		ft_unset(cmd, data->env);
		return (1);
	}
	if (ft_strncmp(cmd->cmd, "export\0", 7) == 0 && cmd->args[1])
	{
		ft_export(cmd, data);
		return (1);
	}
	return (0);
}
