/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:31:26 by pfaust            #+#    #+#             */
/*   Updated: 2017/12/11 11:13:06 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
int		main(int ac, char **av)
{
	int		 fd;
	char	*line;

	line = NULL;
	if (ac < 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	get_next_line(fd, &line);
	dprintf(1, "%s\n", line);
	get_next_line(fd, &line);
	dprintf(1, "%s\n", line);
	get_next_line(fd, &line);
	dprintf(1, "%s\n", line);
	get_next_line(fd, &line);
	dprintf(1, "%s\n", line);
	get_next_line(fd, &line);
	dprintf(1, "%s\n", line);
	get_next_line(fd, &line);
	dprintf(1, "%s\n", line);
	close(fd);
	return (0);
}
