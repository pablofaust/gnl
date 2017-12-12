/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:31:26 by pfaust            #+#    #+#             */
/*   Updated: 2017/12/12 14:08:58 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int		main(int ac, char **av)
{
	int		 	fd;
	int			fd2;
	char		*line;

	line = NULL;
	if (ac < 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		dprintf(1, "%s\n", line);
	close(fd);
	close(fd2);
	return (0);
}
