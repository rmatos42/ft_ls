#include "ft_ls.h"

void 	swap_list(t_list *l1, t_list *l2)
{
	t_elem *elem = l1->content;
	l1->content = l2->content;
	l2->content = elem;
}

void 	sort_list(t_list **list, int (*cmp)(t_elem *, t_elem *))
{
	int swap;
	int i;
	t_elem *elem1;
	t_elem *elem2;
	t_list *ptr1;

	swap = 1;
	while (swap)
	{
		swap = 0;
		ptr1 = *list;
		while (ptr1->next)
		{
			elem1 = ptr1->content;
			elem2 = ptr1->next->content;
			if (!cmp(elem1, elem2))
			{
				swap_list(ptr1, ptr1->next);
				swap = 1;
			}
			ptr1 = ptr1->next;
		}
	}
}
