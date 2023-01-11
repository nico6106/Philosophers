/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:56:31 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/11 19:30:02 by nlesage          ###   ########.fr       */
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
		{
			//printf("philo %ld unlock nb_eat (%d)\n", var->num_philo, var->nb_eat);
			sem_post(var->sem.bis_s_nb_eat);
		}
		ft_sleep(var->num_philo, var);
		ft_think(var->num_philo, var);
		ft_wait_odd(var);
	}
	return (0);
}

void	*ft_thread_death(void *arg)
{
	t_var	*var;
	//int		i;
	long			pass;
	long			time_die;
	struct timeval	t;
	int				death;

	var = (t_var *) arg;
	death = 0;
	pass = 0;
	time_die = var->info.time_die * 1000;
	//var->death = 0;
	while (death == 0)
	{
		if (sem_wait(var->sem.hold) != 0)
			ft_exit(var);
		
		if (var->death != 0)
		{
			if (sem_post(var->sem.hold) != 0)
				ft_exit(var);
			break ;
		}
		pass = gettimeofday(&t, NULL) == -1;
		while (pass == -1)
		{
			printf("erreur gettime %ld\n", var->num_philo);
			pass = gettimeofday(&t, NULL) == -1;
		}
		pass = (t.tv_sec - var->last_eat_s) * 1000000 + (t.tv_usec - var->last_eat_ms);
		
		/*if (sem_wait(var->sem.ecrire) != 0)
			ft_exit(var);
		printf("pass=%ld\n", pass);
		printf("var->info.time_die=%d\n", var->info.time_die);
		printf("var->death=%d\n", var->death);
		if (sem_post(var->sem.ecrire) != 0)
			ft_exit(var);*/
			
		if (pass > time_die) //(long) var->info.time_die * 1000)
		{
			var->death = 1;
			if (sem_wait(var->sem.bis_ecrire) != 0)
				ft_exit(var);
			pass = ft_time_elapsed(var, t.tv_sec, t.tv_usec);
			printf("%ld %ld died\n", pass, var->num_philo + 1);
			if (sem_post(var->sem.hold) != 0)
				ft_exit(var);
			break ;
		}
		if (sem_post(var->sem.hold) != 0)
			ft_exit(var);
		usleep(2000);
	}
	return (NULL);
}


void	ft_wait_all_started(t_var *var)
{
	struct timeval	current_time;

	//printf("%ld attend wait\n", var->num_philo+1);
	if (sem_wait(var->sem.bis_start) != 0)
		ft_exit(var);
	//printf("%ld demarre\n", var->num_philo+1);
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
			check++;
		}
		usleep(500);
	}
	return (0);
}

int	ft_check_death(t_var *var)
{
	/*
	long			pass;
	struct timeval	t;

	if (var->death != 0)
		return (1);
	gettimeofday(&t, NULL);
	pass = (t.tv_sec - var->last_eat_s) * 1000000 + (t.tv_usec - var->last_eat_ms);
	if (pass > (long) var->info.time_die * 1000 && var->death == 0)
	{
		var->death = 1;
		if (sem_wait(var->sem.bis_ecrire) != 0)
			ft_exit(var);
		pass = ft_time_elapsed(var, t.tv_sec, t.tv_usec);
		printf("%ld %ld died\n", pass, var->num_philo + 1);
		return (1);
	}
	*/

	int	status;

	if (sem_wait(var->sem.hold) != 0)
		ft_exit(var);
	status = var->death; 
	if (sem_post(var->sem.hold) != 0)
		ft_exit(var);
	return (status);
}
