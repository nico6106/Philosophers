/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:20:23 by nlesage           #+#    #+#             */
/*   Updated: 2022/12/28 13:19:37 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers.h"

t_info	ft_load_arg(int argc, char **argv)
{
	t_info	info;
	int		error;

	error = 0;
	if (!(argc == 5 || argc == 6))
		error = ft_error_quit("Wrong number of arguments\n", 1);
	if (error == 0 && ft_check_arg(argc, argv) == 0)
		error = ft_error_quit("Wrong format for the arguments\n", 1);
	if (error != 0)
		info.nb_philo = -1;
	else
		info = ft_import_arg(argc, argv);
	return (info);
}

t_info	ft_import_arg(int argc, char **argv)
{
	t_info	info;

	info.nb_philo = ft_atoi(argv[1]);
	info.time_die = ft_atoi(argv[2]);
	info.time_eat = ft_atoi(argv[3]);
	info.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info.nb_eat = ft_atoi(argv[5]);
	else
		info.nb_eat = -1;
	return (info);
}

int	ft_check_arg(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_str_is_number(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	number;
	int	sign;

	i = 0;
	number = 0;
	sign = 1;
	while (nptr[i] && ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9'))
	{
		number = number * 10 + nptr[i] - '0';
		i++;
	}
	return (sign * number);
}

int	ft_str_is_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
