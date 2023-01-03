/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:51:31 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/03 16:45:32 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers.h"

int	ft_eat(long tid, t_var *var)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (ft_is_finished(var) == 0)
	{
		var->last_eat_s[tid] = t.tv_sec;
		var->last_eat_ms[tid] = t.tv_usec / 1000;
		printf("%ld%03ld %ld is eating\n", t.tv_sec, t.tv_usec / 1000, tid);
		ft_usleep(var->info.time_eat * 1, var);
	}
	else
		return (1);
	return (0);
}

int	ft_think(long tid, t_var *var)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (ft_is_finished(var) == 0)
		printf("%ld%03ld %ld is thinking\n", t.tv_sec, t.tv_usec / 1000, tid);
	else
		return (1);
	return (0);
}

int	ft_take_fork(long tid, t_var *var, int left, int right)
{
	if (left < right)
	{
		pthread_mutex_lock(&var->mutex[left]);
		ft_show_take_fork(tid, var);
		pthread_mutex_lock(&var->mutex[right]);
		ft_show_take_fork(tid, var);
	}
	else
	{
		pthread_mutex_lock(&var->mutex[right]);
		ft_show_take_fork(tid, var);
		pthread_mutex_lock(&var->mutex[left]);
		ft_show_take_fork(tid, var);
	}
	return (0);
}

int	ft_show_take_fork(long tid, t_var *var)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (ft_is_finished(var) == 0)
		printf("%ld%03ld %ld has taken a fork\n", t.tv_sec,
			t.tv_usec / 1000, tid);
	else
		return (1);
	return (0);
}

int	ft_sleep(long tid, t_var *var)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (ft_is_finished(var) == 0)
	{
		printf("%ld%03ld %ld is sleeping\n", t.tv_sec, t.tv_usec / 1000, tid);
		ft_usleep(var->info.time_sleep * 1, var);
	}
	else
		return (1);
	return (0);
}
