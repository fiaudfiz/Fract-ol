/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_tile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaudfiz <fiaudfiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 10:56:12 by fiaudfiz          #+#    #+#             */
/*   Updated: 2026/09/30 17:57:08 by fiaudfiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pool.h"
#include <math.h>
#include "fractol.h"

void	render_init(t_render *render, t_fractol *f)
{
	int	i;
	int	x;
	int	y;

	render->fractol = f;
	render->pending = 0;
	pthread_mutex_init(&render->mutex_render, NULL);
	pthread_cond_init(&render->cond_pending, NULL);
	i = 0;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
            render->tiles[i].render = render;
            render->tiles[i].index = i;
			render->tiles[i].x0 = x;
			render->tiles[i].y0 = y;
			render->tiles[i].xf = x + TILE_SIZE;
			render->tiles[i].yf = y + TILE_SIZE;
			if (render->tiles[i].xf > WIN_WIDTH)
				render->tiles[i].xf = WIN_WIDTH;
			if (render->tiles[i].yf > WIN_HEIGHT)
				render->tiles[i].yf = WIN_HEIGHT;
			x += TILE_SIZE;
			i++;
		}
		y += TILE_SIZE;
	}
}

void	render_frame(t_render *render, t_pool *pool)
{
	int	i;

	pthread_mutex_lock(&render->mutex_render);
	render->pending = NB_TILES;
	pthread_mutex_unlock(&render->mutex_render);
	i = 0;
	while (i < NB_TILES)
	{
		pool_submit(pool, render_tile, &render->tiles[i]);
		i++;
	}
	pthread_mutex_lock(&render->mutex_render);
	while (render->pending > 0)
		pthread_cond_wait(&render->cond_pending, &render->mutex_render);
	pthread_mutex_unlock(&render->mutex_render);
}

static void	iterate_pixel(t_fractol *f, double cr, double ci, int *iter)
{
	double	zr;
	double	zi;
	double	tmp_re;
	double	tmp_im;

	if (f->type_of_fractal == 2)
	{
		zr = cr;
		zi = ci;
		cr = f->julia_real_pixel;
		ci = f->julia_imaginary_pixel;
	}
	else
	{
		zr = 0.0;
		zi = 0.0;
	}
	*iter = 0;
	while (*iter < f->max_iteration && zr * zr + zi * zi < 4.0)
	{
		if (f->type_of_fractal == 3)
			tmp_im = -2.0 * zr * zi + ci;
		else if (f->type_of_fractal == 5)
			tmp_im = 2.0 * zr * zi + ci;
		else if (f->type_of_fractal == 4)
			tmp_im = fabs(2.0 * zr * zi) + ci;
		else
			tmp_im = 2.0 * zr * zi + ci;
		if (f->type_of_fractal == 5 || f->type_of_fractal == 4)
			tmp_re = fabs(zr * zr - zi * zi) + cr;
		else
			tmp_re = zr * zr - zi * zi + cr;
		zi = tmp_im;
		zr = tmp_re;
		(*iter)++;
	}
}

/*static void	iterate_pixel(t_fractol *f, double cr, double ci, int *iter)
{
	double	zr;
	double	zi;
	double	tmp;

	zr = 0.0;
	zi = 0.0;
	if (f->type_of_fractal == 2)
	{
		zr = cr;
		zi = ci;
		cr = f->julia_real_pixel;
		ci = f->julia_imaginary_pixel;
	}
	*iter = 0;
	if (f->type_of_fractal == 3)          // burning ship
		while (*iter < f->max_iteration && zr * zr + zi * zi < 4.0)
		{
			tmp = fabs(zr * zr - zi * zi) + cr;
			zi = fabs(2.0 * zr * zi) + ci;
			zr = tmp;
			(*iter)++;
		}
	else if (f->type_of_fractal == 4)     // tricorn
		while (*iter < f->max_iteration && zr * zr + zi * zi < 4.0)
		{
			tmp = zr * zr - zi * zi + cr;
			zi = -2.0 * zr * zi + ci;
			zr = tmp;
			(*iter)++;
		}
	else if (f->type_of_fractal == 5)     // celtic
		while (*iter < f->max_iteration && zr * zr + zi * zi < 4.0)
		{
			tmp = fabs(zr * zr - zi * zi) + cr;
			zi = 2.0 * zr * zi + ci;
			zr = tmp;
			(*iter)++;
		}
	else                                    // mandelbrot / julia
		while (*iter < f->max_iteration && zr * zr + zi * zi < 4.0)
		{
			tmp = zr * zr - zi * zi + cr;
			zi = 2.0 * zr * zi + ci;
			zr = tmp;
			(*iter)++;
		}
}*/

void	render_tile(void *arg)
{
	t_tile		*tile;
	t_render	*render;
	t_fractol	*f;
	int			x;
	int			y;
	int			iter;
	double		cr;
	double		ci;
	int			*pixel_ptr;

	tile = (t_tile *)arg;
	render = tile->render;
	f = render->fractol;
	y = tile->y0;
	while (y < tile->yf)
	{
		x = tile->x0;
		while (x < tile->xf)
		{
			cr = f->min_real_window + (double)x * f->real_factor;
			ci = f->max_imaginary_window + (double)y * f->imaginary_factor;
			iterate_pixel(f, cr, ci, &iter);
			pixel_ptr = (int *)(f->addr + y * f->line_length
					+ x * (f->bits_per_pixel / 8));
			put_color_thread(f, pixel_ptr, iter);
			x++;
		}
		y++;
	}
	pthread_mutex_lock(&render->mutex_render);
	render->pending--;
	if (render->pending == 0)
		pthread_cond_signal(&render->cond_pending);
	pthread_mutex_unlock(&render->mutex_render);
}