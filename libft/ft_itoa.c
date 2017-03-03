/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 12:46:05 by rmatos            #+#    #+#             */
/*   Updated: 2016/09/29 17:38:11 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		nb_len(int nb)
{
	int i;

	i = 0;
	if (nb <= 0)
		i++;
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nb)
{
	char	*result;
	int		len;
	int		i;
	long	value;

	len = nb_len(nb);
	i = len - 1;
	value = (long)nb;
	result = (char *)ft_memalloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	value *= (nb < 0) ? -1 : 1;
	while (value != 0)
	{
		result[i--] = value % 10 + '0';
		value /= 10;
	}
	if (nb < 0)
		result[0] = '-';
	result[len] = '\0';
	if (ft_strlen(result) == 0)
		return ("0");
	return (result);
}
