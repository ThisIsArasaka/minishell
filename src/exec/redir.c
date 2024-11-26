#include "minishell.h"

// int	handle_output_redir(t_redir *redir, int fd_out, t_data *shell)
// {
// 	if (fd_out != -2)
// 		close(fd_out);
// 	if (redir->token == GREATER)
// 	{
// 		fd_out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd_out == -1)
// 		{
// 			perror(redir->file);
// 			shell->excode = 1;
// 			return (-1);
// 		}
// 	}
// 	else if (redir->token == D_GREATER)
// 	{
// 		fd_out = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd_out == -1)
// 		{
// 			perror(redir->file);
// 			shell->excode = 1;
// 			return (-1);
// 		}
// 	}
// 	return (fd_out);
// }

// int	handle_input_redir(t_redir *redir, int fd_in, t_data *shell)
// {
// 	if (fd_in != -2)
// 		close(fd_in);
// 	if (redir->token == LOWER)
// 	{
// 		fd_in = open(redir->file, O_RDONLY);
// 		if (fd_in == -1)
// 		{
// 			perror(redir->file);
// 			shell->excode = 1;
// 			return (-1);
// 		}
// 	}
// 	else if (redir->token == D_LOWER)
// 	{
// 		fd_in = handle_heredoc(redir->file, shell);
// 		if (fd_in == -1)
// 		{
// 			perror("heredoc.tmp");
// 			return (-1);
// 		}
// 	}
// 	return (fd_in);
// }
// void	apply_redirections(t_cmd *cmd, int *fd_in, int *fd_out, t_shell *shell)
// {
// 	t_redir	*redir;

// 	redir = cmd->redir;
// 	while (redir)
// 	{
// 		if (redir->token == LOWER || redir->token == D_LOWER)
// 		{
// 			*fd_in = handle_input_redir(redir, *fd_in, shell);
// 		}
// 		else if (redir->token == GREATER || redir->token == D_GREATER)
// 		{
// 			*fd_out = handle_output_redir(redir, *fd_out, shell);
// 		}
// 		if (*fd_in == -1 || *fd_out == -1)
// 			break ;
// 		redir = redir->next;
// 	}
// }