/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:25:41 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/12 22:43:16 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "ft_printf.h"

// int mult(int count, ...) {
//     va_list args;
//     va_start(args, count);
//     va_arg(args, int);
//     va_end(args);
// }

int	main(int argc, char **argv)
{
	argc += 0;
	// ft_printf("  Mine: % +020.20hhd\n", 10);
	printf("  Mine: % +020.20hhd\n", 'a');
	printf("System: %+20.20ld kjlhoih\n", 1000000000000000);
	return (0);
}

// int main()
// {
//     t_fdata *data;
//     char *str;

//     data = convert_num(12323456786LL, 10, 'a');  // Use long long literal
//     str = data->fstring;
//     printf("  Mine: %s\n", str);
//     printf("Printf: %lld\n", 12323456786LL);  // Use %lld for long long
//     free(data);

//     data = convert_num(12323456786LL, 16, 'a');
//     str = data->fstring;
//     printf("  Mine: %s\n", str);
//     printf("Printf: %llx\n", 12323456786LL);
//     free(data);

//     data = convert_num(12323456786LL, 8, 'a');
//     str = data->fstring;
//     printf("  Mine: %s\n", str);
//     printf("Printf: %llo\n", 12323456786LL);
//     free(data);

//     data = convert_num(12323456786LL, 2, 'a');
//     str = data->fstring;
//     printf("  Mine: %s\n", str);
//     printf("Printf: %lld\n", 12323456786LL);
//     free(data);

//     data = convert_num(-12323456786LL, 10, 'a');
//     str = data->fstring;
//     printf("  Mine: %s\n", str);
//     printf("Printf: %lld\n", -12323456786LL);
//     free(data);

//     data = convert_num(-12323456786LL, 16, 'A');
//     str = data->fstring;
//     printf("  Mine: %s\n", str);
//     printf("Printf: %llX\n", -12323456786LL);
//     free(data);

//     data = convert_num(-12323456786LL, 8, 'a');
//     str = data->fstring;
//     printf("  Mine: %s\n", str);
//     printf("Printf: %llo\n", -12323456786LL);
//     free(data);

//     data = convert_num(-12323456786LL, 2, 'a');
//     str = data->fstring;
//     printf("  Mine: %s\n", str);
//     printf("Printf: %lld\n", -12323456786LL);
//     free(data);

//     return 0;
// }

// // Test Function
// int main() {
//     char a = -42;
//     short b = 255;
//     int c = -123456;
//     unsigned int d = 123456789;
//     long e = -987654321;
//     unsigned long f = 4294967295;
//     long long g = -9223372036854775807LL;
//     unsigned long long h = 18446744073709551615ULL;

//     t_fdata *data;

//     // Test cases for different types
//     data = convert_num_generic(&a, 10, 'a', true, sizeof(a));
//     printf("Decimal (char): %s\n", data->fstring);
//     free(data);

//     data = convert_num_generic(&b, 16, 'a', false, sizeof(b));
//     printf("Hex (short): %s\n", data->fstring);
//     free(data);

//     data = convert_num_generic(&c, 8, 'a', true, sizeof(c));
//     printf("Octal (int): %s\n", data->fstring);
//     free(data);

//     data = convert_num_generic(&d, 2, 'a', false, sizeof(d));
//     printf("Binary (unsigned int): %s\n", data->fstring);
//     free(data);

//     data = convert_num_generic(&e, 10, 'a', true, sizeof(e));
//     printf("Decimal (long): %s\n", data->fstring);
//     free(data);

//     data = convert_num_generic(&f, 16, 'A', false, sizeof(f));
//     printf("Hex (unsigned long): %s\n", data->fstring);
//     free(data);

//     data = convert_num_generic(&g, 10, 'a', true, sizeof(g));
//     printf("Decimal (long long): %s\n", data->fstring);
//     free(data);

//     data = convert_num_generic(&h, 2, 'a', false, sizeof(h));
//     printf("Binary (unsigned long long): %s\n", data->fstring);
//     free(data);

//     return 0;
// }