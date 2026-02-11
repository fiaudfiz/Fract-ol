/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:08:47 by miouali           #+#    #+#             */
/*   Updated: 2026/02/03 11:16:34 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*void	init_palette(t_fractol *f)
{
	int	i;

	i = -1;
	while (++i < MAX_ITER)
	{
		f->palette[i] = (i * 255 / MAX_ITER) << 16;
	}
}

void init_palette(t_fractol *f)
{
    int     i;
    double  t;

    i = -1;
    while (++i < MAX_ITER)
    {
        t = (double)i / MAX_ITER;
        int r = (int)(9 * (1 - t) * t * t * t * 255);
        int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
        int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
        f->palette[i] = (r << 16 | g << 8 | b);
    }
}*/

void	init_palette(t_fractol *f)
{
	int	i;

	i = -1;
	while (++i < MAX_ITER)
	{
		f->palette[i] = (i * 7 % 256) << 16 | (i * 3 % 256);
	}
}

