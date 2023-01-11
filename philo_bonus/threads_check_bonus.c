/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_check_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:47:13 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/11 18:23:54 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

void	*ft_check_nb_eat(void *arg)
{
	t_var	*var;
	int		i;

	var = (t_var *) arg;
	//printf("ft_check_nb_eat: nb_eat=%d\n", var->info.nb_eat);
	if (var->info.nb_eat == -1)
		return (NULL);
		
	i = -1;
	while (++i < var->info.nb_philo)
	{
		if (sem_wait(var->sem.s_nb_eat) != 0)
			ft_exit(var);
	}
	i = -1;
	if (sem_post(var->sem.run) != 0)
			ft_exit(var);
	
	
	/*protection*/
	if (sem_wait(var->sem.admin) != 0)
		ft_exit(var);
	if (sem_post(var->sem.admin) != 0)
		ft_exit(var);
	
	
	while (++i < var->info.nb_philo)
	{
		if (sem_wait(var->sem.s_nb_eat) != 0) /*pb ici?*/
			ft_exit(var);
	}
	while (++i < var->info.nb_philo)
	{
		if (sem_post(var->sem.s_nb_eat) != 0)
			ft_exit(var);
	}
	
	if (sem_wait(var->sem.admin) != 0)
		ft_exit(var);
	var->end_simulation = 1;
	if (sem_post(var->sem.admin) != 0)
		ft_exit(var);
	
	i = -1;
	while (++i < var->info.nb_philo)
	{
		if (kill(var->pid[i], SIGKILL) == -1)
			; //ft_error_quit("Error the PID doesn't exist", 0);
		//printf("signal sent %d\n", i);
	}

	return (NULL);
}

int	ft_check_start(t_var *var)
{
	int	status;

	if (sem_wait(var->sem.admin) != 0)
			ft_exit(var);
	status = var->start;
	if (sem_post(var->sem.admin) != 0)
			ft_exit(var);
	return (status);
}
