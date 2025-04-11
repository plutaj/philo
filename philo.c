/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:06:16 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/11 21:05:52 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Poznamka : chyba niekde v monitoring_f v if statemente

int main(int argc, char **argv)
{
    t_table *table;
	
	table = (t_table *)malloc(sizeof(t_table));
    if (!table)
        exit(1);
    edge_cases(argc, argv, table);
    alloc_init_table(table, argv);
    alloc_philos(table);
	join_forks(table);
	init_monitoring(table);
	usleep(1000);
	threads_create_f(table);
    return (0);
}

long start_timer(int i)
{
    static struct timeval start_time;
    struct timeval end_time;
    long seconds, microseconds;
    
    if (i == 0)
    {
        gettimeofday(&start_time, NULL);
        return 0;
    }
    gettimeofday(&end_time, NULL);
    seconds = end_time.tv_sec - start_time.tv_sec;
    microseconds = end_time.tv_usec - start_time.tv_usec;
    if (microseconds < 0)
    {
        microseconds += 1000000;
        seconds -= 1;
    }
    long elapsed_time = seconds * 1000 + microseconds / 1000;
    return (elapsed_time);
}

// long start_timer(int i)
// {
// 	long	seconds;
// 	long	microseconds;
	
// 	if (i == 0)
// 	{
//     	gettimeofday(&start_time, NULL);
// 		return (0);
// 	}
// 	gettimeofday(&end_time, NULL);
// 	seconds = end_time.tv_sec - start_time.tv_sec;
//     microseconds = end_time.tv_usec - start_time.tv_usec;
    
//     // Convert the time difference to milliseconds
//     long elapsed_time = seconds * 1000 + microseconds / 1000;
// 	return (elapsed_time);
// }

void	threads_create_f(t_table *table)
{
	t_philo *head;

	head = table->philo;
	start_timer(0);
	while (head)
	{
		pthread_create(&head->thread, NULL, dining_philosophers, (void *)head);
		head = head->next;
	}
	head = table->philo;
	while (head)
	{
		pthread_join(head->thread, NULL);
		head = head->next;
	}
	pthread_join(table->monitoring, NULL);
	// write(1, "Threads for philos and monitoring was created and joined.", 57);
}

void	*dining_philosophers(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (1)
	{
		if ((philo->id % 2) == 0)
		{
			if (pthread_mutex_lock(&philo->left_fork) == 0)
			{
				pthread_mutex_lock(&philo->right_fork);
				printf("%ld %d has taken a fork\n", start_timer(1), philo->id);
				printf("%ld %d is eating\n", start_timer(1), philo->id);
				usleep(philo->table->time_to_eat * 1000);
				philo->times_eaten += 1;
				philo->last_meal_time = start_timer(1); // posefit toto
				pthread_mutex_unlock(&philo->left_fork);
				pthread_mutex_unlock(&philo->right_fork);
				printf("%ld %d is sleeping\n", start_timer(1), philo->id);
				usleep(philo->table->time_to_sleep * 1000);
				printf("%ld %d is thinking\n", start_timer(1), philo->id);
				usleep((philo->table->time_to_eat - philo->table->time_to_sleep) * 1000);
			}
		}
		else
		{
			printf("%ld %d is sleeping\n", start_timer(1), philo->id);
			usleep(philo->table->time_to_sleep * 1000);
			printf("%ld %d is thinking\n", start_timer(1), philo->id);
			usleep((philo->table->time_to_eat - philo->table->time_to_sleep) * 1000);
			if (pthread_mutex_lock(&philo->right_fork) == 0)
				pthread_mutex_lock(&philo->left_fork);
			printf("%ld %d has taken a fork\n", start_timer(1), philo->id);
			printf("%ld %d is eating\n", start_timer(1), philo->id);
			usleep(philo->table->time_to_eat * 1000);
			philo->times_eaten += 1;
			philo->last_meal_time = start_timer(1);
			pthread_mutex_unlock(&philo->left_fork);
			pthread_mutex_unlock(&philo->right_fork);
		}	
	}
}

