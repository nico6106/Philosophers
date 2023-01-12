/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_check_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:47:13 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/12 13:22:58 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

void	*ft_check_nb_eat(void *arg)
{
	t_var	*var;
	int		i;

	var = (t_var *) arg;
	if (var->info.nb_eat == -1)
		return (NULL);
	ft_init_thread_check_eat(var);
	i = -1;
	while (++i < var->info.nb_philo)
	{
		if (sem_wait(var->sem.s_nb_eat) != 0)
			ft_exit(var);
	}
	while (++i < var->info.nb_philo)
	{
		if (sem_post(var->sem.s_nb_eat) != 0)
			ft_exit(var);
	}
	ft_end_thread_check_eat(var);
	return (NULL);
}

void	ft_init_thread_check_eat(t_var *var)
{
	int	i;

	i = -1;
	while (++i < var->info.nb_philo)
	{
		if (sem_wait(var->sem.s_nb_eat) != 0)
			ft_exit(var);
	}
	if (sem_post(var->sem.run) != 0)
		ft_exit(var);
	if (sem_wait(var->sem.admin) != 0)
		ft_exit(var);
	if (sem_post(var->sem.admin) != 0)
		ft_exit(var);
	if (sem_wait(var->sem.run) != 0)
		ft_exit(var);
}

void	ft_end_thread_check_eat(t_var *var)
{
	int	i;

	if (sem_wait(var->sem.admin) != 0)
		ft_exit(var);
	if (var->end_simulation == 0)
	{
		var->end_simulation = 1;
		i = -1;
		while (++i < var->info.nb_philo)
		{
			if (kill(var->pid[i], SIGKILL) == -1)
				;
		}
	}
	if (sem_post(var->sem.run) != 0)
		ft_exit(var);
	if (sem_post(var->sem.admin) != 0)
		ft_exit(var);
}

void	*ft_thread_check_death(void *arg)
{
	t_var	*var;
	int		i;

	var = (t_var *) arg;
	usleep(var->info.time_die);
	if (sem_wait(var->sem.end) != 0)
		ft_exit(var);
	i = -1;
	while (++i < var->info.nb_philo)
	{
		if (kill(var->pid[i], SIGKILL) == -1)
			;
	}
	if (sem_post(var->sem.end) != 0)
		ft_exit(var);
	return (NULL);
}
