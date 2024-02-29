/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:05:32 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/02/29 16:59:02 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*result;
	size_t	i;

	i = 0;
	result = (char *)malloc(count * size);
	if (!result)
		return (NULL);
	while (i < count * size)
	{
		result[i] = 0;
		i++;
	}
	return (result);
}

char	*ft_get_one_line(char *save)
{
	int		i;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	return (ft_substr(save, 0, i + 1));
}

char	*ft_get_rest_line(char *save)
{
	int		i;
	char	*new_save;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
		return (free (save), NULL);
	i++;
	new_save = ft_substr(save, i, ft_strlen(save));
	if (new_save == NULL)
		return (free(save), NULL);
	free(save);
	return (new_save);
}

char	*get_read_line(int fd, char *save)
{
	int		x;
	char	buffer[BUFFER_SIZE + 1];

	x = 1;
	while (x)
	{
		x = read(fd, buffer, BUFFER_SIZE);
		if (x == 0)
		{
			if (!ft_strlen(save))
				return (free(save), NULL);
			else if (ft_strlen(save))
				return (save);
		}
		if (x == -1)
			return (free(save), NULL);
		buffer[x] = '\0';
		save = ft_strjoin(save, buffer);
		if (!save)
			return (NULL);
		if (ft_strchr(save, '\n'))
			return (save);
	}
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[FD_OPEN];

	if (fd < 0 || BUFFER_SIZE <= 0 || FD_OPEN < fd)
	{
		if (save[fd])
			free(save[fd]);
		return (NULL);
	}
	if (!save[fd])
	{
		save[fd] = malloc(sizeof(char));
		if (!save[fd])
			return (NULL);
		save[fd][0] = '\0';
	}
	save[fd] = get_read_line(fd, save[fd]);
	if (save[fd] == NULL)
		return (NULL);
	line = ft_get_one_line(save[fd]);
	save[fd] = ft_get_rest_line(save[fd]);
	return (line);
}
