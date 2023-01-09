/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:59:50 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/09 16:46:03 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers.h"

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
	pthread_t		*threads;
	long			i;
	t_var			var;

	var.info = info;
	threads = NULL;
	var.end_properly = 1;
	if (ft_init_and_start(&var, &threads) == 1)
		return ;
	var.threads = threads;
	while (ft_is_finished(&var) == 0)
	{
		usleep(2000);
		ft_call_dead(&var);
	}
	i = -1;
	while (++i < info.nb_philo)
	{
		pthread_join(threads[i], NULL);
		usleep(100);
	}
	ft_free_and_finish(&var);
	ft_free_tab(&var, threads, 0);
}

int	ft_init_and_start(t_var *var, pthread_t **threads)
{
	(*threads) = malloc(var->info.nb_philo * sizeof(pthread_t));
	if (!threads)
		return (1);
	if (ft_init_tab(var) == 1)
		return (ft_free_tab(NULL, (*threads), 1));
	if (ft_init_mutex(var, -1) == 1)
		return (ft_free_tab(var, (*threads), 1));
	if (ft_give_value_mutex(var) == 1)
	{
		ft_handle_destroy_mutex(var, var->info.nb_philo);
		return (ft_free_tab(var, (*threads), 1));
	}
	if (ft_start_threads(var, (*threads)) == 1)
	{
		ft_handle_destroy_mutex(var, var->info.nb_philo);
		return (ft_free_tab(var, (*threads), 1));
	}
	return (0);
}
