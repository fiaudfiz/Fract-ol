/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:39:47 by miouali           #+#    #+#             */
/*   Updated: 2026/03/03 10:57:42 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fractol	f;

	parse_args(ac, av, &f);
	if (!init_fractol(&f))
		return (1);
	init_palette(&f);
	render_fractal_simd(&f);
	mlx_put_image_to_window(f.mlx, f.win, f.img, 0, 0);
	mlx_hook(f.win, 2, 1L << 0, key_handler, &f);
	mlx_hook(f.win, 17, 0, close_handler, &f);
	mlx_hook(f.win, 12, 0, handle_expose, &f);
	mlx_hook(f.win, 4, 1L << 2, mouse_handler, &f);
	mlx_hook(f.win, 5, 1L << 3, mouse_release, &f);
	mlx_hook(f.win, 6, 1L << 6, motion_handler, &f);
	mlx_loop(f.mlx);
	return (0);
}
