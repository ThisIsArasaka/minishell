/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:23:44 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/18 06:27:13 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_var(char *line, int place, t_env *env)
{
	char	*var;

	// if (line[place + 1] == '?')
	// {
	// 	var = ft_itoa(g_status);
	// 	if (!var)
	// 		return (error_msg(MALLOC_ERROR, NULL), free(line), NULL);
	// }
	// else
	{
		var = get_env_value(env, line + place + 1);
		if (!var)
			var = "";
	}
	return (var);
}

char	*replace_var(char *line, int place, t_env *env)
{
	int		i;
	int		j;
	char	*new;
	char	*var;

	i = 0;
	j = 0;
	var = init_var(line, place, env);
	new = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(var) + 2));
	if (!new)
		return (error_msg(MALLOC_ERROR, NULL), free(line), NULL);
	while (line[i])
	{
		if (i == place)
		{
			if (in_quote(line, place))
				add_var(&i, &j, var, new);
			else
				add_var_quoted(&i, &j, var, new);
			skip_var_name(line, &i);
		}
		new[j] = line[i];
		if (line[i])
			i++;
		j++;
	}
	new[j] = 0;
	return (free(line), new);
}

char	*check(char *line, t_env *env)
{
	int	i;

	i = 0;
	if (!check_quote(line))
		return (free(line), NULL);
	while (line[i])
	{
		if (line[i] == '\'')
			skip_quote(line, &i);
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break ;
		}
		if (line[i] == '$' && !ft_isblank(line[i + 1]))
		{
			line = replace_var(line, i, env);
			if (!line)
				return (NULL);
		}
		i++;
	}
	printf("line: %s\n", line);
	return (line);
}
