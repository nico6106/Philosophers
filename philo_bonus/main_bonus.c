/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:59:50 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/10 19:26:14 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_info		info;

	info = ft_load_arg(argc, argv);
	if (info.nb_philo == -1)
		return (ft_error_quit(NULL, 1));
	if (info.nb_philo < 1)
		return (ft_error_quit("Error: wrong number of philosophers\n", 1));
	ft_start_philo(info);
	return (0);
}

void	ft_start_philo(t_info info)
{
	int rv;
	int	i;
	t_var	var;
	//t_sema	sem;

	if (ft_init(&var, info) == 1)
		return ;
	var.pid[0] = fork();
	i = -1;
	//sem_wait(var.sem.run);
	while (++i < info.nb_philo)
	{
		//printf("%d started %d\n", i, var.pid[i]);
		if (var.pid[i] == 0)
		{
			sem_close(var.sem.fourchettes);
			sem_close(var.sem.ecrire);
			sem_close(var.sem.take);
			sem_close(var.sem.run);
			var.death = 0;
			var.nb_eat = 0;
			var.num_philo = i;
			if (ft_reopen_sem(&var) == 1)
				ft_call_error(&var);
			//var.sem = sem;
			ft_philo(&var);
			ft_end_philo(&var);
			if (var.num_philo == 0)
				var.num_philo = -1;
			if (var.death == 1)
				exit(var.num_philo);
			//printf("%d exit\n", i);
			exit (0);
		}
		else if ((i + 1) < info.nb_philo)
			var.pid[i + 1] = fork();
	}
	//sem_post(var.sem.run);
	//printf("all started\n");         /!\ beware this
	waitpid(-1, &rv, 0);
	//printf("i'm the parent, child returned %d\n", rv/256);
	usleep(100000);
	ft_handle_end(&var, rv / 256);
	//printf("i'm the parent, child returned %d\n", rv/256);
	ft_end_pgrm(&var);
	printf("fin pgrm\n");
}

int	ft_end_philo(t_var *var)
{
	free(var->pid);
	sem_close(var->sem.fourchettes);
	sem_close(var->sem.ecrire);
	sem_close(var->sem.take);
	sem_close(var->sem.run);
	return (0);
}

int	ft_handle_end(t_var *var, int val)
{
	int	i;
	int	rv;
	int	retour;

	if (val != 0)
	{
		if (val == 255)
			val = 0;
		i = -1;
		while (++i < var->info.nb_philo)
		{
			if (val != i)
			{
				retour = kill(var->pid[i], SIGUSR1);
				if (retour == -1)
					ft_error_quit("Error the PID doesn't exist", 0);
			}
		}
	}
	i = 0;
	//printf("avant recup\n");
	while (i < var->info.nb_philo)
	{
		//printf("recup %d\n", i);
		waitpid(var->pid[i], &rv, 0);
		//printf("recupere %d=%d\n", i, rv);
		i++;
	}
	return (0);
}

int	ft_end_pgrm(t_var *var)
{
	sem_close(var->sem.ecrire);
	sem_close(var->sem.run);
	sem_unlink(FOURCHETTES);
	sem_unlink(TAKE);
	sem_unlink(ECRIRE);
	sem_unlink(RUN);
	free(var->pid);
	return (0);
}
