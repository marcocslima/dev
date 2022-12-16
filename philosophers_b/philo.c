/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 05:08:04 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/12/13 20:23:37 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_free(t_dbase *dbase, t_philo *philo, int flag)
{
	if (flag == 0)
	{
		free(dbase->forks);
		free(philo);
	}
	free(dbase);
	exit (1);
}

void	print_log(t_philo *philo, int state)
{
	long long	now;

	now = get_time_now();
	if ((state == LEFT_FORK || state == RIGHT_FORK) && philo->dbase->dead == 0)
		printf("%llu %d has taken a fork \n", now, philo->id + 1);
	else if (state == THINK && philo->dbase->dead == 0)
		printf("%llu %d is thinking \n", now, philo->id + 1);
	else if (state == EAT && philo->dbase->dead == 0)
		printf("%llu %d is eating \n", now, philo->id + 1);
	else if (state == SLEEP && philo->dbase->dead == 0)
		printf("%llu %d is sleeping \n", now, philo->id + 1);
	else if (state == DEAD)
		printf("%llu %d died \n", now, philo->id + 1);
}


int	init(t_dbase *dbase, t_philo **philo, int argc, char *argv[])
{
	if (argc > 6 || argc <= 4)
	{
		ft_putstr_fd("ERROR :wrong number of arguments, it needs 5 or 6\n", STDERR);
		exit_free(dbase, *philo, 1);
	}
	dbase->n_philos = ft_atoi(argv[1]);
	dbase->t_die = ft_atoi(argv[2]);
	dbase->t_eat = ft_atoi(argv[3]);
	dbase->t_sleep = ft_atoi(argv[4]);
	dbase->index = -1;
	dbase->n_eats = -1;
	dbase->some_die = 0;
	dbase->dead = 0;
	if (argc == 6)
		dbase->n_eats = ft_atoi(argv[5]);
	dbase->all_eat = 0;
	dbase->forks = malloc(sizeof(pthread_mutex_t) * dbase->n_philos);
	*philo = (t_philo *)malloc(sizeof(t_philo) * dbase->n_philos);
	if ((argc == 6 && dbase->n_eats <= 0) || (dbase->n_philos < 0
			|| dbase->t_die < 0 || dbase->t_eat < 0 || dbase->t_sleep < 0))
	{
		ft_putstr_fd("ERROR :arguments must be > 0\n", STDERR);
		exit_free(dbase, *philo, 0);
	}
	if (dbase->n_philos == 0)
		exit_free(dbase, *philo, 0);
	init_philos(dbase, *philo);
	return (0);
}

void	init_philos(t_dbase *dbase, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < dbase->n_philos)
	{
		pthread_mutex_init(&dbase->forks[i], NULL);
		philo[i].id = i;
		philo[i].eat_count = 0;
		philo[i].dbase = dbase;
		philo[i].state = START;
		philo[i].flag = 0;
		philo[i].f_right = 0;
		philo[i].f_left = 0;
	}
	pthread_mutex_init(&dbase->lock, NULL);
}

void    drop_fork(t_philo *philo, int flag)
{
    pthread_mutex_unlock(&philo->dbase->forks[philo->id]);
	//printf("%d soltou garfo direito....\n", philo->id + 1);
    if(philo->id > 0)
	{
        pthread_mutex_unlock(&philo->dbase->forks[philo->id - 1]);
		//printf("%d soltou garfo esquerdo....\n", philo->id + 1);
	}
	else
	{
        pthread_mutex_unlock(&philo->dbase->forks[philo->dbase->n_philos - 1]);
		//printf("%d soltou garfo esquerdo....\n", philo->id + 1);
	}
	if (flag == 0)
	{
		print_log(philo, SLEEP);
		usleep(philo->dbase->t_sleep * 1000);
		print_log(philo, THINK);
	}
	philo->f_right = 0;
	philo->f_left = 0;
}

