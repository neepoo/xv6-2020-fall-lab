//
// Created by neepoo on 2021/11/12.
//

#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"


void find(char *curPath, char *want) {
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;
  if ((fd = open(curPath, O_RDONLY)) < 0) {
    fprintf(2, "find: cannot open %s\n", curPath);
    return;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "find: cannot stat %s\n", curPath);
    close(fd);
    return;
  }

  if (st.type != T_DIR) {
    fprintf(2, "usage: find <DIRECTORY> <filename>\n");
    return;
  }


  strcpy(buf, curPath);
  p = buf + strlen(buf);
  if (buf[strlen(buf) - 1] != '/') {
    *p++ = '/';
  }
  while (read(fd, &de, sizeof(de)) == sizeof(de)) {
    if (de.inum == 0)
      continue;
    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;
    if (stat(buf, &st) < 0) {
      continue;
    }
    //不要在“.”和“..”目录中递归
    if (st.type == T_DIR && strcmp(p, ".") != 0 && strcmp(p, "..") != 0) {
      find(buf, want);
    } else if (strcmp(want, p) == 0)
      printf("%s\n", buf);
  }
}

int
main(int argc, char *argv[]) {
  char *dir, *filename;

  if (argc < 3) {
    exit(-1);
  }
  dir = argv[1];
  filename = argv[2];
  find(dir, filename);
  exit(0);
}
