////
//// Created by neepoo on 2021/11/12.
////
///*
// * #include "kernel/types.h"
//#include "user/user.h"
//
//int
//main()
//{
//  char *argv[] = { "echo", "this", "is", "echo", 0 };
//
//  exec("echo", argv);
//
//  printf("exec failed!\n");
//
//  exit(0);
//}
// * */
//
#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

//  标准输入的最大长度
#define MAX_LEN  512

int main(int argc, char *argv[]) {
  char *execArgv[MAXARG];
  char line[MAX_LEN];
  char *p = line;
  int i = 1;
  for (; i < argc; i++) {
    execArgv[i - 1] = argv[i];
  }
  int rsz = sizeof(char);
  while (rsz == sizeof(char)) {
    int hh = 0, tt = 0;
    int cnt = i - 1;
    while (1) {
      rsz = read(0, p, sizeof(char));
	  tt++;
      if (*p == ' ' || *p == '\n' || rsz != sizeof(char)) {
        *p = 0;
        execArgv[cnt++] = &line[hh];
        hh = tt;
      }
      if (*p == '\n' || rsz != sizeof(char)) {
        break;
      }
      p++;
    }
    if (fork() == 0) {
      exec(argv[1], execArgv);
    }
    wait(0);
  }


  exit(0);

}
