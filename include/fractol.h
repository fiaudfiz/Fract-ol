/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaudfiz <fiaudfiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:00:41 by miouali           #+#    #+#             */
/*   Updated: 2026/09/30 16:47:20 by fiaudfiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1000
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 32
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1000
# endif

# ifndef MAX_ITER
#  define MAX_ITER 300
# endif

# define TILE_SIZE 32
# define TILES_X ((WIN_WIDTH + TILE_SIZE - 1) / TILE_SIZE)
# define TILES_Y ((WIN_HEIGHT + TILE_SIZE - 1) / TILE_SIZE)
# define NB_TILES (TILES_X * TILES_Y)
# define NB_THREADS 12

# include <stddef.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <strings.h>
# include <limits.h>
# include <stdarg.h>
# include <math.h>
# include "../libs/mlx-linux/mlx.h"
# include <immintrin.h>
# include <pthread.h>

typedef struct s_render	t_render;
typedef struct s_pool		t_pool;

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	double	min_real_window;
	double	max_real_window;
	double	min_imaginary_window;
	double	max_imaginary_window;
	double	julia_real_pixel;
	double	julia_imaginary_pixel;
	double	real_factor;
	double	imaginary_factor;
	double	temp_real;
	double	pixel_real;
	double	pixel_imaginary;
	double	c_real;
	double	c_imaginary;
	double	z_real;
	double	z_imaginary;
	double	equation;
	double	offset;
	double	old_real;
	double	old_imaginary;
	double	init_min_re;
	double	init_max_re;
	double	init_min_im;
	double	init_max_im;
	int		mouse_pressed;
	int		last_x;
	int		last_y;
	int		color_offset;
	int		max_iteration;
	int		type_of_fractal;
	int		iteration;
	int		pixel_x;
	int		pixel_y;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		period;
	int		palette[MAX_ITER];
	int		dx;
	int		dy;
	t_render *render;
	t_pool *pool;
}			t_fractol;

typedef struct s_simd
{
	__m256d		v_z_re;
	__m256d		v_z_im;
	__m256d		v_c_re;
	__m256d		v_c_im;
	__m256d		v_iter;
}		t_simd;

typedef struct s_tile
{
	int x0;
	int	y0;
	int	xf;
	int	yf;
	int	index;
	t_render *render;
}t_tile;

typedef struct s_render
{
	t_tile tiles[NB_TILES];
	t_fractol *fractol;
	int pending;
	pthread_mutex_t mutex_render;
	pthread_cond_t	cond_pending;
}t_render;


//parsing
void	parse_args(int argc, char **argv, t_fractol *f);
void	prog_usage(void);

//init
void	init(t_fractol *f);
int		init_fractol(t_fractol *f);

//handler key&mouse
int		key_handler(int key, t_fractol *f);
int		close_handler(t_fractol *f);
int		mouse_handler(int button, int x, int y, t_fractol *f);
int		handle_expose(t_fractol *f);
int		motion_handler(int x, int y, t_fractol *f);
int		mouse_release(int button, int x, int y, t_fractol *f);

//color
void	init_palette(t_fractol *f);
void	put_color(t_fractol *f, int *pixel_ptr);
void	put_color_thread(t_fractol *f, int *pixel_ptr, int iteration);

//calculate fractal
void	calculate_iteration_simd(t_fractol *f, __m256d v_c_re, __m256d v_c_im,
			__m256d *v_iter);
void	render_fractal_simd(t_fractol *f);

//Fractals
void	compute_mandelbrot(t_simd *s);
void	compute_celtic(t_simd *s);
void	compute_tricorn(t_simd *s);
void	compute_burning_ship(t_simd *s);

void	render_init(t_render *render, t_fractol *f);
void	render_frame(t_render *render, t_pool *pool);
void	render_tile(void *arg);
void	benchmark_pool(t_fractol *f, int nb_frames);
void	handle_zoom(int button, int x, int y, t_fractol *f);
void	apply_zoom(t_fractol *f, double mouse_re,
		double mouse_im, double zoom_factor);

#endif
