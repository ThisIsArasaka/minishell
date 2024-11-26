#include "minishell.h"
void	init_fds(t_fd *fds)
{
    fds->output = -2;
    fds->pipes[0] = -2;
    fds->pipes[1] = -2;
    fds->redir[0] = -2;
    fds->redir[1] = -2;
}

void	set_fds(t_fd *fd)
{
    if (fd->pipes[1] != -2)
        fd->output = fd->pipes[1];
    if (fd->redir[0] != -2)
    {
        if (fd->input != -2)
            close(fd->input);
        fd->input = fd->redir[0];
    }
    if (fd->redir[1] != -2)
    {
        if (fd->pipes[1] != -2)
            close(fd->pipes[1]);
        fd->output = fd->redir[1];
    }
}

void	close_all_fds(t_fd *fds)
{
    printf("close all fds\n");
    if (!(fds->pipes[0] == -2) && fds->pipes[0] >= 0)
        close(fds->pipes[0]);
    printf("close all fds 1\n");
    if (!(fds->pipes[1] == -2) && fds->pipes[1] >= 0)
        close(fds->pipes[1]);
    printf("close all fds 2\n");
    if (!(fds->redir[0] == -2) && fds->redir[0] >= 0)
        close(fds->redir[0]);
    printf("close all fds 3\n");
    if (!(fds->redir[1] == -2) && fds->redir[1] >= 0)
        close(fds->redir[1]);
    printf("close all fds 4\n");
    if (!(fds->output == -2) && fds->output >= 0)
        close(fds->output);
    printf("close all fds 5\n");
    if (!(fds->input == -2) && fds->input >= 0)
        close(fds->input);
    printf("close all fds end\n");
}

void	close_fds_parent(t_fd *fds)
{
    if (fds->input != -2 && fds->input >= 0)
        close(fds->input);
    if (fds->output != -2 && fds->output >= 0)
        close(fds->output);
}

void	wait_child(t_data *data)
{
    int		status;
    pid_t	pid;

    while (1)
    {
        pid = wait(&status);
        if (pid <= 0)
            break ;
        if (WIFEXITED(status))
            data->excode = WEXITSTATUS(status);
        if (errno == 13)
            data->excode = 126;
        else if (WIFSIGNALED(status))
            data->excode = 128 + WTERMSIG(status);
    }
    if (pid == -1 && errno != ECHILD)
    {
        perror("wait");
        data->excode = 127;
        exit(EXIT_FAILURE);
    }
}
