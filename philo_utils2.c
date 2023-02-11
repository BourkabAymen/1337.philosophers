
#include "philo.h"

long long	time_clock(void)
{
	struct timeval	temp;

	gettimeofday(&temp, NULL);
	return (temp.tv_sec * 1000 + (temp.tv_usec / 1000));
}

long long	periode_x(long long time_start, long long time_end)
{
	return (time_end - time_start);
}

int	initielis_mutex(t_philosopher *philosopher)
{
	int	i;

	i = philosopher->nbr_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(philosopher->forks[i]), NULL))
		{
			printf("Erreur d'initielisation de mutex\n");
			return (1);
		}
	}
	if (pthread_mutex_init(&(philosopher->write), NULL))
	{
		printf("Erreur d'initielisation de mutex\n");
		return (1);
	}
	if (pthread_mutex_init(&(philosopher->cheque_repas), NULL))
	{
		printf("Erreur d'initielisation de mutex\n");
		return (1);
	}
	return (0);
}
