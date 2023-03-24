#include "../ft_minishell.h"

int	ft_itoa_len(int n)
{
	int			len;
	long int	nbr;

	nbr = n;
	len = 0;
	if (nbr < 0)
	{
		len++;
		nbr = nbr * (-1);
	}
	while (nbr >= 10)
	{
		nbr = nbr / 10;
		len++;
	}
	len++;
	return (len);
}

char	*ft_itoa(int n)
{
	char		*dest;
	int			len;
	long int	nbr;

	nbr = n;
	len = ft_itoa_len(n);
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	dest[len--] = '\0';
	if (nbr < 0)
	{
		nbr = -nbr;
		dest[0] = '-';
	}
	while (nbr >= 10)
	{
		dest[len--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	dest[len--] = nbr + '0';
	return (dest);
}