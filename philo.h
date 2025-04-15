/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:06:19 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/15 19:38:28 by jpluta           ###   ########.fr       */
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
	t_table			*table;
    int    			id;
    pthread_t       thread;
	int				times_eaten;
	pthread_mutex_t last_meal_time_mutex;
	pthread_mutex_t times_eaten_mutex;
	unsigned int	last_meal_time;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	t_philo			*next;
}						t_philo;

typedef struct s_table
{
    int    	num_of_philo;
    unsigned int    	time_to_die;
    unsigned int    	time_to_eat;
    unsigned int    	time_to_sleep;
    int					number_of_times_each_phil_must_eat;
	pthread_t			monitoring;
	int					stop;
	pthread_mutex_t		stop_mutex;		
	pthread_mutex_t		*forks;
	t_philo 			*philo;
}               			t_table;

/*  philo.c functions  */

void    alloc_init_table(t_table *table, char **argv);
void	alloc_philos(t_table *table);
void    edge_cases(int argc, char **argv, t_table *table);
void	init_monitoring(t_table *table);
void	*monitoring_f(void *arg);
void	join_forks(t_table *table);
void	*dining_philosophers(void *arg);
int		have_all_eaten(t_table *table);
long 	start_timer(int i);
void	init_support_mutexes(t_philo *philo);
void	threads_create_f(t_table *table);
int		check_stop(t_table *table);
void	cleanup(t_table *table);
void	odd_philo(t_philo *philo);
void	even_philo(t_philo *philo);
void	print_sleeping(t_philo *philo);
void	print_thinking(t_philo *philo);

/*  error.c functions  */

void    error_msg_1();
void    error_msg_2();
void    error_msg_3();
void	ft_error2();
void	one_philo_case(char **argv);

/*  utils.c functions  */

int     ft_atoi(const char *str);
int		is_num(char *num);
int		is_digit(char c);
int		ft_strlen(const char *str);

/*	itoa.c	*/

char	*ft_itoa(int n);
int		int_len(long n);
char	*before_alloc(int n);