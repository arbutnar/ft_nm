/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbutnar <arbutnar@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 08:52:02 by arbutnar          #+#    #+#             */
/*   Updated: 2022/01/28 23:03:32 by arbutnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int g_fd = 1;

static void ft_identifier(char c, va_list arg, t_struct *params)
{
    if (c == 'c')
        ft_printchar(va_arg(arg, int), params);
    else if (c == 's')
        ft_printstr(va_arg(arg, char *), params);
    else if (c == 'p')
        ft_utoa_base(va_arg(arg, unsigned long int), params->ebase, params, 2);
    else if (c == 'd')
        ft_itoa_base(va_arg(arg, int), params->dbase, params);
    else if (c == 'i')
        ft_itoa_base(va_arg(arg, int), params->dbase, params);
    else if (c == 'u')
        ft_utoa_base(va_arg(arg, unsigned int), params->dbase, params, 0);
    else if (c == 'x')
        ft_utoa_base(va_arg(arg, unsigned int), params->ebase, params, 0);
    else if (c == 'X')
    {
        params -> exe = 'X';
        ft_utoa_base(va_arg(arg, unsigned int), params->e_base, params, 0);
    }
    else if (c == '%')
        ft_printchar('%', params);
}

static int ft_checkflags(const char *str, t_struct *params)
{
    int i;

    i = 0;
    while (ft_checkidentifier(str[i]) == 0)
    {
        if (str[i] == '-')
            params -> minus = 1;
        if (str[i] == '0' && params -> width == 0)
            params -> zero = 1;
        if (str[i] == '.')
            i = ft_precision(str, i + 1, params);
        if (ft_isdigit(str[i]) && params -> point == 0)
            ft_width(str[i], params);
        if (str[i] == '#')
            params -> sharp = 1;
        if (str[i] == ' ')
            params -> space = 1;
        if (str[i] == '+')
            params -> plus = 1;
        i++;
    }
    return (i);
}

int ft_printf(const char *str, ...)
{
    va_list     arg;
    t_struct    params;
    size_t      len;

    va_start(arg, str);
    len = 0;
    while (*str != '\0')
    {
        if (*str == '%')
        {
            ft_struct_init(&params);
            str += ft_checkflags(str + 1, &params);
            ft_identifier(*(str + 1), arg, &params);
            str++;
            len += params.len;
        }
        else
        {
            write(g_fd, str, 1);
            len++;
        }
        str++;
    }
    return (len);
}

int ft_dprintf(int fd, const char *str, ...)
{
    va_list     arg;
    t_struct    params;
    size_t      len;

    g_fd = fd;
    va_start(arg, str);
    len = 0;
    while (*str != '\0')
    {
        if (*str == '%')
        {
            ft_struct_init(&params);
            str += ft_checkflags(str + 1, &params);
            ft_identifier(*(str + 1), arg, &params);
            str++;
            len += params.len;
        }
        else
        {
            write (g_fd, str, 1);
            len++;
        }
        str++;
    }
    return (len);
}

/*int   main()
{
    //char  *s = "ciao";
    char    c;
    char    *str;
    int     nbr;
    int     pclen;
    int     mylen;

    c = '0';
    str = "ciao";
    nbr = 10;
    mylen = ft_printf(" %.1s %.2s %.3s %.4s ", " - ", "", "4", "");
    pclen = printf(" %.1s %.2s %.3s %.4s ", " - ", "", "4", "");
    printf("mylen = %d pclen: %d\n", mylen, pclen);
    //printf("pclen = %d\n", pclen);
}*/