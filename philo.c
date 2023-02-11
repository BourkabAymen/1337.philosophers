
#include "philo.h"

int	prend_arguiment(t_philosopher *philosopher, char **av)
{
	philosopher->nbr_philo = ft_atoi(av[1]);
	philosopher->time_death = ft_atoi(av[2]);
	philosopher->time_eat = ft_atoi(av[3]);
	philosopher->time_sleep = ft_atoi(av[4]);
	philosopher->sign_eat = 0;
	philosopher->mort = 0;
	if (philosopher->time_death < 0 || philosopher->time_eat < 0
		|| philosopher->time_sleep < 0 || philosopher->nbr_philo <= 0)
	{
		printf("at least one wrong argument\n");
		return (1);
	}
	if (av[5])
	{
		philosopher->nbr_eat = ft_atoi(av[5]);
		if (philosopher->nbr_eat <= 0)
		{
			printf("at least one wrong argument\n");
			return (1);
		}
	}
	else
		philosopher->nbr_eat = -1;
	return (0);
}

int	initielis_philos(t_philosopher *philosopher)
{
	int	i;

	i = philosopher->nbr_philo;
	while (--i >= 0)
	{
		philosopher->philosophers[i].left_fork = i;
		philosopher->philosophers[i].right_fork = (i + 1)
			% philosopher->nbr_philo;
		philosopher->philosophers[i].x_eat = 0;
		philosopher->philosophers[i].t_dernier_repas = 0;
		philosopher->philosophers[i].id = i;
		philosopher->philosophers[i].philosopher = philosopher;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philosopher	philosopher;

	if (ac != 5 && ac != 6)
	{
		printf("Mauvaise nombre d'arguments\n");
		return (0);
	}
	if (prend_arguiment(&philosopher, av))
		return (0);
	if (initielis_mutex(&philosopher))
		return (0);
	initielis_philos(&philosopher);
	if (commence(&philosopher))
		return (0);
	return (0);
}
