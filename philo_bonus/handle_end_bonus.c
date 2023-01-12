/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_end_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:19:45 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/12 17:59:50 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

int	ft_handle_end(t_var *var, int val, int pid_end)
{
	int	i;
	int	rv;
	int	retour;

	if (val != 0)
	{
		i = -1;
		while (++i < var->info.nb_philo)
		{
			if (pid_end != var->pid[i])
			{
				retour = kill(var->pid[i], SIGKILL);
				if (retour == -1)
					ft_error_quit("Error the PID doesn't exist", 0);
			}
		}
	}
	ft_liberate_sem(var);
	i = -1;
	while (++i < var->info.nb_philo)
		waitpid(var->pid[i], &rv, 0);
	return (0);
}

void	ft_liberate_sem(t_var *var)
{
	int	i;

	i = -1;
	while (++i < var->info.nb_philo + 1)
	{
		if (sem_post(var->sem.s_nb_eat) != 0)
			ft_exit(var);
		if (sem_post(var->sem.admin) != 0)
			ft_exit(var);
		if (sem_post(var->sem.run) != 0)
			ft_exit(var);
	}
	if (sem_wait(var->sem.run) != 0)
		ft_exit(var);
	if (sem_post(var->sem.run) != 0)
		ft_exit(var);
}

int	ft_end_pgrm(t_var *var)
{
	sem_close(var->sem.ecrire);
	sem_close(var->sem.s_nb_eat);
	sem_close(var->sem.admin);
	sem_close(var->sem.start);
	sem_close(var->sem.end);
	sem_unlink(FOURCHETTES);
	sem_unlink(TAKE);
	sem_unlink(ECRIRE);
	sem_unlink(RUN);
	sem_unlink(NB_EAT);
	sem_unlink(ADMIN);
	sem_unlink(START);
	sem_unlink(HOLD);
	sem_unlink(END);
	free(var->pid);
	return (0);
}

int	ft_end_philo(t_var *var)
{
	sem_close(var->sem.fourchettes);
	sem_close(var->sem.ecrire);
	sem_close(var->sem.take);
	sem_close(var->sem.start);
	sem_close(var->sem.s_nb_eat);
	sem_close(var->sem.hold);
	free(var->pid);
	return (0);
}
