/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 09:46:02 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/02 13:47:42 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <stdio.h>
#include "../../includes/bircd.h"

void	client_write(t_env *e, int cs)
{
	int i;

	i = 0;
	while (i < e->maxfd)
	{
		if ((e->fds[i].type == FD_CLIENT)
		&& (i != cs)
		&& (strcmp(e->fds[i].channel, e->fds[cs].channel) == 0))
		{
			send(i, e->fds[cs].buf_write, ft_strlen(e->fds[cs].buf_write), 0);
			ft_printf("Send [%s] to [%d]\n", e->fds[cs].buf_write, i);
		}
		i++;
	}
	ft_bzero(e->fds[cs].buf_write, BUF_SIZE);
}
