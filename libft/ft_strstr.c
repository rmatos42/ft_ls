/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:09:04 by rmatos            #+#    #+#             */
/*   Updated: 2016/09/29 17:26:02 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str1, const char *str2)
{
	int i;

	i = 0;
	if (ft_strlen(str2) == 0)
		return ((char *)str1);
	while (*str1)
	{
		if (*str1 == str2[i])
		{
			while (str2[i] != '\0' && *(str1 + i) == str2[i])
				i++;
			if (str2[i] == '\0')
				return (char *)(str1);
		}
		i = 0;
		str1++;
	}
	return (NULL);
}
