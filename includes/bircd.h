/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bircd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 09:46:01 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/02 15:28:02 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIRCD_H
# define BIRCD_H

# include <sys/select.h>
# include "libft.h"

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2

# define BUF_SIZE	4096

# define XV(err,res,str)	(x_void(err, res, str, e_i(__FILE__, __LINE__)))
# define X(err,res,str)		(x_int(err, res, str, e_i(__FILE__, __LINE__)))
# define MAX(a,b)	((a > b) ? a : b)

# define USAGE		"Usage: %s port\n"

typedef struct	s_error
{
	char		*file;
	int			line;
}				t_error;

typedef struct	s_fd
{
	int			type;
	void		(*fct_read)();
	void		(*fct_write)();
	char		buf_read[BUF_SIZE + 1];
	char		buf_write[BUF_SIZE + 1];
	char		*name;
	char		*channel;
}				t_fd;

typedef struct	s_env
{
	t_fd		*fds;
	int			port;
	int			maxfd;
	int			max;
	int			r;
	fd_set		fd_read;
	fd_set		fd_write;
}				t_env;

t_error			e_i(char *file, int line);
void			init_env(t_env *e);
void			get_opt(t_env *e, int ac, char **av);
void			main_loop(t_env *e);
void			srv_create(t_env *e, int port);
void			srv_accept(t_env *e, int s);
void			client_read(t_env *e, int cs);
void			client_write(t_env *e, int cs);
void			clean_fd(t_fd *fd);
void			*x_void(void *err, void *res, char *str, t_error e);
int				x_int(int err, int res, char *str, t_error e);
void			init_fd(t_env *e);
void			do_select(t_env *e);
void			check_fd(t_env *e);
void			change_nick(t_env *e, int cs);
void			display_who(t_env *e, int cs);
void			join_channel(t_env *e, int cs);
void			send_private_msg(t_env *e, int cs);
void			leave_channel(t_env *e, int cs);

#endif
