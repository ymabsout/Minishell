#include "mini_shell.h"

void handle_signal(int sign)
{
	if (sign == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (sign == SIGQUIT)
	{
		puts("test");
		exit(0);
	}
}

int main ()
{
	while (1)
	{
		signal(SIGQUIT,	SIG_IGN);
		signal(SIGINT, handle_signal);
		char *str = readline(":");
	}
}