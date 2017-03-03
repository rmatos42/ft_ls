#include "libft.h"
#include "get_next_line.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include "ft_ls.h"

char	get_filetype(int mode)
{
	if (S_ISREG(mode))
		return '-';
	else if (S_ISDIR(mode))
		return 'd';
	else if (S_ISBLK(mode))
		return 'b';
	else if (S_ISCHR(mode))
		return 'c';
	else if (S_ISFIFO(mode))
		return 'p';
	else if (S_ISLNK(mode))
		return 'l';
	else if (S_ISSOCK(mode))
		return 's';
	return ('X');
}

char	*get_permissions(char *path)
{
	char	*result;
	struct stat	buff;

	result = (char *)ft_memalloc(sizeof(char) * 12);
	if (lstat(path, &buff) != 0)
		return (0);
	result[0] = get_filetype(buff.st_mode);
	result[1] = (buff.st_mode & S_IRUSR) ? 'r' : '-';
	result[2] = (buff.st_mode & S_IWUSR) ? 'w' : '-';
	result[3] = (buff.st_mode & S_IXUSR) ? 'x' : '-';
	result[4] = (buff.st_mode & S_IRGRP) ? 'r' : '-';
	result[5] = (buff.st_mode & S_IWGRP) ? 'w' : '-';
	result[6] = (buff.st_mode & S_IXGRP) ? 'x' : '-';
	result[7] = (buff.st_mode & S_IROTH) ? 'r' : '-';
	result[8] = (buff.st_mode & S_IWOTH) ? 'w' : '-';
	result[9] = (buff.st_mode & S_IXOTH) ? 'x' : '-';
	result[10] = ' ';
	result[11] = '\0';
	return (result);
}

t_elem	*make_elem(char *path, t_flags flags)
{
	t_elem *elem;
	struct stat buff;
	char	str[255 + 1];
	size_t	i;

	if (lstat(path, &buff) != 0)
		return (0);
	elem = (t_elem *)ft_memalloc(sizeof(t_elem));
	if (S_ISLNK(buff.st_mode) && (i = readlink(path, str, 255)))
	{
		elem->link = 1;
		str[i] = '\0';
		elem->lname = ft_strdup(str);
	}
	else
		elem->link = 0;
	if (elem->link && !flags.l)
		stat(path, &buff);
	elem->dir = S_ISDIR(buff.st_mode) ? 1 : 0;
	elem->path = path;
	elem->name = ft_strsplit(path, '/')[get_count(path, '/') - 1];
	elem->mtime = buff.st_mtime;
	elem->mtime_nsec = buff.st_mtimespec.tv_nsec;
	elem->nlink = buff.st_nlink;
	elem->size = buff.st_size;
	elem->group_name = ft_strdup(getgrgid(buff.st_gid)->gr_name);
	elem->user_name = ft_strdup(getpwuid(buff.st_uid)->pw_name);
	printf("%i:%s\n", getpwuid(buff.st_uid), elem->user_name);
	elem->blocks = buff.st_blocks;
	return (elem);
}



t_list	*file_list(char *path, t_flags flags)
{
	DIR				*dir;
	char			*new_path;
	struct dirent	*ent;
	t_elem			*elem;
	int 			count;
	t_list			*lst;

	count = 0;
	if ((dir = opendir(path)) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			new_path = ft_strjoin(path, "/");
			new_path = ft_strjoin(new_path, ent->d_name);
			elem = make_elem(new_path, flags);
			if (elem->name[0] != '.' || flags.a)
			{
				if (!count)
					lst = ft_lstnew(elem);
				else
					ft_lstadd(&lst, ft_lstnew(elem));
				if (elem->dir && !ft_strequ(elem->name, ".") && !ft_strequ(elem->name, "..") && flags.recursive)
					elem->list = file_list(elem->path, flags);
				count++;
			}
		}
		closedir(dir);
	}
	if (count == 0)
		return (NULL);
	if (flags.t && flags.r)
		sort_list(&lst, time_cmp_rev);
	else if (flags.t)
		sort_list(&lst, time_cmp);
	else if (flags.r)
		sort_list(&lst, alpha_cmp_rev);
	else
		sort_list(&lst, alpha_cmp);
	return (lst);
}

