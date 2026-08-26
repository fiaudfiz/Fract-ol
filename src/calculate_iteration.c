/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_iteration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:14:17 by miouali           #+#    #+#             */
/*   Updated: 2026/02/26 16:30:54 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_z_vectors(t_fractol *f, t_simd *s)
{
	if (f->type_of_fractal == 2)
	{
		s->v_z_re = s->v_c_re;
		s->v_z_im = s->v_c_im;
		s->v_c_re = _mm256_set1_pd(f->julia_real_pixel);
		s->v_c_im = _mm256_set1_pd(f->julia_imaginary_pixel);
	}
	else
	{
		s->v_z_re = _mm256_setzero_pd();
		s->v_z_im = _mm256_setzero_pd();
	}
}

void	dispatch_fractal(t_fractol *f, t_simd *s)
{
	if (f->type_of_fractal == 1 || f->type_of_fractal == 2)
		compute_mandelbrot(s);
	else if (f->type_of_fractal == 3)
		compute_burning_ship(s);
	else if (f->type_of_fractal == 4)
		compute_tricorn(s);
	else if (f->type_of_fractal == 5)
		compute_celtic(s);
}

void	iterate_simd(t_fractol *f, t_simd *s)
{
	int		n;
	__m256d	v_z_re2;
	__m256d	v_z_im2;
	__m256d	v_mask;

	n = 0;
	while (n < f->max_iteration)
	{
		v_z_re2 = _mm256_mul_pd(s->v_z_re, s->v_z_re);
		v_z_im2 = _mm256_mul_pd(s->v_z_im, s->v_z_im);
		v_mask = _mm256_cmp_pd(_mm256_add_pd(v_z_re2, v_z_im2),
				_mm256_set1_pd(4.0), _CMP_LT_OQ);
		if (_mm256_movemask_pd(v_mask) == 0)
			break ;
		s->v_iter = _mm256_add_pd(s->v_iter, _mm256_and_pd(v_mask,
					_mm256_set1_pd(1.0)));
		dispatch_fractal(f, s);
		n++;
	}
}

void	calculate_iteration_simd(t_fractol *f, __m256d v_c_re,
		__m256d v_c_im, __m256d *v_iter)
{
	t_simd	s;

	s.v_c_im = v_c_im;
	s.v_c_re = v_c_re;
	s.v_iter = *v_iter;
	s.v_z_im = _mm256_setzero_pd();
	s.v_z_re = _mm256_setzero_pd();
	init_z_vectors(f, &s);
	iterate_simd(f, &s);
	*v_iter = s.v_iter;
}
