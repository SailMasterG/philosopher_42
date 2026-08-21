/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 19:11:27 by chguerre          #+#    #+#             */
/*   Updated: 2026/08/21 20:35:12 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_input(int argc, char **argv)
{
	int			i;
	long long	number;
	int			error;

	i = 1;
	error = 0;
	while (i < argc)
	{
		number = ft_strtol(argv[i], &error);
		if (error == 1)
			return (0);
		if (number <= 0)
			return (0);
		i++;
	}
	return (1);
}
