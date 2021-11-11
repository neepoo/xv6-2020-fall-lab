//
// Created by neepoo on 2021/11/11.
//

#include "kernel/types.h"
#include "user/user.h"

int
main(){
  int fds[2];
  int pid;
  char buf[2];
  int ppid;
  pipe(fds);
  pid = fork();
  if (pid == 0){
    ppid = getpid();
    read(fds[0], buf, sizeof buf);
    fprintf(1, "%d: received ping\n", atoi(buf));
    fprintf(fds[1], "%d", ppid);
  } else{
    // 通过pipe发送父进程的pid给子进程
    ppid = getpid();
    fprintf(fds[1], "%d", ppid);
    wait(0);

    read(fds[0], buf, sizeof buf);
    fprintf(1, "%d: received pong\n", atoi(buf));
  }
  exit(0);
}
