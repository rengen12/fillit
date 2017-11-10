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
# include <fcntl.h>
# include "libft/libft.h"

typedef struct			s_tetrimin
{
	int					x[4];
	int					y[4];
	char				c;
	struct s_tetrimin	*next;
}						t_tetrimin;

int						ft_evaluate(int n, char **frame);
void					ft_join(int n, t_tetrimin *t);
t_tetrimin				*convert_tetrs(char *buff);
int						sp_test(char **sp);
int						ft_valid(char *buff);
int						ft_tetr_num(char *buff);
int						ft_test_figchars(char **sp);
int						find_min(int n);
t_tetrimin				*ft_mklst(t_tetrimin *t, char **sp, char c);
t_tetrimin				*convert_tetrs(char *buff);
char					**mkframe(int min);
char					**ft_frame_back(int side, char **src, char c);
#endif
