/*
 * ps.c
 *
 *  Created on: Sep 19, 2012
 *      Author: bradley
 */

#include <conio.h>
#include <geekos/user.h>
#include <process.h>

#define MAXTBLSIZE 50

int main(int argc, char **argv) {
	struct Process_Info ptable[MAXTBLSIZE] = {0}; /* Holds the process table */
	int numProcesses = 10;
	/* Fills ptable with all of the processes information and returns the number
	 * of processes entered into the table
	 */

	numProcesses = PS(ptable, MAXTBLSIZE);

	/* Error Handling */
	if (numProcesses == 0) {
		Print("Failed: Not enough memory\n");
		Exit(-7);
	} else if (numProcesses < 0) {
		Print("Failed\n");
		Exit(-1);
	}

	/* Prints the process table */
	Print("PID PPID PRIO STAT COMMAND\n");
	char status = 0;
	int i;
	for (i = 0; i < numProcesses; i++) {
		if (ptable[i].status == STATUS_RUNNABLE) {
			status = 'R';
		} else if (ptable[i].status == STATUS_BLOCKED) {
			status = 'B';
		} else {
			status = 'Z';
		}
		Print("%3d %4d %4d %4c %s\n", ptable[i].pid, ptable[i].parent_pid,
				ptable[i].priority, status, ptable[i].name);
	}

	return 0;
}
