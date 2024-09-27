/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:56:17 by olardeux          #+#    #+#             */
/*   Updated: 2024/09/28 00:06:56 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_file(char *filename)
{
	int		fd;
	int		readed;
	char	*file;
	char	buf[FILE_READ_BUFFER_SIZE + 1];

	printf("filename = %s\n", filename);
	if (access(filename, F_OK) == -1)
		return (error_msg(NO_FILE, filename), NULL);
	if (access(filename, R_OK) == -1)
		return (error_msg(NO_PERM, filename), NULL);
	fd = open(filename, O_RDONLY);
	readed = 1;
	if (fd < 0)
		return (NULL);
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
		file = ft_strjoin(file, buf);
	}
	close(fd);
	return (file);
}
