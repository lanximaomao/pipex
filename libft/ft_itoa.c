/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:58:47 by lsun              #+#    #+#             */
/*   Updated: 2022/11/16 15:57:41 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit_num(long n)
{
	int	digit;

	digit = 1;
	if (n < 0)
	{
		digit++;
		n = n * (-1);
	}
	while (n / 10 > 0)
	{
		n = n / 10;
		digit++;
	}
	return (digit);
}

char	*ft_itoa(int n)
{
	int		digit;
	long	ln;
	char	*str;

	ln = (long int)n;
	digit = ft_digit_num(ln);
	str = (char *)malloc(sizeof(char) * (digit + 1));
	if (!str)
		return (NULL);
	str[digit] = '\0';
	if (ln < 0)
	{
		str[0] = '-';
		ln = ln * (-1);
	}
	while (ln >= 10 && digit > 0)
	{
		str[digit - 1] = ln % 10 + 48;
		ln = ln / 10;
		digit--;
	}
	if (ln < 10)
		str[digit - 1] = ln % 10 + 48;
	return (str);
}
