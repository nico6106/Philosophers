/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:57:53 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/09 15:26:44 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers.h"

int	ft_init_tab(t_var *var)
{
	var->last_eat_s = malloc(var->info.nb_philo * sizeof(long));
	if (!var->last_eat_s)
		return (ft_error_quit("Error with malloc allocation\n", 1));
	var->last_eat_ms = malloc(var->info.nb_philo * sizeof(long));
	if (!var->last_eat_ms)
	{
		free(var->last_eat_s);
		return (ft_error_quit("Error with malloc allocation\n", 1));
	}
	var->mutex = malloc(var->info.nb_philo * sizeof(pthread_mutex_t));
	if (!var->mutex)
	{
		free(var->last_eat_ms);
		free(var->last_eat_s);
		return (ft_error_quit("Error with malloc allocation\n", 1));
	}
	var->tab_nb_eat = malloc(var->info.nb_philo * sizeof(int));
	if (!var->tab_nb_eat)
	{
		free(var->mutex);
		free(var->last_eat_ms);
		free(var->last_eat_s);
		return (ft_error_quit("Error with malloc allocation\n", 1));
	}
	return (0);
}

int	ft_init_mutex(t_var *var, int i)
{
	if (pthread_mutex_init(&var->mutex_tab_nb_eat, NULL) != 0)
		return (ft_error_quit("Error with mutex initialization\n", 1));
	if (pthread_mutex_init(&var->mutex_dead, NULL) != 0)
	{
		ft_pthread_mutex_destroy(&var->mutex_tab_nb_eat);
		return (ft_error_quit("Error with mutex initialization\n", 1));
	}
	if (pthread_mutex_init(&var->mutex_start, NULL) != 0)
	{
		ft_pthread_mutex_destroy(&var->mutex_tab_nb_eat);
		ft_pthread_mutex_destroy(&var->mutex_dead);
		return (ft_error_quit("Error with mutex initialization\n", 1));
	}
	if (pthread_mutex_init(&var->mutex_tab_eat, NULL) != 0)
	{
		ft_pthread_mutex_destroy(&var->mutex_tab_nb_eat);
		ft_pthread_mutex_destroy(&var->mutex_dead);
		ft_pthread_mutex_destroy(&var->mutex_start);
		return (ft_error_quit("Error with mutex initialization\n", 1));
	}
	while (++i < var->info.nb_philo)
		if (pthread_mutex_init(&(var->mutex[i]), NULL) != 0)
			return (ft_handle_destroy_mutex(var, i));
	return (0);
}

int	ft_give_value_mutex(t_var *var)
{
	int	i;

	i = -1;
	if (pthread_mutex_lock(&var->mutex_tab_nb_eat) != 0)
		return (ft_error_quit("Error with mutex lock\n", 1));
	while (++i < var->info.nb_philo)
		var->tab_nb_eat[i] = 0;
	if (pthread_mutex_unlock(&var->mutex_tab_nb_eat) != 0)
		return (ft_error_quit("Error with mutex unlock\n", 1));
	if (pthread_mutex_lock(&var->mutex_dead) != 0)
		return (ft_error_quit("Error with mutex lock\n", 1));
	var->dead = 0;
	if (pthread_mutex_unlock(&var->mutex_dead) != 0)
		return (ft_error_quit("Error with mutex unlock\n", 1));
	return (0);
}

int	ft_start_threads(t_var *var, pthread_t *threads)
{
	int	i;

	if (pthread_mutex_lock(&var->mutex_start) != 0)
		return (ft_error_quit("Error with mutex lock\n", 1));
	i = -1;
	while (++i < var->info.nb_philo)
	{
		if (pthread_mutex_lock(&var->mutex_dead) != 0)
			return (ft_error_quit("Error with mutex lock\n", 1));
		var->tid = i;
		if (pthread_mutex_unlock(&var->mutex_dead) != 0)
			return (ft_error_quit("Error with mutex lock\n", 1));
		if (pthread_create(&(threads[i]), NULL, ft_philo, var))
			return (ft_handle_thread_creation_error(var, threads, i));
		usleep(1000);
	}
	if (ft_init_time(var) != 0)
		return (1);
	if (pthread_mutex_unlock(&var->mutex_start) != 0)
		return (1);
	return (0);
}

int	ft_init_time(t_var *var)
{
	struct timeval	current_time;
	int				i;

	i = 0;
	if (pthread_mutex_lock(&var->mutex_tab_eat) != 0)
		return (ft_error_quit("Error with mutex lock\n", 1));
	gettimeofday(&current_time, NULL);
	while (i < var->info.nb_philo)
	{
		var->last_eat_s[i] = current_time.tv_sec;
		var->last_eat_ms[i] = current_time.tv_usec / 1;
		i++;
	}
	var->time_start_s = current_time.tv_sec;
	var->time_start_ms = current_time.tv_usec;
	if (pthread_mutex_unlock(&var->mutex_tab_eat) != 0)
		return (ft_error_quit("Error with mutex unlock\n", 1));
	return (0);
}
