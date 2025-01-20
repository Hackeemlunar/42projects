#include "ft_printf.h"

void	printstruct(t_modinfo *info)
{
	printf("    Flags: %s\n", info->flags);
	printf("    width: %d\n", info->width);
	printf("   Specif: %c\n", info->specifier);
	printf("precision: %d\n", info->precision);
    printf("    count: %d\n", info->flags_count);
    printf("\n");
}

void reset_modinfo(t_modinfo *modinfo) {
    memset(modinfo, 0, sizeof(t_modinfo)); 
}

int main()
{
    t_modinfo modinfo;    

    char *fmt = "Hello, \n%-+ 0##50.454s%-#323.3d%%\n!!!\n";
    while (*fmt != '\0')
    {
        if (*fmt == '%')
        {
            parse_format(fmt + 1, &modinfo);
            printstruct(&modinfo);
            fmt += modinfo.flags_count;
            reset_modinfo(&modinfo);
        }
        else
            printf("%c", *fmt);
        fmt++;
    }
    return 0;
}
