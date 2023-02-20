/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourkab <abourkab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:40:59 by abourkab          #+#    #+#             */
/*   Updated: 2023/02/20 21:06:16 by abourkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_valid_input(int argc, char **argv);
static bool	is_only_digit(char *arg);

/**
 * @brief is_valid_args 
 * It checks the numer of arguments
 * It checks the arguments if they are positive numbers by calling is_valid_input
 * @param argc Arguments Count
 * @param argv Arguments Vector
 * @return bool
 */
bool	is_valid_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf(ERR_PARAM);
		return (false);
	}
	if (is_valid_input(argc, argv) == false)
		return (false);
	return (true);
}

/**
 * @brief is_valid_input 
 * It checks if the arguments are only numbers
 * It checks if the arguments are between 0 and LONG_MAX
 * @param argc arg count
 * @param argv arg vector
 * @return boolean
 */
static bool	is_valid_input(int argc, char **argv)
{
	int		i;
	long	value;

	value = 0;
	i = 1;
	while (i < argc)
	{
		if (is_only_digit(argv[i]) == false)
		{
			printf("Invalid input in [%s]. Only digit accepted.\n", argv[i]);
			return (false);
		}
		value = ft_ato_long(argv[i]);
		if (value < 0 || value > LONG_MAX)
		{
			printf("Invalid input in [%ld]. Negative or so long.\n", value);
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @brief is_param_valid
 * This function checks if nbr_philo and time_to_die and time_to_eat 
 * and time_to_sleep
 * respect the requirements of the page correction
 * @param str - string argument
 * @return boolean
 */
bool	is_param_valid(t_table *table)
{
	if (table->nbr_philo > 200)
	{
		printf(ERR_INV_INP, table->nbr_philo);
		return (false);
	}
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
	{
		printf(ERR_SIXTY);
		return (false);
	}
	return (true);
}

/**
 * @brief Look char by char to verify if the input is correct
 * @param str - string argument
 * @return boolean
 */
static bool	is_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
