CFLAGS=-c -g -Wall -Werror
CC=gcc

all: signal_handler.out signal_sigaction.out signal_alarm.out signal_segfault.out recv_signal.out send_signal.out

signal_handler.out: signal_handler.o
	$(CC) -o signal_handler.out signal_handler.o

signal_sigaction.out: signal_sigaction.o
	$(CC) -o signal_sigaction.out signal_sigaction.o

signal_alarm.out: signal_alarm.o
	$(CC) -o signal_alarm.out signal_alarm.o

signal_segfault.out: signal_segfault.o
	$(CC) -o signal_segfault.out signal_segfault.o

recv_signal.out: recv_signal.o
	$(CC) -o recv_signal.out recv_signal.o

send_signal.out: send_signal.o
	$(CC) -o send_signal.out send_signal.o

clean:
	rm -f *.o *.out

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

