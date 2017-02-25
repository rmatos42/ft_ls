/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:09:06 by rmatos            #+#    #+#             */
/*   Updated: 2016/09/29 15:55:07 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*result;

	result = ft_strnew((size_t)(ft_strlen((char *)s)));
	if (!result)
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		result[i] = f(s[i]);
	result[i] = '\0';
	return (result);
}
