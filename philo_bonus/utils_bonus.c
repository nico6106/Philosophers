/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:58:52 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/12 18:00:01 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

int	ft_compute_time(t_var *var)
{
	int	diff;

	diff = var->info.time_sleep - var->info.time_eat;
	if (diff <= 0)
		return (var->info.time_eat - var->info.time_sleep + 2);
	return (0);
}

void	ft_wait_odd(t_var *var)
{
	if (var->info.nb_philo % 2 == 1)
		ft_usleep(ft_compute_time(var), var);
}

long	ft_time_elapsed(t_var *var, long sec, long us)
{
	long	pass;

	pass = (sec - var->time_start_s) * 1000 + (us - var->time_start_ms) / 1000;
	return (pass);
}

int	ft_return_arg(char *argv)
{
	long	number;

	number = ft_atoi(argv);
	if (number > 2147483647 || number < -2147483648)
		return (-2);
	return ((int) number);
}
