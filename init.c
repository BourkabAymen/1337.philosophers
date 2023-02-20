/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourkab <abourkab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:39:10 by abourkab          #+#    #+#             */
/*   Updated: 2023/02/20 21:04:57 by abourkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void				sort_fork_by_philo(t_philo *philo);
static bool				init_philo(t_table *table);
static bool				init_mutex(t_table *table);
static pthread_mutex_t	*init_forks(t_table *table);

/**
 * @brief init_table 
 * It allocates a table by calling the malloc function
 * It initializes 7 variables having as type bool and long and time_t
 * It initializes the philo structre in the table by calling init_philo
 * 
 * @param argc Arguments Count
 * @param argv Arguments Vector
 * @return pointer to t_table
 */

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (error_msg_null(ERR_MALLOC, NULL));
	table->nbr_philo = ft_ato_long(argv[1]);
	table->time_to_die = ft_ato_long(argv[2]);
	table->time_to_eat = ft_ato_long(argv[3]);
	table->time_to_sleep = ft_ato_long(argv[4]);
	table->time_must_eat = -1;
	if (argc == 6)
		table->time_must_eat = ft_ato_long(argv[5]);
	table->dinner_end = false;
	table->start_dining = datetime_now();
	if (init_philo(table) == false || table->philo == NULL)
		return (NULL);
	if (init_mutex(table) == false || is_param_valid(table) == false)
		return (NULL);
	return (table);
}

/**
 * @brief Initializes Philo structure existing in the table.
 * 1 : It allocates a sufficient memory for all the philosophers (philos)
 * after that and for each philosopher we should allocate and precise the needed 
 * memory for each one in the memory that is already allocated.
 * 2 : It initializes the data existing in the struct philo like:
 * table
 * id
 * nbr_meals_done
 * fork array by calling sort_fork_by_philo
 * 3 : It initializes the general_meal_lock mutex
 * * * thread_philo and last_meal are not initialized in this function
 * @param table
 */
static bool	init_philo(t_table *table)
{
	t_philo	**philos;
	long	i;

	i = 0;
	philos = malloc(sizeof(t_philo) * table->nbr_philo);
	if (philos == NULL)
		return (error_msg_null(ERR_MALLOC, NULL));
	while (i < table->nbr_philo)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (philos[i] == NULL)
			return (error_msg_null(ERR_MALLOC, NULL));
		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->nbr_meals_done = 0;
		sort_fork_by_philo(philos[i]);
		if (pthread_mutex_init(&philos[i]->general_meal_lock, 0) != 0)
			return (error_msg_null(ERR_MUTEX, NULL));
		i++;
	}
	table->philo = philos;
	return (true);
}

/**
 * @brief Initialize Forks. Each fork will be a mutex.
 * But after allocating dynamically the memory needed for the forks (mutexes)
 * because the number of forks may change (because it s simply the number of 
 * philosophers)
 * @param table
 * @return pthread_mutex_t*
 */
static pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	long			i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philo);
	if (!forks)
		return (error_msg_null(ERR_MALLOC, NULL));
	while (i < table->nbr_philo)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (error_msg_null(ERR_MUTEX, NULL));
		i++;
	}
	return (forks);
}

/**
 * @brief Initialize part of Mutex used in project
 * It Initializes Forks (mutexes) by calling init_forks
 * It Initializes the other 2 mutexes in the table structre
 * @param tablet tbl structure
 * @return Boolean - success or failure
 */
static bool	init_mutex(t_table *table)
{
	table->fork_lock = init_forks(table);
	if (!table->fork_lock)
		return (false);
	if (pthread_mutex_init(&table->dinner_end_lock, 0) != 0)
		return (error_msg_null(ERR_MUTEX, NULL));
	if (pthread_mutex_init(&table->log_lock, 0) != 0)
		return (error_msg_null(ERR_MUTEX, NULL));
	return (true);
}

/**
 * @brief Will define what fork the philo can take.
 * Was made this way to avoid dead lock.
 * it initializes for the specified philosopher the values of the fork array
 * These values are between 0 and nbr_philo - 1
 * In case of 3 philosophers :
 ** fork[0] : is the left or the right of the philosopher
 ** fork[1] : is the right or the left of the philosopher
 *** philo[0]philo->fork[0]:0 and ->fork[1]:1
 *** philo[1]philo->fork[0]:2 and ->fork[1]:1
 *** philo[2]philo->fork[0]:2 and ->fork[1]:0
 * @param philo
 */
static void	sort_fork_by_philo(t_philo *philo)
{
	philo->fork[0] = philo->id;
	if (philo->table->nbr_philo > 1)
	{
		philo->fork[1] = (philo->id + 1) % philo->table->nbr_philo;
		if (philo->id % 2 != 0)
		{
			philo->fork[0] = (philo->id + 1) % philo->table->nbr_philo;
			philo->fork[1] = philo->id;
		}
	}
}
