#include "minishell.h"

// Fonctions auxiliaires
void cleanup_exec(char **envp, char *cmd_path) 
{
    if (envp) 
	{
        int i = 0;
        while (envp[i]) 
		{
            free(envp[i]);
            i++;
        }
        free(envp);
    }
    if (cmd_path) 
		free(cmd_path);
}

void reset_signals_to_default() 
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

// Construction du tableau des variables d'environnement à partir de la liste chaînée
char **build_envp_cache(t_env *env) {
    int i = 0;
    t_env *tmp = env;

    while (tmp) {  // Compter le nombre de variables d'environnement
        i++;
        tmp = tmp->next;
    }

    char **envp_copy = malloc((i + 1) * sizeof(char *));
    if (!envp_copy) {
        perror("malloc failed for envp_copy");
        return NULL;
    }

    i = 0;
    tmp = env;
    while (tmp) {
        char *env_var = malloc(strlen(tmp->name) + strlen(tmp->value) + 2);  // +2 pour '=' et '\0'
        if (!env_var) {
            perror("malloc failed for env_var");
            while (i-- > 0) free(envp_copy[i]);
            free(envp_copy);
            return NULL;
        }
        strcpy(env_var, tmp->name);
        strcat(env_var, "=");
        strcat(env_var, tmp->value);
        envp_copy[i++] = env_var;
        tmp = tmp->next;
    }
    envp_copy[i] = NULL;
    return envp_copy;
}

// Fonction pour obtenir les chemins de PATH sous forme de tableau
char **get_paths_from_env() 
{
    char *path = getenv("PATH");
    if (!path) 
	{
        perror("PATH variable not found.");
        return NULL;
    }
    // Utilisation de `ft_split` pour diviser les chemins de `PATH` par `:`
    return ft_split(path, ':');
}

// Trouver le chemin complet d'une commande
char *find_cmd_path(char *cmd, t_env *env) 
{
    char **paths = get_paths_from_env(env);
    char *full_path = NULL;
    int i = 0;

    if (!paths) 
		return NULL;

    while (paths[i])
	{
        full_path = malloc(strlen(paths[i]) + strlen(cmd) + 2);  // +2 pour '/' et '\0'
        if (full_path) 
		{
            strcpy(full_path, paths[i]);
            strcat(full_path, "/");
            strcat(full_path, cmd);
        }

        if (access(full_path, X_OK) == 0) 
		{
            int j = 0;
            while (paths[j]) 
			{
                free(paths[j]);
                j++;
            }
            free(paths);
            return full_path;
        }
        free(full_path);
        i++;
    }
    int j = 0;
    while (paths[j]) 
	{
        free(paths[j]);
        j++;
    }
    free(paths);
    return NULL;
}


// Exécution d'une commande
void exec_cmd(t_cmd_list *cmd_list, t_env *env) 
{
    char **envp = build_envp_cache(env);
    char *cmd_path;

    if (!cmd_list || !cmd_list->cmd) {
        cleanup_exec(envp, NULL);
        return;
    }

    cmd_path = find_cmd_path(cmd_list->cmd, env);
    if (!cmd_path) 
	{
        cleanup_exec(envp, NULL);
        printf("%s: command not found\n", cmd_list->cmd);
        exit(127);  // Code d'erreur standard pour "commande introuvable"
    }

    reset_signals_to_default();
    if (execve(cmd_path, cmd_list->args, envp) == -1) 
	{
        perror("execve failed");
		printf("Failed to execute: %s\n", cmd_list->cmd);
        cleanup_exec(envp, cmd_path);
        exit(1);
    }
}


// // Configuration des pipes (exec -25)
// void setup_pipes(t_fd *fds) 
// {
//     if (pipe(fds->pipes) == -1) 
// 	{
//         perror("Pipe failed");
//         exit(1);
//     }
// }

// Redirection des descripteurs de fichiers pour les pipelines (exec -25)
// void redirect_input_output(t_fd *fds) 
// {
//     if (fds->input != -2) 
// 	{
//         dup2(fds->input, STDIN_FILENO);
//         close(fds->input);
//     }
//     if (fds->pipes[1] != -2) 
// 	{
//         dup2(fds->pipes[1], STDOUT_FILENO);
//         close(fds->pipes[1]);
//     }
// }

// Fermer les descripteurs inutilisés après le fork (exec -25)
// void close_fds_parent(t_fd *fds) 
// {
//     close(fds->pipes[0]);
//     close(fds->pipes[1]);
// }


// Fonction principale d’exécution
void exec(t_data *data) 
{
    t_cmd_list *current_cmd =data->cmd_list;
    int num_cmds = 0;

    // Compter le nombre de commandes
    while (current_cmd) 
	{
        num_cmds++;
        current_cmd = current_cmd->next;
    }

    // Allocation dynamique pour les pipes
    int (*pipe_fds)[2] = malloc(sizeof(int[2]) * (num_cmds - 1));
    if (!pipe_fds) 
	{
        perror("malloc failed for pipe_fds");
        exit(1);
    }

    // Initialiser tous les pipes nécessaires
    int i = 0;
    while (i < num_cmds - 1) 
	{
        if (pipe(pipe_fds[i]) == -1) 
		{
            perror("Pipe failed");
            free(pipe_fds);
            exit(1);
        }
        i++;
    }

    current_cmd = data->cmd_list;
    i = 0;
    while (current_cmd) 
	{
        pid_t pid = fork();
        if (pid == 0) 
		{  // Enfant

            // Rediriger l'entrée depuis le pipe précédent (si ce n'est pas la première commande)
            if (i > 0) {
                dup2(pipe_fds[i - 1][0], STDIN_FILENO);
            }

            // Rediriger la sortie vers le pipe suivant (si ce n'est pas la dernière commande)
            if (i < num_cmds - 1) {
                dup2(pipe_fds[i][1], STDOUT_FILENO);
            }

            // Fermer tous les pipes dans l'enfant
            int j = 0;
            while (j < num_cmds - 1) {
                close(pipe_fds[j][0]);
                close(pipe_fds[j][1]);
                j++;
            }

            // Exécuter la commande
            exec_cmd(current_cmd, data->env);
            exit(1);  // Quitter si l'exécution échoue
        } 
        else if (pid > 0) 
		{  // Parent
            // Fermer les descripteurs inutilisés dans le parent
            if (i > 0) close(pipe_fds[i - 1][0]);  // Fermer l'entrée du pipe précédent
            if (i < num_cmds - 1) close(pipe_fds[i][1]);  // Fermer la sortie du pipe actuel
        } 
        else 
		{
            perror("fork failed");
            free(pipe_fds);
            exit(1);
        }

        // Passer à la commande suivante
        current_cmd = current_cmd->next;
        i++;
    }

    // Fermer tous les descripteurs restants
    int j = 0;
    while (j < num_cmds - 1) 
	{
        close(pipe_fds[j][0]);
        close(pipe_fds[j][1]);
        j++;
    }
    free(pipe_fds);

    // Attendre tous les processus enfants
    int status;
    while (wait(&status) > 0);
}

ok
