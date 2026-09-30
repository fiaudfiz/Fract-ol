/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaudfiz <fiaudfiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 15:20:37 by fiaudfiz          #+#    #+#             */
/*   Updated: 2026/09/30 15:31:01 by fiaudfiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define _POSIX_C_SOURCE 199309L
#include "fractol.h"
#include "pool.h"
#include <time.h>
#include <unistd.h>

static double	elapsed_ms(struct timespec start, struct timespec end)
{
	return ((end.tv_sec - start.tv_sec) * 1000.0
		+ (end.tv_nsec - start.tv_nsec) / 1000000.0);
}

void	benchmark_pool(t_fractol *f, int nb_frames)
{
	struct timespec	start;
	struct timespec	end;
	double			total;
	double			t;
	double			min;
	double			max;
	int				i;

	total = 0;
	min = 1e9;
	max = 0;
	i = 0;
	while (i < nb_frames)
	{
		apply_zoom(f, 0.0, 0.0, 0.99);
		f->real_factor = (f->max_real_window - f->min_real_window) / WIN_WIDTH;
		f->imaginary_factor = (f->min_imaginary_window - f->max_imaginary_window) / WIN_HEIGHT;
		clock_gettime(CLOCK_MONOTONIC, &start);
		render_frame(f->render, f->pool);
		clock_gettime(CLOCK_MONOTONIC, &end);
		t = elapsed_ms(start, end);
		total += t;
		if (t < min)
			min = t;
		if (t > max)
			max = t;
		i++;
	}
	printf("frames: %d | avg: %.2f ms | min: %.2f ms | max: %.2f ms\n",
		nb_frames, total / nb_frames, min, max);
}