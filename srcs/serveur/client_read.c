/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 09:46:02 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/02 15:14:09 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "../../includes/bircd.h"

void			check_cmd(t_env *e, int cs)
{
	if (strncmp("/nick", e->fds[cs].buf_read, 5) == 0)
		change_nick(e, cs);
	else if (strncmp("/who", e->fds[cs].buf_read, 4) == 0)
		display_who(e, cs);
	else if (strncmp("/join", e->fds[cs].buf_read, 5) == 0)
		join_channel(e, cs);
	else if (strncmp("/leave", e->fds[cs].buf_read, 6) == 0)
		leave_channel(e, cs);
	else if (strncmp("/msg", e->fds[cs].buf_read, 4) == 0)
		send_private_msg(e, cs);
}

void			client_read_deco(t_env *e, int cs)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (i < e->maxfd)
	{
		if ((e->fds[i].type == FD_CLIENT)
		&& (i != cs)
		&& (strcmp(e->fds[i].channel, e->fds[cs].channel) == 0))
		{
			tmp = ft_strjoin(e->fds[cs].name, " disconnected.\n");
			send(i, tmp, ft_strlen(tmp), 0);
		}
		i++;
	}
	close(cs);
	clean_fd(&e->fds[cs]);
	printf("client #%d gone away\n", cs);
}

void			client_read_send(t_env *e, int cs, char *tmp, char *tosend)
{
	int		i;

	i = 0;
	while (strrchr(e->fds[cs].buf_read, '\n') == NULL)
	{
		printf("received: [%s]\n", e->fds[cs].buf_read);
		tosend = ft_strjoin(tosend, e->fds[cs].buf_read);
		recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	}
	tosend = ft_strjoin(tosend, e->fds[cs].buf_read);
	tmp = ft_strjoin(e->fds[cs].name, ": ");
	tmp = ft_strjoin(tmp, tosend);
	while (i < e->maxfd)
	{
		if ((e->fds[i].type == FD_CLIENT)
		&& (i != cs)
		&& (strcmp(e->fds[i].channel, e->fds[cs].channel) == 0))
		{
			send(i, tmp, ft_strlen(tmp), 0);
			printf("send [%s] to %d\n", tmp, i);
		}
		i++;
	}
}

void			client_read(t_env *e, int cs)
{
	int		r;
	char	*tmp;
	char	*tosend;

	tmp = NULL;
	tosend = NULL;
	ft_bzero(e->fds[cs].buf_read, ft_strlen(e->fds[cs].buf_read));
	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	if (r <= 0)
		client_read_deco(e, cs);
	else
	{
		if (e->fds[cs].buf_read[0] == '/')
			check_cmd(e, cs);
		else
			client_read_send(e, cs, tmp, tosend);
		ft_bzero(tmp, ft_strlen(tmp));
		ft_bzero(tosend, ft_strlen(tosend));
	}
}
