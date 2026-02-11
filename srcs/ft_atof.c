#include "fractol.h"

double	ft_atof(char *s)
{
	double	res;
	double	div;
	int		sign;

	res = 0.0;
	sign = 1;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		res = res * 10.0 + (*s++ - '0');
	if (*s == '.')
	{
		s++;
		div = 10.0;
		while (*s >= '0' && *s <= '9')
		{
			res = res + (*s++ - '0') / div;
			div *= 10.0;
		}
	}
	return (res * sign);
}