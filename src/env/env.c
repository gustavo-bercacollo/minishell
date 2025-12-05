/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:53:53 by klima-do          #+#    #+#             */
/*   Updated: 2025/11/26 20:13:52 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
void	env_add_back(t_env **env_lst, t_env *new);

int	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (*s++)
	{
		count++;
	}
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char) c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}
char	*ft_strdup(const char *s)
{
	char	*str;
	char	*start;
	size_t	size;

	size = ft_strlen(s);
	str = malloc(size + 1);
	if (!str)
		return (NULL);
	start = str;
	while (*s)
		*str++ = *s++;
	*str = '\0';
	return (start);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	string_size;
	size_t	index;

	string_size = ft_strlen(s);
	index = 0;
	if (!s)
		return (NULL);
	if (start > string_size)
		start = string_size;
	if (len > string_size - start)
		len = string_size - start;
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	while (len && s[start])
	{
		ptr[index] = s[start];
		index++;
		start++;
		len--;
	}
	ptr[index] = '\0';
	return (ptr);
}

void	add_env_node(t_env **env_lst, char *env_line)
{
	char	*postion;
	t_env	*env_node;

	postion = ft_strchr(env_line, '=');
	if (!postion)
		return ;
	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return ; 
	env_node->key = ft_substr(env_line, 0, postion - env_line);
	env_node->value = ft_strdup(postion + 1);
	env_node->next = NULL;
	env_add_back(env_lst, env_node);
}


void	env_add_back(t_env **env_lst, t_env *new)
{
	t_env	*last;

	if(!env_lst || !new)
		return ;
	if (*env_lst == NULL)
	{
		*env_lst = new;
		return ;
	}
	last = *env_lst;
	while(last->next)
		last = last->next;
	last->next = new;
}
t_env	*get_env(char **env)
{
	int		i;
	t_env	*node;

	i = 0;
	node = NULL;
	while(env[i])
	{
		add_env_node(&node, env[i]);
		i++;
	}
	return (node);
}

int main(int argc, char **argv, char **envp)
{
    t_env *head;
    t_env *tmp;

    head = get_env(envp);

    tmp = head;
    while (tmp)
    {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}
