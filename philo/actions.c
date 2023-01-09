/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:51:31 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/09 16:48:18 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers.h"

void	ft_eat(long tid, t_var *var)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (ft_is_finished(var) == 0)
	{
		if (pthread_mutex_lock(&var->mutex_tab_eat) != 0)
			ft_exit(var);
		var->last_eat_s[tid] = t.tv_sec;
		var->last_eat_ms[tid] = t.tv_usec / 1;
		if (pthread_mutex_unlock(&var->mutex_tab_eat) != 0)
			ft_exit(var);
		if (pthread_mutex_lock(&var->mutex_start) != 0)
			ft_exit(var);
		if (ft_is_finished(var) == 0)
			printf("%ld %ld is eating\n",
				ft_time_elapsed(var, t.tv_sec, t.tv_usec), tid + 1);
		if (pthread_mutex_unlock(&var->mutex_start) != 0)
			ft_exit(var);
		ft_usleep(var->info.time_eat * 1, var, tid);
		if (pthread_mutex_lock(&var->mutex_tab_nb_eat) != 0)
			ft_exit(var);
		var->tab_nb_eat[tid] = var->tab_nb_eat[tid] + 1;
		if (pthread_mutex_unlock(&var->mutex_tab_nb_eat) != 0)
			ft_exit(var);
	}
}

int	ft_think(long tid, t_var *var)
{
	struct timeval	t;
	long			pass;

	gettimeofday(&t, NULL);
	if (pthread_mutex_lock(&var->mutex_start) != 0)
		ft_exit(var);
	pass = ft_time_elapsed(var, t.tv_sec, t.tv_usec);
	if (ft_is_finished(var) == 0)
		printf("%ld %ld is thinking\n", pass, tid + 1);
	if (pthread_mutex_unlock(&var->mutex_start) != 0)
		ft_exit(var);
	return (0);
}

int	ft_take_fork(long tid, t_var *var, int left, int right)
{
	if (left < right)
	{
		if (pthread_mutex_lock(&var->mutex[left]) != 0)
			ft_exit(var);
		ft_show_take_fork(tid, var);
		if (pthread_mutex_lock(&var->mutex[right]) != 0)
			ft_exit(var);
		ft_show_take_fork(tid, var);
	}
	else
	{
		if (pthread_mutex_lock(&var->mutex[right]) != 0)
			ft_exit(var);
		ft_show_take_fork(tid, var);
		if (pthread_mutex_lock(&var->mutex[left]) != 0)
			ft_exit(var);
		ft_show_take_fork(tid, var);
	}
	return (0);
}

int	ft_show_take_fork(long tid, t_var *var)
{
	struct timeval	t;
	long			pass;

	gettimeofday(&t, NULL);
	if (pthread_mutex_lock(&var->mutex_start) != 0)
		ft_exit(var);
	pass = ft_time_elapsed(var, t.tv_sec, t.tv_usec);
	if (ft_is_finished(var) == 0)
		printf("%ld %ld has taken a fork\n", pass, tid + 1);
	if (pthread_mutex_unlock(&var->mutex_start) != 0)
		ft_exit(var);
	return (0);
}

int	ft_sleep(long tid, t_var *var)
{
	struct timeval	t;
	long			pass;

	gettimeofday(&t, NULL);
	if (ft_is_finished(var) == 0)
	{
		if (pthread_mutex_lock(&var->mutex_start) != 0)
			ft_exit(var);
		pass = ft_time_elapsed(var, t.tv_sec, t.tv_usec);
		if (ft_is_finished(var) == 0)
			printf("%ld %ld is sleeping\n", pass, tid + 1);
		if (pthread_mutex_unlock(&var->mutex_start) != 0)
			ft_exit(var);
		ft_usleep(var->info.time_sleep * 1, var, tid);
	}
	else
		return (1);
	return (0);
}
