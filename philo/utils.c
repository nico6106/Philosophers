/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:58:52 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/12 18:41:54 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers.h"

int	ft_compute_time(t_var *var)
{
	int	diff;

	diff = var->info.time_sleep - var->info.time_eat;
	if (diff <= 0)
		return (var->info.time_eat - var->info.time_sleep + 2);
	return (0);
}

long	ft_time_elapsed(t_var *var, long sec, long us)
{
	long	pass;

	pass = (sec - var->time_start_s) * 1000 + (us - var->time_start_ms) / 1000;
	return (pass);
}

long	ft_reduc(t_var *var, long sec, long us)
{
	long	pass;

	pass = ft_time_elapsed(var, sec, us);
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
