#include "fractol.h"
#include "../libs/libft/includes/libft.h"

static int	is_valid_double(char *str)
{
	int	has_dot;
	int	has_digit;

	has_dot = 0;
	has_digit = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else if (*str >= '0' && *str <= '9')
			has_digit = 1;
		else
			return (0);
		str++;
	}
	return (has_digit);
}

static void	set_julia(int argc, char **argv, t_fractol *f)
{
	f->type_of_fractal = 2;
	if (argc == 4)
	{
		if (!is_valid_double(argv[2]) || !is_valid_double(argv[3]))
		{
			ft_putstr_fd("Error: Julia arguments must be numbers.\n", 2);
			prog_usage();
		}
		f->julia_real_pixel = ft_atof(argv[2]);
		f->julia_imaginary_pixel = ft_atof(argv[3]);
	}
	else if (argc == 2)
	{
		f->julia_real_pixel = -0.4;
		f->julia_imaginary_pixel = 0.6;
	}
	else
	{
		ft_putstr_fd("Error: Julia needs 0 or 2 coordinates.\n", 2);
		prog_usage();
	}
}

void	parse_args(int argc, char **argv, t_fractol *f)
{
	if (argc < 2 || argc > 4)
		prog_usage();
	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 11))
		f->type_of_fractal = 1;
	else if (!ft_strncmp(argv[1], "julia", 6))
		set_julia(argc, argv, f);
	else if (argc == 2 && !ft_strncmp(argv[1], "burning_ship", 13))
		f->type_of_fractal = 3;
	else if (argc == 2 && !ft_strncmp(argv[1], "tricorn", 8))
		f->type_of_fractal = 4;
	else if (argc == 2 && !ft_strncmp(argv[1], "celtic", 7))
		f->type_of_fractal = 5;
	else
	{
		ft_putstr_fd("Error: Invalid fractal name or wrong arguments.\n", 2);
		prog_usage();
	}
}