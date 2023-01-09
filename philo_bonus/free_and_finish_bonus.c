/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_finish_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 09:44:40 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/09 17:42:29 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

void	ft_free_and_finish(t_var *var)
{
	int	i;

	i = -1;
	while (++i < var->info.nb_philo)
		ft_pthread_mutex_destroy(&var->mutex[i]);
	ft_pthread_mutex_destroy(&var->mutex_dead);
	ft_pthread_mutex_destroy(&var->mutex_start);
	ft_pthread_mutex_destroy(&var->mutex_tab_eat);
	ft_pthread_mutex_destroy(&var->mutex_tab_nb_eat);
}

int	ft_free_tab(t_var *var, pthread_t *threads, int retour)
{
	if (threads)
		free(threads);
	if (var)
	{
		free(var->last_eat_s);
		free(var->last_eat_ms);
		free(var->mutex);
		free(var->tab_nb_eat);
	}
	return (retour);
}

void	ft_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex) != 0)
	{
		pthread_mutex_unlock(mutex);
		pthread_mutex_destroy(mutex);
	}
}

int	ft_handle_destroy_mutex(t_var *var, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		ft_pthread_mutex_destroy(&(var->mutex[i]));
	ft_pthread_mutex_destroy(&var->mutex_tab_eat);
	ft_pthread_mutex_destroy(&var->mutex_tab_nb_eat);
	ft_pthread_mutex_destroy(&var->mutex_start);
	return (ft_error_quit("Error with mutex initialization\n", 1));
}
