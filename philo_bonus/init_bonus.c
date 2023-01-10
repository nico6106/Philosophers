/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:06:27 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/10 18:13:04 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

int	ft_init_sem(t_var *var, t_info info)
{
	sem_unlink(FOURCHETTES);
	sem_unlink(TAKE);
	sem_unlink(ECRIRE);
	sem_unlink(RUN);
	var->sem.fourchettes = sem_open(FOURCHETTES, O_CREAT, 0777, info.nb_philo);
	if (var->sem.fourchettes == SEM_FAILED)
		return (1);
	sem_close(var->sem.fourchettes);
	var->sem.ecrire = sem_open(ECRIRE, O_CREAT, 0777, 1);
	if (var->sem.ecrire == SEM_FAILED)
		return (1);
	var->sem.take = sem_open(TAKE, O_CREAT, 0777, 1);
	if (var->sem.take == SEM_FAILED)
		return (1);
	sem_close(var->sem.take);
	var->sem.run = sem_open(RUN, O_CREAT, 0777, 1);
	if (var->sem.run == SEM_FAILED)
		return (1);
	return (0);
}

int	ft_reopen_sem(t_var *var)
{
	var->sem.fourchettes = sem_open(FOURCHETTES, O_RDWR);
	if (var->sem.fourchettes == SEM_FAILED)
		return (1);
	var->sem.ecrire = sem_open(ECRIRE, O_RDWR);
	if (var->sem.ecrire == SEM_FAILED)
		return (1);
	var->sem.take = sem_open(TAKE, O_RDWR);
	if (var->sem.take == SEM_FAILED)
		return (1);
	var->sem.run = sem_open(RUN, O_RDWR);
	if (var->sem.run == SEM_FAILED)
		return (1);
	return (0);
}

int	ft_init(t_var *var, t_info info)
{
	if (ft_init_sem(var, info) == 1)
		return (1);
	var->pid = malloc(info.nb_philo * sizeof(pid_t));
	if (!var->pid)
		return (ft_close_sem_error(var));
	var->info = info;
	return (0);
}

int	ft_close_sem_error(t_var *var)
{
	sem_close(var->sem.ecrire);
	sem_close(var->sem.run);
	return (1);
}
