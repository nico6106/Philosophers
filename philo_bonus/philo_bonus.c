/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:56:31 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/10 19:28:19 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

int	ft_philo(t_var *var)
{
	//t_philo	philo;
	//int	i=0;

	//philo = ft_init_philo(var);
	//if (philo.left == -1)
	//	return (NULL);
	ft_wait_all_started(var);
	//if (var->info.nb_philo == 1)
	//	ft_handle_one_phil(philo.tid, var);
	ft_think(var->num_philo, var);
	if (var->num_philo % 2 == 1)
		ft_usleep(var->info.time_eat, var);
	///*
	while (ft_check_death(var) == 0) //ft_is_finished(var) == 0 && ft_finished(var) == 0)
	{
		ft_take_fork(var->num_philo, var);
		ft_eat(var->num_philo, var);
		ft_unlock_fork(var);
		if (var->nb_eat == var->info.nb_eat + 0 && var->nb_eat != -1)
			break ;
		//if (ft_finished(var) == 1)
		//	return (NULL);
		ft_sleep(var->num_philo, var);
		ft_think(var->num_philo, var);
		//ft_wait_odd(var, philo.tid);
		
	}
	//*/
	return (0);
}

void	ft_wait_all_started(t_var *var)
{
	struct timeval	current_time;

	if (sem_wait(var->sem.run) != 0)
		ft_exit(var);
	if (sem_post(var->sem.run) != 0)
		ft_exit(var);
	gettimeofday(&current_time, NULL);
	var->time_start_s = current_time.tv_sec;
	var->time_start_ms = current_time.tv_usec;
	var->last_eat_s = current_time.tv_sec;
	var->last_eat_ms = current_time.tv_usec;
	//printf("%ld: s=%ld ms=%ld\n", var->num_philo+1, var->time_start_s, var->time_start_ms);
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
			//else if (ft_finished(var) == 1)
			//	return (1);
			check++;
		}
		usleep(500);
	}
	return (0);
}

int	ft_check_death(t_var *var)
{
	long			pass;
	struct timeval	t;

	if (var->death != 0)
		return (1);
	if (var->nb_eat >= var->info.nb_eat + 0 && var->info.nb_eat != -1)
		return (1);
	gettimeofday(&t, NULL);
	pass = (t.tv_sec - var->last_eat_s) * 1000000 + (t.tv_usec - var->last_eat_ms);
	if (pass > (long) var->info.time_die * 1000 && var->death == 0)
	{
		//printf("time_die=%d, pass=%ld\n", var->info.time_die, pass);
		if (sem_wait(var->sem.ecrire) != 0)
			ft_exit(var);
		
		pass = ft_time_elapsed(var, t.tv_sec, t.tv_usec);
		printf("%ld %ld died\n", pass, var->num_philo + 1);
		
		//if (sem_post(var->sem.ecrire) != 0)
		//	ft_exit(var);
		var->death = 1;
		return (1);
	}
	return (0);
}
