/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:35:45 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 10:04:17 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_reverse(char *str)
{
	int	index;

	index = ft_strlen(str) - 1;
	while (index >= 0)
	{
		write(1, &str[index], 1);
		index--;
	}
}

int	ft_check_base(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[i] == str[j] || str[j] == '+' || str[j] == '-')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_putnbr_base(int n, char *base)
{
	int		len_base;
	int		calc;
	char	*result;
	int		i;

	i = 0;
	calc = 0;
	if (ft_strlen(base) <= 1 || ft_check_base(base) == 1)
		return (0);
	len_base = ft_strlen(base);
	result = ft_calloc(sizeof(char), ft_size_base(n, len_base) + 1);
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n == 0)
		result[i++] = base[0];
	else
	{
		while (n > 0)
		{
			calc = n % len_base;
			result[i++] = base[calc];
			n /= len_base;
		}
	}
	result[i] = '\0';
	ft_reverse(result);
	free(result);
	return (ft_size_base(n, len_base));
}