void 	fill_arg_list(t_list **files, t_list **dirs, char **argv, t_flags flags)
{
	t_elem *elem;
	int		i;
	int 	i_f;
	int		i_d;

	i = 1;
	i_f = 0;
	i_d = 0;
	while (argv[i])
	{
		elem = make_elem(argv[i], flags);
		if (elem && elem->dir)
		{
			if (i_d == 0)
				*dirs = ft_lstnew(elem);
			else
				ft_lstadd(dirs, ft_lstnew(elem));
			elem->list = file_list(elem->path, flags);
			i_d++;
		}
		else if (elem)
		{
			if (i_f == 0)
				*files = ft_lstnew(elem);
			else
				ft_lstadd(files, ft_lstnew(elem));
			i_f++;
		}
		i++;
	}
	if (*files && flags.t && flags.r)
		sort_list(files, time_cmp_rev);
	else if (*files && flags.t)
		sort_list(files, time_cmp);
	else if (*files && flags.r)
		sort_list(files, alpha_cmp_rev);
	else if (*files)
		sort_list(files, alpha_cmp);
	if (*dirs && flags.t && flags.r)
		sort_list(dirs, time_cmp_rev);
	else if (*dirs && flags.t)
		sort_list(dirs, time_cmp);
	else if (*dirs && flags.r)
		sort_list(dirs, alpha_cmp_rev);
	else if (*dirs)
		sort_list(dirs, alpha_cmp);
}

int		get_block_total(t_list *list, t_flags flags)
{
	t_elem	*elem;
	int		sum;

	sum = 0;
	while (list)
	{
		elem = list->content;
		if ((!ft_strequ(elem->name, ".") && !ft_strequ(elem->name, "..") && elem->name[0] != '.') || flags.a)
			sum += elem->blocks;
		list = list->next;
	}
	return (sum);
}

int		big_link(t_list *list, t_flags flags)
{
	t_elem	*elem;
	int		big;

	big = 0;
	while (list)
	{
		elem = list->content;
		if (nb_len(elem->nlink) > big && ((!ft_strequ(elem->name, ".") && !ft_strequ(elem->name, "..") && elem->name[0] != '.') || flags.a))
			big = nb_len(elem->nlink);
		list = list->next;
	}
	return (big);
}

int		big_user(t_list *list, t_flags flags)
{
	t_elem	*elem;
	int		big;

	big = 0;
	while (list)
	{
		elem = list->content;
		if (ft_strlen(elem->user_name) > big && ((!ft_strequ(elem->name, ".") && !ft_strequ(elem->name, "..") && elem->name[0] != '.') || flags.a))
			big = ft_strlen(elem->user_name);
		list = list->next;
	}
	return (big);
}

int		big_group(t_list *list, t_flags flags)
{
	t_elem	*elem;
	int		big;

	big = 0;
	while (list)
	{
		elem = list->content;
		if (ft_strlen(elem->group_name) > big && ((!ft_strequ(elem->name, ".") && !ft_strequ(elem->name, "..") && elem->name[0] != '.') || flags.a))
			big = ft_strlen(elem->group_name);
		list = list->next;
	}
	return (big);
}

int		big_size(t_list *list, t_flags flags)
{
	t_elem	*elem;
	int		big;

	big = 0;
	while (list)
	{
		elem = list->content;
		if (nb_len(elem->size) > big && ((!ft_strequ(elem->name, ".") && !ft_strequ(elem->name, "..") && elem->name[0] != '.') || flags.a))
			big = nb_len(elem->size);
		list = list->next;
	}
	return (big);
}

char	*format_time(char *str)
{
	return (ft_strsub(str, 4, 12));
}

int		list_len(t_list *list, t_flags flags)
{
	t_elem	*elem;
	int		count;

	count = 0;
	while (list)
	{
		elem = list->content;
		count++;
		list = list->next;
	}
	return (count);
}

