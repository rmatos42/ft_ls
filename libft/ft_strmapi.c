/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:21:27 by rmatos            #+#    #+#             */
/*   Updated: 2016/09/25 16:08:29 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*result;

	result = ft_strnew((size_t)ft_strlen((char *)s));
	if (!result)
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		result[i] = f(i, s[i]);
	return (result);
}
