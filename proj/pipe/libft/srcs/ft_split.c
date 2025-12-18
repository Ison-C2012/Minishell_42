/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:59:58 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/06 13:51:07 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_array(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*arr)
		free(*arr++);
	free(tmp);
	return (NULL);
}

static size_t	word_count(char const *s, char c)
{
	size_t	cnt;
	int		flg;

	cnt = 0;
	flg = 1;
	while (*s)
	{
		if (*s == c)
			flg = 1;
		else
		{
			if (flg == 1)
				cnt++;
			flg = 0;
		}
		s++;
	}
	return (cnt);
}

static char	**null_string(void)
{
	char	**arr;

	arr = ft_calloc(2, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arr[0] = ft_strdup("");
	if (arr[0] == NULL)
		return (NULL);
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	cnt;
	size_t	len;
	size_t	i;

	cnt = word_count(s, c);
	if (cnt == 0)
		return (null_string());
	arr = (char **)ft_calloc(cnt + 1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (*s && i < cnt)
	{
		len = 0;
		while (*s && *s == c)
			s++;
		while (s[len] && s[len] != c)
			len++;
		arr[i] = ft_substr(s, 0, len);
		if (arr[i++] == NULL)
			return (free_array(arr));
		s += len;
	}
	return (arr);
}
