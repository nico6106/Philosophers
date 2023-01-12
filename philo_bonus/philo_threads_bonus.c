/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:06:20 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/12 13:07:18 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

void	*ft_thread_death(void *arg)
{
	t_var			*var;
	long			pass;
	struct timeval	t;

	var = (t_var *) arg;
	while (1)
	{
		if (sem_wait(var->sem.hold) != 0)
			ft_exit(var);
		gettimeofday(&t, NULL);
		pass = (t.tv_sec - var->last_eat_s) * 1000000
			+ (t.tv_usec - var->last_eat_ms);
		if (pass > (long) var->info.time_die * 1000)
		{
			pass = ft_time_elapsed(var, t.tv_sec, t.tv_usec);
			ft_is_dead(var, pass);
		}
		if (sem_post(var->sem.hold) != 0)
			ft_exit(var);
		usleep(5000);
	}
	return (NULL);
}

void	ft_is_dead(t_var *var, long pass)
{
	if (sem_wait(var->sem.ecrire) != 0)
		ft_exit(var);
	printf("%ld %ld died\n", pass, var->num_philo + 1);
	if (sem_post(var->sem.end) != 0)
		ft_exit(var);
	var->death = 1;
	if (sem_post(var->sem.hold) != 0)
		ft_exit(var);
	if (sem_wait(var->sem.ecrire) != 0)
		ft_exit(var);
	while (1)
		;
}
