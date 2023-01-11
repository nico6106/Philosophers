/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:06:27 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/11 19:00:54 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

int	ft_init_sem(t_var *var, t_info info)
{
	sem_unlink(FOURCHETTES);
	sem_unlink(TAKE);
	sem_unlink(ECRIRE);
	sem_unlink(RUN);
	sem_unlink(NB_EAT);
	sem_unlink(ADMIN);
	sem_unlink(START);
	sem_unlink(HOLD);
	var->sem.fourchettes = sem_open(FOURCHETTES, O_CREAT, 0777, info.nb_philo);
	if (var->sem.fourchettes == SEM_FAILED)
		return (1);
	sem_close(var->sem.fourchettes);
	var->sem.hold = sem_open(HOLD, O_CREAT, 0777, info.nb_philo);
	if (var->sem.hold == SEM_FAILED)
		return (1);
	sem_close(var->sem.hold);
	var->sem.s_nb_eat = sem_open(NB_EAT, O_CREAT, 0777, info.nb_philo);
	if (var->sem.s_nb_eat == SEM_FAILED)
		return (1);
	var->sem.ecrire = sem_open(ECRIRE, O_CREAT, 0777, 1);
	if (var->sem.ecrire == SEM_FAILED)
		return (1);
	var->sem.take = sem_open(TAKE, O_CREAT, 0777, 1);
	if (var->sem.take == SEM_FAILED)
		return (1);
	var->sem.run = sem_open(RUN, O_CREAT, 0777, 1);
	if (var->sem.run == SEM_FAILED)
		return (1);
	var->sem.admin = sem_open(ADMIN, O_CREAT, 0777, 1);
	if (var->sem.admin == SEM_FAILED)
		return (1);
	var->sem.start = sem_open(START, O_CREAT, 0777, 1);
	if (var->sem.start == SEM_FAILED)
		return (1);
	
	/*
	if (sem_post(var->sem.s_nb_eat) != 0)
		ft_exit(var);
	*/
	return (0);
}

int	ft_reopen_sem(t_var *var)
{	
	
	
	
	
	var->sem.bis_fourchettes = sem_open(FOURCHETTES, O_RDWR);
	if (var->sem.bis_fourchettes == SEM_FAILED)
		return (1);
	var->sem.bis_ecrire = sem_open(ECRIRE, O_RDWR);
	if (var->sem.bis_ecrire == SEM_FAILED)
		return (1);
	var->sem.bis_take = sem_open(TAKE, O_RDWR);
	if (var->sem.bis_take == SEM_FAILED)
		return (1);
	var->sem.bis_s_nb_eat = sem_open(NB_EAT, O_RDWR);
	if (var->sem.bis_s_nb_eat == SEM_FAILED)
		return (1);
	var->sem.bis_start = sem_open(START, O_RDWR);
	if (var->sem.bis_start == SEM_FAILED)
		return (1);
	var->sem.hold = sem_open(START, O_RDWR);
	if (var->sem.hold == SEM_FAILED)
		return (1);
	

	/*
	i = -1;
	while (++i < var->info.nb_philo)
	{
		if (sem_post(var->sem.fourchettes) != 0)
			ft_exit(var);
	}
	*/
	
	//if (sem_post(var->sem.ecrire) != 0)
	//	ft_exit(var);
	//if (sem_post(var->sem.take) != 0)
	//	ft_exit(var);
	//if (sem_post(var->sem.start) != 0)
	//	ft_exit(var);
	
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
	sem_close(var->sem.s_nb_eat);
	sem_close(var->sem.take);
	sem_close(var->sem.admin);
	sem_close(var->sem.start);
	return (1);
}
