/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 13:07:08 by thomasgerma       #+#    #+#             */
/*   Updated: 2020/06/06 22:28:58 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		neg;
	int		total;

	total = 0;
	neg = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		total = (total * 10) + (str[i] - 48);
		i++;
	}
	return (total * neg);
}

size_t			ft_strlen(const char *str)
{
	int			i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	locate;

	i = 0;
	locate = 0;
	if (!dst || !src)
		return (0);
	while (src[i])
	{
		if (i < dstsize)
		{
			dst[i] = src[i];
			locate = i + 1;
		}
		i++;
	}
	if (i >= dstsize)
		locate = dstsize - 1;
	if (dstsize != 0)
		dst[locate] = '\0';
	return (i);
}

char			*ft_strjoin(char const *s1, char const *s2, int option)
{
	size_t	s1len;
	size_t	s2len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	s1len = 0;
	if (s1)
		s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * (s1len + s2len + 1))))
		return (NULL);
	if (s1)
		ft_strlcpy(str, s1, s1len + 1);
	ft_strlcpy(str + s1len, s2, s2len + 1);
	if (option == 1 || option == 3)
		free((char *)s1);
	if (option == 2 || option == 3)
		free((char *)s2);
	str[s1len + s2len] = '\0';
	return (str);
}

char * ft_itoa(int n)
{
	char *str;

	if (!(str = (char *)malloc(sizeof(char) * 2)))
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		str[1] = '\0';
		str = ft_strjoin(str, ft_itoa(-n), 3);
	}
	else if (n >= 10)
	{
		free(str);
		str = ft_strjoin(ft_itoa(n / 10), ft_itoa(n % 10), 3);
	}
	else if (n < 10 && n >= 0)
	{
		str[0] = n + 48;
		str[1] = '\0';
	}
	return (str);
}

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		(*((unsigned char *)dst)) = ((unsigned char *)src)[i];
		dst++;
		if (((unsigned char *)src)[i] == (unsigned char)c)
			return (dst);
		i++;
	}
	return (NULL);
}
