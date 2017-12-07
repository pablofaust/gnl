/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:23:24 by pfaust            #+#    #+#             */
/*   Updated: 2017/12/07 18:04:50 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_stock		*ft_newstock(int fd)
{
	t_stock	*new;

	if (!(new = (t_stock*)malloc(sizeof(t_stock))))
		return (NULL);
	new->fd = fd;
	new->str = ft_strnew(1);
	new->next = NULL;
	return (new);
}

int		get_next_line(const int fd, char **line)
{
	static t_stock		*list;
	t_stock				*elem;
	char				*eol;
	char				buf[BUFF_SIZE + 1];
	int					ret;

	if (!list)
		list = ft_newstock(fd);
	while (list->fd != fd && list)
		list = list->next;
	if (!list->next && list->fd != fd)
	{
		elem = ft_newstock(fd);
		list->next = elem;
		list = list->next;
	}
	if (list->str != NULL)
	{
		if ((eol = ft_strchr(list->str, '\n')))
			*line = ft_strsub(list->str, 0, (eol - list->str));
		else
		{
			while ((ret = read(fd, buf, BUFF_SIZE)))
			{
				buf[ret] = '\0';
				dprintf(1, "ret %d\n", ret);
				dprintf(1,"buf %s\n", buf);
				if ((eol = ft_strchr(buf, '\n')))
				{
					dprintf(1,"calcul : %ld", eol - buf);
					//buf[eol - buf] ='\0';
					dprintf(1, "buf : %s\n", buf);
					break ;
				}
			}
			buf[ret] = '\0';
		}
	}
	return (1);
}

