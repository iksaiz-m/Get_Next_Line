/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:32:50 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/02/28 18:50:17 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (save)
			free(save);
		return (NULL);
	}
	if (!save)
	{
		save = malloc(sizeof(char));
		if (!save)
			return (NULL);
		save[0] = '\0';
	}
	save = get_read_line(fd, save);
	if (save == NULL)
		return (NULL);
	line = ft_get_one_line(save);
	save = ft_get_rest_line(save);
	return (line);
}

/* int main()
{
    char *filename;
    int fd;
    
    filename = "multiple_line_with_nl";
    fd = open(filename, 0, O_RDONLY);
    if (fd == -1)
    {
        printf("\nError Opening File\n");
        exit(1);
    }
    else
    {
        printf("\nFile %s opened sucessfully!\n", filename);
    }
    printf("LINEA1:%s", get_next_line(fd));
    printf("LINEA2:%s", get_next_line(fd));
	printf("LINEA3:%s", get_next_line(fd));
    printf("LINEA4:%s", get_next_line(fd));
    printf("LINEA5:%s", get_next_line(fd));
    printf("LINEA6:%s", get_next_line(fd));
	printf("LINEA7:%s", get_next_line(fd));

    return (0);
} */
