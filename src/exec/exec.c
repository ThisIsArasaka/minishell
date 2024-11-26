#include "minishell.h"

// Fonction pour obtenir les chemins depuis la variable d'environnement PATH
char **get_paths_from_env(t_env *env) 
{
    char *path;
    char **paths;

    // Obtenir la valeur de la variable PATH dans l'environnement
    path = get_env_value(env, "PATH");
    if (!path)
        return (NULL);

    // Séparer les chemins par ':' pour les ajouter dans un tableau
    paths = ft_split(path, ':');
    if (!paths) {
        perror("ft_split failed");
        return (NULL);
    }

    return (paths);
}

// Fonction pour trouver le chemin d'une commande
char *find_cmd_path(t_data *data, char *cmd) 
{
    char **paths;
    char *full_path;
    int i;

    paths = get_paths_from_env(data->env);
    if (!paths)
        return (NULL);

    i = 0;
    while (paths[i]) {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin_free(full_path, cmd); // Correction: utiliser ft_strjoin_free
        if (access(full_path, X_OK) == 0) {
            ft_free_split(paths);
            return (full_path);
        }
        data->excode = 126;
        free(full_path);
        i++;
    }

    ft_free_split(paths);
    return (NULL);
}

// Fonction pour exécuter la commande
void exec_cmd(t_data *data, t_cmd_list *cmd, char **envp) {
    if (!cmd || !cmd->cmd)
        return;

    // Convertir la liste d'environnement en un tableau de chaînes
    envp = env_list_to_envp(data->env);
    if (!cmd || !cmd->cmd || cmd->cmd[0] == '\0') {
        free_envp(envp);
        exit(1);
    }

    cmd->cmd_path = find_cmd_path(data, cmd->cmd); // Trouver le chemin de la commande
    if (!cmd->cmd_path) {
        free_envp(envp);
        printf("%s: command not found\n", cmd->cmd);
        data->excode = 127;
        exit(1);
    }

    // Exécuter la commande avec execve
    if (execve(cmd->cmd_path, cmd->args, envp) == -1) 
    {
        //data->excode = 0;
        free_envp(envp);
        exit(1);
    }

    free_envp(envp);
}

// Fonction principale d'exécution des commandes
void exec(t_data *data) 
{
    printf("exec/ starting...\n");
    t_cmd_list *current_cmd;
    t_fd fds;

    fds.input = -2;
    current_cmd = data->cmd_list;
    while (current_cmd) 
    {   
        // Initialiser les redirections et les fds
        init_fds_and_redirections(current_cmd, &fds);

        // Si la commande n'est pas un builtin, exécuter le processus
        if (current_cmd->cmd && current_cmd->cmd[0]) {
            //if (!(is_builtin(current_cmd)))
                execute_process(data, current_cmd, &fds);
        }

        // Fermer les descripteurs de fichiers après l'exécution
        close_fds_parent(&fds);
        fds.input = fds.pipes[0];

        // Si c'est la dernière commande, fermer également les fds
        if (!current_cmd->next)
            close_fds_parent(&fds);

        // Passer à la commande suivante
        current_cmd = current_cmd->next;
    }

    // Attendre tous les processus enfants
    wait_child(data);
    close_all_fds(&fds);
}

///
// Configuration des pipes (exec -25)
void setup_pipes(t_fd *fds) 
{
    if (pipe(fds->pipes) == -1) 
	{
        perror("Pipe failed");
        exit(1);
    }
}

//Redirection des descripteurs de fichiers pour les pipelines (exec -25)
void redirect_input_output(t_fd *fds) 
{
    if (fds->input != -2) 
	{
        dup2(fds->input, STDIN_FILENO);
        close(fds->input);
    }
    if (fds->pipes[1] != -2) 
	{
        dup2(fds->pipes[1], STDOUT_FILENO);
        close(fds->pipes[1]);
    }
}


//env
int	count_env_entries(t_env *env_list)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env_list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**env_list_to_envp(t_env *env_list)
{
	int		size;
	int		i;
	char	**envp;
	t_env	*tmp;

	// Compter le nombre d'entrées dans la liste d'environnement
	size = count_env_entries(env_list);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (error_msg(MALLOC_ERROR, NULL), NULL);

	// Remplir le tableau
	i = 0;
	tmp = env_list;
	while (tmp)
	{
		if (!tmp->isunset)
		{
			// Créer une entrée pour l'environnement
			envp[i] = ft_strjoin(tmp->name, "=");
			if (!envp[i])
				return (free_tab(envp), error_msg(MALLOC_ERROR, NULL), NULL);

			envp[i] = ft_strjoin_free(envp[i], tmp->value);
			if (!envp[i])
				return (free_tab(envp), error_msg(MALLOC_ERROR, NULL), NULL);
			
			i++;
		}
		tmp = tmp->next;
	}

	envp[i] = NULL; // Terminer le tableau
	return (envp);
}




// Gère les redirections pour une commande donnée
// int handle_redirections(t_cmd_list *cmd)
// {
//     int fd;

