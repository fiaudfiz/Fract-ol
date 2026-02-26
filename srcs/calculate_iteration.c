/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_iteration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:14:17 by miouali           #+#    #+#             */
/*   Updated: 2026/02/03 09:39:30 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_z_vectors(t_fractol *f, __m256d *v_z_re, __m256d *v_z_im, __m256d *v_c_re, __m256d *v_c_im)
{
	if (f->type_of_fractal == 2)
	{
		*v_z_re = *v_c_re;
		*v_z_im = *v_c_im;
		*v_c_re = _mm256_set1_pd(f->julia_real_pixel);
		*v_c_im = _mm256_set1_pd(f->julia_imaginary_pixel);
	}
	else
	{
		*v_z_re = _mm256_setzero_pd();
		*v_z_im = _mm256_setzero_pd();
		
	}
}

void	dispatch_fractal(t_fractol *f, __m256d *v_z_re, __m256d *v_z_im, __m256d v_c_re, __m256d v_c_im)
{
	if (f->type_of_fractal == 1 || f->type_of_fractal == 2)
		compute_mandelbrot(v_z_re, v_z_im, v_c_re, v_c_im);
	else if (f->type_of_fractal == 3)
		compute_burning_ship(v_z_re, v_z_im, v_c_re, v_c_im);
	else if (f->type_of_fractal == 4)
		compute_tricorn(v_z_re, v_z_im, v_c_re, v_c_im);
	else if (f->type_of_fractal == 5)
		compute_celtic(v_z_re, v_z_im, v_c_re, v_c_im);
}

void	iterate_simd(t_fractol *f, __m256d *v_z_re, __m256d *v_z_im, __m256d v_c_re, __m256d v_c_im , __m256d *v_iter)
{
	int	n;
	__m256d v_z_re2;
	__m256d	v_z_im2;
	__m256d	v_mask;

	n = 0;
	while (n < f->max_iteration)
	{
		v_z_re2 = _mm256_mul_pd(*v_z_re, *v_z_re);
		v_z_im2 = _mm256_mul_pd(*v_z_im, *v_z_im);
		v_mask = _mm256_cmp_pd(_mm256_add_pd(v_z_re2, v_z_im2), _mm256_set1_pd(4.0), _CMP_LT_OQ);
		if (_mm256_movemask_pd(v_mask) == 0)
			break;
		*v_iter = _mm256_add_pd(*v_iter, _mm256_and_pd(v_mask, _mm256_set1_pd(1.0)));
		dispatch_fractal(f, v_z_re, v_z_im, v_c_re, v_c_im);
		n++;
	}
}

void	calculate_iteration_simd(t_fractol *f, __m256d v_c_re, __m256d v_c_im, __m256d *v_iter)
{
	__m256d v_z_re;
    __m256d v_z_im;

	v_z_im = _mm256_setzero_pd();
	v_z_re = _mm256_setzero_pd();
	init_z_vectors(f, &v_z_re, &v_z_im, &v_c_re, &v_c_im);
	iterate_simd(f, &v_z_re, &v_z_im, v_c_re, v_c_im, v_iter);
}
