#ifndef TERMINAL_H
#define TERMINAL_H

#define ON '1'
#define OFF '0'

#define DONE_MSG " => done\n"
#define FAILED_MSG " => failed\n"
#define COMMAND_MSG "Enter the command [0: Off, 1: On]: "

void terminal_init(void);

void terminal_run(void);

#endif /* TERMINAL_H */