//     if (cmd->output)
//     {
//         printf("Redirection de sortie: %s\n", cmd->output);
//         if (cmd->append)
//             fd = open(cmd->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
//         else
//             fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         if (fd == -1)
//         {
//             perror(cmd->output);
//             return (-1);
//         }
//         dup2(fd, 1);
//         close(fd);
//         printf("Redirection de sortie réussie.\n");
//     }
//     if (cmd->input)
//     {
//         printf("Redirection d'entrée: %s\n", cmd->input);
//         fd = open(cmd->input, O_RDONLY);
//         if (fd == -1)
//         {
//             perror(cmd->input);
//             return (-1);
//         }
//         dup2(fd, 0);
//         close(fd);
//         printf("Redirection d'entrée réussie.\n");
//     }
//     return (0);
// }




// // Fonctions auxiliaires
// void cleanup_exec(char **envp, char *cmd_path) 
// {
//     if (envp) 
// 	{
//         int i = 0;
//         while (envp[i]) 
// 		{
//             free(envp[i]);
//             i++;
//         }
//         free(envp);
//     }
//     if (cmd_path) 
// 		free(cmd_path);
// }

// void reset_signals_to_default() 
// {
//     signal(SIGINT, SIG_DFL);
//     signal(SIGQUIT, SIG_DFL);
// }

// // Construction du tableau des variables d'environnement à partir de la liste chaînée
// char **build_envp_cache(t_env *env) {
//     int i = 0;
//     t_env *tmp = env;

//     while (tmp) {  // Compter le nombre de variables d'environnement
//         i++;
//         tmp = tmp->next;
//     }

//     char **envp_copy = malloc((i + 1) * sizeof(char *));
//     if (!envp_copy) {
//         perror("malloc failed for envp_copy");
//         return NULL;
//     }

//     i = 0;
//     tmp = env;
//     while (tmp) {
//         char *env_var = malloc(strlen(tmp->name) + strlen(tmp->value) + 2);  // +2 pour '=' et '\0'
//         if (!env_var) {
//             perror("malloc failed for env_var");
//             while (i-- > 0) free(envp_copy[i]);
//             free(envp_copy);
//             return NULL;
//         }
//         strcpy(env_var, tmp->name);
//         strcat(env_var, "=");
//         strcat(env_var, tmp->value);
//         envp_copy[i++] = env_var;
//         tmp = tmp->next;
//     }
//     envp_copy[i] = NULL;
//     return envp_copy;
// }

// // Fonction pour obtenir les chemins de PATH sous forme de tableau
// char **get_paths_from_env() 
// {
//     char *path = getenv("PATH");
//     if (!path) 
// 	{
//         perror("PATH variable not found.");
//         return NULL;
//     }
//     // Utilisation de `ft_split` pour diviser les chemins de `PATH` par `:`
//     return ft_split(path, ':');
// }

// // Trouver le chemin complet d'une commande
// char *find_cmd_path(char *cmd) 
// {
//     char **paths = get_paths_from_env();
//     char *full_path = NULL;
//     int i = 0;

//     if (!paths) 
// 		return NULL;

//     while (paths[i])
// 	{
//         full_path = malloc(strlen(paths[i]) + strlen(cmd) + 2);  // +2 pour '/' et '\0'
//         if (full_path) 
// 		{
//             strcpy(full_path, paths[i]);
//             strcat(full_path, "/");
//             strcat(full_path, cmd);
//         }

//         if (access(full_path, X_OK) == 0) 
// 		{
//             int j = 0;
//             while (paths[j]) 
// 			{
//                 free(paths[j]);
//                 j++;
//             }
//             free(paths);
//             return full_path;
//         }
//         free(full_path);
//         i++;
//     }
//     int j = 0;
//     while (paths[j]) 
// 	{
//         free(paths[j]);
//         j++;
//     }
//     free(paths);
//     return NULL;
// }
// void exec_cmd(t_cmd_list *cmd_list, t_env *env) 
// {
//     char **envp = build_envp_cache(env);
//     char *cmd_path;

//     if (!cmd_list || !cmd_list->cmd) {
//         cleanup_exec(envp, NULL);
//         return;
//     }

//     cmd_path = find_cmd_path(cmd_list->cmd);
//     if (!cmd_path) 
// 	{
//         cleanup_exec(envp, NULL);
//         printf("%s: command not found\n", cmd_list->cmd);
//         exit(127);  // Code d'erreur standard pour "commande introuvable"
//     }

//     reset_signals_to_default();
//     if (execve(cmd_path, cmd_list->args, envp) == -1) 
// 	{
//         perror("execve failed");
// 		printf("Failed to execute: %s\n", cmd_list->cmd);
//         cleanup_exec(envp, cmd_path);
//         exit(1);
//     }
// }



// // Fonction principale d’exécution
// void exec(t_data *data) {
//     printf("exec/ Starting execution...\n");
//     t_cmd_list *current_cmd = data->cmd_list;

//     if (!current_cmd) {
//         printf("No commands to execute.\n");
//         return;
//     }

