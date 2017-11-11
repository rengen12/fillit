/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rengen <rengen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:59:45 by amichak           #+#    #+#             */
/*   Updated: 2017/11/11 04:17:46 by rengen           ###   ########.fr       */
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

int						ft_valid(char *buff);
int						sp_test(char **sp);
char					**mkframe(int min);
char					**ft_frame_back(int side, char **src, char c);
void					ft_tabdel(char **tab);
void					ft_print_tab(char **tab);
void					ft_tetrdel(t_tetrimin **t);
void					ft_join(int n, t_tetrimin *t);
t_tetrimin				*convert_tetrs(char *buff);
t_tetrimin				*ft_mklst(t_tetrimin *t, char **sp, char c);
#endif
