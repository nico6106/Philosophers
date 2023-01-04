/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:19:42 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/04 18:42:36 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philosophers.h"

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

void	ft_handle_one_phil(long tid, t_var *var)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	pthread_mutex_lock(&var->mutex[tid]);
	printf("%ld%03ld %ld has taken a fork\n", t.tv_sec,
		t.tv_usec / 1000, tid + 1);
	usleep(var->info.time_die * 1000);
	pthread_mutex_unlock(&var->mutex[tid]);
	pthread_mutex_lock(&var->mutex_dead);
	var->dead = 1;
	pthread_mutex_unlock(&var->mutex_dead);
	gettimeofday(&t, NULL);
	printf("%ld%03ld %ld died\n", t.tv_sec, t.tv_usec / 1000, tid + 1);
}
