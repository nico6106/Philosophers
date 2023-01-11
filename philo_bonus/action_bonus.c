/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:00:56 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/11 19:25:21 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

int	ft_think(long tid, t_var *var)
{
	struct timeval	t;
	long			pass;

	gettimeofday(&t, NULL);
	if (ft_check_death(var) == 0)
	{
		if (sem_wait(var->sem.bis_ecrire) != 0)
			ft_exit(var);
		pass = ft_time_elapsed(var, t.tv_sec, t.tv_usec);
		printf("%ld %ld is thinking\n", pass, tid + 1);
		if (sem_post(var->sem.bis_ecrire) != 0)
			ft_exit(var);
	}
	return (0);
}

int	ft_take_fork(long tid, t_var *var)
{
	if (sem_wait(var->sem.bis_take) != 0)
		ft_exit(var);
	if (sem_wait(var->sem.bis_fourchettes) != 0)
		ft_exit(var);
	ft_show_take_fork(tid, var);
	if (sem_wait(var->sem.bis_fourchettes) != 0)
		ft_exit(var);
	ft_show_take_fork(tid, var);
	if (sem_post(var->sem.bis_take) != 0)
		ft_exit(var);
	return (0);
}

int	ft_show_take_fork(long tid, t_var *var)
{
	struct timeval	t;
	long			pass;

	gettimeofday(&t, NULL);
	if (ft_check_death(var) == 0)
	{
		pass = ft_time_elapsed(var, t.tv_sec, t.tv_usec);
		if (sem_wait(var->sem.bis_ecrire) != 0)
			ft_exit(var);
		printf("%ld %ld has taken a fork\n", pass, tid + 1);
		if (sem_post(var->sem.bis_ecrire) != 0)
			ft_exit(var);
	}
	return (0);
}

int	ft_unlock_fork(t_var *var)
{
	if (sem_post(var->sem.bis_fourchettes) != 0)
		ft_exit(var);
	if (sem_post(var->sem.bis_fourchettes) != 0)
		ft_exit(var);
	return (0);
}

void	ft_eat(long tid, t_var *var)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (ft_check_death(var) == 0)
	{
		if (sem_wait(var->sem.hold) != 0)
			ft_exit(var);
		var->last_eat_s = t.tv_sec;
		var->last_eat_ms = t.tv_usec;
		if (sem_post(var->sem.hold) != 0)
			ft_exit(var);
		if (sem_wait(var->sem.bis_ecrire) != 0)
			ft_exit(var);
		printf("%ld %ld is eating\n",
			ft_time_elapsed(var, t.tv_sec, t.tv_usec), tid + 1);
		if (sem_post(var->sem.bis_ecrire) != 0)
			ft_exit(var);
		ft_usleep(var->info.time_eat * 1, var);
		var->nb_eat = var->nb_eat + 1;
	}

}

int	ft_sleep(long tid, t_var *var)
{
	struct timeval	t;
	long			pass;

	gettimeofday(&t, NULL);
	if (ft_check_death(var) == 0)
	{
		pass = ft_time_elapsed(var, t.tv_sec, t.tv_usec);
		if (sem_wait(var->sem.bis_ecrire) != 0)
			ft_exit(var);
		printf("%ld %ld is sleeping\n", pass, tid + 1);
		if (sem_post(var->sem.bis_ecrire) != 0)
			ft_exit(var);
		ft_usleep(var->info.time_sleep * 1, var);
	}
	return (0);
}
