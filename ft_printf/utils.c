#include "ft_printf.h"

static char	*convert_number(unsigned long n, int base, int is_negative, int upc)
{
	char	temp[21];
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (n > 0)
	{
        if (n % base < 10)
            temp[i++] = n % base + '0';
        else
            if (upc)
                temp[i++]  = n % base - 10 + 'A';
            else
                temp[i++]  = n % base - 10 + 'a';
        n /= base;
	}
	res = (char *)malloc(i + is_negative + 1);
	if (!res)
		return (NULL);
	if (is_negative)
		res[j++] = '-';
	while (i > 0)
		res[j++] = temp[--i];
	res[j] = '\0';
	return (res);
}

char	*ft_itoa_base(long nbr, int base, int uppercase)
{
    unsigned long    n;
	int		is_negative;

	is_negative = 0;
    if (nbr == 0)
        return (ft_strdup("0"));
    if (nbr < 0 && base == 10)
    {
        is_negative = 1;
        n = -nbr;
    }
    else
    {
		n = nbr;
	}
	return (convert_number(n, base, is_negative, uppercase));   
}

void	ft_putstr_pf(t_fdata *data)
{
    int	i;

    i = 0;
    while (i < data->count)
    {
        write(1, &data->fstring[i], 1);
        i++;
    }
}

void	apply_prefix(char **fstring, const char *prefix, t_fdata *fdata)
{
	char	*new_string;
    size_t  len;

    len = ft_strlen(prefix);
	new_string = malloc(fdata->count + len + 1);
	if (!new_string)
		return ;
	ft_strcpy(new_string, prefix);
	ft_strcat(new_string, *fstring);
	free(*fstring);
	*fstring = new_string;
	fdata->fstring = new_string;
	fdata->count += len;
}
