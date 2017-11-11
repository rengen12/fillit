/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraymax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rengen <rengen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:53:51 by amichak           #+#    #+#             */
/*   Updated: 2017/11/11 02:24:16 by rengen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_arraymax(int *arr, size_t size)
{
	int			max;
	size_t		i;

	if (size == 0 || !arr)
	{
		return (0);
	}
	i = 0;
	max = arr[i];
	while (++i < size)
		if (arr[i] > max)
			max = arr[i];
	return (max);
}
