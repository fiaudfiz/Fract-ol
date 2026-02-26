/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:08:47 by miouali           #+#    #+#             */
/*   Updated: 2026/02/15 15:00:13 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_palette(t_fractol *f)
{
	int	i;

	i = -1;
	while (++i < MAX_ITER)
	{
		f->palette[i] = ((i + f->color_offset) * 7 % 256) << 16 | ((i + f->color_offset) * 3 % 256);
	}
}

void	put_color(t_fractol *f, int *pixel_ptr)
{
	if (f->iteration == f->max_iteration)
		*pixel_ptr = 0x000000;
	else
		*pixel_ptr = f->palette[f->iteration % MAX_ITER];
}
