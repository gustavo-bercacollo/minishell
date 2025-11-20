/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:53:53 by klima-do          #+#    #+#             */
/*   Updated: 2025/11/19 19:06:55 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_command *cmd, char **envp)
{

}

int	exec_single(t_command *cmd, char **envp)
{
	char	*path;
	int		status;
	pid_t	pid;

	pid = fork();
	if	(pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		path = get_path(envp, cmd->argv[0]);
	    if (!path)
        {
            printf("minishell: command not found: %s\n", cmd->argv[0]);
            exit(127);
        }
		execve(path, cmd->argv, envp);
		perror("execve");
		exit(1);
	}
	waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}

// int	exec_pipiline(t_command *cmd, char **envp)
// {
// 	t_command	*head;
// 	int	prev_pipe[2] = {-1, -1};
// 	int next_pipe[2];
// 	char	*path;void	add_arg(t_command *cmd, char *word)
// {
// 	int count;
// 	int	i;
// 	char **new_argv;
	
// 	count = 0;
// 	if (cmd->argv)
// 		while (cmd->argv[count])
// 			count++;
// 	new_argv = malloc(sizeof(char *) * (count + 2));
// 	if (!new_argv)
// 		return (NULL);
		
// 	i = 0;
// 	while (i < count)
// 		new_argv[i] = cmd->argv[i];
// 	new_argv[count] = ft_strdup(word);
// 	new_argv[count + 1] = NULL;
// 	free(cmd->argv);
// 	cmd->argv = new_argv;
// }
// 	while(cmd)
// 	{
// 		if (cmd->next != NULL)
// 			pipe(next_pipe);
// 		pid_t	pid;

// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (prev_pipe[0] != -1)
// 				dup2(prev_pipe[0], STDIN_FILENO);
// 			if(cmd->next != NULL)
// 				dup2(next_pipe[1], STDOUT_FILENO);
// 			close(prev_pipe[0]);
// 			close(prev_pipe[1]);
// 			close(next_pipe[0]);
// 			close(next_pipe[1]);
// 			path = get_path(envp, cmd->argv[0]);
// 			execve(path, cmd->argv, envp);
// 			perror("execve");
// 			exit(1);
// 		}
// 		close(prev_pipe[0]);
//     	close(prev_pipe[1]);
//     	prev_pipe[0] = next_pipe[0];
//     	prev_pipe[1] = next_pipe[1];

//     	cmd = cmd->next;
// 	}
// 	while (wait(NULL) > 0)
//     ;
// }