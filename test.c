#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atol(const char *str, long *out)
{
	int		sign;
	long	result;
	int		i;

	sign = 1;
	result = 0;
	i = 0;
	while (ft_is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (ft_is_digit(str[i]))
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (-1);
		result = result * 10 + (str[i++] - '0');
	}
	*out = result * sign;
	return (0);
}

int	main(void)
{
	const char	*input = "9223372036854775808";
	long		value;
	int			status;

	status = ft_atol(input, &value);
	if (status == 0)
		printf("Değer: %ld\n", value);
	else
		printf("Hata: %d (taşma)\n", status);
	return (0);
}