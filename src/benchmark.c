# define _POSIX_C_SOURCE 199309L
#include "fractol.h"
#include "pool.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static double	elapsed_ms(struct timespec start, struct timespec end)
{
	return ((end.tv_sec - start.tv_sec) * 1000.0
		+ (end.tv_nsec - start.tv_nsec) / 1000000.0);
}

static int	cmp_double(const void *a, const void *b)
{
	double	x;
	double	y;

	x = *(const double *)a;
	y = *(const double *)b;
	if (x < y)
		return (-1);
	if (x > y)
		return (1);
	return (0);
}

/* nearest-rank : la plus petite valeur telle que p% des mesures lui sont <= */
static double	percentile(double *sorted, int n, double p)
{
	double	rank;
	int		idx;

	rank = p / 100.0 * n;
	idx = (int)rank;
	if (idx < rank)
		idx++;
	idx--;
	if (idx < 0)
		idx = 0;
	if (idx >= n)
		idx = n - 1;
	return (sorted[idx]);
}

static void	print_stats(double *times, int n)
{
	double	total;
	int		i;

	total = 0;
	i = 0;
	while (i < n)
		total += times[i++];
	qsort(times, n, sizeof(double), cmp_double);
	printf("frames: %d | avg: %.2f ms | min: %.2f ms | max: %.2f ms\n",
		n, total / n, times[0], times[n - 1]);
	printf("p50: %.2f ms | p95: %.2f ms | p99: %.2f ms | p99.9: %.2f ms\n",
		percentile(times, n, 50.0), percentile(times, n, 95.0),
		percentile(times, n, 99.0), percentile(times, n, 99.9));
}

void	benchmark_pool(t_fractol *f, int nb_frames)
{
	struct timespec	start;
	struct timespec	end;
	double			*times;
	int				i;

	times = malloc(sizeof(double) * nb_frames);
	if (!times)
		return ;
	i = 0;
	while (i < nb_frames)
	{
		apply_zoom(f, 0.0, 0.0, 0.99);
		f->real_factor = (f->max_real_window - f->min_real_window) / WIN_WIDTH;
		f->imaginary_factor = (f->min_imaginary_window
				- f->max_imaginary_window) / WIN_HEIGHT;
		clock_gettime(CLOCK_MONOTONIC, &start);
		render_frame(f->render, f->pool);
		clock_gettime(CLOCK_MONOTONIC, &end);
		times[i++] = elapsed_ms(start, end);
	}
	print_stats(times, nb_frames);
	free(times);
}