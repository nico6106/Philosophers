/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_end_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:55:35 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/09 17:42:32 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

int	ft_is_finished(t_var *var)
{
	int	status;

	if (pthread_mutex_lock(&var->mutex_dead) != 0)
		ft_exit(var);
	status = var->dead;
	if (pthread_mutex_unlock(&var->mutex_dead) != 0)
		ft_exit(var);
	return (status);
}

int	ft_finished(t_var *var)
{
	int	i;

	i = 0;
	if (var->info.nb_eat == -1)
		return (0);
	if (pthread_mutex_lock(&var->mutex_tab_nb_eat) != 0)
		ft_exit(var);
	while (i < var->info.nb_philo)
	{
		if (var->tab_nb_eat[i] < var->info.nb_eat)
		{
			if (pthread_mutex_unlock(&var->mutex_tab_nb_eat) != 0)
				ft_exit(var);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_unlock(&var->mutex_tab_nb_eat) != 0)
		ft_exit(var);
	if (pthread_mutex_lock(&var->mutex_dead) != 0)
		ft_exit(var);
	var->dead = 1;
	if (pthread_mutex_unlock(&var->mutex_dead) != 0)
		ft_exit(var);
	return (1);
}

int	ft_call_dead(t_var *var)
{
	struct timeval	t;
	int				i;

	i = -1;
	if (ft_is_finished(var) == 1)
		return (1);
	gettimeofday(&t, NULL);
	while (++i < var->info.nb_philo)
	{
		if (ft_sub_call_dead(var, i, t.tv_sec, t.tv_usec) == 1)
			return (1);
	}
	return (0);
}

int	ft_sub_call_dead(t_var *var, int i, long sec, long usec)
{
	long	pass;

	pass = 0;
	if (pthread_mutex_lock(&var->mutex_tab_eat) != 0)
		ft_exit(var);
	pass = (sec - var->last_eat_s[i]) * 1000000 + (usec - var->last_eat_ms[i]);
	if (pthread_mutex_unlock(&var->mutex_tab_eat) != 0)
		ft_exit(var);
	if (pass > (long) var->info.time_die * 1000 && ft_is_finished(var) == 0)
	{
		if (pthread_mutex_lock(&var->mutex_dead) != 0)
			ft_exit(var);
		var->dead = 1;
		if (pthread_mutex_unlock(&var->mutex_dead) != 0)
			ft_exit(var);
		if (pthread_mutex_lock(&var->mutex_start) != 0)
			ft_exit(var);
		pass = ft_time_elapsed(var, sec, usec);
		printf("%ld %d died\n", pass, i + 1);
		if (pthread_mutex_unlock(&var->mutex_start) != 0)
			ft_exit(var);
		return (1);
	}
	return (0);
}
