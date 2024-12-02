/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:23:44 by olardeux          #+#    #+#             */
/*   Updated: 2024/12/02 11:16:40 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_var(char *line, int place, t_data *data)
{
	char	*var;

	if (line[place + 1] == '?')
	{
		var = ft_itoa(data->excode);
		if (!var)
			return (error_msg(MALLOC_ERROR, NULL), free(line), NULL);
	}
	else
	{
		var = get_env_value(data->env, line + place + 1);
		if (!var)
			var = "";
	}
	return (var);
}

void	replace_var_loop(t_parsing *p, char *var, char *new, int place)
{
	while (p->line[p->i])
	{
		if (p->i == place)
		{
			if (in_quote(p->line, place) || var[0] == '\0')
				add_var(&p->i, &p->j, var, new);
			else
				add_var_quoted(&p->i, &p->j, var, new);
			skip_var_name(p->line, &p->i);
		}
		new[p->j] = p->line[p->i];
		if (p->line[p->i])
			p->i++;
		p->j++;
	}
}

char	*replace_var(char *line, int place, t_data *data)
{
	t_parsing	p;
	char		*new;
	char		*var;

	p.i = 0;
	p.j = 0;
	p.line = line;
	var = init_var(line, place, data);
	new = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(var) + 2));
	if (!new)
		return (error_msg(MALLOC_ERROR, NULL), free(line), NULL);
	replace_var_loop(&p, var, new, place);
	if (line[place + 1] == '?')
		free(var);
	new[p.j] = 0;
	return (free(line), new);
}

char	*check(char *line, t_data *data)
{
	int	i;

	i = 0;
	if (!check_quote(line))
		return (data->excode = 2, error_msg("quote", NULL), free(line), NULL);
	while (line[i])
	{
		if (line[i] == '\'')
			skip_quote(line, &i);
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break ;
		}
		if (line[i] == '$' && (!ft_isblank(line[i + 1]) && line[i + 1] != '\0'
				&& (ft_isalnum(line[i + 1]) || line[i + 1] == '?')))
		{
			line = replace_var(line, i, data);
			if (!line)
				return (NULL);
		}
		i++;
	}
	return (line);
}
