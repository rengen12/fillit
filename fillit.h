/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:59:45 by amichak           #+#    #+#             */
/*   Updated: 2017/11/08 18:00:18 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

typedef struct	s_tetrimin
{
	int	x[4];
	int	y[4];
	char c;
	int placed;
}				t_tetrimin;

int			ft_evaluate(int n, char **frame);
void		ft_join(int j, int n, t_tetrimin *tetr_conv);
t_tetrimin	*convert_tetrs(int qfig, char ***tetr);
#endif
