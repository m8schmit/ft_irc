/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 09:46:02 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/02 15:26:15 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

int					create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		error_display("ERROR: connect()");
	return (sock);
}

void				check_fd(t_env *e)
{
	int n;

	n = 0;
	if ((n = FD_ISSET(e->sock, &e->fd_read)))
		fct_read(e);
	if ((n = FD_ISSET(0, &e->fd_read)))
		fct_write(e);
}

void				ft_irc(t_env *e)
{
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	FD_SET(e->sock, &e->fd_read);
	FD_SET(0, &e->fd_read);
	if (strlen(e->buff_write) > 0)
		FD_SET(0, &e->fd_write);
	select(e->sock + 1, &e->fd_read, &e->fd_write, NULL, NULL);
	check_fd(e);
}

int					main(int ac, char **av)
{
	int		port;
	t_env	e;

	if (ac != 3)
		usage(av[0]);
	port = ft_atoi(av[2]);
	if (ft_strcmp(av[1], "localhost") == 0)
		av[1] = "127.0.0.1";
	if ((e.sock = create_client(av[1], port)) == -1)
		error_display("ERROR: sock()");
	while (1)
		ft_irc(&e);
}