//     // Compter le nombre de commandes
//     int num_cmds = 0;
//     t_cmd_list *tmp = current_cmd;
//     while (tmp) {
//         num_cmds++;
//         tmp = tmp->next;
//     }

//     // Allouer les pipes
//     int (*pipe_fds)[2] = malloc(sizeof(int[2]) * (num_cmds - 1));
//     if (!pipe_fds) {
//         perror("malloc failed for pipe_fds");
//         exit(1);
//     }

//     // Initialiser les pipes
//     int pipe_index = 0;
//     while (pipe_index < num_cmds - 1) {
//         printf("Creating pipe %d\n", pipe_index);
//         if (pipe(pipe_fds[pipe_index]) == -1) {
//             perror("Pipe creation failed");
//             free(pipe_fds);
//             exit(1);
//         }
//         pipe_index++;
//     }

//     int i = 0;
//     while (current_cmd) 
//     {
//         printf("Processing command '%s', i = %d, num_cmds = %d\n", current_cmd->cmd, i, num_cmds);


//         // Vérifier si c'est un builtin
//         if (is_builtin(current_cmd)) 
//         {
            
//             printf("exec/ Command is a builtin\n");
//             // Gestion des redirections pour les builtins
//             if (handle_redirections(current_cmd) == -1) 
//             {
//                 printf("exec/ handle_redir_builtin\n");
//                 current_cmd = current_cmd->next;
//                 i++;
//                 continue;
//             }
//             printf("exec/ starting input redir\n");
//             // Rediriger les pipes si nécessaire
//             if (fcntl(STDOUT_FILENO, F_GETFD) == -1) 
//             {
//                 printf("STDOUT_FILENO was closed. Re-opening...\n");
//                 if (open("/dev/null", O_WRONLY) != STDOUT_FILENO) 
//                 {
//                     perror("Failed to reinitialize STDOUT_FILENO");
//                     exit(1);
//                 }
// }
//             if (i > 0) 
//             {  // Pipe d'entrée
//                 if (dup2(pipe_fds[i - 1][0], STDIN_FILENO) == -1) 
//                 {
//                     perror("dup2 input failed");
//                     exit(1);
//                 }
//                 printf("exec/ Pipe input redirection successful\n");
//             }
//             printf("exec/ starting pipe output redir\n");
//             if (i < num_cmds - 1) 
//             {  // Pipe de sortie
//                 printf("Attempting dup2(pipe_fds[%d][1] = %d, STDOUT_FILENO = %d)\n", i, pipe_fds[i][1], STDOUT_FILENO);
//                 if (dup2(pipe_fds[i][1], STDOUT_FILENO) == -1) 
//                 {
//                     perror("dup2 output failed");
//                     exit(1);
//                 }
//                 printf("exec/ Pipe output redirection successful\n");
//             }
//             printf("exec/ starting close pipes\n");
//             // Fermer tous les pipes inutilisés
//             int j = 0;
//             while (j < num_cmds - 1) {
//                 close(pipe_fds[j][0]);
//                 close(pipe_fds[j][1]);
//                 j++;
//             }
//             printf("exec/ bultins_close\n");

//             // Exécuter le builtin et passer à la commande suivante
//             builtin(data);
//             current_cmd = current_cmd->next;
//             i++;
//             continue;
//         }

//         // Commande externe : créer un processus enfant
//         pid_t pid = fork();
//         if (pid == 0) 
//         {  // Processus enfant
//             printf("exec/ Child process\n");
//             if (handle_redirections(current_cmd) == -1)
//                 exit(1);

//             // Rediriger les pipes
//             if (i > 0)  // Pipe d'entrée
//                 dup2(pipe_fds[i - 1][0], STDIN_FILENO);
//             if (i < num_cmds - 1)  // Pipe de sortie
//                 dup2(pipe_fds[i][1], STDOUT_FILENO);

//             // Fermer tous les pipes inutilisés
//             int j = 0;
//             while (j < num_cmds - 1) {
//                 close(pipe_fds[j][0]);
//                 close(pipe_fds[j][1]);
//                 j++;
//             }

//             // Exécuter la commande
//             exec_cmd(current_cmd, data->env);
//             exit(1);  // En cas d'échec
//         } else if (pid > 0) {  // Processus parent
//             if (i > 0)
//                 close(pipe_fds[i - 1][0]);  // Fermer la lecture du pipe précédent
//             if (i < num_cmds - 1)
//                 close(pipe_fds[i][1]);  // Fermer l'écriture du pipe actuel
//         } else {
//             perror("fork failed");
//             free(pipe_fds);
//             exit(1);
//         }

//         current_cmd = current_cmd->next;
//         i++;
//     }

//     // Fermer tous les descripteurs de fichiers restants
//     int j = 0;
//     while (j < num_cmds - 1) {
//         close(pipe_fds[j][0]);
//         close(pipe_fds[j][1]);
//         j++;
//     }
//     free(pipe_fds);

//     // Attendre tous les processus enfants
//     int status;
//     while (wait(&status) > 0)
//         ;
// }