/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:06:52 by rmatos            #+#    #+#             */
/*   Updated: 2016/09/26 19:28:48 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int len;

	if (c == '\0')
	{
		while (*str)
			str++;
		return ((char *)str);
	}
	len = ft_strlen((char *)str);
	while (*str)
		str++;
	str--;
	while (len > 0)
	{
		if (*str == (char)c)
			return ((char *)str);
		str--;
		len--;
	}
	return (NULL);
}
