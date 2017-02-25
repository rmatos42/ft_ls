#include "libft.h"
#include "get_next_line.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include "ft_ls.h"

int 	is_dir(char *path)
{
	struct stat statbuf;
	if (stat(path, &statbuf) != 0)
		return (0);
	if (statbuf.st_mode & S_IFDIR)
		return (1);
	else
		return (0);
}


// void 	print_files(char *path)
// {
// 	DIR *dir;
// 	char	*new_path;
// 	struct dirent *ent;
//
// 	if ((dir=opendir(path)) != NULL)
// 	{
// 		while ((ent = readdir(dir)) != NULL)
// 		{
// 			new_path = ft_strjoin(path, "/");
// 			new_path = ft_strjoin(new_path, ent->d_name);
// 			if (is_dir(new_path) && !ft_strequ(ent->d_name, ".") && !ft_strequ(ent->d_name, ".."))
// 			{
// 				printf("\n%s\n", ent->d_name);
// 				print_files(new_path);
// 				free(new_path);
// 			}
// 			else
// 				printf("%s\n", ent->d_name);
// 		}
// 		closedir(dir);
// 	}
// }

t_elem	*make_elem(char *path)
{
	t_elem	*elem;

	elem = (t_elem *)ft_memalloc(sizeof(t_elem));
	elem->dir = is_dir(path);
	elem->path = path;
	elem->name = ft_strsplit(path, '/')[get_count(path, '/') - 1];
	return (elem);
}

t_list	*print_files(char *path)
{
	DIR				*dir;
	char			*new_path;
	struct dirent	*ent;
	t_elem			*elem;
	t_list			*lst;

	if ((dir = opendir(path)) != NULL)
	{
		if ((ent = readdir(dir)) != NULL)
		{
			new_path = ft_strjoin(path, "/");
			new_path = ft_strjoin(new_path, ent->d_name);
			elem = make_elem(new_path);
			if (elem->dir && !ft_strequ(ent->d_name, ".") && !ft_strequ(ent->d_name, ".."))
				elem->list = print_files(elem->path);
			lst = ft_lstnew(elem, sizeof(elem));
		}
		while ((ent = readdir(dir)) != NULL)
		{
			new_path = ft_strjoin(path, "/");
			new_path = ft_strjoin(new_path, ent->d_name);
			elem = make_elem(new_path);
			ft_lstadd(&lst, ft_lstnew(elem, sizeof(elem)));
			if (elem->dir && !ft_strequ(ent->d_name, ".") && !ft_strequ(ent->d_name, ".."))
				elem->list = print_files(elem->path);
		}
		closedir(dir);
	}
	return (lst);
}

void 	print_list(t_list *list)
{
	t_list 	*list_tmp;
	t_elem	*elem;

	list_tmp = list;
	while (list)
	{
		elem = list->content;
		if (!ft_strequ(elem->name, ".") && !ft_strequ(elem->name, "..") && elem->name[0] != '.')
			printf("%s ", elem->name);
		list = list->next;
	}
	printf("\n\n");
	list = list_tmp;
	while (list)
	{
		elem = list->content;
		if (elem->dir && !ft_strequ(elem->name, ".") && !ft_strequ(elem->name, "..") && elem->name[0] != '.')
		{
			printf("%s:\n", elem->path);
			print_list(elem->list);
		}
		list = list->next;
	}
}

int		main(int argc, char **argv)
{
	t_list *lst = print_files(".");
	print_list(lst);

}
