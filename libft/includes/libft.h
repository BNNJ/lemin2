/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:36:43 by pfragnou          #+#    #+#             */
/*   Updated: 2018/05/17 01:16:03 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BUFF_SIZE 8
# define BINARY 0

# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stddef.h>
# include <stdint.h>

typedef struct			s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
	struct s_list	*prev;
	struct s_list	*start;
}						t_list;

typedef struct			s_string
{
	char		*content;
	size_t		len;
}						t_string;

/*
** reader struct for get_next_line
*/

typedef struct			s_file_rd
{
	int					fd;
	long long			rd_len;
	t_string			*string;
	struct s_file_rd	*next;
	struct s_file_rd	*start;
}						t_file_rd;

/*
** used in ft_get_stdin
*/

# define GSTD_BUFSIZ 1024

typedef struct			s_stdbuf
{
	size_t			size;
	struct s_stdbuf	*next;
	char			buf[GSTD_BUFSIZ];
}						t_stdbuf;

/*
** math stuff
*/

# define RAD M_PI / 180
# define DEG 180 / M_PI

typedef struct			s_point
{
	int		x;
	int		y;
}						t_point;

typedef struct			s_vec3
{
	double	x;
	double	y;
	double	z;
}						t_vec3;

typedef struct			s_vec4
{
	double	x;
	double	y;
	double	z;
	double	w;
}						t_vec4;

typedef struct			s_mat4
{
	t_vec4	x;
	t_vec4	y;
	t_vec4	z;
	t_vec4	w;
}						t_mat4;

typedef struct			s_qtr
{
	t_vec3	v;
	double	w;
}						t_qtr;

void					*ft_memset(void *s, int c, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst, const void *src, int c,
	size_t n);
void					*ft_memmove(void *dst, const void *src, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);

int						ft_atoi(const char *str);
int						ft_strtoi(char **str);
char					*ft_itoa(int n);
char					*ft_lltoa_base(long long int n, char base_len, char opt,
	int pad);
char					*ft_ulltoa_base(unsigned long long n, char base_len,
	char opt, int pad);

size_t					ft_strlen(const char *s);
size_t					ft_strlen_s(const char *s);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strnstr(const char *haystack, const char *needle,
	size_t len);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strdup(const char *s1);
char					*ft_strdup_s(const char *s1);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strncpy(char *dst, const char *src, size_t n);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strncat(char *s1, const char *s2, size_t n);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strjoin_f(char *s1, char *s2, int opt);
char					*ft_strtrim(char const *s);
int						get_next_line(int fd, char **line);
int						ft_findchar(char *str, char c);
char					*ft_strchrs(const char *s, int c);
char					*ft_strchrsp(const char *s, int c);

int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);

char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s,
	char (*f)(unsigned int, char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strsub_f(char *s, unsigned int start, size_t len);
char					*ft_strsub(char const *s, unsigned int start,
	size_t len);
char					**ft_strsplit(char const *s, char c);

void					ft_putchar(char c);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr(char const *s);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl(char const *s);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr(int n);
void					ft_putnbr_fd(int n, int fd);
void					ft_print_addr(const void *ptr);

t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstdelone(t_list **alst, void(*del)(void *, size_t));
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

t_string				*ft_tstr_new(size_t size);
void					ft_tstr_del(t_string **str);
void					ft_tstr_clr(t_string *str);
int						ft_tstr_cmp(const t_string *s1, const t_string *s2);
int						ft_tstr_eq(const t_string *s1, const t_string *s2);
t_string				*ft_tstr_dup(t_string *s1);
t_string				*ft_tstr_sub(t_string *s, size_t start,
	size_t len, int f);
t_string				*ft_tstr_join(t_string *s1, t_string *s2, int opt);
char					*ft_tstr_to_str(t_string *str);
void					ft_tstr_print(t_string *str);
int						ft_tstr_findchar(t_string *str, char c);

/*
** math
** vectors, matrices && quaternions
*/

t_vec3					ft_vec3_new(const double x, const double y,
	const double z);
t_qtr					ft_vec3_to_qtr(const t_vec3 *v, const double angle);
void					ft_vec3_norm(t_vec3 *v);
double					ft_vec3_len(const t_vec3 *v);
double					ft_vec3_angle(const t_vec3 *v1, const t_vec3 *v2);
t_vec3					ft_vec3_add(const t_vec3 *v1, const t_vec3 *v2);
t_vec3					ft_vec3_sub(const t_vec3 *v1, const t_vec3 *v2);
double					ft_vec3_scalprod(const t_vec3 *v1, const t_vec3 *v2);
t_vec3					ft_vec3_crossprod(const t_vec3 *v1, const t_vec3 *v2);
t_vec3					ft_vec3_by_scalar(const t_vec3 *v, const double s);

t_qtr					ft_qtr_new(const double x, const double y,
	const double z, const double w);
void					ft_qtr_norm(t_qtr *q);
double					ft_qtr_len(const t_qtr *q);
t_qtr					ft_qtr_add(const t_qtr *q1, const t_qtr *q2);
t_qtr					ft_qtr_sub(const t_qtr *q1, const t_qtr *q2);
t_qtr					ft_qtr_mult(const t_qtr *q1, const t_qtr *q2);
t_qtr					ft_qtr_by_scalar(const t_qtr *q1, const double s);
t_qtr					ft_qtr_conj(const t_qtr *q);
t_qtr					ft_qtr_invert(const t_qtr *q);
t_vec3					ft_qtr_rotate(const t_vec3 *p,
	const t_vec3 *axis, const double angle);
double					ft_qtr_scalprod(t_qtr *q1, t_qtr *q2);

t_vec4					ft_vec4_by_mat4(t_vec4 *v, t_mat4 *m);
t_vec4					ft_vec4_by_scalar(const t_vec4 *v, const double s);
double					ft_vec4_len(const t_vec4 *v);
double					ft_vec4_scalprod(const t_vec4 *v1, const t_vec4 *v2);

t_mat4					ft_mat4_rotx(double angle);
t_mat4					ft_mat4_roty(double angle);
t_mat4					ft_mat4_rotz(double angle);
t_mat4					ft_mat4_scale(double x, double y, double z);
t_mat4					ft_mat4_trslt(double x, double y, double z);

#endif
