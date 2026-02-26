/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fractal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:13:17 by miouali           #+#    #+#             */
/*   Updated: 2026/02/03 10:39:21 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void    put_row(t_fractol *f, int **pixel_ptr, double *results)
{
	int	i;

	i = 0;
	while (i < 4 && (f->pixel_x + i) < WIN_WIDTH)
	{
		f->iteration = (int)results[i];
		put_color(f, *pixel_ptr);
		(*pixel_ptr)++;
		i++;
	}
}

static void		render_row(t_fractol *f, int **pixel_ptr, __m256d v_offsets)
{
	__m256d v_c_re;
	__m256d v_c_im;
	__m256d	v_iter;
	double	results[4];
	
	v_c_im = _mm256_set1_pd(f->pixel_imaginary);
	while (f->pixel_x < WIN_WIDTH)
	{
		v_iter = _mm256_setzero_pd();
		v_c_re = _mm256_add_pd(_mm256_set1_pd(f->min_real_window),
           	_mm256_mul_pd(_mm256_add_pd(_mm256_set1_pd((double)f->pixel_x), v_offsets), 
               _mm256_set1_pd(f->real_factor)));
		calculate_iteration_simd(f, v_c_re, v_c_im, &v_iter);
		_mm256_storeu_pd(results, v_iter);
		put_row(f, pixel_ptr, results);
		f->pixel_x += 4;
	}
}

void	render_fractal_simd(t_fractol *f)
{
	int		*pixel_ptr;
	__m256d	v_offsets;

	pixel_ptr = (int *)f->addr;
	init(f);
	v_offsets = _mm256_set_pd(3.0, 2.0, 1.0, 0.0);
	while (f ->pixel_y < WIN_HEIGHT)
	{
		f->pixel_x = 0;
		f ->pixel_imaginary = f->max_imaginary_window
				+ (double)f ->pixel_y * f->imaginary_factor;
		render_row(f, &pixel_ptr, v_offsets);
		f->pixel_y ++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

