/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:48:31 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/04 18:50:49 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers.h"

void	*ft_philo(void *arg)
{
	t_var			*var;
	long			tid;
	int				left;
	int				right;

	var = (t_var *) arg;
	tid = var->tid;
	left = (int) var->tid;
	right = ((int) var->tid + 1) % var->info.nb_philo;
	ft_wait_all_started(var);
	if (var->info.nb_philo == 1)
		ft_handle_one_phil(tid, var);
	if (tid % 2 == 1)
		ft_usleep(var->info.time_eat, var, tid);
	while (ft_is_dead(var, tid) == 0)
	{
		ft_take_fork(tid, var, left, right);
		ft_eat(tid, var);
		pthread_mutex_unlock(&var->mutex[left]);
		pthread_mutex_unlock(&var->mutex[right]);
		ft_sleep(tid, var);
		ft_think(tid, var);
	}
	return (NULL);
}

int	ft_usleep(long time_sleep, t_var *var, long tid)
{
	struct timeval	t;
	struct timeval	rt;
	long			pass;
	int				check;

	gettimeofday(&rt, NULL);
	gettimeofday(&t, NULL);
	pass = (t.tv_sec - rt.tv_sec) * 1000 + (t.tv_usec - rt.tv_usec) / 1000;
	check = 1;
	while (pass < time_sleep)
	{
		gettimeofday(&t, NULL);
		pass = (t.tv_sec - rt.tv_sec) * 1000 + (t.tv_usec - rt.tv_usec) / 1000;
		usleep(100);
		if (pass > 5 * check)
		{
			if (ft_is_dead(var, tid) == 1)
				return (1);
			check++;
		}
	}
	return (0);
}

int	ft_is_finished(t_var *var)
{
	int	status;

	pthread_mutex_lock(&var->mutex_dead);
	status = var->dead;
	pthread_mutex_unlock(&var->mutex_dead);
	return (status);
}

int	ft_is_dead(t_var *var, long tid)
{
	struct timeval	t;
	long			pass;

	if (ft_is_finished(var) == 1)
		return (1);
	gettimeofday(&t, NULL);
	pthread_mutex_lock(&var->mutex_tab_eat);
	pass = (t.tv_sec - var->last_eat_s[tid]) * 1
		+ (t.tv_usec / 1 - var->last_eat_ms[tid] * 1);
	pthread_mutex_unlock(&var->mutex_tab_eat);
	if (pass > var->info.time_die * 1000)
	{
		pthread_mutex_lock(&var->mutex_dead);
		var->dead = 1;
		pthread_mutex_unlock(&var->mutex_dead);
		pthread_mutex_lock(&var->mutex_start);
		printf("%ld%03ld %ld died\n", t.tv_sec, t.tv_usec / 1000, tid + 1);
		pthread_mutex_unlock(&var->mutex_start);
		return (1);
	}
	return (0);
}

void	ft_wait_all_started(t_var *var)
{
	pthread_mutex_lock(&var->mutex_start);
	pthread_mutex_unlock(&var->mutex_start);
}
