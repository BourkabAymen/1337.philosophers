/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourkab <abourkab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:40:10 by abourkab          #+#    #+#             */
/*   Updated: 2023/02/20 21:05:54 by abourkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // Printf
# include <stdlib.h> // Malloc
# include <pthread.h> //pthread_*, mutex
# include <unistd.h> // usleep
# include <stdbool.h> //boolean
# include <limits.h> // long_max
# include <sys/time.h> // gettimeofday

# define ERR_PARAM "Wrong arguments. Check the subject and try again.\n"
# define ERR_THREAD	"Error: Could not create thread.\n"
# define ERR_MALLOC	"Error: Could not allocate memory.\n"
# define ERR_MUTEX	"Error: Could not create mutex.\n"
# define ERR_INV_INP "Invalid input in [%li].\n"
# define ERR_SIXTY "Invalid input. Must be greater than 60.\n"

# ifndef PRETTY
#  define PRETTY 1
# endif

typedef struct s_table	t_table;

typedef enum e_fork
{
	F_LEFT = 0,
	F_RIGHT = 1
}	t_fork;
typedef enum e_state
{
	S_EATING,
	S_SLEEPING,
	S_THINKING,
	S_DEAD,
	S_LEFT_FORK,
	S_RIGHT_FORK,
	S_END_dining
}	t_state;

/**
 * id :
 * table :
 * nbr_meals_done :
 * fork[2] :
 * general_meal_lock :
 * last_meal : This variable has as a value at first the start_dining value 
 * and ater that its value change for each philosopher and has as a value the 
 * time when 
 * philosopher will start eating
 */
typedef struct s_philo
{
	long			id;
	t_table			*table;
	long			nbr_meals_done;
	int				fork[2];
	pthread_mutex_t	general_meal_lock;
	pthread_t		thread_philo;
	time_t			last_meal;
}				t_philo;

/**
 * start_dining : The origin time
 * nbr_philo : The number of philos
 * time_to_die : The time after it the philosopher must die
 * time_to_eat : The time after it the philosopher must eat
 * time_to_sleep : The time after it the philosopher must sleep
 * time_must_eat : The number each philosopher must eat if it s specified
 * philo : is an array of nbr_philo of s_philo structre having the data 
 * for each one
 * dinner_end : is a boolean variable that is True if one philosopher dies
 * fork_lock : is an array of nbr_philo of mutexes that represents the forks 
 * used to eat
 * dinner_end_lock : is a mutex used to check if dinner_end = True in one thread 
 * because it's a variable shared between all the philosophers 
 * log_lock : is a mutex used to write " ... is eating ... " for example but 
 * for only one philosopher (thread) 
 * thread_table : is a thread that checks the first philosopher that will die
 * this variable is used in pthread_create and pthread_join 
 */
typedef struct s_table
{
	time_t			start_dining;
	long			nbr_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_must_eat;
	t_philo			**philo;
	bool			dinner_end;
	pthread_mutex_t	*fork_lock;
	pthread_mutex_t	dinner_end_lock;
	pthread_mutex_t	log_lock;
	pthread_t		thread_table;
}				t_table;

/**
 * @brief The threads will call this method. Will start all the routines.
 * Sleep / think / eat
 * @param data - Philosopher structure
 */
void	*dining_routines(void *data);

/**
 * @brief First method in project.
 * @param argc Arguments count
 * @param argv Arguments Vector
 * @return boolean
 */
bool	is_valid_args(int argc, char **argv);

/**
 * @brief Asc to Long function.
 * @param str String to be checked and transformed
 * @return long value
 */
long	ft_ato_long(const char *str);

/**
 * @brief Check if argument is a valid digit
 * @param c
 * @return boolean
 */
bool	ft_isdigit(int c);

/**
 * @brief Initialize the structure table
 * @param argc Arg Count
 * @param argv Arg Vectors
 * @return t_table* Return this structure or null if error.
 */
t_table	*init_table(int argc, char **argv);

/**
 * @brief Handle msg error. Create Malloc / Mutex and Thread errors
 * @param str String with error message
 * @param table Object to be cleaned
 */
void	*error_msg_null(char *str, t_table *table);

/**
 * @brief Will return the DateTime now, but in milliseconds
 * @return integer value
 */
int		datetime_now(void);

/**
 * @brief Will subtract the current DatetimeNow, from start dining to log
 * the time in program
 * @param start_dining
 * @return time_t
 */
int		get_time_ms(int start_dining);

/**
 * @brief Log the status of current philo. Will return the text in prompt
 *  with
 * the action of the philo
 * @param philo Philosopher structure
 * @param status Status to log
 */
void	log_status(t_philo *philo, t_state status);

/**
 * @brief Sleep is not allowed in this project. This will simulate it.
 * Handle the time to sleep the thread
 * @param table
 * @param duration Milliseconds to thread sleep
 */
void	thread_sleep(t_table *table, time_t duration);

/**
 * @brief Will free all memory allocation in program
 * @param table Table structure
 */
void	*free_table(t_table *table);

/**
 * @brief Check if the dinner has finished / Flag 'dinner end' updated to true
 * @param table table structure by ref
 * @return boolean value
 */
bool	has_dinner_finish(t_table *table);

/**
 * @brief Add Pretty header, when configured.
 */
void	header_pretty(void);

/**
 * @brief Verify if the program must be finished Thread to check this.
 * USleep to avoid Memory leak in the end of program
 * @param data
 * @return void*
 */
void	*finish_routines_reached(void *data);

/**
 * @brief Update property '-dinner end' in a Mutex context
 * @param table Table structure by ref
 * @param value Value to update
 */
void	set_dinner_end_value(t_table *table, bool value);

/**
 * @brief set_last_meal_value
 * @param philo
 */
void	set_last_meal_value(t_philo *philo, time_t value);

/**
 * @brief Responsible to increment number of time the philo eat
 * @param philo
 */
void	increment_number_of_eats(t_philo *philo);

/**
 * @brief Validation about the params passed by
 * @param table Table structure
 * @return boolean. Valid or invalid
 */
bool	is_param_valid(t_table *table);

/**
 * @brief Responsible for manage the time to think of each Philo.
 * This is necessary because we must increase or decrement the 
 * time to keep
 * thinking. This will be changed by the range of philo will die
 */
long	handle_thinking_time(t_philo *philo);

#endif
