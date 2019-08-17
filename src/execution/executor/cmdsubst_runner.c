#include "tmpsh.h"
#include "libft.h"
#include "forker.h"
#include "sigmask_modif.h"
#include "fd_management.h"
#include "heredoc_apply.h"
#include "job_control.h"
#include "run_ast.h"

/*
** prepare_cmdsubst_pipe:
**
** Create pipe for a cmdsubt and store them in a pylst.
*/

static t_pylst		*prepare_cmdsubst_pipe(void)
{
	int		pipe_fd[2];
	t_pylst	*pipe_lst;
	int		stdin;
	int		stdout;

	setup_pipe_fd(pipe_fd);
	pipe_lst = NULL;
	stdin = pipe_fd[0];
	stdout = pipe_fd[1];
	push_pylst(&pipe_lst, &stdin, 0, _ptr);
	push_pylst(&pipe_lst, &stdout, 0, _ptr);
	return (pipe_lst);
}

/*
** run_cmdsubst:
**
** Fork and prepare a subshell for CMDSUBT replacement.
** Prepare the right subshell configuration, blocking job control.
** Replace stdin/stdout apropriately.
** Link to the subast his pid and filedescriptor.
*/

static void		run_cmdsubst(t_ast *subast)
{
	t_pylst	*pipe_fd;
	pid_t	pid;
	int		stdin;
	int		stdout;

	pipe_fd = prepare_cmdsubst_pipe();
	pid = fork_prepare(getpgrp(), false);
	if (pid == 0)
	{
		clear();
		g_jobs->allow_background = false;
		change_sigmask(SIGTSTP, SIG_BLOCK);
		stdin = -1;
		stdout = -1;
		if (ft_strequ(subast->type, "CMDSUBST2"))
			stdin = *(int *)pop_pylst(&pipe_fd, 0);
		else if (ft_strequ(subast->type, "CMDSUBST1") || \
				ft_strequ(subast->type, "CMDSUBST3"))
			stdout = *(int *)pop_pylst(&pipe_fd, 1);
		replace_std_fd(stdin, stdout);
		close(*(int *)pop_pylst(&pipe_fd, 0));
		run_ast(subast);
		exit(g_last_status);
	}
	else
	{
		subast->pid = pid;
		if (ft_strequ(subast->type, "CMDSUBST2"))
			subast->link_fd = *(int *)pop_pylst(&pipe_fd, 1);
		else
			subast->link_fd = *(int *)pop_pylst(&pipe_fd, 0);
		close(*(int *)pop_pylst(&pipe_fd, 0));
	}
}

/*
** prepare_cmd_subst:
**
** For each CMDSUBST[123] or DQUOTES, run in a subshell his ast representation.
** Do not wait any of those subprocess.
*/

void	prepare_cmd_subst(t_acb *branch)
{
	t_ast	*subast;

	heredoc_apply(branch->redirectionfd, prepare_cmd_subst);
	while (iter_pylst(branch->subast, (void **)&subast))
	{
		if (ft_start_with(subast->type, "CMDSUBST"))
			run_cmdsubst(subast);
		else if (ft_strequ(subast->type, "DQUOTES"))
			prepare_cmd_subst((t_acb *)subast->list_branch->value);
	}
}
