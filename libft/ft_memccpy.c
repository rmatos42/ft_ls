/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 12:47:33 by rmatos            #+#    #+#             */
/*   Updated: 2016/09/29 17:28:51 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	char	*s1;
	char	*s2;
	int		found;

	s1 = (char *)dest;
	s2 = (char *)src;
	i = -1;
	found = 0;
	while (++i < n)
	{
		if (*s2 == c)
		{
			*s1++ = *s2++;
			found = 1;
			return (s1);
		}
		*s1++ = *s2++;
	}
	if (found == 0)
		return (NULL);
	return ("");
}
