
#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philos
{
	int						id;
	int						x_eat;
	int						right_fork;
	int						left_fork;
	long long				t_dernier_repas;
	pthread_t				id_thread;
	struct s_philosopher	*philosopher;
}	t_philos;

typedef struct s_philosopher
{
	int				nbr_philo;
	int				time_eat;
	int				time_death;
	int				mort;
	int				nbr_eat;
	int				time_sleep;
	int				sign_eat;
	int				first_time_cklok;
	pthread_mutex_t	cheque_repas;
	pthread_mutex_t	write;
	pthread_mutex_t	forks[250];
	t_philos		philosophers[250];
}	t_philosopher;
// philo.c
int				prend_arguiment(t_philosopher *philosopher, char **av);
int				nitielis_philos(t_philosopher *philosopher);
// philo_utils.c
int				ft_long(int i);
int				ft_atoi(const char *str);
void			print_action(t_philosopher *t_philosopher, char *str, int id);
void			sleep_philo(long long time, t_philosopher *t_philosopher);
// philo_utils2.c
long long		time_clock(void);
long long		periode_x(long long time_start, long long time_end);
int				initielis_mutex(t_philosopher *philosopher);
// philo_utils3.c
void			philo_eats(t_philos *philos);
void			*action(void *void_philo);
void			death_check(t_philosopher *r, t_philos *p);
void			exit_philo(t_philosopher *philosopher, t_philos *philo);
int				commence(t_philosopher *philosopher);

#endif
