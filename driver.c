#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<signal.h>


int main (int argc, char *argv[]){
	char *cmd2[] = { "./a1-ece650.py", 0 };
	char *cmd3[] = {"./a2-ece650", 0};

	int i;
	char *cmd[10];
	cmd[0] = "./a3";
	for(i = 1; i < argc; i++){
		cmd[i] = argv[i];
	}
	cmd[i+1] = '\0';
	char *env[] = {0};

	int status;
	int fd1[2];
	int fd2[2];
	int fd3[2];
	pipe(fd1);
	pipe(fd2);
	pipe(fd3);

	int pid1;
        pid1 = fork();
        switch(pid1){
        case 0:
                dup2(fd1[1], 1);
                close(fd1[0]);
                execve(cmd[0], &cmd[0], env);
                perror(cmd[0]);
        default:
                break;
        case -1:
                perror("Error: ");
                exit(1);

        }

        int pid2;
        pid2 = fork();
        switch(pid2){
        case 0:
                dup2(fd1[0], 0);
                close(fd1[1]);
                dup2(fd2[1], 1);
                close(fd2[0]);
                execvp(cmd2[0], cmd2);
                perror(cmd2[0]);
        default:
                break;
        case -1:
                perror("Error: ");
                exit(1);
        }

	close(fd1[0]);
        close(fd1[1]);

	int pid3;
        pid3 = fork();
        char c;
        switch(pid3){
        case 0:
                while(read(fd2[0], &c, 1)){
                       	printf("%c", c);
                       	write(fd3[1], &c, 1);
               	}
        default:
                break;
	case -1:
		perror("Error: ");
		exit(1);
        }

	close(fd2[0]);
        close(fd2[1]);


	int pid4;
        pid4 = fork();
        char tmp;
        switch(pid4){
        case 0:
                while ((tmp = getchar()) != EOF){
                        write(fd3[1], &tmp, 1);
                }
        default:
                break;
        case -1:
                perror("Error: ");
                exit(1);
        }


	int pid5;
        pid5 = fork();
        switch(pid5){
        case 0:
                dup2(fd3[0], 0);
                close(fd3[1]);
                execvp(cmd3[0], cmd3);
                perror(cmd3[0]);
        default:
                break;
        case -1:
                perror("Error: ");
                exit(1);
        }

	close(fd3[0]);
	close(fd3[1]);


	 while ((pid1 = wait(&status)) != -1){
                fprintf(stderr, "process %d exits with %d\n", pid1, WEXITSTATUS(status));
		kill(pid2, SIGKILL);
		kill(pid3, SIGKILL);
		kill(pid4, SIGKILL);
		kill(pid5, SIGKILL);
	}

	 while ((pid2 = wait(&status)) != -1){
                fprintf(stderr, "process %d exits with %d\n", pid2, WEXITSTATUS(status));
	}

	 while ((pid3 = wait(&status)) != -1){
                fprintf(stderr, "process %d exits with %d\n", pid3, WEXITSTATUS(status));
	}

	 while ((pid4 = wait(&status)) != -1){
                fprintf(stderr, "process %d exits with %d\n", pid4, WEXITSTATUS(status));
	}

	 while ((pid5 = wait(&status)) != -1){
                fprintf(stderr, "process %d exits with %d\n", pid5, WEXITSTATUS(status));
	}

	return 0;
}

