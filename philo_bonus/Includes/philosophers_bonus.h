/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:00:04 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/09 17:53:40 by nlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <semaphore.h>
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

typedef struct s_philo
{
	long	tid;
	int		left;
	int		right;
}	t_philo;

typedef struct s_var
{
	long			tid;
	t_info			info;
	pthread_t		*threads;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_start;
	pthread_mutex_t	mutex_tab_eat;
	pthread_mutex_t	mutex_tab_nb_eat;
	int				dead;
	long			*last_eat_s;
	long			*last_eat_ms;
	long			time_start_s;
	long			time_start_ms;
	int				*tab_nb_eat;
	int				end_properly;
}	t_var;

//main.c
int		main(int argc, char **argv);
void	ft_start_philo(t_info info);
int		ft_init_and_start(t_var *var, pthread_t **threads);

//start_threads.c
int		ft_init_tab(t_var *var);
int		ft_init_mutex(t_var *var, int i);
int		ft_give_value_mutex(t_var *var);
int		ft_start_threads(t_var *var, pthread_t *threads);
int		ft_init_time(t_var *var);

//philo.c
void	*ft_philo(void *threadid);
int		ft_usleep(long time_sleep, t_var *var, long tid);
void	ft_wait_all_started(t_var *var);
t_philo	ft_init_philo(t_var *var);

//actions.c
int		ft_think(long tid, t_var *var);
int		ft_sleep(long tid, t_var *var);
void	ft_eat(long tid, t_var *var);
int		ft_show_take_fork(long tid, t_var *var);
int		ft_take_fork(long tid, t_var *var, int left, int right);

//actions2.c
void	ft_unlock_fork(t_var *var, t_philo philo);
void	ft_wait_odd(t_var *var, long tid);

//load_arg.c
t_info	ft_load_arg(int argc, char **argv);
t_info	ft_import_arg(int argc, char **argv);
long	ft_atoi(const char *nptr);
int		ft_str_is_number(char *str);
int		ft_check_arg(int argc, char **argv);

//handle_end.c
int		ft_is_finished(t_var *var);
int		ft_call_dead(t_var *var);
int		ft_finished(t_var *var);
int		ft_sub_call_dead(t_var *var, int i, long sec, long usec);

//handle_error.c
int		ft_error_quit(char *str, int retour);
void	ft_handle_one_phil(long tid, t_var *var);
void	ft_kill_threads(pthread_t *threads, int n);
void	ft_exit(t_var *var);
int		ft_handle_thread_creation_error(t_var *var, pthread_t *threads, int i);

//utils.c
int		ft_compute_time(t_var *var);
long	ft_time_elapsed(t_var *var, long sec, long us);
int		ft_return_arg(char *argv);

//free_and_finish.c
void	ft_free_and_finish(t_var *var);
void	ft_pthread_mutex_destroy(pthread_mutex_t *mutex);
int		ft_handle_destroy_mutex(t_var *var, int n);
int		ft_free_tab(t_var *var, pthread_t *threads, int retour);

#endif