void	join_forks(t_table *table)
{
	int	i;
	t_philo	*current;

	i = 0;
	current = table->philo;
	while (table->num_of_philo > i)
	{
		current->left_fork = table->forks[i];
		current->right_fork = table->forks[(i + 1) % table->num_of_philo];
		i++;
	}
}

void	init_monitoring(t_table *table)
{
	pthread_create(&table->monitoring, NULL, monitoring_f, (void *)table); // add 3rd param
}

void	*monitoring_f(void *arg)
{
	t_philo	*head;
	t_table	*table = (t_table *)arg;

	head = table->philo;
	while (head)
	{
		pthread_mutex_init(&head->last_meal_time_mutex, NULL); // added 1
		head = head->next;
	}
	head = table->philo;
	while (1)
	{
		while (head)
		{
			pthread_mutex_lock(&head->last_meal_time_mutex); // added 1
			if ((head->last_meal_time - start_timer(1)) > table->time_to_die) // chyba niekde tu 
			{
				printf("Philo number %u died of starvation\n", head->id);
				exit(0);
			}
			pthread_mutex_unlock(&head->last_meal_time_mutex); // added 1
			head = head->next;
		}
		head = table->philo;
		if (have_all_eaten(table))
		{
			write (1, "Program succsessfully finished\n", 31);
			exit(0);
		}
		usleep(1000);
	}
}

int	have_all_eaten(t_table *table)
{
	t_philo	*head;

	head = table->philo;
	if (table->number_of_times_each_phil_must_eat == -1) // case when argc == 5
		return (0);
	while (head)
	{
		if (head->times_eaten < table->number_of_times_each_phil_must_eat)
			return (0);
		head = head->next;
	}
	return (1);
}

void    alloc_init_table(t_table *table, char **argv)
{
	int	i;

	i = 0;
    table->num_of_philo = ft_atoi(argv[1]);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->num_of_philo);
    if (!table->forks)
		exit(1);
	while (i < table->num_of_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);
	if (table->number_of_times_each_phil_must_eat != -1) // case when argc == 5
    	table->number_of_times_each_phil_must_eat = ft_atoi(argv[5]);
	table->philo = NULL;
}

void	alloc_philos(t_table *table)
{
	int n;
	t_philo *new_philo;
	t_philo	*head;
	t_philo *current;
	
    n = 0;
	new_philo = (t_philo *)malloc(sizeof(t_philo));
	if (!new_philo)
		error_msg_1();
	head = new_philo;
	
	new_philo->id = n;
	new_philo->last_meal_time = 0;
	new_philo->times_eaten = 0;
	new_philo->next = NULL;
	new_philo->table = table;
	table->philo = new_philo;
	n++;
	while(n < table->num_of_philo)
	{
		new_philo = (t_philo *)malloc(sizeof(t_philo));
		if (!new_philo)
			error_msg_2();
		new_philo->id = n;
		new_philo->last_meal_time = 0;
		new_philo->times_eaten = 0;
		new_philo->next = NULL;
		new_philo->table = table;
		current = table->philo;
        while (current->next != NULL)
			current = current->next;
		current->next = new_philo;
		n++;
	}
	table->philo = head;
}

void    edge_cases(int argc, char **argv, t_table *table)
{
    int num_of_philo;
	int	i;

    if (argc < 5 || argc > 6)
    {
        printf("Error [Wrong number of arguments]\n");
        exit(0);
    }
	if (argc == 5)
		table->number_of_times_each_phil_must_eat = -1;
	i = 1;
	while (i < argc)
	{
		if (!is_num(argv[i]))
			ft_error2();
		i++;
	}
    num_of_philo = ft_atoi(argv[1]);
    if (num_of_philo < 1)
    {
        printf("Error [Wrong number of philosophers]\n");
        exit(0);
    }
}