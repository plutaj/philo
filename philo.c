/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:06:16 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/02 19:07:46 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_table *table;

    alloc_fill_table(table, argv);
    alloc_create_philos(table);
    edge_cases(argc, argv);
    return (0);
}

void    alloc_fill_table(t_table *table, char **argv)
{
    table = (t_table *)malloc(sizeof(t_table));
    if (!table)
        exit(1);
    table->num_of_philo = atoi(argv[1]);
    table->time_to_die = atoi(argv[2]);
    table->time_to_eat = atoi(argv[3]);
    table->time_to_sleep = atoi(argv[4]);
    table->number_of_times_each_phil_must_eat = atoi(argv[5]);
	table->philo = NULL;
}

void    alloc_create_philos(t_table *table)
{
    int n;

    n = 0;
	t_philo *new_philo;
	t_philo	*head;

	new_philo = NULL;
	if (table->philo == NULL && table->num_of_philo > 0)
	{
		new_philo = (t_philo *)malloc(sizeof(t_philo));
		if (!new_philo)
			error_msg();
		head = new_philo;
		new_philo->id = n;
		pthread_create(&new_philo->thread, NULL, NULL, &new_philo->id); // add 3rd param
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

    num_of_philo = atoi(argv[1]);
    if (argc != 5)
    {
        printf("Error [Wrong number of arguments]\n");
        exit(0);
    }
    if (num_of_philo < 1)
    {
        printf("Error [Wrong number of philosophers]\n");
        exit(0);
    }
}