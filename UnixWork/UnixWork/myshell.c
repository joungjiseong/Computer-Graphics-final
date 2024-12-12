#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAXLEN 100
#define MAXARG 7

void parse_command(char* command, char** args, int* background, char** infile, char** outfile) {
    int argn = 0;
    char* token;
    *background = 0;
    *infile = NULL;
    *outfile = NULL;

    if (command[strlen(command) - 1] == '&') {
        *background = 1;
        command[strlen(command) - 1] = '\0';
    }

    token = strtok(command, " \t\n");
    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            *infile = strtok(NULL, " \t\n");
        }
        else if (strcmp(token, ">") == 0) {
            *outfile = strtok(NULL, " \t\n");
        }
        else {
            args[argn++] = token;
        }
        token = strtok(NULL, " \t\n");
    }
    args[argn] = NULL;
}

void execute_command(char* command) {
    char* args[MAXARG];
    int background;
    char* infile;
    char* outfile;

    parse_command(command, args, &background, &infile, &outfile);

    if (args[0] == NULL) return;
    if (strcmp(args[0], "quit") == 0) exit(0);

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return;
    }
    if (pid == 0) {
        if (infile) {
            int fd = open(infile, O_RDONLY);
            if (fd < 0) {
                perror("open infile");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        if (outfile) {
            int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("open outfile");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    }
    else if (!background) {
        waitpid(pid, NULL, 0);
    }
}

void execute_line(char* line) {
    char* command = strtok(line, ";");
    while (command != NULL) {
        execute_command(command);
        command = strtok(NULL, ";");
    }
}

int main() {
    char buf[MAXLEN];

    while (1) {
        printf("[shell] ");
        if (fgets(buf, MAXLEN, stdin) == NULL) break;
        if (buf[0] == '\n') continue;
        execute_line(buf);
    }
    return 0;
}
