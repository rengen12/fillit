/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rengen <rengen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 13:01:22 by dbuy              #+#    #+#             */
/*   Updated: 2017/11/11 04:22:05 by rengen           ###   ########.fr       */
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

static int	ft_test_figchars(char **sp)
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

int			sp_test(char **sp)
{
	if (!*sp)
		return (0);
	if (ft_test_figchars(sp) > 0)
		return (1);
	return (sp_test(sp + 4));
}

void		ft_tetrdel(t_tetrimin **t)
{
	t_tetrimin *tmp;

	if (!t)
		return ;
	while (*t)
	{
		if ((*t)->next)
		{
			tmp = (*t)->next;
		}
		else
			tmp = NULL;
		free(*t);
		*t = tmp;
	}
}
