/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:45:00 by brivera           #+#    #+#             */
/*   Updated: 2025/09/04 12:16:02 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace_char(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static int	ft_overflow_check(long result, int digit, int sign)
{
	unsigned long	abs_min;

	if (sign == 1)
	{
		if (result > (LONG_MAX - digit) / 10)
			return (1);
	}
	else
	{
		abs_min = (unsigned long)LONG_MAX + 1;
		if ((unsigned long)result > (abs_min - digit) / 10)
			return (1);
	}
	return (0);
}

static int	ft_parse_sign(const char *str, int *i, int *sign)
{
	while (ft_isspace_char(str[*i]))
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (!ft_isdigit(str[*i]))
		return (0);
	return (1);
}

static int	ft_parse_digits(const char *str, int *i, long *num, int sign)
{
	while (ft_isdigit(str[*i]))
	{
		if (ft_overflow_check(*num, str[*i] - '0', sign))
			return (0);
		*num = *num * 10 + (str[*i] - '0');
		(*i)++;
	}
	if (str[*i] != '\0')
		return (0);
	return (1);
}

int	ft_atol(const char *str, long *result, int *overflow)
{
	long	num;
	int		sign;
	int		i;

	*result = 0;
	*overflow = 0;
	if (!str || !*str)
		return (0);
	num = 0;
	sign = 1;
	i = 0;
	if (!ft_parse_sign(str, &i, &sign))
		return (0);
	if (!ft_parse_digits(str, &i, &num, sign))
	{
		*overflow = 1;
		return (0);
	}
	*result = num * sign;
	return (1);
}
