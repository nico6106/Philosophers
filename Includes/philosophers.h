/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:00:04 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/05 12:45:32 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_info
{
	int	nb_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nb_eat;
}	t_info;

typedef struct s_var
{
	long			tid;
	t_info			info;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_start;
	pthread_mutex_t	mutex_tab_eat;
	pthread_mutex_t	mutex_tab_nb_eat;
	int				dead;
	long			*last_eat_s;
	long			*last_eat_ms;
	int				*tab_nb_eat;
}	t_var;

//main.c
int		main(int argc, char **argv);
void	ft_start_threads(t_info info);

//philo.c
void	*ft_philo(void *threadid);
int		ft_usleep(long time_sleep, t_var *var, long tid);
int		ft_is_finished(t_var *var);
int		ft_is_dead(t_var *var, long tid);
void	ft_wait_all_started(t_var *var);

int	ft_call_dead(t_var *var);
int	ft_finished(t_var *var);

//actions.c
int		ft_think(long tid, t_var *var);
int		ft_sleep(long tid, t_var *var);
int		ft_eat(long tid, t_var *var);
int		ft_show_take_fork(long tid, t_var *var);
int		ft_take_fork(long tid, t_var *var, int left, int right);

//load_arg.c
t_info	ft_load_arg(int argc, char **argv);
t_info	ft_import_arg(int argc, char **argv);
int		ft_atoi(const char *nptr);
int		ft_str_is_number(char *str);
int		ft_check_arg(int argc, char **argv);

//handle_error.c
int		ft_error_quit(char *str, int retour);
void	ft_handle_one_phil(long tid, t_var *var);

#endif