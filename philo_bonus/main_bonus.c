/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:59:50 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/11 19:29:36 by nlesage          ###   ########.fr       */
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
	int	pid_end;
	pthread_t	thread_check_nb_eat;
	t_var	var;

	var.start = 0;
	var.death = 0;
	if (ft_init(&var, info) == 1)
		return ;
		
	
	if (sem_wait(var.sem.run) != 0)
			ft_exit(&var);
	if (sem_wait(var.sem.admin) != 0)
			ft_exit(&var);
	if (pthread_create(&thread_check_nb_eat, NULL, ft_check_nb_eat, &var))
	{
		ft_end_pgrm(&var);
		return ;
	}
	pthread_detach(thread_check_nb_eat);

	
	if (sem_wait(var.sem.run) != 0)
		ft_exit(&var);
	if (sem_post(var.sem.run) != 0)
		ft_exit(&var);

	if (sem_wait(var.sem.start) != 0)
		ft_exit(&var);

	var.pid[0] = fork();
	//usleep(1000);
	i = -1;
	var.end_simulation = 0;

	while (++i < info.nb_philo)
	{
		//printf("%d started %d\n", i, var.pid[i]);
		if (var.pid[i] == 0)
		{
			var.death = 0;
			var.nb_eat = 0;
			var.num_philo = i;
			if (ft_reopen_sem(&var) == 1)
				ft_call_error(&var);
			
			ft_philo(&var);
			rv = var.death;
			ft_end_philo(&var);
			//if (i == 0)
			//	i = -1;
			//if (rv == 1)
			//	exit(i);
			//printf("%d exit\n", i);
			exit (rv);
		}
		else if ((i + 1) < info.nb_philo)
		{
			var.pid[i + 1] = fork();
			//usleep(1000);
		}
	}
	
	if (sem_post(var.sem.admin) != 0)
		ft_exit(&var);
	//printf("all started\n");
	i = -1;
	while (++i < info.nb_philo + 1)
	{
		if (sem_post(var.sem.start) != 0)
			ft_exit(&var);
	}
	
	//printf("all started\n");         /!\ beware this
	pid_end = waitpid(-1, &rv, 0);
	//printf("finished= %d, pid_end=%d\n", rv/256, pid_end);
	if (sem_wait(var.sem.admin) != 0)
		ft_exit(&var);
	if (var.end_simulation == 0)
		ft_handle_end(&var, rv / 256, pid_end);
	if (sem_post(var.sem.admin) != 0)
		ft_exit(&var);
	usleep(1000);
	ft_end_pgrm(&var);
}

int	ft_end_philo(t_var *var)
{

	sem_close(var->sem.fourchettes);
	sem_close(var->sem.ecrire);
	sem_close(var->sem.take);
	sem_close(var->sem.run);
	sem_close(var->sem.admin);
	sem_close(var->sem.start);

	sem_close(var->sem.bis_fourchettes);
	sem_close(var->sem.bis_ecrire);
	sem_close(var->sem.bis_take);
	sem_close(var->sem.bis_s_nb_eat);
	sem_close(var->sem.bis_start);
	sem_close(var->sem.hold);

	free(var->pid);
	return (0);
}

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
	i = -1;
	while (++i < var->info.nb_philo)
		sem_post(var->sem.s_nb_eat);
	i = -1;
	while (++i < var->info.nb_philo)
		waitpid(var->pid[i], &rv, 0);
	return (0);
}

int	ft_end_pgrm(t_var *var)
{
	sem_close(var->sem.ecrire);
	sem_close(var->sem.run);
	sem_close(var->sem.s_nb_eat);
	sem_close(var->sem.take);
	sem_close(var->sem.admin);
	sem_close(var->sem.start);
	sem_unlink(FOURCHETTES);
	sem_unlink(TAKE);
	sem_unlink(ECRIRE);
	sem_unlink(RUN);
	sem_unlink(NB_EAT);
	sem_unlink(ADMIN);
	sem_unlink(START);
	sem_unlink(HOLD);
	free(var->pid);
	return (0);
}
