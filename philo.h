/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:06:19 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/04 20:35:16 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

/*  structs  */

typedef struct s_philo t_philo;
typedef struct s_table t_table;

typedef struct s_philo
{
    unsigned int    id;
    pthread_t       thread;
	unsigned int	times_eaten;
	unsigned int	last_meal_time;
	t_philo			*next;
}               t_philo;

typedef struct s_table
{
    unsigned int    	num_of_philo;
    unsigned int    	time_to_die;
    unsigned int    	time_to_eat;
    unsigned int    	time_to_sleep;
    unsigned int    	number_of_times_each_phil_must_eat;
	pthread_t			*monitoring;
	pthread_mutex_t		*forks;
	t_philo 			*philo;
}               t_table;

/*  philo.c functions  */
void    alloc_init_table(t_table *table, char **argv);
void    create_philos(t_table *table);
void	alloc_philos(t_table *table, t_philo *new_philo, t_philo *head, int n);
void    edge_cases(int argc, char **argv);
void	init_monitoring(t_table *table);
void	*monitoring_f(void *arg);
int		have_all_eaten(t_table *table);

/*  error.c functions  */
void    error_msg();
void	ft_error2();

/*  utils.c functions  */
int     ft_atoi(const char *str);
int		is_num(char *num);
int		is_digit(char c);

/*	itoa.c	*/
char	*ft_itoa(int n);
int		int_len(long n);
char	*before_alloc(int n);