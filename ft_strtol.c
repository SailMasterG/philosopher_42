/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:20:50 by chguerre          #+#    #+#             */
/*   Updated: 2026/08/21 20:31:49 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parsing_long(char *str, int *i, long *result)
{
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		if (*result > LONG_MAX / 10)
			return (0);
		if (*result == LONG_MAX / 10 && (str[*i] - '0') > LONG_MAX % 10)
			return (0);
		*result = *result * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (1);
}

long	ft_strtol(char *str, int *error)
{
	long	nbr_long;
	int		sign;
	int		i;

	sign = 1;
	i = 0;
	nbr_long = 0;
	if (str[i] == '\0')
		return (*error = 1);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (*error = 1);
	if (!parsing_long(str, &i, &nbr_long))
		return (*error = 1);
	nbr_long *= sign;
	if (str[i] != '\0' || (nbr_long < LONG_MIN || nbr_long > LONG_MAX))
		return (*error = 1);
	return (nbr_long);
}
