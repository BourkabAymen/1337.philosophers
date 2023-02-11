
#include "philo.h"

void	philo_eats(t_philos *philos)
{
	t_philosopher	*philosopher;

	philosopher = philos->philosopher;
	pthread_mutex_lock(&(philosopher->forks[philos->left_fork]));
	print_action(philosopher, " has taken a fork", philos->id);
	pthread_mutex_lock(&(philosopher->forks[philos->right_fork]));
	print_action(philosopher, " has taken a fork", philos->id);
	pthread_mutex_lock(&(philosopher->cheque_repas));
	print_action(philosopher, " is eating", philos->id);
	philos->t_dernier_repas = time_clock();
	pthread_mutex_unlock(&(philosopher->cheque_repas));
	sleep_philo(philosopher->time_sleep, philosopher);
	(philos->x_eat)++;
	pthread_mutex_unlock(&(philosopher->forks[philos->left_fork]));
	pthread_mutex_unlock(&(philosopher->forks[philos->right_fork]));
}

void	*action(void *void_philo)
{
	int				i;
	t_philos		*philos;
	t_philosopher	*philosopher;

	i = 0;
	philos = (t_philos *)void_philo;
	philosopher = philos->philosopher;
	if (philos->id % 2)
		usleep(15000);
	while (!(philosopher->mort) && philosopher->sign_eat == 0)
	{
		philo_eats(philos);
		print_action(philosopher, " is sleeping", philos->id);
		sleep_philo(philosopher->time_sleep, philosopher);
		print_action(philosopher, " is thinking", philos->id);
		i++;
	}
	return (NULL);
}

void	death_check(t_philosopher *r, t_philos *p)
{
	int	i;

	while (!(r->sign_eat))
	{
		i = 0;
		while (i < r->nbr_philo && !(r->mort))
		{
			pthread_mutex_lock(&(r->cheque_repas));
			if (periode_x(p[i].t_dernier_repas, time_clock()) >= r->time_death)
			{
				print_action(r, " mort", i);
				r->mort = 1;
			}
			pthread_mutex_unlock(&(r->cheque_repas));
			usleep(100);
			i++;
		}
		if (r->mort)
			break ;
		i = 0;
		while (r->nbr_eat != -1 && i < r->nbr_philo && p[i].x_eat >= r->nbr_eat)
			i++;
		if (i == r->nbr_philo)
			r->sign_eat = 1;
	}
}

void	exit_philo(t_philosopher *philosopher, t_philos *philo)
{
	int	i;

	i = -1;
	while (++i < philosopher->nbr_philo)
		pthread_detach(philo[i].id_thread);
	i = -1;
	while (++i < philosopher->nbr_philo)
		pthread_mutex_destroy(&(philosopher->forks[i]));
	pthread_mutex_destroy(&(philosopher->write));
	pthread_mutex_destroy(&(philosopher->cheque_repas));
}

int	commence(t_philosopher *philosopher)
{
	int			i;
	t_philos	*philos;

	i = 0;
	philos = philosopher->philosophers;
	philosopher->first_time_cklok = time_clock();
	while (i < philosopher->nbr_philo)
	{
		if (pthread_create(&(philos[i].id_thread), NULL, action, &philos[i]))
		{
			printf("erreur lors de la création des threads\n");
			return (1);
		}
		philos[i].t_dernier_repas = time_clock();
		i++;
	}
	death_check(philosopher, philosopher->philosophers);
	exit_philo(philosopher, philos);
	return (0);
}
