/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 14:43:19 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/02 15:25:49 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../includes/libft.h"

# define BUFF_SIZE 4096

typedef struct	s_env
{
	int			sock;
	fd_set		fd_read;
	fd_set		fd_write;
	char		buff_read[BUFF_SIZE];
	char		buff_write[BUFF_SIZE];

}				t_env;

void			error_display(char *str);
void			reconnect(t_env *e);
void			check_cmd(t_env *e);
void			fct_read(t_env *e);
void			fct_write(t_env *e);
void			check_fd(t_env *e);
void			ft_irc(t_env *e);
void			usage(char *str);
int				create_client(char *addr, int port);
#endif
