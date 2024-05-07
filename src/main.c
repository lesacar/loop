#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libgen.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdbool.h>

#define K 1000

volatile sig_atomic_t stop;

void execute_command(const char* command) {
    // Fork a child process
    pid_t pid = fork();

    if (pid == -1) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        // Execute the command
        execlp("/bin/sh", "/bin/sh", "-c", command, NULL);
        // If execlp returns, an error occurred
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        // Wait for the child process to complete
        int status;
        waitpid(pid, &status, 0);
    }
}

void inthand(int32_t signum) {
    stop = 1;
}

int32_t maloop(char** out, int32_t argc, const char** argv, bool cust) {
    *out = malloc(1024);
    if (*out == NULL) return -1;
	int lc = 0;
	if (cust == true) {lc++;}
    int c = 0; // count 
    for (int i = 1 + lc; i < argc; i++) {
        for (int j = 0; j < strlen(argv[i]); j++) {
            (*out)[c] = argv[i][j];
            c++;
        }
        (*out)[c] = ' ';
        c++;
    }
    (*out)[c] = '\0';
    return 0;
}

int32_t main(int argc, const char** argv) {
    if (argc < 2) {
        fprintf(stderr, "\"%s\" needs a command to loop\n", basename((char*)argv[0]));
        exit(EXIT_FAILURE);
    }

	if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
		if (argc == 2) {
			fprintf(stdout, "%s: usage:\n%s \'command\' arg1 arg2 ...\n", argv[0], basename((char*)argv[0]));
			return(EXIT_SUCCESS);
		} else { fprintf(stderr, "Can't pass -h / --help with trailing arguments\n"); exit(EXIT_FAILURE);}
	}

	char* out;
	bool cust = false;

	int64_t sleep = 250000000L; // Use int64_t for larger range

    if (atoi(argv[1]) != 0) {
        int tmp = atoi(argv[1]);
        sleep = tmp * 1000000LL; // LL specifies long long literals
        if (sleep < 1LL * 1000000LL) { // Ensure minimum sleep is 1 millisecond
            sleep = 1LL * 1000000LL;
        }
        cust = true;
		if (sleep > 999 * K * K) {sleep = 999 * K * K;}
		if (sleep < 1 * K * K) {sleep = 1 * K * K;}
    }
    maloop(&out, argc, argv, cust);
	printf("(every %.3f sec) ", (float)sleep / (K * K * K));
    printf("LOOPING: ----> %s\n", out);

    signal(SIGINT, inthand);

    while (!stop) {
		execute_command(out);
        struct timespec sleep_time = {0, sleep};
        int result = nanosleep(&sleep_time, NULL);
        if (result != 0) {
            perror("nanosleep");
            exit(EXIT_FAILURE);
        }
    }


    free(out);
    return 0;
}
