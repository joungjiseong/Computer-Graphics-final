#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAXLEN 100
#define MAXARG 10

void execute_command(char* cmd);
void execute_pipe(char* cmd1, char* cmd2);

int main() {
    char buf[MAXLEN];
    char* cmds[MAXARG];
    char* s, * save;
    int cmdn;
    int i;

    while (1) {
        printf("[shell] ");
        if (fgets(buf, sizeof(buf), stdin) == NULL || buf[0] == '\0') continue;

        buf[strcspn(buf, "\n")] = 0;

        cmdn = 0;
        s = strtok_r(buf, ";", &save);
        while (s) {
            cmds[cmdn++] = s;
            s = strtok_r(NULL, ";", &save);
        }
        cmds[cmdn] = NULL;

        for (i = 0; i < cmdn; i++) {
            char* pipe_pos = strchr(cmds[i], '|');
            if (pipe_pos) {
                *pipe_pos = '\0';
                char* cmd1 = cmds[i];
                char* cmd2 = pipe_pos + 1;
                execute_pipe(cmd1, cmd2);
            }
            else {
                execute_command(cmds[i]);
            }
        }
    }
    return 0;
}

void execute_command(char* cmd) {
    char* args[MAXARG];
    char* s, * save;
    int argn = 0;
    int background = 0;
    int fd;
    int i;

    s = strtok_r(cmd, " \t", &save);
    while (s) {
        args[argn++] = s;
        s = strtok_r(NULL, "\t", &save);
    }
    args[argn] = NULL;

    if (argn == 0) return;
    if (strcmp(args[0], "quit") == 0) exit(0);

    if (argn > 1 && strcmp(args[argn - 1], "&") == 0) {
        background = 1;
        args[argn - 1] = NULL;
    }

    for (i = 0; i < argn; i++) {
        if (strcmp(args[i], "<") == 0) {
            if ((fd = open(args[i + 1], O_RDONLY)) == -1) {
                perror("open failed");
                return;
            }
            dup2(fd, 0);
            close(fd);
            args[i] = NULL;
            break;
        }
    }

    int pid = fork();
    if (pid == -1) {
        perror("fork failed");
    }
    else if (pid == 0) {
        execvp(args[0], args);
        perror("exec failed");
        exit(1);
    }
    else {
        if (!background) {
            waitpid(pid, NULL, 0);
        }
    }
}

void execute_pipe(char* cmd1, char* cmd2) {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe failed");
        return;
    }

    int pid1 = fork();
    if (pid1 == -1) {
        perror("fork failed");
        return;
    }
    else if (pid1 == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execute_command(cmd1);
        exit(0);
    }

    int pid2 = fork();
    if (pid2 == -1) {
        perror("fork failed");
        return;
    }
    else if (pid2 == 0) {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execute_command(cmd2);
        exit(0);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
