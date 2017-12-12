/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:23:24 by pfaust            #+#    #+#             */
/*   Updated: 2017/12/12 16:06:37 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_stock		*ft_newstock(int fd)
{
	t_stock	*new;

	if (!(new = (t_stock*)malloc(sizeof(t_stock))))
		return (NULL);
	new->fd = fd;
	new->str = ft_strnew(0);
	new->done = 0;
	new->next = NULL;
	return (new);
}

int		ft_read_file(const int fd, char **line, t_stock *elem)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*eol;
	char	*tmp;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
//		dprintf(1, "buf : %s\n", buf);
		if ((eol = ft_strchr(buf, '\n')))
		{
			tmp = ft_strsub(buf, 0, (eol- buf));
			*line = ft_strjoin(elem->str, tmp);
			elem->str = ft_strsub(buf, (eol - buf + 1), (ft_strlen(eol) - 1));
		//	if (line != NULL && ft_strlen(elem->str) == 0)
	//		{
	//			elem->done = 1;
	//			return (0);
	//		}
			return (1);
		}
		else
			elem->str = ft_strjoin(elem->str, buf);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static t_stock		*list;
	t_stock				*elem;
	char				*eol;

	if (fd < 0)
		return (-1);
	if (!list)
		list = ft_newstock(fd);
	elem = list;
	while (elem->fd != fd && elem->next)
		elem = elem->next;
	if (!elem->next && elem->fd != fd)
	{
		elem->next = ft_newstock(fd);
		elem = elem->next;
	}
	if (elem->done == 1)
		return (0);
	if ((eol = ft_strchr(elem->str, '\n')))
	{
	//	ft_putendl("str avec /n");
//		dprintf(1, "line avant : %s, str avant : %s\n", *line, elem->str);
		*line = ft_strsub(elem->str, 0, (eol - elem->str));
		elem->str = ft_strsub(elem->str, (eol - elem->str + 1), ft_strlen(eol));
//		dprintf(1, "line apres : %s, str apres : %s\n\n", *line, elem->str);
	}
	else
	{
//		ft_putendl("str vide ou sans /n");
//		dprintf(1, "line avant : %s, str avant : %s\n", *line, elem->str);
		if (!(ft_read_file(fd, line, elem)))
			return (0);
//		dprintf(1, "line apres : %s, str apres : %s\n\n", *line, elem->str);
	}
	return (1);
}
