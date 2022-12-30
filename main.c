/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:59:50 by nlesage           #+#    #+#             */
/*   Updated: 2022/12/30 18:20:59 by nlesage          ###   ########.fr       */
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
	//pthread_mutex_t *mutex;
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

	
	i = -1;
	while (++i < info.nb_philo)
		pthread_mutex_init(&(var.mutex[i]), NULL);
	//var.mutex = mutex;
	
	i = 0;
	while (i < info.nb_philo)
	{
		//printf("Main: launching %ld\n", i);
		var.tid = i;
		gettimeofday(&current_time, NULL);
		var.last_eat_s[i] = current_time.tv_sec;
		var.last_eat_ms[i] = current_time.tv_usec / 1000;
		//printf("%ld%c%03ld %ld Main : set up\n", var.last_eat_s[i], ' ', var.last_eat_ms[i], i);
		rc = pthread_create(&(threads[i]), NULL, ft_philo, &var);
		//pthread_detach(threads[i]);
		//pthread_join(threads[i], NULL);
		if (rc)
		{
    		printf("ERROR; return code from pthread_create() is %d\n", rc);
    		//return (error);
   		}
		usleep(1);
		i++;
	}
	
	while (ft_is_finished(&var) == 0)
	{
		usleep(200);
	}
	
	i = -1;
	while (++i < info.nb_philo)
	{
		pthread_join(threads[i], NULL);
		usleep(100);
	}

	i = -1;
	while (++i < info.nb_philo)
		pthread_mutex_destroy(&(var.mutex[i]));
	
	
	usleep(10);
	//pthread_detach(threads[info.nb_philo - 1]);
	free(threads);
	free(var.mutex);
	//return (NULL);
}


void *ft_philo(void *arg)
{
	t_var	*var;
	long	tid;
	int		left;
	int		right;
	struct timeval current_time;

	char	c = 0;
	

	
	var = (t_var *) arg;
	tid = var->tid;
	left = (int) var->tid;
	right = ((int) var->tid + 1) % var->info.nb_philo;
	while (ft_is_finished(var) == 0)
	{
		//usleep(1);
		//printf("Thread #%ld (i=%d)\n", tid, i);

		if (left < right)
		{
			pthread_mutex_lock(&var->mutex[left]);
			gettimeofday(&current_time, NULL);
			printf("%ld%c%03ld %ld has taken a fork\n", current_time.tv_sec, c, current_time.tv_usec / 1000, tid);
			pthread_mutex_lock(&var->mutex[right]);
			gettimeofday(&current_time, NULL);
			printf("%ld%c%03ld %ld has taken a fork\n", current_time.tv_sec, c, current_time.tv_usec / 1000, tid);
		}
		else
		{
			pthread_mutex_lock(&var->mutex[right]);
			gettimeofday(&current_time, NULL);
			printf("%ld%c%03ld %ld has taken a fork\n", current_time.tv_sec, c, current_time.tv_usec / 1000, tid);
			pthread_mutex_lock(&var->mutex[left]);
			gettimeofday(&current_time, NULL);
			printf("%ld%c%03ld %ld has taken a fork\n", current_time.tv_sec, c, current_time.tv_usec / 1000, tid);
		}
		
		//gettimeofday(&current_time, NULL);
		var->last_eat_s[tid] = current_time.tv_sec;
		var->last_eat_ms[tid] = current_time.tv_usec / 1000;
		
		printf("%ld%c%03ld %ld is eating\n", current_time.tv_sec, c, current_time.tv_usec / 1000, tid);
		usleep(var->info.time_eat * 1000);
		
		pthread_mutex_unlock(&var->mutex[left]);
		pthread_mutex_unlock(&var->mutex[right]);

		gettimeofday(&current_time, NULL);
		printf("%ld%c%03ld %ld is sleeping\n", current_time.tv_sec, c, current_time.tv_usec / 1000, tid);
		usleep(var->info.time_sleep * 1000);
		
		gettimeofday(&current_time, NULL);
		printf("%ld%c%03ld %ld is thinking\n", current_time.tv_sec, c, current_time.tv_usec / 1000, tid);

		if (ft_call_dead(var) == 1)
			break ;
	}
	//printf("I quit %ld\n", tid);
	return (NULL);
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
	int				status;

	char	c = 0;

	i = 0;
	status = ft_is_finished(var);
	gettimeofday(&time, NULL);
	while (i < var->info.nb_philo)
	{
		pass = (time.tv_sec - var->last_eat_s[i]) * 1000 + (time.tv_usec / 1000 - var->last_eat_ms[i]);
		if (pass > var->info.time_die && status == 0)
		{
			pthread_mutex_lock(&var->mutex_dead);
			var->dead = 1;
			pthread_mutex_unlock(&var->mutex_dead);
			//printf("%ld%c%03ld %d died\n", time.tv_sec, c, time.tv_usec / 1000, i);
			printf("%ld%c%03ld %d died [data known=%ld%c%03ld], pass=%ld\n", time.tv_sec, c, time.tv_usec / 1000, i, var->last_eat_s[i],c, var->last_eat_ms[i], pass);
			return (1);
		}
		i++;
	}
	return (0);
}
