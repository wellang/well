/*Copyright (c) TristanWellman 2022*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined __gnu_linux__ || defined __linux__ || defined linux
#include <sys/stat.h>
#endif
#include "log_parse.h"


char *logparse_set_log_file(const char *fname) {
  char *tfbuf;
  char buf[0x100];
  snprintf(buf, sizeof(buf), "%s%s.toml", LOG_DIR, fname);
  tfbuf = buf;
  return tfbuf;
}

struct LOG_DATA LOGPARSE_INIT_FILE(const char *wellfname) {
  struct LOG_DATA log;

  const char *fname = wellfname;
  log.FILE_NAME = fname;

#if defined __gnu_linux__ || defined __linux__ || defined linux

  struct stat st;
  stat(log.FILE_NAME, &st);
  long int fsize = st.st_size;
  char buf[0x100];
  snprintf(buf, sizeof(buf), "%ld (bytes)", fsize);
  log.FILE_SIZE = buf;

#else

  FILE *file = fopen(log.FILE_NAME, "r");
  fseek(file, 0L, SEEK_END);
  long int fsize = ftell(file);
  char buf[0x100];
  snprintf(buf, sizeof(buf), "%ld (bytes)", fsize);
  log.FILE_SIZE = buf;

#endif

  return log;
}
