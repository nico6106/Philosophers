/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:19:42 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/12 13:10:15 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

int	ft_error_quit(char *str, int retour)
{
	int	i;

	if (str)
	{
		i = -1;
		while (str[++i])
			write(2, &str[i], 1);
	}
	return (retour);
}

int	ft_call_error(t_var *var)
{
	ft_end_philo(var);
	printf("erreur\n");
	if (var->num_philo == 0)
		var->num_philo = -1;
	exit (var->num_philo);
}

int	ft_close_sem_error(t_var *var)
{
	sem_close(var->sem.ecrire);
	sem_close(var->sem.run);
	sem_close(var->sem.s_nb_eat);
	sem_close(var->sem.take);
	sem_close(var->sem.admin);
	sem_close(var->sem.start);
	sem_close(var->sem.end);
	return (1);
}

int	ft_exit(t_var *var)
{
	ft_end_philo(var);
	printf("erreur\n");
	if (var->num_philo == 0)
		var->num_philo = -1;
	exit (var->num_philo);
}

int	ft_handle_one_phil(long tid, t_var *var)
{
	struct timeval	t;
	long			pass;

	gettimeofday(&t, NULL);
	if (sem_wait(var->sem.fourchettes) != 0)
		ft_exit(var);
	pass = ft_time_elapsed(var, t.tv_sec, t.tv_usec);
	printf("%ld %ld has taken a fork\n", pass, tid + 1);
	ft_usleep(var->info.time_die * 1, var);
	if (sem_post(var->sem.fourchettes) != 0)
		ft_exit(var);
	gettimeofday(&t, NULL);
	pass = ft_time_elapsed(var, t.tv_sec, t.tv_usec);
	return (1);
}
