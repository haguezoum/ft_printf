#include <unistd.h>
#include <stdarg.h>

int ft_strlen(char *str)
{
    int len = -1;
    while(str[++len]);
    return len;
}

int print_char(char c)
{
   return write(1, &c, 1);
}

int print_string(char *str)
{
    if(!str) return (print_string("(null)"));
    return write(1,str,ft_strlen(str));
}

int print_number(int num)
{
    int lenght = 0;
    if(num == -2147483648) return (print_string("-2147483648"));
    if(num <  0)
    {
        lenght += print_char('-');
        num *= -1;
    }
    if(num < 10)
       lenght += print_char(num + '0');
    else
    {
        lenght += print_number(num/10);
        lenght += print_number(num%10);
    }
    return lenght;
}

int print_hexa(unsigned int num)
{
    int lenght = 0;
    char *hexa = "0123456789abcdef";

    if(num < 16) lenght +=  print_char(hexa[num]);
    else
    {
        lenght += print_hexa(num/16);
        lenght += print_hexa(num%16);
    }
    return lenght;
}

int ft_printf(const char *s, ...)
{
    va_list ap;
    int len = 0;
    char *str = (char *)s;

    va_start(ap, s);
    while(*str)
    {
        if(*str == '%')
        {
            str++;
            if(*str == 's') len += print_string(va_arg(ap, char*));
            else if(*str == 'd') len += print_number(va_arg(ap, int));
            else if(*str == 'x') len += print_hexa(va_arg(ap, unsigned int));
        }
        else
           len +=  print_char(*str);
        str++;
    }
    va_end(ap);
    return len;
}