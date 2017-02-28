#include "libft.h"
#include "get_next_line.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include "ft_ls.h"

int 	is_dir(char *path)
{
	struct stat buff;
	if (stat(path, &buff) != 0)
		return (0);
	if (buff.st_mode & S_IFDIR)
		return (1);
	else
		return (0);
}

time_t	get_atime(char *path)
{
	struct stat buff;
	if (stat(path, &buff) != 0)
		return (0);
	return (buff.st_atime);
}

time_t	get_mtime(char *path)
{
	struct stat buff;
	if (stat(path, &buff) != 0)
		return (0);
	return (buff.st_mtime);
}

time_t	get_ctime(char *path)
{
	struct stat buff;
	if (stat(path, &buff) != 0)
		return (0);
	return (buff.st_ctime);
}

long	get_atime_nsec(char *path)
{
	struct stat buff;
	if (stat(path, &buff) != 0)
		return (0);
	return (buff.st_atimespec.tv_nsec);
}

long	get_mtime_nsec(char *path)
{
	struct stat buff;
	if (stat(path, &buff) != 0)
		return (0);
	return (buff.st_mtimespec.tv_nsec);
}

long	get_ctime_nsec(char *path)
{
	struct stat buff;
	if (stat(path, &buff) != 0)
		return (0);
	return (buff.st_ctimespec.tv_nsec);
}

int		get_link_count(char *path)
{
	struct stat buff;
	if (stat(path, &buff) != 0)
		return (0);
	return buff.st_nlink;
}

int		get_size(char *path)
{
	struct stat buff;
	if (stat(path, &buff) != 0)
		return (0);
	return buff.st_size;
}

char	*get_permissions(char *path)
{
	char	*result;
	struct stat	buff;

	result = (char *)ft_memalloc(sizeof(char) * 11);
	if (stat(path, &buff) != 0)
		return (0);
	result[0] = is_dir(path) ? 'd' : '-';
	result[1] = (buff.st_mode & S_IRUSR) ? 'r' : '-';
	result[2] = (buff.st_mode & S_IWUSR) ? 'w' : '-';
	result[3] = (buff.st_mode & S_IXUSR) ? 'x' : '-';
	result[4] = (buff.st_mode & S_IRGRP) ? 'r' : '-';
	result[5] = (buff.st_mode & S_IWGRP) ? 'w' : '-';
	result[6] = (buff.st_mode & S_IXGRP) ? 'x' : '-';
	result[7] = (buff.st_mode & S_IROTH) ? 'r' : '-';
	result[8] = (buff.st_mode & S_IWOTH) ? 'w' : '-';
	result[9] = (buff.st_mode & S_IXOTH) ? 'x' : '-';
	result[10] = '\0';
	return (result);
}

t_elem	*make_elem(char *path)
{
	t_elem	*elem;

	elem = (t_elem *)ft_memalloc(sizeof(t_elem));
	elem->dir = is_dir(path);
	elem->path = path;
	elem->name = ft_strsplit(path, '/')[get_count(path, '/') - 1];
	elem->atime = get_atime(path);
	elem->atime_nsec = get_atime_nsec(path);
	elem->mtime = get_mtime(path);
	elem->mtime_nsec = get_mtime_nsec(path);
	elem->ctime = get_ctime(path);
	elem->ctime_nsec = get_ctime_nsec(path);
	elem->nlink = get_link_count(path);
	elem->size = get_size(path);
	return (elem);
}

t_list	*file_list(char *path)
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
				elem->list = file_list(elem->path);
			lst = ft_lstnew(elem);
		}
		while ((ent = readdir(dir)) != NULL)
		{
			new_path = ft_strjoin(path, "/");
			new_path = ft_strjoin(new_path, ent->d_name);
			elem = make_elem(new_path);
			ft_lstadd(&lst, ft_lstnew(elem));
			if (elem->dir && !ft_strequ(ent->d_name, ".") && !ft_strequ(ent->d_name, ".."))
				elem->list = file_list(elem->path);
		}
		closedir(dir);
	}
	sort_list(&lst, alpha_cmp);
	return (lst);
}

void 	print_recursive(t_list *list)
{
	t_list 	*list_tmp;
	t_elem	*elem;

	list_tmp = list;
	while (list)
	{
		elem = list->content;
		// if (!ft_strequ(elem->name, ".") && !ft_strequ(elem->name, "..") && elem->name[0] != '.')
		printf("%s %i %i:%s:%s", get_permissions(elem->path), elem->nlink, elem->size, elem->name, ctime(&elem->mtime));
		list = list->next;
	}
	printf("\n");
	list = list_tmp;
	while (list)
	{
		elem = list->content;
		if (elem->dir && !ft_strequ(elem->name, ".") && !ft_strequ(elem->name, "..") && elem->name[0] != '.')
		{
			printf("%s\n", elem->path);
			print_recursive(elem->list);
		}
		list = list->next;
	}
}

void 	print_files(t_list *list)
{
	t_elem *elem;

	while (list)
	{
		elem = list->content;
		if (!ft_strequ(elem->name, ".") && !ft_strequ(elem->name, "..") && elem->name[0] != '.')
			printf("%s:%s\n", elem->name, ctime(&elem->mtime));
		list = list->next;
	}
}

int		main(int argc, char **argv)
{
	t_list *lst = file_list(".");
	print_recursive(lst);

}
