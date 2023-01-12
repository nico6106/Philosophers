/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:59:50 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/12 18:02:18 by nlesage          ###   ########.fr       */
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
	int		rv;
	int		pid_end;
	t_var	var;

	if (ft_init(&var, info) == 1)
		return ;
	if (ft_launch_checker_threads(&var) == 1)
		return ;
	ft_fork_and_start(&var);
	pid_end = waitpid(-1, &rv, 0);
	if (sem_wait(var.sem.admin) != 0)
		ft_exit(&var);
	if (var.end_simulation == 0)
		ft_handle_end(&var, rv / 256, pid_end);
	if (sem_post(var.sem.admin) != 0)
		ft_exit(&var);
	if (sem_post(var.sem.run) != 0)
		ft_exit(&var);
	if (sem_post(var.sem.end) != 0)
		ft_exit(&var);
	usleep(10000);
	ft_end_pgrm(&var);
}
