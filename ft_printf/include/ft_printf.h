/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 12:37:25 by pfragnou          #+#    #+#             */
/*   Updated: 2018/06/27 12:37:27 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define LINUX_MODE 0
# define COLOR_ENABLED 1
# define BUFFSIZE 128

# ifndef UINTMAX_WIDTH
#  define UINTMAX_WIDTH sizeof(uintmax_t) * 8
# endif

# define UCBASE "0123456789ABCDEF"
# define LCBASE "0123456789abcdef"

# define F_ZERO 1
# define F_HASH 2
# define F_PLUS 4
# define F_MINUS 8
# define F_SPACE 16
# define F_BIN 32
# define F_DISPLAY 64

# define F_WIDTH 128
# define F_PRECI 256

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <wchar.h>
# include <stdint.h>
# include <fcntl.h>

typedef struct	s_buf
{
	char		content[BUFFSIZE];
	int			cursor;
	char		**str;
	char		strmode;
	int			fd;
	size_t		size;
	int			ret;
}				t_buf;

typedef struct	s_par
{
	int			flags;
	size_t		width;
	size_t		precision;
	char		type;
	char		prefix[3];
	int			base;
	enum
	{
		H,
		HH,
		NONE,
		L,
		LL,
		Z,
		J
	}			e_mod;
}				t_par;

typedef int		(*t_fct)(t_par*, va_list, t_buf*);

/*
** ftpf_printf.c
*/

int				ft_printf(const char *format, ...);
int				ft_dfprintf(int fd, const char *format, va_list ap);
int				ft_dprintf(int fd, const char *format, ...);

/*
** ftpf_sprintf.c
*/

int				ft_asprintf(char **str, const char *format, ...);
int				ft_sprintf(char *str, const char *format, ...);
int				ft_snprintf(char *str, size_t size, const char *format, ...);

/*
** parser.c
*/

int				ftpf_groundcontrol(const char *format, va_list ap, t_buf *buf);

/*
** parser_flags.c
*/

void			ftpf_get_flags(t_par *p, const char **format, va_list ap);
void			ftpf_get_format_flag(t_par *p, const char **format);
void			ftpf_get_width(t_par *p, const char **format, va_list ap);
void			ftpf_get_precision(t_par *p, const char **format, va_list ap);
void			ftpf_get_size_flag(t_par *par, const char **format);
void			ftpf_get_type(t_par *p, const char **format);

/*
** handler_buffer.c
*/

void			ftpf_buffer_flush(t_buf *buf);
int				ftpf_buffer_literal(const char *str, t_buf *buf);
void			ftpf_buffer_copy(const char *str, t_buf *buf, int precision);
void			ftpf_buffer_fill(t_buf *buf, char c, size_t size);

/*
** handler_display.c
*/

int				ftpf_handle_display(const char **format, t_buf *buf, int len);

/*
** handler_char.c
*/

int				ftpf_convert_wchar(wchar_t c, char *str);
int				ftpf_handle_wchar(t_par *p, va_list ap, t_buf *buf);
int				ftpf_handle_char(t_par *p, va_list ap, t_buf *buf);
char			ftpf_wchar_len(wchar_t c);

/*
** handler_str.c
*/

int				ftpf_handle_wstr(t_par *p, va_list ap, t_buf *buf);
int				ftpf_handle_str(t_par *p, va_list ap, t_buf *buf);

/*
** handler_int.c
*/

int				ftpf_handle_int(t_par *p, va_list ap, t_buf *buf);
void			ftpf_umaxtoa_base(uintmax_t nb, size_t len,
	t_par *p, t_buf *buf);

/*
** handler_float.c
*/

int				ftpf_handle_float(t_par *p, va_list ap, t_buf *buf);

/*
** handler_ptr.c
*/

int				ftpf_handle_ptr(t_par *p, va_list ap, t_buf *buf);
int				ftpf_handle_n(t_par *p, va_list ap, t_buf *buf);

/*
** handler_binflag.c
*/

int				ftpf_handle_bin(void *ptr, t_par *p, t_buf *buf);

/*
** handler_file.c
*/

int				ftpf_handle_file(t_par *p, va_list ap, t_buf *buf);

/*
** handler_array.c
*/

int				ftpf_handle_int_array(t_par *p, va_list ap, t_buf *buf);
int				ftpf_handle_str_array(t_par *p, va_list ap, t_buf *buf);

/*
** minilibft.c
*/

int				ftpf_atoi(const char *str);
void			*ftpf_memset(void *b, int c, size_t n);
int				ftpf_strlen(const char *str);
int				ftpf_findchar(const char *str, char c);
void			*ftpf_memcpy(void *dst, const void *src, size_t n);

#endif
