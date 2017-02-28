#include "ft_ls.h"

int		alpha_cmp(t_elem *elem1, t_elem *elem2)
{
	if (ft_strcmp(elem1->name, elem2->name) > 0)
		return (0);
	if (ft_strcmp(elem1->name, elem2->name) == 0)
		return (time_cmp(elem1, elem2));
	return (1);
}

int		alpha_cmp_rev(t_elem *elem1, t_elem *elem2)
{
	if (ft_strcmp(elem1->name, elem2->name) < 0)
		return (0);
	if (ft_strcmp(elem1->name, elem2->name) == 0)
		return time_cmp_rev(elem1, elem2);
	return (1);
}

int		time_cmp(t_elem *elem1, t_elem *elem2)
{
	if (elem1->mtime < elem2->mtime)
		return (0);
	if (elem1->mtime == elem2->mtime && elem1->mtime_nsec < elem2->mtime_nsec)
		return (0);
	if (elem1->mtime == elem2->mtime && elem1->mtime_nsec == elem2->mtime_nsec)
		return (alpha_cmp(elem1, elem2));
	return (1);
}

int		time_cmp_rev(t_elem *elem1, t_elem *elem2)
{
	if (elem1->mtime > elem2->mtime)
		return (0);
	if (elem1->mtime == elem2->mtime && elem1->mtime_nsec > elem2->mtime_nsec)
		return (0);
	if (elem1->mtime == elem2->mtime && elem1->mtime_nsec == elem2->mtime_nsec)
		return (alpha_cmp_rev(elem1, elem2));
	return (1);
}
