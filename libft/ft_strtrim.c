/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:53:58 by rmatos            #+#    #+#             */
/*   Updated: 2016/09/30 16:01:24 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_newlen(const char *s)
{
	int end;
	int start;

	end = ft_strlen((char *)s) - 1;
	start = 0;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
		end--;
	if (end < start)
		return (0);
	return (end - start + 1);
}

char	*ft_strtrim(const char *s)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (ft_newlen(s) == 0)
		return ("");
	result = ft_strnew((size_t)ft_newlen(s));
	if (!result)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (j < ft_newlen(s))
		result[j++] = s[i++];
	return (result);
}
