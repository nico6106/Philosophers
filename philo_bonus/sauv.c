

/*main*/

/*
			var.sem.fourchettes = sem_open(FOURCHETTES, O_RDWR);
			/*
			sem_wait(var.sem.fourchettes);
			sem_wait(var.sem.fourchettes);
			printf("hello, i'm the child %d\n", i);
			sleep(2);
			sem_post(var.sem.fourchettes);
			sem_post(var.sem.fourchettes);
			*/

/*
void	ft_start_philo2(t_info info)
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
*/