/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:06:16 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/03/22 16:23:48 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_table table;
    t_philo *philo;

    alloc_fill_table(&table, argv);
    alloc_create_philos(&philo, &table);
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
}

void    alloc_create_philos(t_philo *philo, t_table *table)
{
    int n;

    n = 0;
    philo = (t_philo *)malloc(sizeof(t_philo *) * table->num_of_philo);
    if (!philo)
        error_msg();
    while (n < table->num_of_philo)
    {
        philo[n++].id = n;
        n++;
    }
    
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