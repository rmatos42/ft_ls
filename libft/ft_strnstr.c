/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:06:41 by rmatos            #+#    #+#             */
/*   Updated: 2016/09/29 17:37:11 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(str2) == 0)
		return ((char *)str1);
	while (*str1 && j < n)
	{
		if (*str1 == str2[i])
		{
			while (str2[i] != '\0' && *(str1 + i) == str2[i] && (j + i) < n)
				i++;
			if (str2[i] == '\0')
				return (char *)(str1);
		}
		i = 0;
		str1++;
		j++;
	}
	return (NULL);
}
