/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:06:16 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/16 18:45:44 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	init_support_mutexes(table->philo);
	threads_create_f(table);
	cleanup(table);
    return (0);
}

void	init_support_mutexes(t_philo *philo)
{
	t_philo	*head;
	head = philo;

	while (head)
	{
		pthread_mutex_init(&head->last_meal_time_mutex, NULL);
		pthread_mutex_init(&head->times_eaten_mutex, NULL);
		pthread_mutex_init(&head->stop_mutex, NULL);
		head = head->next;
	}
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

void	threads_create_f(t_table *table)
{
	t_philo *head;

	head = table->philo;
	usleep(1000);
	start_timer(0);
	while (head)
	{
		pthread_mutex_lock(&head->last_meal_time_mutex);
		head->last_meal_time = start_timer(1);
		pthread_mutex_unlock(&head->last_meal_time_mutex);
		head = head->next;
	}
	init_monitoring(table);
	head = table->philo;
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
}

void	*dining_philosophers(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (!check_stop(philo->table))
	{
		if (check_stop(philo->table))
			break;
		if ((philo->id % 2) == 0)
			even_philo(philo);
		else
			odd_philo(philo);
	}
	return (NULL);
}

void	odd_philo(t_philo *philo)
{
	if (check_stop(philo->table))
		return ;
	if(!check_stop(philo->table))
		print_sleeping(philo);
	if(!check_stop(philo->table))
		print_thinking(philo);
	if (pthread_mutex_lock(&philo->right_fork) == 0 && !check_stop(philo->table))
	{
		pthread_mutex_lock(&philo->left_fork);
		print_taken_fork_eating(philo);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_lock(&philo->times_eaten_mutex);
		philo->times_eaten += 1;
		pthread_mutex_unlock(&philo->times_eaten_mutex);
		pthread_mutex_lock(&philo->last_meal_time_mutex);
		philo->last_meal_time = start_timer(1);
		pthread_mutex_unlock(&philo->last_meal_time_mutex);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
}

void	even_philo(t_philo *philo)
{
	if(check_stop(philo->table))
		return;
	if (pthread_mutex_lock(&philo->left_fork) == 0 && !check_stop(philo->table))
	{
		pthread_mutex_lock(&philo->right_fork);
		print_taken_fork_eating(philo);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_lock(&philo->times_eaten_mutex);
		philo->times_eaten += 1;
		pthread_mutex_unlock(&philo->times_eaten_mutex);
		pthread_mutex_lock(&philo->last_meal_time_mutex);
		philo->last_meal_time = start_timer(1);
		pthread_mutex_unlock(&philo->last_meal_time_mutex);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		if(!check_stop(philo->table))
			print_sleeping(philo);
		if(!check_stop(philo->table))
			print_thinking(philo);
	}
}

void	print_taken_fork_eating(t_philo *philo)
{
	if (!check_stop(philo->table))
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%ld %d has taken a fork\n", start_timer(1), philo->id);
		printf("%ld %d is eating\n", start_timer(1), philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
}

void print_thinking(t_philo *philo)
{
	if(!check_stop(philo->table))
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%ld %d is thinking\n", start_timer(1), philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		usleep((philo->table->time_to_eat - philo->table->time_to_sleep) * 1000);
	}
}

void print_sleeping(t_philo *philo)
{
	if(!check_stop(philo->table))
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%ld %d is sleeping\n", start_timer(1), philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		usleep(philo->table->time_to_sleep * 1000);
	}
}

void	join_forks(t_table *table)
{
	int	i;
	t_philo			*current;

	i = 0;
	current = table->philo;
	while (table->num_of_philo > i)
	{
		current->left_fork = table->forks[i];
		current->right_fork = table->forks[(i + 1) % table->num_of_philo];
		i++;
		current = current->next;
	}
}

void	init_monitoring(t_table *table)
{
	pthread_create(&table->monitoring, NULL, monitoring_f, (void *)table);
}

void	*monitoring_f(void *arg)
{
	t_philo	*head;
	t_table	*table;
	
	table = (t_table *)arg;
	while (1)
	{
		head = table->philo;
		while (head)
		{
			pthread_mutex_lock(&head->last_meal_time_mutex);
			if ((start_timer(1) - head->last_meal_time) > table->time_to_die)
			{
				pthread_mutex_unlock(&head->last_meal_time_mutex);
				pthread_mutex_lock(&table->print_mutex);
				printf("%ld %u died\n", start_timer(1), head->id);
				pthread_mutex_unlock(&table->print_mutex);
				pthread_mutex_lock(&table->stop_mutex);
				table->stop = 1;
				pthread_mutex_unlock(&table->stop_mutex);
				return (NULL);
			}
			else 
				pthread_mutex_unlock(&head->last_meal_time_mutex);
			head = head->next;
		}
		if (have_all_eaten(table))
		{
			pthread_mutex_lock(&table->stop_mutex);
			write (1, "Program succsessfully finished\n", 31);
			table->stop = 1;
			pthread_mutex_unlock(&table->stop_mutex);
			return (NULL);
		}
		usleep(1000);
	}
}

int	check_stop(t_table *table)
{
	int result;

	pthread_mutex_lock(&table->stop_mutex);
	result = table->stop;
	pthread_mutex_unlock(&table->stop_mutex);
	return result;
}

int	have_all_eaten(t_table *table)
{
	t_philo	*head;

	head = table->philo;
	if (table->number_of_times_each_phil_must_eat == -1)
		return (0);
	while (head)
	{
		pthread_mutex_lock(&head->times_eaten_mutex);
		if (head->times_eaten < table->number_of_times_each_phil_must_eat)
		{
			pthread_mutex_unlock(&head->times_eaten_mutex);
			return (0);
		}
		pthread_mutex_unlock(&head->times_eaten_mutex);
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
	if (table->number_of_times_each_phil_must_eat != -1)
    	table->number_of_times_each_phil_must_eat = ft_atoi(argv[5]);
	table->philo = NULL;
	table->stop = 0;
	pthread_mutex_init(&table->stop_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
}

void	alloc_philos(t_table *table)
{
	int 	n;
	t_philo *new_philo;
	t_philo *current;
	
    n = 0;
	new_philo = (t_philo *)malloc(sizeof(t_philo));
	if (!new_philo)
		error_msg_1();

	new_philo->id = n;
	new_philo->last_meal_time = 0;
	new_philo->times_eaten = 0;
	new_philo->next = NULL;
	new_philo->table = table;
	table->philo = new_philo;
	current = new_philo;
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
		current->next = new_philo;
		current = new_philo;
		n++;
	}
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
	if (*argv[1] == '1')
		one_philo_case(argv);
}

void	cleanup(t_table *table)
{
	int			i = 0;
	t_philo		*tmp;
	t_philo		*philo = table->philo;

	while (philo)
	{
		pthread_mutex_destroy(&philo->last_meal_time_mutex);
		pthread_mutex_destroy(&philo->times_eaten_mutex);
		pthread_mutex_destroy(&philo->stop_mutex);
		tmp = philo;
		philo = philo->next;
		free(tmp);
	}
	while (i < table->num_of_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->stop_mutex);
	free(table->forks);
	free(table);
}