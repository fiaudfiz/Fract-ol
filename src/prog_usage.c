/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:11:09 by miouali           #+#    #+#             */
/*   Updated: 2026/08/26 13:41:55 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "ft_printf.h"

void	prog_usage(void)
{
	ft_printf("Usage: ./fractol [fractal_name]\n");
	ft_printf("Available Fractals :\n");
	ft_printf("  mandelbrot    - Classic Mandelbrot set\n");
	ft_printf("  julia [re im] - Julia set (optional: real and "
		"imaginary parts)\n");
	ft_printf("  burning_ship  - Burning Ship fractal\n");
	ft_printf("  tricorn       - Tricorn fractal\n");
	ft_printf("  celtic        - Celtic Mandelbrot\n");
	ft_printf("\n💡 Tips:\n");
	ft_printf("  • Use mouse wheel to zoom in/out\n");
	ft_printf("  • Uses arrows to navigate\n");
	ft_printf("  • Use drag mouse to navigate\n");
	ft_printf("  • Use C to change colors\n");
	ft_printf("  • Uses R to reset view\n");
	ft_printf("  • Press ESC to exit\n");
	exit(1);
}
