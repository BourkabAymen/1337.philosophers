/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourkab <abourkab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:39:25 by abourkab          #+#    #+#             */
/*   Updated: 2023/02/20 21:05:14 by abourkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end_dining(t_table *table);
static bool	start_dining(t_table *table);

/**
 * @brief Main Class of program 
 * It checks the arguments by calling the function is_valid_args
 * It allocates and initializes a table by calling the function init_table
 * @param argc Arguments Count
 * @param argv Arguments Vector
 * @return int
 */
int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (is_valid_args(argc, argv) == false)
		return (EXIT_FAILURE);
	table = init_table(argc, argv);
	if (!table)
		return (EXIT_FAILURE);
	if (start_dining(table) == false)
		return (EXIT_FAILURE);
	end_dining(table);
	return (EXIT_SUCCESS);
}

/**
 * @brief Responsible to finish the philo dining.
 * Will join all threads and free all objects
 * pthread_join is a synchronization method that blocks the calling thread 
 * (that is, the thread that calls the method) 
 * until the thread whose Join method is called has completed. 
 * Use this method to ensure that a thread has been terminated. 
 * @param table Table structure
 */
static void	end_dining(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(table->philo[i]->thread_philo, NULL);
		i++;
	}
	if (table->nbr_philo > 1)
		pthread_join(table->thread_table, NULL);
	free_table(table);
}

/**
 * @brief This function will start the dining of philosophers.
 * it creates all the threads needed thread_philo for each philosopher
 * and they Will start the threads (thread_philo)(Nbr threads is the 
 * same nbr philo)
 * it creates all the thread_table needed to check the death
 * and it Will start the thread (thread_table) to finish the dinner.
 * @param table structure
 */
static bool	start_dining(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_create(&table->philo[i]->thread_philo, NULL,
				&dining_routines, table->philo[i]) != 0)
			return (error_msg_null(ERR_THREAD, table));
		i++;
	}
	if (table->nbr_philo > 1)
	{
		if (pthread_create(&table->thread_table, NULL, &finish_routines_reached,
				table) != 0)
			return (error_msg_null(ERR_THREAD, table));
	}
	return (true);
}
