/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_serv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 15:12:24 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/02 15:16:17 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "../../includes/bircd.h"

void		change_nick(t_env *e, int cs)
{
	char **tab;
	char *tmp;

	tmp = NULL;
	tab = ft_strsplit(e->fds[cs].buf_read, ' ');
	if (tab[1] && !tab[2])
	{
		tmp = ft_strjoin(e->fds[cs].name, " is now know has ");
		tmp = ft_strjoin(tmp, tab[1]);
		tab[1][ft_strlen(tab[1]) - 1] = '\0';
		e->fds[cs].name = ft_strdup(tab[1]);
		ft_strcat(e->fds[cs].buf_write, tmp);
		free(tmp);
	}
}

void		display_who(t_env *e, int cs)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	while (i < e->maxfd)
	{
		if ((e->fds[i].name != NULL)
			&& (strcmp(e->fds[i].channel, e->fds[cs].channel) == 0))
		{
			tmp = ft_strjoin(e->fds[i].name, "\n");
			tmp2 = ft_strjoin(tmp2, tmp);
		}
		i++;
	}
	ft_printf("tmp: %s\n", tmp2);
	send(cs, tmp2, ft_strlen(tmp2), 0);
}

void		join_channel(t_env *e, int cs)
{
	int		i;
	char	*tmp;
	char	**tab;

	i = -1;
	tmp = NULL;
	tab = ft_strsplit(e->fds[cs].buf_read, ' ');
	if ((tab[1] && !tab[2]) && tab[1][0] == '#')
	{
		tmp = ft_strjoin(e->fds[cs].name, " has left ");
		tmp = ft_strjoin(tmp, e->fds[cs].channel);
		tmp = ft_strjoin(tmp, "\n");
		ft_strcat(e->fds[cs].buf_write, tmp);
		client_write(e, cs);
		tmp = ft_strjoin(e->fds[cs].name, " has join ");
		tmp = ft_strjoin(tmp, tab[1]);
		tmp = ft_strjoin(tmp, "\0");
		tab[1][ft_strlen(tab[1]) - 1] = '\0';
		e->fds[cs].channel = ft_strdup(tab[1]);
		ft_strcat(e->fds[cs].buf_write, tmp);
		free(tmp);
	}
	else
		send(cs, "Try /help instead. :-)\n", 24, 0);
}

void		send_private_msg(t_env *e, int cs)
{
	char	**tab;
	char	*tmp;
	int		i;

	i = 1;
	tmp = NULL;
	tab = ft_strsplit(e->fds[cs].buf_read, ' ');
	if (tab[1] && tab[2])
	{
		tmp = ft_strjoin(e->fds[cs].name, ": ");
		while (tab[++i] != NULL)
		{
			tmp = ft_strjoin(tmp, tab[i]);
			if (tab[i + 1] != NULL)
				tmp = ft_strjoin(tmp, " ");
		}
		ft_printf("try to send [%s] to %s.", tmp, tab[1]);
		i = -1;
		while (++i < e->maxfd)
		{
			if ((e->fds[i].type == FD_CLIENT)
				&& (strcmp(tab[1], e->fds[i].name) == 0))
				send(i, tmp, ft_strlen(tmp), 0);
		}
	}
}
