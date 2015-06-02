/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_cli.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 15:21:12 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/02 15:26:48 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

void				ft_help(void)
{
	write(0, "HELP:\n", 6);
	write(0, "\t\x1B[1;37m/nick <nickname>\x1B[0m -- change nickname\n", 49);
	write(0, "\t\x1B[1;37m/join <#chan>\x1B[0m -- change chan\n", 42);
	write(0, "\t\x1B[1;37m/leave <#chan>\x1B[0m -- quit chan\n", 41);
	write(0, "\t\x1B[1;37m/who\x1B[0m -- list users\n", 32);
	write(0, "\t\x1B[1;37m/msg <nick> <message>\x1B[0m", 34);
	write(0, "-- send private msg\n", 21);
	write(0, "\t\x1B[1;37m/connect <machine> [port] \x1B[0m", 38);
	write(0, "-- change server\n", 18);
	write(0, "\t\x1B[1;37m/quit \x1B[0m -- leave chan and server\n", 44);
}

void				reconnect(t_env *e)
{
	char	**tab;
	int		port;

	tab = ft_strsplit(e->buff_write, ' ');
	if (tab[1] != NULL && tab[2] != NULL)
	{
		close(e->sock);
		port = ft_atoi(tab[2]);
		if (ft_strcmp(tab[1], "localhost") == 0)
			tab[1] = "127.0.0.1";
		if ((e->sock = create_client(tab[1], port)) == -1)
			error_display("ERROR: sock()");
		while (1)
			ft_irc(e);
	}
	else
		ft_printf("Usage: /connect <machine> [port].\n");
}

void				check_cmd(t_env *e)
{
	if (ft_strncmp("/quit", e->buff_write, 5) == 0)
	{
		ft_putendl("Disconnected.");
		exit(0);
	}
	else if (ft_strncmp("/connect", e->buff_write, 8) == 0)
		reconnect(e);
	else if (ft_strncmp("/help", e->buff_write, 5) == 0)
		ft_help();
	else if (ft_strncmp("/nick", e->buff_write, 5) == 0
			|| ft_strncmp("/join", e->buff_write, 5) == 0
			|| ft_strncmp("/leave", e->buff_write, 6) == 0
			|| ft_strncmp("/who", e->buff_write, 4) == 0
			|| ft_strncmp("/msg", e->buff_write, 4) == 0
			|| ft_strncmp("/connect", e->buff_write, 8) == 0)
		;
	else
		write(0, "Try /help instead. :-)\n", 23);
}
