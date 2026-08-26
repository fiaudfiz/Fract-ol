/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_simd_fractal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:34:17 by miouali           #+#    #+#             */
/*   Updated: 2026/02/26 16:37:41 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	compute_mandelbrot(t_simd *s)
{
	__m256d	new_im;
	__m256d	new_re;
	__m256d	z_re2;
	__m256d	z_im2;

	z_im2 = _mm256_mul_pd(s->v_z_im, s->v_z_im);
	z_re2 = _mm256_mul_pd(s->v_z_re, s->v_z_re);
	new_im = _mm256_add_pd(_mm256_mul_pd(_mm256_mul_pd(_mm256_set1_pd(2.0),
					s->v_z_re), s->v_z_im), s->v_c_im);
	new_re = _mm256_add_pd(_mm256_sub_pd(z_re2, z_im2), s->v_c_re);
	s->v_z_re = new_re;
	s->v_z_im = new_im;
}

void	compute_tricorn(t_simd *s)
{
	__m256d	new_im;
	__m256d	new_re;
	__m256d	z_re2;
	__m256d	z_im2;

	z_im2 = _mm256_mul_pd(s->v_z_im, s->v_z_im);
	z_re2 = _mm256_mul_pd(s->v_z_re, s->v_z_re);
	new_im = _mm256_add_pd(_mm256_mul_pd(_mm256_mul_pd(_mm256_set1_pd(-2.0),
					s->v_z_re), s->v_z_im), s->v_c_im);
	new_re = _mm256_add_pd(_mm256_sub_pd(z_re2, z_im2), s->v_c_re);
	s->v_z_re = new_re;
	s->v_z_im = new_im;
}

void	compute_celtic(t_simd *s)
{
	__m256d	new_im;
	__m256d	new_re;
	__m256d	z_re2;
	__m256d	z_im2;

	z_im2 = _mm256_mul_pd(s->v_z_im, s->v_z_im);
	z_re2 = _mm256_mul_pd(s->v_z_re, s->v_z_re);
	new_im = _mm256_add_pd(_mm256_mul_pd(_mm256_mul_pd(_mm256_set1_pd(2.0),
					s->v_z_re), s->v_z_im), s->v_c_im);
	new_re = _mm256_add_pd(_mm256_andnot_pd(_mm256_set1_pd(-0.0),
				_mm256_sub_pd(z_re2, z_im2)), s->v_c_re);
	s->v_z_re = new_re;
	s->v_z_im = new_im;
}

void	compute_burning_ship(t_simd *s)
{
	__m256d	new_im;
	__m256d	new_re;
	__m256d	z_re2;
	__m256d	z_im2;

	z_im2 = _mm256_mul_pd(s->v_z_im, s->v_z_im);
	z_re2 = _mm256_mul_pd(s->v_z_re, s->v_z_re);
	new_im = _mm256_add_pd(_mm256_or_pd(_mm256_set1_pd(-0.0),
				_mm256_mul_pd(_mm256_mul_pd(_mm256_set1_pd(2.0),
						s->v_z_re), s->v_z_im)), s->v_c_im);
	new_re = _mm256_add_pd(_mm256_andnot_pd(_mm256_set1_pd(-0.0),
				_mm256_sub_pd(z_re2, z_im2)), s->v_c_re);
	s->v_z_re = new_re;
	s->v_z_im = new_im;
}
