/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:02:02 by rmatos            #+#    #+#             */
/*   Updated: 2016/09/29 17:22:11 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t i;
	size_t end;

	i = 0;
	while (dest[i] != '\0' && i < n)
		i++;
	end = i;
	while (src[i - end] && i < n - 1)
	{
		dest[i] = src[i - end];
		i++;
	}
	if (end < n)
		dest[i] = '\0';
	return (end + ft_strlen(src));
}
