/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:56:31 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/12 17:58:48 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

int	ft_philo(t_var *var)
{
	ft_wait_all_started(var);
	if (pthread_create(&(var->check_death), NULL, ft_thread_death, var))
		ft_call_error(var);
	pthread_detach(var->check_death);
	if (var->info.nb_philo == 1)
		return (ft_handle_one_phil(var->num_philo, var));
	ft_think(var->num_philo, var);
	if (var->num_philo % 2 == 1)
		ft_usleep(var->info.time_eat, var);
	while (ft_check_death(var) == 0)
	{
		ft_take_fork(var->num_philo, var);
		ft_eat(var->num_philo, var);
		ft_unlock_fork(var);
		if (var->nb_eat == var->info.nb_eat + 0 && var->nb_eat != -1)
			sem_post(var->sem.s_nb_eat);
		ft_sleep(var->num_philo, var);
		ft_think(var->num_philo, var);
		ft_wait_odd(var);
	}
	return (0);
}

void	ft_wait_all_started(t_var *var)
{
	struct timeval	current_time;

	if (sem_wait(var->sem.start) != 0)
		ft_exit(var);
	gettimeofday(&current_time, NULL);
	var->time_start_s = current_time.tv_sec;
	var->time_start_ms = current_time.tv_usec;
	var->last_eat_s = current_time.tv_sec;
	var->last_eat_ms = current_time.tv_usec;
}

int	ft_usleep(long time_sleep, t_var *var)
{
	struct timeval	t;
	struct timeval	rt;
	long			pass;
	int				check;

	(void) var;
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
			if (ft_check_death(var) == 1)
				return (1);
			check++;
		}
		usleep(500);
	}
	return (0);
}

int	ft_check_death(t_var *var)
{
	int	status;

	if (sem_wait(var->sem.hold) != 0)
		ft_exit(var);
	status = var->death;
	if (sem_post(var->sem.hold) != 0)
		ft_exit(var);
	return (status);
}

int	ft_unlock_fork(t_var *var)
{
	if (sem_post(var->sem.fourchettes) != 0)
		ft_exit(var);
	if (sem_post(var->sem.fourchettes) != 0)
		ft_exit(var);
	return (0);
}
