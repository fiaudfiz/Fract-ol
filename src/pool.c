/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaudfiz <fiaudfiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 09:16:47 by fiaudfiz          #+#    #+#             */
/*   Updated: 2026/09/30 14:37:47 by fiaudfiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pool.h"
#include "ft_stdlib.h"
#include <stdbool.h>

static  void    *worker_loop(void *arg)
{
    t_pool *pool;
    t_task  task;

    pool = arg;
    while(1)
    {
        pthread_mutex_lock(&pool->mutex_queue);
        while(pool->count == 0 && !pool->shutdown)
            pthread_cond_wait(&pool->not_empty, &pool->mutex_queue);
        if(pool->count == 0)
        {
            pthread_mutex_unlock(&pool->mutex_queue);
            return (NULL);
        }
        task = pool->file[pool->head];
        pool->head = (pool->head + 1) % pool->max_capacity;
        pool->count--;
        pthread_cond_signal(&pool->not_full);
        pthread_mutex_unlock(&pool->mutex_queue);
        task.fn(task.arg);
    }
}


t_pool  *pool_create(int nb_threads, int capcacity)
{
    t_pool *pool;
    int     i = 0;

    pool = ft_calloc(1, sizeof(t_pool));
    if (!pool)
        return NULL;
    pool->max_capacity = capcacity;
    pool->file = ft_calloc(pool->max_capacity, sizeof(t_task));
    if (!pool->file)
    {
        free(pool);
        return(NULL);
    }
    pool->tab_of_threads = ft_calloc(nb_threads, sizeof(pthread_t));
    if (!pool->tab_of_threads)
    {
        free(pool->file);
        free(pool);
        return (NULL);
    }
    pthread_mutex_init(&pool->mutex_queue, NULL);
    pthread_cond_init(&pool->not_empty, NULL);
    pthread_cond_init(&pool->not_full, NULL);
    while (i < nb_threads && pthread_create(&pool->tab_of_threads[i], NULL, worker_loop, pool) == 0)
        i++;
    pool->nb_threads = i;
    if (i == 0)
        return (pool_destroy(pool), NULL);
    return (pool);
}

int	pool_submit(t_pool *pool, t_task_fn fn, void *arg)
{
	pthread_mutex_lock(&pool->mutex_queue);
	while (pool->count == pool->max_capacity && !pool->shutdown)
		pthread_cond_wait(&pool->not_full, &pool->mutex_queue);
	if (pool->shutdown)
	{
		pthread_mutex_unlock(&pool->mutex_queue);
		return (-1);
	}
	pool->file[pool->tail].fn = fn;
	pool->file[pool->tail].arg = arg;
	pool->tail = (pool->tail + 1) % pool->max_capacity;
	pool->count++;
	pthread_cond_signal(&pool->not_empty);
	pthread_mutex_unlock(&pool->mutex_queue);
	return (0);
}

void	pool_destroy(t_pool *pool)
{
	int	i;
 
	pthread_mutex_lock(&pool->mutex_queue);
	pool->shutdown = true;
	pthread_cond_broadcast(&pool->not_empty);
	pthread_cond_broadcast(&pool->not_full);
	pthread_mutex_unlock(&pool->mutex_queue);
	i = 0;
	while (i < pool->nb_threads)
		pthread_join(pool->tab_of_threads[i++], NULL);
	pthread_mutex_destroy(&pool->mutex_queue);
	pthread_cond_destroy(&pool->not_empty);
	pthread_cond_destroy(&pool->not_full);
	free(pool->file);
	free(pool->tab_of_threads);
	free(pool);
}