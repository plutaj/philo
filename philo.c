/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:06:16 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/04 20:30:15 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_table *table;

	table = NULL;
    edge_cases(argc, argv);
    alloc_init_table(table, argv);
    create_philos(table);
	init_monitoring(table);
    return (0);
}

void	init_monitoring(t_table *table)
{
    pthread_t	monitoring;
	
	table->monitoring = &monitoring;
	pthread_create(&monitoring, NULL, monitoring_f, (void *)table); // add 3rd param
}

void	*monitoring_f(void *arg)
{
	t_philo	*head;
	t_table	*table = (t_table *)arg;

	head = table->philo;
	while (1)
	{
		while (table->philo)
		{
			if (table->philo->last_meal_time > table->time_to_die)
			{
				write (1, "\nPhilo", 6); /*later needed to destroy threads*/
				write (1, table->philo->id, 1); /*vyhandlovat string do write nie int*/
				write (1, "died of starvation\n", 18);
				exit(0);
			}
			table->philo = table->philo->next;
		}
		table->philo = head;
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
	while (table->philo)
	{
		if (table->philo->times_eaten < table->number_of_times_each_phil_must_eat)
		{
			table->philo = head;
			return (0);
		}
		table->philo = table->philo->next;
	}
	table->philo = head;
	return (1);
}

void    alloc_init_table(t_table *table, char **argv)
{
	int	i;

	i = 0;
    table = (t_table *)malloc(sizeof(t_table));
    if (!table)
        exit(1);
    table->num_of_philo = atoi(argv[1]);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->num_of_philo);
    if (!table->forks)
		exit(1);
	while (i < table->num_of_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	table->time_to_die = atoi(argv[2]);
    table->time_to_eat = atoi(argv[3]);
    table->time_to_sleep = atoi(argv[4]);
    table->number_of_times_each_phil_must_eat = atoi(argv[5]);
	table->philo = NULL;
}

void    create_philos(t_table *table)
{
    int n;

    n = 0;
	t_philo *new_philo;
	t_philo	*head;

	new_philo = NULL;
	head = NULL;
	alloc_philos(table, new_philo, head, n);
}

void	alloc_philos(t_table *table, t_philo *new_philo, t_philo *head, int n)
{
	if (table->philo == NULL && table->num_of_philo > 0)
	{
		new_philo = (t_philo *)malloc(sizeof(t_philo));
		if (!new_philo)
			error_msg();
		head = new_philo;
		new_philo->id = n;
		pthread_create(&new_philo->thread, NULL, NULL, &new_philo->id); // add 3rd param
		new_philo->last_meal_time = 0;
		new_philo->times_eaten = 0;
		new_philo->next = NULL;
		table->philo = new_philo;
		n++;
	}
	while(n < table->num_of_philo)
	{
		new_philo = (t_philo *)malloc(sizeof(t_philo));
		if (!new_philo)
			error_msg();
		new_philo->id = n;
		new_philo->last_meal_time = 0;
		new_philo->times_eaten = 0;
		pthread_create(&new_philo->thread, NULL, NULL, &new_philo->id); // add 3rd param
		table->philo->next = new_philo;
		table->philo = table->philo->next;
		table->philo->next = NULL;
		n++;
	}
	table->philo = head;
}

void    edge_cases(int argc, char **argv)
{
    int num_of_philo;
	int	i;

	i = 2;
    if (argc != 6)
    {
        printf("Error [Wrong number of arguments]\n");
        exit(0);
    }
	if (!is_num(argv[1]))
		ft_error2();
    num_of_philo = ft_atoi(argv[1]);
    if (num_of_philo < 1)
    {
        printf("Error [Wrong number of philosophers]\n");
        exit(0);
    }
	while (i <= 5)
	{
		if (0 > ft_atoi(argv[i]))
			ft_error2();
		if (!(is_num(argv[i])))
			error_msg();
		i++;
	}
}