/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 13:01:22 by dbuy              #+#    #+#             */
/*   Updated: 2017/11/04 13:01:23 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			ft_valid(char *buff)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (buff[++i] != '\0')
	{
		if (buff[i] != '.' && buff[i] != '#' && buff[i] != '\n')
			return (8);
		if (buff[i] == '.' || buff[i] == '#')
			count++;
		if (count > 4)
			return (4);
		if (i == 0 && buff[i] == '\n' && count != 4)
			return (1);
		if (buff[i] == '\n' && count == 4)
			count = 0;
		if (i > 1)
			if (buff[i] == '\n' && buff[i - 1] == '\n' && buff[i - 2] == '\n')
				return (2);
		if (((i + 1) % 21) == 0 && buff[i] != '\n')
			return (1);
	}
	return (((i + 1) % 21 != 0 || (i + 1) > 546) ? 7 : 0);
}

int			ft_tetr_num(char *buff)
{
	int i;
	int count;

	count = 0;
	i = -1;
	while (buff[++i] != '\0')
		if (buff[i] == '\n')
			count++;
	return ((count + 1) / 5);
}

static int	ft_cont(int i, int j, char **sp)
{
	int cont;

	cont = 0;
	if (i > 0)
		if (sp[i - 1][j] == '#')
			cont++;
	if (j > 0)
		if (sp[i][j - 1] == '#')
			cont++;
	if (i < 3)
		if (sp[i + 1][j] == '#')
			cont++;
	if (sp[i][j + 1] == '#')
		cont++;
	return (cont);
}

int			ft_test_figchars(char **sp)
{
	int i;
	int j;
	int count;
	int cont;

	i = -1;
	count = 0;
	cont = 0;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			if (sp[i][j] == '#')
			{
				cont += ft_cont(i, j, sp);
				count++;
			}
	}
	return ((count != 4 || cont < 6) ? 1 : 0);
}

int			find_min(int n)
{
	int sqr;
	int out;

	out = 0;
	sqr = n * 4;
	while (out <= sqr)
	{
		if (out * out >= sqr)
			return (out);
		out++;
	}
	return (0);
}
