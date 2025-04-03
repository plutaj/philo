/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:06:19 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/03 16:46:53 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

/*  structs  */
typedef struct s_table
{
    unsigned int    	num_of_philo;
    unsigned int    	time_to_die;
    unsigned int    	time_to_eat;
    unsigned int    	time_to_sleep;
    unsigned int    	number_of_times_each_phil_must_eat;
	pthread_mutex_t		*forks;
	t_philo 			*philo;
}               t_table;

typedef struct s_philo
{
    unsigned int    id;
    pthread_t       thread;
	unsigned int	times_eaten;
	unsigned int	last_meal_time;
	t_philo			*next;
}               t_philo;

/*  philo.c functions  */
void    alloc_init_table(t_table *table, char **argv);
void    alloc_create_philos(t_table *table);
void	alloc_philos(t_table *table, t_philo *new_philo, t_philo *head, int n);
void    edge_cases(int argc, char **argv);

/*  error.c functions  */
void    error_msg();

/*  utils.c functions  */
int     ft_atoi(const char *str);

/*	itoa.c	*/
char			*ft_itoa(int n);
static int		int_len(long n);
static char		*before_alloc(int n);