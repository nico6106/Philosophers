/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:00:04 by nlesage           #+#    #+#             */
/*   Updated: 2023/01/10 18:42:34 by nlesage          ###   ########.fr       */
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
}	t_sema;

typedef struct s_var
{
	t_sema	sem;
	pid_t	*pid;
	t_info	info;
	long	num_philo;
	long	time_start_s;
	long	time_start_ms;
	long	last_eat_s;
	long	last_eat_ms;
	int		nb_eat;
	int		death;
}	t_var;

//main.c
int		main(int argc, char **argv);
void	ft_start_philo(t_info info);

int	ft_end_pgrm(t_var *var);
int	ft_end_philo(t_var *var);
int	ft_handle_end(t_var *var, int val);

//load_arg.c
t_info	ft_load_arg(int argc, char **argv);
t_info	ft_import_arg(int argc, char **argv);
long	ft_atoi(const char *nptr);
int		ft_str_is_number(char *str);
int		ft_check_arg(int argc, char **argv);

//utils.c
int		ft_return_arg(char *argv);
long	ft_time_elapsed(t_var *var, long sec, long us);

//handle_error.c
int		ft_error_quit(char *str, int retour);
int	ft_call_error(t_var *var);
int	ft_exit(t_var *var);

//init_bonus.c
int		ft_init_sem(t_var *var, t_info info);
int		ft_init(t_var *var, t_info info);
int	ft_reopen_sem(t_var *var);

int	ft_close_sem_error(t_var *var);

//philo_bonus.c
int		ft_philo(t_var *var);
void	ft_wait_all_started(t_var *var);
int	ft_usleep(long time_sleep, t_var *var);
int	ft_check_death(t_var *var);

//action_bonus.c
int	ft_think(long tid, t_var *var);
int	ft_take_fork(long tid, t_var *var);
int	ft_show_take_fork(long tid, t_var *var);
int	ft_unlock_fork(t_var *var);

void	ft_eat(long tid, t_var *var);
int	ft_sleep(long tid, t_var *var);

#endif