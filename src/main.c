/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaudfiz <fiaudfiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:39:47 by miouali           #+#    #+#             */
/*   Updated: 2026/09/30 16:55:05 by fiaudfiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "pool.h"

int	main(int ac, char **av)
{
	t_fractol	f;
	t_render	render;
	t_pool		*pool;

	parse_args(ac, av, &f);
	if (!init_fractol(&f))
		return (1);
	init(&f);
	printf ("%d", get_nb_threads());
	pool = pool_create(get_nb_threads(), NB_TILES*2);
	if (!pool)
		return (1);
	render_init(&render, &f);
	f.render = &render;
	f.pool = pool;
	init_palette(&f);
	//benchmark_pool(&f, 5000);
	render_frame(&render, pool);
	mlx_put_image_to_window(f.mlx, f.win, f.img, 0, 0);
	mlx_hook(f.win, 2, 1L << 0, key_handler, &f);
	mlx_hook(f.win, 17, 0, close_handler, &f);
	mlx_hook(f.win, 12, 0, handle_expose, &f);
	mlx_hook(f.win, 4, 1L << 2, mouse_handler, &f);
	mlx_hook(f.win, 5, 1L << 3, mouse_release, &f);
	mlx_hook(f.win, 6, 1L << 6, motion_handler, &f);
	mlx_loop(f.mlx);
	pool_destroy(pool);
	return (0);
}
