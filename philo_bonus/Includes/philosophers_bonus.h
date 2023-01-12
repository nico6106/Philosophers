/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:00:04 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/12 18:00:36 by nlesage          ###   ########.fr       */
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

# include <sys/types.h>
# include <sys/wait.h>

# include <fcntl.h>
# include <sys/stat.h>

# define FOURCHETTES "/fourchettes"
# define TAKE "/take"
# define ECRIRE "/ecrire"
# define RUN "/run"
# define NB_EAT "/nbeat"
# define ADMIN "/admin"
# define START "/start"
# define HOLD "/hold"
# define END "/end"

typedef struct s_info
{
	int	nb_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nb_eat;
}	t_info;

typedef struct s_sema
{
	sem_t	*fourchettes;
	sem_t	*ecrire;
	sem_t	*take;
	sem_t	*run;
	sem_t	*s_nb_eat;
	sem_t	*admin;
	sem_t	*start;
	sem_t	*hold;
	sem_t	*end;
}	t_sema;

typedef struct s_var
{
	t_sema		sem;
	pid_t		*pid;
	t_info		info;
	long		num_philo;
	long		time_start_s;
	long		time_start_ms;
	long		last_eat_s;
	long		last_eat_ms;
	int			nb_eat;
	int			death;
	int			end_simulation;
	int			start;
	pthread_t	check_death;
}	t_var;

//main.c
int		main(int argc, char **argv);
void	ft_start_philo(t_info info);

//start_philo.c
int		ft_launch_checker_threads(t_var *var);
int		ft_launch_checker_threads_death(t_var *var);
void	ft_fork_and_start(t_var *var);
void	ft_fork_and_start_next(t_var *var);

//load_arg.c
t_info	ft_load_arg(int argc, char **argv);
t_info	ft_import_arg(int argc, char **argv);
long	ft_atoi(const char *nptr);
int		ft_str_is_number(char *str);
int		ft_check_arg(int argc, char **argv);

//utils.c
int		ft_return_arg(char *argv);
long	ft_time_elapsed(t_var *var, long sec, long us);
void	ft_wait_odd(t_var *var);
int		ft_compute_time(t_var *var);

//handle_error.c
int		ft_error_quit(char *str, int retour);
int		ft_call_error(t_var *var);
int		ft_exit(t_var *var);
int		ft_handle_one_phil(long tid, t_var *var);
int		ft_close_sem_error(t_var *var);

//init_bonus.c
int		ft_init(t_var *var, t_info info);
int		ft_init_sem(t_var *var, t_info info);
int		ft_init_sem_next(t_var *var, t_info info);
int		ft_reopen_sem(t_var *var);
int		ft_reopen_sem_next(t_var *var);

//philo_bonus.c
int		ft_philo(t_var *var);
void	ft_wait_all_started(t_var *var);
int		ft_usleep(long time_sleep, t_var *var);
int		ft_check_death(t_var *var);
int		ft_unlock_fork(t_var *var);

//philo_threads_bonus.c
void	*ft_thread_death(void *arg);
void	ft_is_dead(t_var *var, long pass);

//action_bonus.c
int		ft_think(long tid, t_var *var);
int		ft_take_fork(long tid, t_var *var);
int		ft_show_take_fork(long tid, t_var *var);
void	ft_eat(long tid, t_var *var);
int		ft_sleep(long tid, t_var *var);

//threads_check_bonus.c
void	*ft_check_nb_eat(void *arg);
void	ft_init_thread_check_eat(t_var *var);
void	ft_end_thread_check_eat(t_var *var);
void	*ft_thread_check_death(void *arg);

//handle_end_bonus.c
int		ft_handle_end(t_var *var, int val, int pid_end);
void	ft_liberate_sem(t_var *var);
int		ft_end_pgrm(t_var *var);
int		ft_end_philo(t_var *var);
#endif