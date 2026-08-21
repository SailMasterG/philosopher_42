/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 19:11:27 by chguerre          #+#    #+#             */
/*   Updated: 2026/08/21 18:48:32 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	validate_arg(char *str)
{
	long long	number;

	number = atoi(str);
	if (number <= 0)
		return (0);
	return (1);
}

int	validate_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '-')
			j++;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("Entry is not valid, verify and try again");
				return (0);
			}
			j++;
		}
		if (!validate_arg(argv[i]))
		{
			printf("Argument negative is not valid.");
			return (0);
		}
		i++;
	}
	return (1);
}
