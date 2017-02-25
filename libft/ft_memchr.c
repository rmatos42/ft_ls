/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 12:48:59 by rmatos            #+#    #+#             */
/*   Updated: 2016/09/29 17:15:47 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int c, size_t num)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	uc;

	i = -1;
	uc = (unsigned char)c;
	str = (unsigned char *)ptr;
	while (++i < num)
		if (str[i] == uc)
			return (str += i);
	return (NULL);
}
