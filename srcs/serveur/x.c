/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 09:46:02 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/02 15:04:56 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/bircd.h"

t_error		e_i(char *file, int line)
{
	t_error	err;

	err.file = file;
	err.line = line;
	return (err);
}

int			x_int(int err, int res, char *str, t_error e)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s, %d)\n", str, e.file, e.line);
		exit (1);
	}
	return (res);
}

void		*x_void(void *err, void *res, char *str, t_error e)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s, %d)\n", str, e.file, e.line);
		exit (1);
	}
	return (res);
}
