/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:13:41 by miouali           #+#    #+#             */
/*   Updated: 2026/02/26 16:32:02 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init(t_fractol *f)
{
	f ->pixel_y = 0;
	f ->pixel_x = 0;
	f -> real_factor = (f->max_real_window - f->min_real_window) / WIN_WIDTH;
	f -> imaginary_factor = (f->min_imaginary_window - f->max_imaginary_window)
		/ WIN_HEIGHT;
}
