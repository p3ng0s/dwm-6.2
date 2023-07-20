/*
** p4p1: http://p4p1.github.io/
** Created on: dim. 31 mai 2020 07:50:09  CEST
** status.c
** File description:
** <..>
*/

void
runStartupCommand(int pos)
{
	unsigned int	id = 0;

	if ((id = fork()) < 0)
		exit(EXIT_FAILURE);
	if (id == 0) {
		if (execvp(stup_prgs[pos][0], (char **)stup_prgs[pos]) < 0) {
			fprintf(stderr, "Command: %s failed\n", stup_prgs[pos][0]);
			exit(-1);
		}
		exit(0);
	}
}

void
startup(void)
{
	unsigned int id = 0;

	if ((id = fork()) < 0)
		exit(EXIT_FAILURE);
	if (id == 0) {
		/* Child process in wich we will do the Autostart commands */
		for (int i = 0; stup_prgs[i][0] != NULL; i++) {
			runStartupCommand(i);
		}
		exit(0);
	} else {
		child_pid = id;
	}
}
