/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_accept.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 09:46:02 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/02 14:31:36 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../../includes/bircd.h"

void			srv_accept(t_env *e, int s)
{
	int								cs;
	struct sockaddr_in				csin;
	socklen_t						csin_len;

	csin_len = sizeof(csin);
	cs = X(-1, accept(s, (struct sockaddr*)&csin, &csin_len), "accept");
	printf("New client #%d from %s:%d\n", cs,
	inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	e->fds[cs].name = ft_strjoin("Unknown", ft_itoa(cs));
	ft_printf("New client now know as %s.\n", e->fds[cs].name);
	e->fds[cs].channel = ft_strdup("#default");
	ft_printf("%s has join %s\n", e->fds[cs].name, e->fds[cs].channel);
	clean_fd(&e->fds[cs]);
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
}
