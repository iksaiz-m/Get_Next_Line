/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:50:02 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/02/16 18:09:26 by iksaiz-m         ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
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
	if (s[i] == (char)c)
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}

char	*get_one_line(int fd, char *save)
{
	int		x;
	char	buffer[BUFFER_SIZE + 1];

	x = 1;
	save = malloc(1);
	save[0] = '\0';
	while (x)
	{
	x = read(fd, buffer, BUFFER_SIZE);
		// lo que has leido en buffer, lo pegas con un strjoin al save //
	save = ft_strjoin(save, buffer);
		if (x == 0)
		{
			if (!ft_strlen(save))
				return (NULL);
			else if (ft_strlen(save))
				return (save);
		}
		//if (x == -1)
			//hay que gestionar-> 
		//printf("LEIDO: %s\n", save);
		//else
			//if (ft_strchr(save, '\n'))
			//	return (save);
			//haces substr del save
			//
			//break ;
	}
	// lo que has leido en buffer, lo pegas con un strjoin al save //
	return (save);
}

char	*get_next_line(int fd)
{	
	char		*line;
	static char	*save;
		
/* 	if (!save)
	{
		
	}
	else
	{
		
	} */
	//line = ft_calloc(0, sizeof(char));
	line = get_one_line(fd, save);
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
    printf("%s", get_next_line(fd));
    //printf("File Contents: %s\n", buffer);
    return 0;
}

		//ft_memcpy(buffer, ft_strchr(buffer, '\n') + 1, 	ft_strlen(ft_strchr(buffer, '\n') + 1) + 1);
		//hola iker\n 
		//hola julen\0
		