#ifndef FT_LS_H
# define FT_LS_H

#include "libft.h"
#include <stdio.h>
#include <time.h>

typedef	struct	s_elem
{
	int			dir;
	t_list		*list;
	char		*name;
	char		*path;
	time_t		atime; //last access
	long		atime_nsec;
	time_t		mtime; //last modification
	long		mtime_nsec;
	time_t		ctime; //last status change
	long		ctime_nsec;
	int			nlink;
	int			size;
}				t_elem;

void 	sort_list(t_list **list, int (*f)(t_elem *, t_elem *));
int		alpha_cmp(t_elem *elem1, t_elem *elem2);
int		time_cmp(t_elem *elem1, t_elem *elem2);
int		alpha_cmp_rev(t_elem *elem1, t_elem *elem2);
int		time_cmp_rev(t_elem *elem1, t_elem *elem2);

#endif
