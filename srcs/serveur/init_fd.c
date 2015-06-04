/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 09:46:02 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/02 15:34:17 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/select.h>
#include "../../includes/bircd.h"

void	copy_buf(char *str, char *buf)
{
	int	i;

	i = 0;
	while (str[i])
	{
		buf[i] = str[i];
		i++;
	}
}

void	init_fd(t_env *e)
{
	int	i;

	i = 0;
	e->max = 0;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	while (i < e->maxfd)
	{
		if (e->fds[i].type != FD_FREE)
		{
			FD_SET(i, &e->fd_read);
			if (strlen(e->fds[i].buf_write) > 0)
				FD_SET(i, &e->fd_write);
			e->max = MAX(e->max, i);
			ft_bzero(e->fds[i].buf_write, ft_strlen(e->fds[i].buf_write));
		}
		i++;
	}
}