void	clean_to_exit(t_philo *philo)
{
	//philo->dbase->dead = 1000;
	philo->dbase->index = -1;
	while (++philo->dbase->index < philo->dbase->n_philos)
		pthread_mutex_destroy(&philo->dbase->forks[philo->dbase->index]);
	free(philo->dbase->forks);
	free(philo->dbase);
	exit (0);
}

void	verify_state(t_philo *philo)
{
	long long verify_death;
			
	verify_death = get_time_now() - philo->last_eat;
	if (verify_death > philo->dbase->t_die && philo->dbase->some_die == 0)
	{
		drop_fork(philo, 1);
		philo->dbase->some_die = 1;
		print_log(philo, DEAD);
		clean_to_exit(philo);
		exit (0);
	}
	else
	{
		print_log(philo, EAT);
		usleep(philo->dbase->t_eat * 1000);
		philo->last_eat = get_time_now();
		philo->eat_count++;
		if (philo->eat_count == philo->dbase->n_eats)
		{
			philo->dbase->all_eat++;
			if(philo->dbase->all_eat >= philo->dbase->n_philos)
				philo->dbase->index = -1;
			clean_to_exit(philo);
			exit (0);
		}
		drop_fork(philo, 0);
	}
}

void    get_forks(t_philo *philo)
{
	if (philo->dbase->n_philos == 1)
		clean_to_exit(philo);
	if(pthread_mutex_lock(&philo->dbase->forks[philo->id]) == 0)
	{
		print_log(philo, RIGHT_FORK);
		philo->f_right = RIGHT_FORK;
		//printf("%d Pegou o direito !!!!\n", philo->id + 1);
		if (philo->id > 0)
		{
			if(pthread_mutex_lock(&philo->dbase->forks[philo->id - 1]) == 0)
			{
				print_log(philo, LEFT_FORK);
				philo->f_left = LEFT_FORK;
				//printf("%d Pegou o esquerdo !!!!\n", philo->id + 1);
			}
			//else
			//{
			//	pthread_mutex_unlock(&philo->dbase->forks[philo->id]);
			//	printf("%d Soltou o direito !!!!\n", philo->id + 1);
			//}
		}
		else
		{
			if(pthread_mutex_lock(&philo->dbase->forks[philo->dbase->n_philos - 1]) == 0)
			{
				print_log(philo, LEFT_FORK);
				philo->f_left = LEFT_FORK;
				//printf("%d Pegou o esquerdo !!!!\n", philo->id + 1);
			}
			//else
			//{
			//	pthread_mutex_unlock(&philo->dbase->forks[philo->id]);
			//	printf("%d Soltou o direito !!!!\n", philo->id + 1);
			//}
		}
	}
	if (philo->f_right + philo->f_left == 11)
		verify_state(philo);
	else
	{
		philo->f_left = 0;
		philo->f_right = 0;
		printf("%d AQUI !!!!\n", philo->id);
		//drop_fork(philo, 1);
	}	
}

void	*simulation(void *var)
{
	t_philo	*philo;

	philo = var;
	while(1)
		get_forks(philo);
	return (NULL);
}

int	main(int argc, char *argv[])
{
    t_dbase 	*dbase;
    t_philo 	*philo;
	int i = -1;
	int j = -1;
    
    dbase = (t_dbase *)malloc(sizeof(t_dbase));
    if (init(dbase, &philo, argc, argv))
		return (ERROR);
	dbase->t_init = get_time_now();
	philo->dbase->dead = 0;
	//dbase->index = -1;
	//while (++dbase->index < dbase->n_philos)
	while (++i < dbase->n_philos)
	{
		usleep(50);
		pthread_create(&philo[i].td, NULL, &simulation, &philo[i]);
	}
	//philo->dbase->index = -1;
	//while (++philo->dbase->index < philo->dbase->n_philos)
	while (++j < philo->dbase->n_philos)
		pthread_join(philo[j].td, NULL);
	return (0);
}
