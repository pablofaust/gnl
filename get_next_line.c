/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:23:24 by pfaust            #+#    #+#             */
/*   Updated: 2017/12/11 11:45:41 by pfaust           ###   ########.fr       */
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
	char				*tmp;

	dprintf(1,"\n\n---------DEBUT DE NOUVEAU GET NEXT LINE ------------\n\n");
	if (!list)
		list = ft_newstock(fd);
	else 
		dprintf(1,"str static : %s\n",list->str);
	elem = list;
	while (elem->fd != fd && elem)
		elem = elem->next;
	if (!elem->next && elem->fd != fd)
	{
		elem->next = ft_newstock(fd);
		//list->next = elem;
		elem = elem->next;
	}
	if ((eol = ft_strchr(elem->str, '\n')))
	{
		dprintf(1, "il y a un maillon avec saut a la ligne\n");
		*line = ft_strsub(elem->str, 0, (eol - elem->str));
		dprintf(1, "line : %s\n", *line);
		elem->str = ft_strsub(elem->str, (eol - elem->str), ft_strlen(eol));
		dprintf(1, "nouveau maillon : %s\n\n", elem->str);
		return (1);
	}
	else
	{
		dprintf(1, "il n'y a pas de saut a la ligne dans le maillon\n");
		while ((ret = read(fd, buf, BUFF_SIZE)))
		{
			buf[ret] = '\0';
			if ((eol = ft_strchr(buf, '\n')))
			{
				tmp = ft_strsub(buf, 0, (eol - buf));
				*line = ft_strjoin(elem->str, tmp);
				dprintf(1, "line = %s + %s = %s\n", elem->str, tmp, *line);
				dprintf(1, "buf = %s\n", buf);
				elem->str = ft_strsub(buf, (eol - buf + 1), ft_strlen(eol) -1);
				dprintf(1, "MAJ du maillon : %s\n\n", elem->str);
				return (1);
			}
			else
			{
				elem->str = ft_strjoin(elem->str, buf);
				dprintf(1, "pas de EOL trouve, on stock le buf dans list : %s\n", elem->str);
			}
		}
	}
	return (0);
}
