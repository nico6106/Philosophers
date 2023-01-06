/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:48:31 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/06 19:30:39 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers.h"

void	*ft_philo(void *arg)
{
	t_var	*var;
	t_philo	philo;

	var = (t_var *) arg;
	philo = ft_init_philo(var);
	if (philo.left == -1)
		return (NULL);
	ft_wait_all_started(var);
	if (var->info.nb_philo == 1)
		ft_handle_one_phil(philo.tid, var);
	ft_think(philo.tid, var);
	if (philo.tid % 2 == 1)
		ft_usleep(var->info.time_eat, var, philo.tid);
	while (ft_is_finished(var) == 0 && ft_finished(var) == 0)
	{
		ft_take_fork(philo.tid, var, philo.left, philo.right);
		ft_eat(philo.tid, var);
		pthread_mutex_unlock(&var->mutex[philo.left]);
		pthread_mutex_unlock(&var->mutex[philo.right]);
		if (ft_finished(var) == 1)
			return (NULL);
		ft_sleep(philo.tid, var);
		ft_think(philo.tid, var);
		if (var->info.nb_philo % 2 == 1)
			ft_usleep(ft_compute_time(var), var, philo.tid);
	}
	return (NULL);
}

t_philo	ft_init_philo(t_var *var)
{
	t_philo	philo;

	if (pthread_mutex_lock(&var->mutex_dead) != 0)
	{
		ft_exit(var);
		philo.left = -1;
		return (philo);
	}
	philo.tid = var->tid;
	if (pthread_mutex_unlock(&var->mutex_dead) != 0)
	{
		ft_exit(var);
		philo.left = -1;
		return (philo);
	}
	philo.left = philo.tid;
	philo.right = (philo.tid + 1) % var->info.nb_philo;
	return (philo);
}

int	ft_usleep(long time_sleep, t_var *var, long tid)
{
	struct timeval	t;
	struct timeval	rt;
	long			pass;
	int				check;

	(void) tid;
	gettimeofday(&rt, NULL);
	gettimeofday(&t, NULL);
	pass = (t.tv_sec - rt.tv_sec) * 1000000 + (t.tv_usec - rt.tv_usec);
	check = 1;
	while (pass < time_sleep * 1000)
	{
		gettimeofday(&t, NULL);
		pass = (t.tv_sec - rt.tv_sec) * 1000000 + (t.tv_usec - rt.tv_usec);
		if (pass > 5 * check * 1000)
		{
			if (ft_is_finished(var) == 1)
				return (1);
			else if (ft_finished(var) == 1)
				return (1);
			check++;
		}
		usleep(500);
	}
	return (0);
}

void	ft_wait_all_started(t_var *var)
{
	if (pthread_mutex_lock(&var->mutex_start) != 0)
		ft_exit(var);
	if (pthread_mutex_unlock(&var->mutex_start) != 0)
		ft_exit(var);
}
