
#include "philo.h"

int	ft_long(int i)
{
	if (i == -1)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				signe;
	unsigned long	n;

	n = 0;
	signe = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = signe * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - 48);
		if (n > 2147483647 && signe == 1)
			return (ft_long(signe));
		if (n > 2147483648 && signe == -1)
			return (ft_long(signe));
		i++;
	}
	return (n * signe);
}

void	sleep_philo(long long time, t_philosopher *t_philosopher)
{
	long long	start;

	start = time_clock();
	while (!(t_philosopher->mort))
	{
		if (periode_x(start, time_clock()) >= time)
			break ;
		usleep(60);
	}
}

void	print_action(t_philosopher *t_philosopher, char *str, int id)
{
	pthread_mutex_lock(&(t_philosopher->write));
	if (!(t_philosopher->mort))
	{
		printf("%lli ", time_clock() - t_philosopher->first_time_cklok);
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(t_philosopher->write));
	return ;
}
