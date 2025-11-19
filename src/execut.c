/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:53:53 by klima-do          #+#    #+#             */
/*   Updated: 2025/11/17 20:01:52 by klima-do         ###   ########.fr       */
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

int	exec_pipiline(t_command *cmd, char **envp)
{
	t_command	*head;
	int	prev_pipe[2] = {-1, -1};
	int next_pipe[2];
	char	*path;
	while(cmd)
	{
		if (cmd->next != NULL)
			pipe(next_pipe);
		pid_t	pid;

		pid = fork();
		if (pid == 0)
		{
			if (prev_pipe[0] != -1)
				dup2(prev_pipe[0], STDIN_FILENO);
			if(cmd->next != NULL)
				dup2(next_pipe[1], STDOUT_FILENO);
			close(prev_pipe[0]);
			close(prev_pipe[1]);
			close(next_pipe[0]);
			close(next_pipe[1]);
			path = get_path(envp, cmd->argv[0]);
			execve(path, cmd->argv, envp);
			perror("execve");
			exit(1);
		}
		close(prev_pipe[0]);
    	close(prev_pipe[1]);
    	prev_pipe[0] = next_pipe[0];
    	prev_pipe[1] = next_pipe[1];

    	cmd = cmd->next;
	}
	while (wait(NULL) > 0)
    ;
}