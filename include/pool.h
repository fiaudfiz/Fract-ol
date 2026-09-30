/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaudfiz <fiaudfiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 08:28:41 by fiaudfiz          #+#    #+#             */
/*   Updated: 2026/09/30 11:05:55 by fiaudfiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POOL_H
# define POOL_H

#include <pthread.h>
#include <stdbool.h>

typedef void	(*t_task_fn)(void *);

typedef struct s_task
{
	t_task_fn	fn;
	void		*arg;
}	t_task;

typedef struct s_pool
{
    pthread_t   *tab_of_threads;
    int         nb_threads;
    t_task      *file;
    int         max_capacity;
    int         head;
    int         tail;
    int         count;
    bool        shutdown;
    pthread_mutex_t mutex_queue;
    pthread_cond_t  not_empty;
    pthread_cond_t  not_full;
}t_pool;


t_pool *pool_create(int nb_threads, int capcacity);
int pool_submit(t_pool *pool, t_task_fn fn, void *arg);
void    pool_destroy(t_pool *pool);

#endif