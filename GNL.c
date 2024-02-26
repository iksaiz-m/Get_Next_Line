/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GNL.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:32:50 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/02/26 20:01:35 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL.h"

void	ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

  char	*ft_strjoin(char *s1, char *s2)
{
	char	*joinstring;
	size_t	i;
	size_t	k;

	i = ft_strlen(s1);
	k = ft_strlen(s2);
	joinstring = (char *)malloc((i + k + 1) * sizeof(char));
	if (!joinstring)
		return (NULL);
	ft_memcpy(joinstring, s1, i);
	ft_memcpy(joinstring + i, s2, k);
	joinstring[i + k] = '\0';
	free(s1);
	return (joinstring);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*another;

	if (start >= ft_strlen(s))
		return (malloc(1));
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	another = malloc((len + 1));
	if (!another)
		return (NULL);
	ft_memcpy(another, (s + start), len + 1);
	another[len] = '\0';
	return (another);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}
char	*ft_get_one_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
			i++;
		line = (char *)malloc(sizeof(char) * (i + 2));
		if (!line)
			return (NULL);
		/* if (save[i] == '\n')
			i++; */
		//printf("Numero:%d\n", i);
		line = ft_substr(save, 0, i);
		//printf("Patata:%s\n",line);
		return (line);
	return (save);
}
/* char    *ft_get_rest_line(char *save)
{
    char    *new_save = NULL;
    size_t  i;
    size_t  j;
    
    i = 0;
    j = 0;
    if (!save)
        return (NULL);
    while(save[i] != '\n')
        i++;
    while(save[i] != '\0')
        new_save[j] = save[i];
		i++;
		j++;
        free (save);
    return (new_save);
} */
char	*ft_get_rest_line(char *save)
{
	int		i;
	char	*new_save;
	
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	//printf("Numero2:%d\n", i);
	if (!save[i])
		return (free (save), NULL);
	new_save = (char *)malloc((ft_strlen(save) - i) * sizeof(char));
	i++;
	//printf("Cuanto mide save:%zu\n", ft_strlen(save));
	new_save = ft_substr(save, i, ft_strlen(save));
	return (new_save);
}

/* char    *get_read_line(int fd, char *save)
{
    char	buffer[BUFFER_SIZE + 1];
    int		x;

    save = malloc(1);
	if (!save)
		return (NULL);
    x = 1;
    while (x)
	{
	    x = read(fd, buffer, BUFFER_SIZE);
        if (x == 0)
		{
			if (!ft_strlen(save))
				return (NULL);
			else if (ft_strlen(save))
				return (save);
		}
        save = ft_strjoin(save, buffer);
        if (ft_strchr(save, '\n'))
            return(save);
    }
    return (save);
} */
char	*get_read_line(int fd, char *save)
{
	int		x;
	char	buffer[BUFFER_SIZE + 1];

	x = 1;
	while (x)
	{
		x = read(fd, buffer, BUFFER_SIZE);
		//printf("letras contadas:%d\n", x);
		if (x == 0)
		{
			if (!ft_strlen(save))
				return (NULL);
			else if (ft_strlen(save))
				return (save);
		}
		if (x == -1)
			return (free (buffer), free(save), NULL);
		 buffer[x] = '\0';
	// lo que has leido en buffer, lo pegas con un strjoin al save //
		save = ft_strjoin(save, buffer);
		//printf("LEIDO\n");
			if (ft_strchr(save, '\n'))
			{
				//line = ft_substr(save, 0, number);
				//save = ft_substr(save, number, ft_strlen(save));
				//printf("Save:%s\n", save);
				return(save);
			}
			//	return (save);
			//haces substr del save
			//
			//break ;
	}
	free(buffer);
	return (save);
}

/* char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;
	
	line = (char *)malloc(sizeof(char) * 1);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_read_line(fd, save);
	//save = ft_get_rest_line(line);
    return(line);
} */
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
		save = 	malloc(sizeof(char));
		if (!save)
			return (NULL);
		save[0] = '\0';
	}
	save = get_read_line(fd, save);
	if (save == NULL)
		return (NULL);
	line = ft_get_one_line(save);
	save = ft_get_rest_line(save);
	//line = (ft_substr(line, 0, number));
	//save = ft_substr(save, number, ft_strlen(save));
	//printf("Guardando:%s\n",save);
	//number = ft_strchr(save, '\n');
	//save = ft_substr(save, number, ft_strlen(save));

	//clean save
	//save = ft_clean_save;
	return(line);
}

int main()
{
    char *filename;
    int fd;
    
    filename = "GNL.txt";
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

    return (0);
}

/* int	ft_lfc(char *str, char c) // lfc -> Lenght For Char
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (str[l] != '\0')
		l ++;
	while (i <= l)
	{
		if (str[i] == (unsigned char)c)
			return (i);
		i ++;
	}
	return (-1);
}

char	*ft_strjoin(char *line, char *buffer)
{
	char	*s;
	size_t	i;
	size_t	j;

	if (!buffer)
		return (line);
	s = malloc((ft_lfc(line, '\0') + ft_lfc(buffer, '\0') + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (line[i] != '\0')
	{
		s[i] = line[i];
		i ++;
	}
	j = 0;
	while (buffer[j - 1] != '\n' && buffer[j] != '\0')
	{
		s[i + j] = buffer[j];
		j ++;
	}
	s[i + j] = '\0';
	free(line);
	return (s);
} */

/* char	*ft_strjoin(char *storage, char *buff)
{
	size_t		i;
	size_t		k;
	size_t		len;
	char		*temp;

	if (storage == NULL && buff == NULL)
		return (NULL);
	temp = NULL;
	len = ft_strlen(storage) + ft_strlen(buff);
	temp = malloc(sizeof(char ) * (len + 1));
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (storage[i])
	{
		temp[i] = storage[i];
		i++;
	}
	temp[i] = '\0';
	k = 0;
	while (buff != NULL && buff[k] != '\0')
		temp[i++] = buff[k++];
	temp[i] = '\0';
	return (free(storage), temp);
} */