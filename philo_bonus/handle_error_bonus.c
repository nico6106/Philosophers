/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:19:42 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/09 17:42:34 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

int	ft_error_quit(char *str, int retour)
{
	int	i;

	if (str)
	{
		i = -1;
		while (str[++i])
			write(2, &str[i], 1);
	}
	return (retour);
}

void	ft_handle_one_phil(long tid, t_var *var)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (pthread_mutex_lock(&var->mutex[tid]) != 0)
		ft_exit(var);
	printf("%ld%03ld %ld has taken a fork\n", t.tv_sec,
		t.tv_usec / 1000, tid + 1);
	usleep(var->info.time_die * 1000);
	if (pthread_mutex_unlock(&var->mutex[tid]) != 0)
		ft_exit(var);
	if (pthread_mutex_lock(&var->mutex_dead) != 0)
		ft_exit(var);
	var->dead = 1;
	if (pthread_mutex_unlock(&var->mutex_dead) != 0)
		ft_exit(var);
	gettimeofday(&t, NULL);
	printf("%ld%03ld %ld died\n", t.tv_sec, t.tv_usec / 1000, tid + 1);
}

int	ft_handle_thread_creation_error(t_var *var, pthread_t *threads, int i)
{
	if (pthread_mutex_lock(&var->mutex_dead) != 0)
		return (1);
	var->dead = 1;
	if (pthread_mutex_unlock(&var->mutex_dead) != 0)
		return (1);
	if (pthread_mutex_unlock(&var->mutex_start) != 0)
		return (1);
	ft_kill_threads(threads, i);
	return (ft_error_quit("Error from pthread_create\n", 1));
}

void	ft_exit(t_var *var)
{
	int	treat;

	treat = 1;
	if (pthread_mutex_lock(&var->mutex_dead) != 0)
		return ;
	if (var->end_properly == 0)
		treat = 0;
	var->end_properly = 0;
	var->dead = 1;
	if (pthread_mutex_unlock(&var->mutex_dead) != 0)
		return ;
	if (pthread_mutex_lock(&var->mutex_start) != 0)
		return ;
	if (treat == 1)
		ft_error_quit("Error with the lock/unlock function in a philo.\n", 0);
	if (pthread_mutex_unlock(&var->mutex_start) != 0)
		return ;
}

void	ft_kill_threads(pthread_t *threads, int n)
{
	int	i;

	i = -1;
	if (n < 1)
		return ;
	while (++i <= n)
	{
		pthread_join(threads[i], NULL);
		usleep(1000);
	}
}
