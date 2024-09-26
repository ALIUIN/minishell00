#include "../minishell.h"


void	deffine_in(t_line *line)
{
	t_line	*cur;
	t_line	*cur_best;

	cur = line;
	cur_best = NULL;
	while (cur)
	{
		if (*(cur->cmd) == '<')
		{
			printf("%s\n", cur->cmd);
			if (cur_best != NULL)
				cur_best->isbest = false;
			cur_best = cur;
			cur->isbest = true;
			cur = cur->next;
		}
		else if (cur_best != NULL && *(cur->cmd) == '|')
			cur_best = NULL;
		else
			cur = cur->next;
	}
}
void	deffine_out(t_line *line)
{
	t_line	*cur;
	t_line	*cur_best;

	cur = line;
	cur_best = NULL;
	while (cur)
	{
		if (*(cur->cmd) == '>')
		{
			if (cur_best != NULL)
				cur_best->isbestout = false;
			cur_best = cur;
			cur->isbestout = true;
			printf("%d\n", cur->isbestout);
			cur = cur->next;
		}
		else if (cur_best != NULL && *(cur->cmd) == '|')
			cur_best = NULL;
		else
			cur = cur->next;
	}
}

void	sort_list(t_line *line)
{
	deffine_out(line);
	deffine_in(line);
}
