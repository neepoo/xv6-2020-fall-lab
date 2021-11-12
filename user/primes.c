//
// Created by neepoo on 2021/11/12.
//

#include "kernel/types.h"
#include "user/user.h"

int nums[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
              30, 31, 32, 33, 34, 35};
int len = 34;  // 表示数组长度

int primes(int *a, int l, int firstPrime) {
  int idx = 0;
  for (int i = 0; i < l; ++i) {
    // 埃氏筛法,因为能够保证当前nums的第一个元素是质数p,将nums中是p倍数的数全部筛掉
    if (a[i] % firstPrime != 0) {
      a[idx++] = a[i];
    }
  }
  return idx;
}

void dfs(int a[], int l) {
  // 打印第一个素数
  int firstPrime = a[0];
  fprintf(1, "prime %d\n", firstPrime);
  if (l == 1) {
    exit(0);
  }
  int fds[2];
  pipe(fds);
  int currentLen = primes(nums, l, firstPrime);
  if (fork() == 0) {
    read(fds[0], nums, sizeof(int) * currentLen);
    close(fds[0]);
    dfs(nums, currentLen);
  } else {
    // 再将数组元素通过管道告诉子进程
    write(fds[1], (char *) nums, (int) currentLen * sizeof(int));
    close(fds[1]);
    wait(0);
  }
}

int
main() {
  dfs(nums, len);
  exit(0);
}
