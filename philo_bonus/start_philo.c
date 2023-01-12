/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:52:30 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/12 18:01:08 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

int	ft_launch_checker_threads(t_var *var)
{
	pthread_t	thread_check_nb_eat;

	if (sem_wait(var->sem.end) != 0)
		ft_exit(var);
	if (var->info.nb_eat > 0)
	{
		if (sem_wait(var->sem.run) != 0)
			ft_exit(var);
		if (sem_wait(var->sem.admin) != 0)
			ft_exit(var);
		if (pthread_create(&thread_check_nb_eat, NULL, ft_check_nb_eat, var))
		{
			ft_end_pgrm(var);
			return (1);
		}
		pthread_detach(thread_check_nb_eat);
	}
	if (sem_wait(var->sem.run) != 0)
		ft_exit(var);
	if (sem_post(var->sem.run) != 0)
		ft_exit(var);
	return (0);
}

int	ft_launch_checker_threads_death(t_var *var)
{
	pthread_t	thread_check_death;

	if (pthread_create(&thread_check_death, NULL, ft_thread_check_death, var))
	{
		ft_end_pgrm(var);
		return (1);
	}
	pthread_detach(thread_check_death);
	return (0);
}

void	ft_fork_and_start(t_var *var)
{
	int	i;
	int	rv;

	if (sem_wait(var->sem.start) != 0)
		ft_exit(var);
	var->pid[0] = fork();
	i = -1;
	while (++i < var->info.nb_philo)
	{
		if (var->pid[i] == 0)
		{
			var->num_philo = i;
			if (ft_reopen_sem(var) == 1)
				ft_call_error(var);
			ft_philo(var);
			rv = var->death;
			ft_end_philo(var);
			exit (rv);
		}
		else if ((i + 1) < var->info.nb_philo)
			var->pid[i + 1] = fork();
	}
	ft_fork_and_start_next(var);
}

void	ft_fork_and_start_next(t_var *var)
{
	int	i;

	if (ft_launch_checker_threads_death(var) == 1)
		return ;
	if (sem_post(var->sem.admin) != 0)
		ft_exit(var);
	i = -1;
	while (++i < var->info.nb_philo + 1)
	{
		if (sem_post(var->sem.start) != 0)
			ft_exit(var);
	}
}
