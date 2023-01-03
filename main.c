/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:59:50 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/03 16:05:52 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_info		info;
	//pthread_t	*threads;

	info = ft_load_arg(argc, argv);
	if (info.nb_philo == -1)
		return (ft_error_quit(NULL, 1));
	//printf("Arguments ok\n");
	//threads = ft_start_threads(info);
	ft_start_threads(info);
	//free(threads);
	return (0);
}

//pthread_t	*ft_start_threads(t_info info)
void	ft_start_threads(t_info info)
{
	pthread_t		*threads;
	long			i;
	int 			rc;
	t_var			var;
	struct timeval current_time;


	threads = malloc(info.nb_philo * sizeof(pthread_t));
	if (!threads)
		i = 0;
	var.last_eat_s = malloc(info.nb_philo * sizeof(long));
	if (!var.last_eat_s)
		i = 0;
	var.last_eat_ms = malloc(info.nb_philo * sizeof(long));
	if (!var.last_eat_ms)
		i = 0;
	var.mutex = malloc(info.nb_philo * sizeof(pthread_mutex_t));
	if (!var.mutex)
		i = 0; //return (error)
				
	var.info = info;
	pthread_mutex_init(&var.mutex_dead, NULL);
	pthread_mutex_lock(&var.mutex_dead);
	var.dead = 0;
	pthread_mutex_unlock(&var.mutex_dead);

	pthread_mutex_init(&var.mutex_start, NULL);
	pthread_mutex_lock(&var.mutex_start);
	
	i = -1;
	while (++i < info.nb_philo)
		pthread_mutex_init(&(var.mutex[i]), NULL);
	
	i = 0;
	while (i < info.nb_philo)
	{
		var.tid = i;
		rc = pthread_create(&(threads[i]), NULL, ft_philo, &var);
		if (rc)
		{
    		printf("ERROR; return code from pthread_create() is %d\n", rc);
    		//return (error);
   		}
		usleep(1000);
		i++;
	}

	i = 0;
	gettimeofday(&current_time, NULL);
	while (i < info.nb_philo)
	{
		var.last_eat_s[i] = current_time.tv_sec;
		var.last_eat_ms[i] = current_time.tv_usec / 1000;
		i++;
	}

	pthread_mutex_unlock(&var.mutex_start);	
	
	while (ft_is_finished(&var) == 0)
	{
		ft_usleep(500, &var);
	}
	
	i = -1;
	while (++i < info.nb_philo)
	{
		pthread_join(threads[i], NULL);
		usleep(10);
	}

	i = -1;
	while (++i < info.nb_philo)
		pthread_mutex_destroy(&(var.mutex[i]));
	pthread_mutex_destroy(&var.mutex_dead);
	pthread_mutex_destroy(&var.mutex_start);
	
	free(threads);
	free(var.last_eat_s);
	free(var.last_eat_ms);
	free(var.mutex);
	//return (NULL);
}


void *ft_philo(void *arg)
{
	t_var			*var;
	long			tid;
	int				left;
	int				right;
	
	var = (t_var *) arg;
	tid = var->tid;
	left = (int) var->tid;
	right = ((int) var->tid + 1) % var->info.nb_philo;
	ft_wait_all_started(var);
	if (tid % 2 == 1)
		ft_usleep(var->info.time_eat, var);
	while (ft_is_finished(var) == 0)
	{
		ft_take_fork(tid, var, left, right);
		ft_eat(tid, var);
		pthread_mutex_unlock(&var->mutex[left]);
		pthread_mutex_unlock(&var->mutex[right]);
		ft_sleep(tid, var);
		ft_think(tid, var);
		if (ft_call_dead(var) == 1)
			break ;
	}
	return (NULL);
}

int	ft_usleep(long time_sleep, t_var *var)
{
	struct timeval	time;
	struct timeval	ref_time;
	long			pass;

	gettimeofday(&ref_time, NULL);
	gettimeofday(&time, NULL);
	pass = (time.tv_sec - ref_time.tv_sec) * 1000 + (time.tv_usec / 1000 - ref_time.tv_usec / 1000);
	while (pass < time_sleep)
	{
		gettimeofday(&time, NULL);
		pass = (time.tv_sec - ref_time.tv_sec) * 1000 + (time.tv_usec / 1000 - ref_time.tv_usec / 1000);
		usleep(500);
		if (ft_call_dead(var) == 1)
			return (1);
	}
	return (0);
}

int	ft_is_finished(t_var *var)
{
	int	status;
	pthread_mutex_lock(&var->mutex_dead);
	status = var->dead;
	pthread_mutex_unlock(&var->mutex_dead);
	return (status);
}

int	ft_call_dead(t_var *var)
{
	struct timeval	time;
	long			pass;
	int				i;
	//int				status;

	i = 0;
	//status = ft_is_finished(var);
	if (ft_is_finished(var) == 1)
		return (1);
	gettimeofday(&time, NULL);
	while (i < var->info.nb_philo)
	{
		pass = (time.tv_sec - var->last_eat_s[i]) * 1000 + (time.tv_usec / 1000 - var->last_eat_ms[i]);
		if (pass > var->info.time_die && ft_is_finished(var) == 0)
		{
			pthread_mutex_lock(&var->mutex_dead);
			var->dead = 1;
			pthread_mutex_unlock(&var->mutex_dead);
			printf("%ld%03ld %d died\n", time.tv_sec, time.tv_usec / 1000, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_wait_all_started(t_var *var)
{
	pthread_mutex_lock(&var->mutex_start);
	pthread_mutex_unlock(&var->mutex_start);
}
