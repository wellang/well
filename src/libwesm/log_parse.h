/*Copyright (c) Tristan Wellman 2022*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LOG_PARSE_H_
#define LOG_PARSE_H_

#if defined _WIN32 || defined _WIN64 || defined __WIN32__
#define LOG_DIR ".\\.config\\wellang\\logs\\"
#else
#define LOG_DIR "~/.config/wellang/logs/"
#endif

/*char tfbuf[0x100];
#define logparse_set_log_file(fname)                            \
  snprintf(tfbuf, sizeof(tfbuf), "%s%s.toml", LOG_DIR, fname);       \
  return tfbuf;                                                    \
*/
struct LOG_DATA {
  const char *FILE_NAME;
  const char *FILE_SIZE;

  int *TOTAL_VAR_NUM[sizeof(int)];
  int *TOTAL_STRING_NUM[sizeof(int)];
  int *TOTAL_ASM_NUM[sizeof(int)];

  int *TOAL_MACRO_NUM[sizeof(int)];
  int *TOTAL_FUNC_NUM[sizeof(int)];

  const char *MACRO_NAMES[sizeof(int)];
  const char *FUNC_NAMES[sizeof(int)];
  const char *VAR_NAMES[sizeof(int)];
};

char *logparse_set_log_file(const char *fname, char *buf);
struct LOG_DATA LOGPARSE_SET_FILE(const char *wellfname);

#endif /* LOG_PARSE_H_ */
