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

void	put_color(t_fractol *f, int *pixel_ptr)
{
	if (f->iteration == f->max_iteration)
		*pixel_ptr = 0x000000;
	else
		*pixel_ptr = f->palette[f->iteration % MAX_ITER];
}

void	render_fractal(t_fractol *f)
{
	int	*pixel_ptr;

	pixel_ptr = (int *)f->addr;
	init(f);
	while (f ->pixel_y < WIN_HEIGHT)
	{
		f ->pixel_x = 0;
		f ->pixel_imaginary = f->max_imaginary_window
			+ (double)f ->pixel_y * f->imaginary_factor;
		while (f ->pixel_x < WIN_WIDTH)
		{
			f ->pixel_real = f->min_real_window
				+ (double)f ->pixel_x * f->real_factor;
			f -> iteration = 0;
			if (!fractal(f, &pixel_ptr))
			{
				calculate_iteration(f);
				put_color(f, pixel_ptr);
				pixel_ptr++;
				f->pixel_x++;
			}
		}
		f->pixel_y++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}


void	render_fractal_simd(t_fractol *f)
{
	int		*pixel_ptr;
	__m256d	v_c_re;
	__m256d	v_c_im;
	__m256d	v_offsets;
	__m256d	v_iter;
	double	results[4];
	int	i = 0;

	pixel_ptr = (int *)f->addr;
	init(f);
	v_offsets = _mm256_set_pd(3.0, 2.0, 1.0, 0.0);
	while (f ->pixel_y < WIN_HEIGHT)
	{
		f->pixel_x = 0;
		f ->pixel_imaginary = f->max_imaginary_window
				+ (double)f ->pixel_y * f->imaginary_factor;
		v_c_im = _mm256_set1_pd(f->pixel_imaginary);
		while (f->pixel_x < WIN_WIDTH)
		{
			v_iter = _mm256_setzero_pd();
			v_c_re = _mm256_add_pd(_mm256_set1_pd(f->min_real_window),
            	_mm256_mul_pd(_mm256_add_pd(_mm256_set1_pd((double)f->pixel_x), v_offsets), 
                _mm256_set1_pd(f->real_factor)));
			calculate_iteration_simd(f, v_c_re, v_c_im, &v_iter); //new_fonction a ecrire
			_mm256_storeu_pd(results, v_iter);
			i = 0;
			while (i < 4 && (f->pixel_x + i) < WIN_WIDTH)
			{
				f->iteration = (int)results[i];
				put_color(f, pixel_ptr);
				pixel_ptr++;
				i++;
			}
			f->pixel_x += 4;
		}
		f->pixel_y ++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

void	calculate_iteration_simd(t_fractol *f, __m256d v_c_re, __m256d v_c_im, __m256d *v_iter)
{
	__m256d	v_mask;
	__m256d v_z_re2;
	__m256d	v_z_im2;
	__m256d	v_four;
	__m256d	v_one;
	int		n = 0;
	v_four = _mm256_set1_pd(4.0);
	v_one = _mm256_set1_pd(1.0);
	__m256d v_z_re = _mm256_setzero_pd();
    __m256d v_z_im = _mm256_setzero_pd();

	while (n < f->max_iteration)
	{
		v_z_re2 = _mm256_mul_pd(v_z_re, v_z_re);
		v_z_im2 = _mm256_mul_pd(v_z_im, v_z_im);
		v_mask = _mm256_cmp_pd(_mm256_add_pd(v_z_re2, v_z_im2), v_four, _CMP_LT_OQ);
		if (_mm256_movemask_pd(v_mask) == 0)
			break;
		*v_iter = _mm256_add_pd(*v_iter, _mm256_and_pd(v_mask, v_one));
		v_z_im = _mm256_add_pd(_mm256_mul_pd(_mm256_set1_pd(2.0), 
			_mm256_mul_pd(v_z_re, v_z_im)), v_c_im);
		v_z_re = _mm256_add_pd(_mm256_sub_pd(v_z_re2, v_z_im2), v_c_re);
		n++;
	}
}

