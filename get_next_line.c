/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charly </var/spool/mail/charly>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:09:10 by charly            #+#    #+#             */
/*   Updated: 2024/01/10 15:10:34 by charly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	**ft_split_first(const char *s, char c)
{
	char	**splits;
	char	*c_ptr;
	size_t	slen1;
	size_t	slen2;

	splits = malloc(2 * sizeof(char *));
	c_ptr = ft_strchr(s, c);
	if (!c_ptr)
	{
		splits[0] = ft_strdup(s);
		splits[1] = malloc(1);
		splits[1][0] = '\0';
		return (splits);
	}
	slen1 = c_ptr - s + 2;
	slen2 = ft_strlen(s) - slen1 + 2;
	splits[0] = malloc(slen1);
	splits[0][slen1 - 1] = '\0';
	splits[1] = malloc(slen2);
	splits[1][slen2 - 1] = '\0';
	ft_memcpy(splits[0], s, slen1 - 1);
	ft_memcpy(splits[1], s + slen1 - 1, slen2 - 1);
	return (splits);
}

char	*read_until_chr(int fd, char c)
{
	char	*buff;
	char	*read_buff;
	size_t	nread;

	read_buff = malloc(BUFFER_SIZE + 1);
	buff = malloc(1);
	buff[0] = '\0';
	nread = BUFFER_SIZE;
	while (!ft_strchr(buff, c) && nread == BUFFER_SIZE)
	{
		nread = read(fd, read_buff, BUFFER_SIZE);
		if (nread == (size_t) - 1)
		{
			free(read_buff);
			free(buff);
			return (NULL);
		}
		read_buff[nread] = '\0';
		ft_strconcat(&buff, read_buff);
	}
	free(read_buff);
	return (buff);
}

int	fill_buff(int fd, char **buff)
{
	char	*read_buff;

	read_buff = NULL;
	if (!ft_strchr(*buff, '\n'))
	{
		read_buff = read_until_chr(fd, '\n');
		if (read_buff)
			ft_strconcat(buff, read_buff);
		else
			return (ERROR);
	}
	if (read_buff && !*read_buff)
	{
		free(read_buff);
		return (ENDFILE);
	}
	if (read_buff)
		free(read_buff);
	return (SUCCESS);
}

char	*get_next_line(int fd)
{
	static char	*buff[1024];
	char		**splits;
	char		*line;
	int			res_fill_buff;

	if (BUFFER_SIZE == 0 || fd < 0)
		return (NULL);
	if (!buff[fd])
	{
		buff[fd] = malloc(1);
		buff[fd][0] = '\0';
	}
	res_fill_buff = fill_buff(fd, &(buff[fd]));
	if (res_fill_buff == ERROR || (res_fill_buff == ENDFILE && !*buff[fd]))
	{
		free(buff[fd]);
		buff[fd] = NULL;
		return (NULL);
	}
	splits = ft_split_first(buff[fd], '\n');
	free(buff[fd]);
	buff[fd] = splits[1];
	line = splits[0];
	free(splits);
	return (line);
}
