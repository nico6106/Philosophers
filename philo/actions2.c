/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:54:41 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/09 08:59:35 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers.h"

void	ft_unlock_fork(t_var *var, t_philo philo)
{
	if (pthread_mutex_unlock(&var->mutex[philo.left]) != 0)
		ft_exit(var);
	if (pthread_mutex_unlock(&var->mutex[philo.right]) != 0)
		ft_exit(var);
}

void	ft_wait_odd(t_var *var, long tid)
{
	if (var->info.nb_philo % 2 == 1)
		ft_usleep(ft_compute_time(var), var, tid);
}
