#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

typedef struct s_struct
{
    int     minus;
    int     zero;
    int     sharp;
    char    exe;
    int     space;
    int     plus;
    int     point;
    int     width;
    int     precision;
    size_t  len;
    char    *dbase;
    char    *ebase;
    char    *e_base;
}               t_struct;

void    ft_strrev(char *str);
void    ft_printchar(char c, t_struct *params);
void    ft_printstr(char *str, t_struct *params);
void    ft_printnum(char *str, t_struct *params);
void    ft_struct_init(t_struct *params);
int     ft_checkidentifier(char c);
void    ft_utoa_base(unsigned long int n, char *base, t_struct *params, int a);
void    ft_itoa_base(long long n, char *base, t_struct *params);
int     ft_precision(const char *str, int i, t_struct *params);
void    ft_width(char ch, t_struct *params);
void    ft_print_params(t_struct *params);

#endif