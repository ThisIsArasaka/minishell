#include "minishell.h"

void	loop_here_doc(char *delimiter, int fd)
{
	char	*line;
	char	*limiter;

	(limiter = ft_strjoin(delimiter, "\n"));
	while (1)
	{
		line = readline(RED "> " RESET);
		if (g_sig == SIGINT)
		{
			//shell->excode = 130;
			//shell->tmpexcode = 130;
			g_sig = 0;
			free(line);
			break ;
		}
		if (line == NULL || (!ft_strncmp(line, limiter, ft_strlen(line))
				&& ft_strlen(line) == ft_strlen(limiter) - 1))
		{
			free(line);
			break ;
		}
		(ft_putstr_fd(line, fd), ft_putstr_fd("\n", fd));
		free(line);
	}
	free(limiter);
}

int	handle_heredoc(char *delimiter)
{
	char	*file_name;
	int		fd_out;
	int		fd_in;

	file_name = ft_strdup("heredoc_tmp_");
	while (access(file_name, F_OK) == 0)
		file_name = strjoin_free(file_name, "42");
	fd_out = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("Error opening heredoc file");
		free(file_name);
		return (-1);
	}
	loop_here_doc(delimiter, fd_out);
	close(fd_out);
	fd_in = open(file_name, O_RDONLY);
	if (fd_in == -1)
	{
		perror("Error opening heredoc file for reading");
		free(file_name);
		return (-1);
	}
	(unlink(file_name), free(file_name));
	return (fd_in);
}