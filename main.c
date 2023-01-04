/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:59:50 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/04 18:51:22 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_info		info;

	info = ft_load_arg(argc, argv);
	if (info.nb_philo == -1)
		return (ft_error_quit(NULL, 1));
	if (info.nb_philo < 1)
		return (ft_error_quit("Error: wrong number of philosophers\n", 1));
	ft_start_threads(info);
	return (0);
}

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
    		printf("ERROR: return code from pthread_create() is %d\n", rc);
    		//return (error);
   		}
		usleep(1000);
		i++;
	}

	i = 0;
	pthread_mutex_init(&var.mutex_tab_eat, NULL);
	pthread_mutex_lock(&var.mutex_tab_eat);
	gettimeofday(&current_time, NULL);
	while (i < info.nb_philo)
	{
		var.last_eat_s[i] = current_time.tv_sec;
		var.last_eat_ms[i] = current_time.tv_usec / 1;
		i++;
	}
	pthread_mutex_unlock(&var.mutex_tab_eat);	

	pthread_mutex_unlock(&var.mutex_start);	
	
	while (ft_is_finished(&var) == 0)
	{
		ft_usleep(1000, &var, 0);
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
	pthread_mutex_destroy(&var.mutex_tab_eat);
	
	free(threads);
	free(var.last_eat_s);
	free(var.last_eat_ms);
	free(var.mutex);
	//return (NULL);
}



