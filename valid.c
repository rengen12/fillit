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

#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "fillit.h"

int		find_min(int n)
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

int		ft_valid(char *buff)
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
	if ((i + 1) % 21 != 0 || (i + 1) > 546)
		return (7);
	return (0);
}

int		ft_tetr_num(char *buff)
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

char	*ft_read(char *file)
{
	int		fd;
	char	*buff;
    int     ret;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	if (!(buff = (char*)malloc(1000)))
		return (NULL);
	ret = read(fd, buff, 1000);
    buff[ret] = '\0';
	if (close(fd) == -1)
		return (NULL);
	return (buff);
}

int		ft_test_figchars(char **sp)
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
				if (i > 0)
					if(sp[i - 1][j] == '#')
						cont++;
				if (j > 0)
					if(sp[i][j - 1] == '#')
						cont++;
				if (i < 3)
					if(sp[i + 1][j] == '#')
						cont++;
				if (j < 3)
					if(sp[i][j + 1] == '#')
						cont++;				
				count++;
			}
	}
	if (count != 4 || cont < 6)
		return (1);
	return (0);
}

int		sp_test(char **sp)
{
	if (!*sp)
		return (0);
	if (ft_test_figchars(sp) > 0)
		return (1);
	return (sp_test(sp + 4));
}

int		print_errors(int i)
{
	if (i == 100)
		ft_putendl("usage: fillit target_file");
	if (i == 101)
		ft_putendl("error");
	return (0);
}

void	print_t(t_tetrimin *t)
{
	t_tetrimin *temp;
	int i;
	int j;

	i = -1;
	j = 0;
	temp = t;
	while (temp)
	{
		puts("Next");
		while (++i < 4)
			printf("j = %d; t.x[i] = %d; t.y[i] = %d; Char = %c\n", j, temp->x[i], temp->y[i], temp->c);
		i = -1;
		j++;
		temp = temp->next;
	}
}

int		main(int ac, char **av)
{
	char		*buff;
	int			count;
	t_tetrimin	*t;

	if (ac == 1)
		return (print_errors(100));
	if (ac != 2)
		return (print_errors(101));
	if (!(buff = ft_read(av[1])))
		return (print_errors(101));
	if (ft_valid(buff) > 0)
		return (print_errors(101));
	count = ft_tetr_num(buff);
	if (!(t = convert_tetrs(buff)))
		return (print_errors(101));
//	print_t(t);
	ft_join(find_min(count), t);
	return (0);
}
