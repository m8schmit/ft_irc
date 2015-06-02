/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 15:22:03 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/02 15:27:02 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

void				fct_read(t_env *e)
{
	if (recv(e->sock, e->buff_read, BUFF_SIZE, 0) < 0)
	{
		close(e->sock);
		exit(0);
	}
	ft_printf("%s", e->buff_read);
	ft_bzero(e->buff_read, BUFF_SIZE);
}

void				fct_write(t_env *e)
{
	int ret;

	ft_bzero(e->buff_write, ft_strlen(e->buff_write));
	ret = read(0, e->buff_write, BUFF_SIZE);
	e->buff_write[ret] = 0;
	if (e->buff_write[0] == '/')
		check_cmd(e);
	send(e->sock, e->buff_write, ret, 0);
}
