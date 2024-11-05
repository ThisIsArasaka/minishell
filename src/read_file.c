/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:56:17 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/03 10:40:33 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_open(char *filename)
{
	int	fd;

	if (access(filename, F_OK) == -1)
		return (error_msg(NO_FILE, filename), 0);
	if (access(filename, R_OK) == -1)
		return (error_msg(NO_PERM, filename), 0);
	fd = open(filename, O_RDONLY);
	return (fd);
}

char	*read_file(char *filename)
{
	int		fd;
	int		readed;
	char	*file;
	char	buf[FILE_READ_BUFFER_SIZE + 1];

	fd = check_open(filename);
	if (fd <= 0)
		return (NULL);
	readed = 1;
	file = ft_strdup("");
	if (!file)
		return (error_msg(MALLOC_ERROR, NULL), NULL);
	while (readed != 0)
	{
		readed = read(fd, buf, FILE_READ_BUFFER_SIZE);
		if (readed < 0)
		{
			free(file);
			return (NULL);
		}
		buf[readed] = '\0';
		file = ft_strjoin_free(file, buf);
	}
	close(fd);
	return (file);
}
