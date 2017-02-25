/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 13:37:16 by rmatos            #+#    #+#             */
/*   Updated: 2016/09/29 17:27:31 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_nlen(const char *str, char c, int n)
{
	int i;
	int len;
	int count;

	i = 0;
	len = 0;
	count = 0;
	while (count <= n)
	{
		if (str[i] != c && (str[i - 1] == c || i == 0))
			count++;
		if (count == n)
		{
			while (str[i] != '\0' && str[i] != c)
			{
				i++;
				len++;
			}
			return (len);
		}
		i++;
	}
	return (0);
}

char	*get_nword(const char *str, char c, int n)
{
	int		i;
	int		j;
	int		count;
	char	*result;

	i = 0;
	j = 0;
	count = 0;
	result = (char *)ft_memalloc(sizeof(char) * (get_nlen(str, c, n) + 1));
	if (!result)
		return (NULL);
	while (count <= n)
	{
		if (str[i] != c && (str[i - 1] == c || i == 0))
			count++;
		if (count == n)
		{
			while (j < get_nlen(str, c, n))
				result[j++] = str[i++];
			return (result);
		}
		i++;
	}
	return (NULL);
}

int		get_count(const char *str, char c)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (str[++i] != '\0')
		if (str[i] != c && (str[i - 1] == c || i == 0))
			count++;
	return (count);
}

char	**ft_strsplit(const char *s, char c)
{
	int		i;
	char	**result;

	i = -1;
	result = (char **)ft_memalloc(sizeof(char *) * (get_count(s, c) + 1));
	if (!result)
		return (NULL);
	while (++i < get_count(s, c))
		result[i] = get_nword(s, c, i + 1);
	result[i++] = 0;
	return (result);
}
