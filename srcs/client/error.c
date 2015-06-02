/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 15:20:11 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/02 15:25:28 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

void			usage(char *str)
{
	ft_printf("Usage: %s <addr> <port>\n", str);
	exit (-1);
}

void			error_display(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(-1);
}
