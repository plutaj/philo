/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:06:19 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/02 18:54:04 by jpluta           ###   ########.fr       */
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
    unsigned int    num_of_philo;
    unsigned int    time_to_die;
    unsigned int    time_to_eat;
    unsigned int    time_to_sleep;
    unsigned int    number_of_times_each_phil_must_eat;
	t_philo 		*philo;
}               t_table;

typedef struct s_philo
{
    unsigned int    id;
    pthread_t       thread;
	t_philo			*next;
}               t_philo;

/*  utils.c functions  */
int     ft_atoi(const char *str);

/*  philo.c functions  */
void    alloc_fill_table(t_table *table, char **argv);
void    alloc_create_philos(t_table *table);
void    edge_cases(int argc, char **argv);

/*  error.c functions  */
void    error_msg();