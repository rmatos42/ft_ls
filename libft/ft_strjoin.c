/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:00:54 by rmatos            #+#    #+#             */
/*   Updated: 2016/10/17 16:40:35 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	int		count;

	count = 0;
	result = ft_strnew((ft_strlen(s1) + ft_strlen(s2)));
	if (!result)
		return (NULL);
	while (*s1)
		result[count++] = *(s1++);
	while (*s2)
		result[count++] = *(s2++);
	result[count] = '\0';
	return (result);
}
