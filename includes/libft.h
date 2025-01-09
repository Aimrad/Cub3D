/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:53:49 by gtoure            #+#    #+#             */
/*   Updated: 2024/11/04 18:36:40 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <string.h>
# include <assert.h>
# include <fcntl.h>
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

long			ft_atoi_lib(const char *nptr);
void			ft_bzero_lib(void *s, size_t n);
void			*ft_calloc_lib(size_t size, size_t nmemb);
int				ft_isalnum_lib(int c);
int				ft_isalpha_lib(int c);
int				ft_isdigit_lib(int c);
int				ft_isascii_lib(int c);
int				ft_isprint_lib(int c);
char			*ft_itoa_lib(long nbr);
void			*ft_memchr_lib(const void *s, int c, size_t n);
int				ft_memcmp_lib(const void *s1, const void *s2, size_t n);
void			*ft_memcpy_lib(void *dst, const void *src, size_t n);
void			*ft_memmove_lib(void *dest, const void *src, size_t n);
void			*ft_memset_lib(void *s, int c, size_t n);
void			ft_putchar_fd_lib(char c, int fd);
void			ft_putendl_fd_lib(char *s, int fd);
void			ft_putnbr_fd_lib(int n, int fd);
void			ft_putstr_fd_lib(char *s, int fd);
char			**ft_split_lib(char const *s, char c);
char			*ft_strchr_lib(const char *s, int c);
char			*ft_strdup_lib(const char *s);
void			ft_striteri_lib(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin_lib(const char *s1, const char *s2);
size_t			ft_strlcat_lib(char *dst, const char *src, size_t size);
size_t			ft_strlcpy_lib(char *dst, const char *src, size_t size);
size_t			ft_strlen_lib(const char *s);
char			*ft_strmapi_lib(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp_lib(const char *s1, const char *s2, size_t n);
char			*ft_strstr_lib(const char *haystack, const char *needle);
char			*ft_strrchr_lib(const char *s, int c);
char			*ft_strtrim_lib(char const *s1, char const *set);
char			*ft_substr_lib(char const *s, unsigned int start, size_t len);
int				ft_tolower_lib(int c);
int				ft_toupper_lib(int c);
t_list			*ft_lstnew_lib(void *content);
void			ft_lstadd_front_lib(t_list **lst, t_list *new);
int				ft_lstsize_lib(t_list *lst);
t_list			*ft_lstlast_lib(t_list *lst);
void			ft_lstadd_back_lib(t_list **lst, t_list *new);
void			ft_lstdelone_lib(t_list *lst, void (*del)(void*));
void			ft_lstclear_lib(t_list **lst, void (*del)(void*));
void			ft_lstiter_lib(t_list *lst, void (*f)(void *));

#endif
