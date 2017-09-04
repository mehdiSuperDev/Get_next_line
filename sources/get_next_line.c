/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraheemu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 16:13:42 by mraheemu          #+#    #+#             */
/*   Updated: 2016/05/23 17:08:27 by mraheemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		find_end_of_line(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int		return_line(char *str, char **tmp, char **line)
{
	size_t	end_of_line;

	end_of_line = find_end_of_line(str);
	*line = ft_strsub(str, 0, end_of_line);
	if (ft_strlen(str) > end_of_line)
		*tmp = ft_strsub(str, end_of_line + 1, ft_strlen(str));
	else
		*tmp = ft_memalloc(1);
	ft_strdel(&str);
	return (1);
}

static int		return_last_line(char **tmp, char **line)
{
	*line = ft_strsub(*tmp, 0, ft_strlen(*tmp));
	ft_strdel(tmp);
	return (1);
}

static void		tmp_alloc(char **tmp)
{
	if (*tmp == NULL)
		*tmp = ft_memalloc(1);
}

int				get_next_line(const int fd, char **line)
{
	char		buffer[BUFF_SIZE + 1];
	char		*str;
	static char	*tmp;
	int			ret;

	if (fd < 0 || line == NULL)
		return (-1);
	tmp_alloc(&tmp);
	while (1)
	{
		ret = read(fd, buffer, BUFF_SIZE);
		if (ret < 0)
			return (-1);
		if (ret >= 0)
			buffer[ret] = '\0';
		str = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = str;
		if ((ret == 0 && ft_strlen(tmp) == 0))
			return (0);
		if ((ret < BUFF_SIZE) && (ft_strchr(tmp, '\n') == NULL))
			return (return_last_line(&tmp, line));
		if ((ft_strchr(str, '\n') != NULL))
			return (return_line(str, &tmp, line));
	}
}