void 	print_recursive(t_list *list, t_flags flags)
{
	t_list 	*list_tmp;
	t_elem	*elem;

	list_tmp = list;
	if (flags.l && list_len(list, flags))
		printf("total %i\n", get_block_total(list, flags));
	while (list)
	{
		elem = list->content;
		if ((!ft_strequ(elem->name, ".") && !ft_strequ(elem->name, "..") && elem->name[0] != '.') || flags.a)
		{
			if (flags.l)
			{
				printf("%s%*i%*s%*s%*i %s %s", get_permissions(elem->path), big_link(list_tmp, flags) + 1, elem->nlink, big_user(list_tmp, flags) + 1, elem->user_name, big_group(list_tmp, flags) + 2, elem->group_name, big_size(list_tmp, flags) + 2, elem->size, format_time(ctime(&elem->mtime)), elem->name);
				if (elem->link)
					printf(" -> %s\n", elem->lname);
				else
					printf("\n");
			}
			else
				printf("%s\n", elem->name);
		}
		list = list->next;
	}
	list = list_tmp;
	while (list && flags.recursive)
	{
		elem = list->content;
		if (elem->dir && !ft_strequ(elem->name, ".") && !ft_strequ(elem->name, "..") && (elem->name[0] != '.' || flags.a))
		{
			printf("\n%s:\n", elem->path);
			print_recursive(elem->list, flags);
		}
		list = list->next;
	}
}

void 	print_args(t_list *files, t_list *dirs, t_flags flags)
{
	t_list	*files_tmp;
	t_list	*dirs_tmp;
	t_elem	*elem;
	t_elem	*elem2;

	files_tmp = files;
	dirs_tmp = dirs;
	while (files)
	{
		elem = files->content;
		if ((!ft_strequ(elem->name, ".") && !ft_strequ(elem->name, "..") && elem->name[0] != '.') || flags.a)
		{
			if (flags.l)
			{
				printf("%s%*i%*s%*s%*i %s %s", get_permissions(elem->path), big_link(files_tmp, flags) + 1, elem->nlink, big_user(files_tmp, flags) + 1, elem->user_name, big_group(files_tmp, flags) + 2, elem->group_name, big_size(files_tmp, flags) + 2, elem->size, format_time(ctime(&elem->mtime)), elem->path);
				if (elem->link)
					printf(" -> %s\n", elem->lname);
				else
					printf("\n");
			}
			else
				printf("%s\n", elem->path);
		}
		files = files->next;
	}
	if (list_len(dirs, flags) && list_len(files_tmp, flags))
		printf("\n");
	while (dirs)
	{
		elem = dirs->content;
		if (list_len(dirs_tmp, flags) > 1)
			printf("%s:\n", elem->name);
		print_recursive(elem->list, flags);
		if (dirs->next)
			printf("\n");
		dirs = dirs->next;
	}
}

t_flags	make_flags(char *str)
{
	t_flags flags;

	flags.l = (ft_strchr(str, 'l') && str[0] == '-') ? 1 : 0;
	flags.r = (ft_strchr(str, 'r') && str[0] == '-') ? 1 : 0;
	flags.a = (ft_strchr(str, 'a') && str[0] == '-') ? 1 : 0;
	flags.recursive = (ft_strchr(str, 'R') && str[0] == '-') ? 1 : 0;
	flags.t = (ft_strchr(str, 't') && str[0] == '-') ? 1 : 0;
	return (flags);
}

int		main(int argc, char **argv)
{
	t_flags flags = make_flags((argv[1]) ? ft_strsplit(argv[1], ' ')[0] : "");
	t_list *files;
	t_list *dirs;
	t_list *list;
	if (argc > 2 || (argv[1] && argv[1][0] != '-'))
	{
		fill_arg_list(&files, &dirs, argv, flags);
		print_args(files, dirs, flags);
	}
	else
	{
		list = file_list(".", flags);
		print_recursive(list, flags);
	}

}
