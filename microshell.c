#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void	error(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int	cd(char **argv, int i)
{
	if (i != 2)
		return (error("error: cd: bad arguments\n"), 1);
	if (chdir(argv[1]) < 0)
		return (error("error: cd: cannot change directory to "), error(argv[1]), error("\n"), 1);
	return (0);
}

void	set_pipe(int has_pipe, int *fd, int end)
{
	if (has_pipe && (dup2(fd[end], end) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		error("error: fatal\n"), exit(1);
}

int	execute(char **argv, int i, char **envp)
{
	int	has_pipe;
	int	fd[2];
	int	pid;
	int	status;

	has_pipe = argv[i] && !strcmp(argv[i], "|");
	if (!has_pipe && !strcmp(*argv, "cd"))
		return (cd(argv, i));
	if (has_pipe && pipe(fd))
		error("error: fatal\n"), exit(1);
	if ((pid = fork()) == -1)
		error("error: fatal\n"), exit(1);
	if (!pid)
	{
		argv[i] = 0;
		set_pipe(has_pipe, fd, 1);
		if (!strcmp(*argv, "cd"))
			exit(cd(argv, i));
		execve(*argv, argv, envp);
		error("error: cannot execute "), error(*argv), error("\n"), exit(1);
	}
	waitpid(pid, &status, 0);
	set_pipe(has_pipe, fd, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (argv[i])
	{
		argv += i + 1;
		i = 0;
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;
		if (i)
			status = execute(argv, i, envp);
	}
	return (status);
}