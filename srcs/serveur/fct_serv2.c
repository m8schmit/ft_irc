/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_serv2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 15:13:44 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/02 15:14:39 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "../../includes/bircd.h"

void		leave_channel(t_env *e, int cs)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(e->fds[cs].name, " has left ");
	tmp = ft_strjoin(tmp, e->fds[cs].channel);
	ft_strcat(e->fds[cs].buf_write, tmp);
	client_write(e, cs);
	e->fds[cs].channel = ft_strdup("#default");
}
