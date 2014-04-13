/* File: utiliy.cc
 * ---------------
 * Implementation of simple printing functions to report failures or
 * debugging information triggered by keys.
 */

#define __STDC_LIMIT_MACROS

#include <getopt.h>
#include <stdarg.h>
#include <string.h>
#include <vector>
#include <stdint.h>
#include <ctype.h>
#include <errno.h>

#include "decaf/utility.h"
#include "decaf/lexer.h"

static std::vector<const char*> kDebugKeys;
static const int kBufferSize = 2048;
static const char* kDefaultOutputFile = "a.out";

void Failure(const char *format, ...)  {
  va_list args;
  char errbuf[kBufferSize];
  va_start(args, format);
  vsprintf(errbuf, format, args);
  va_end(args);
  fflush(stdout);
  fprintf(stderr,"\n*** Failure: %s\n\n", errbuf);
  abort();
}

int IndexOf(const char *key)  {
  for (unsigned int i = 0; i < kDebugKeys.size(); ++i) {
    if (!strcmp(kDebugKeys[i], key)) {
      return i;
    }
  }
  return -1;
}

bool IsDebugOn(const char *key) {
  return (IndexOf(key) != -1);
}

void SetDebugForKey(const char *key, bool value) {
  int k = IndexOf(key);
  if (!value && k != -1) {
    kDebugKeys.erase(kDebugKeys.begin() + k);
  } else if (value && k == -1) {
    kDebugKeys.push_back(key);
  }
}

void PrintDebug(const char *key, const char *format, ...) {
  va_list args;
  char buf[kBufferSize];
  if (!IsDebugOn(key)) {
    return;
  }

  va_start(args, format);
  vsprintf(buf, format, args);
  va_end(args);
  printf("+++ (%s): %s%s", key, buf, buf[strlen(buf)-1] != '\n'? "\n" : "");
}

void ParseCommandLine(int argc, char *argv[]) {
  int c;
  kTestFlag = TEST_NONE;
  char* test_type = NULL;
  char* debug_level = NULL;
  char* output_file = NULL;
  while ((c = getopt(argc, argv, "o:d:t:")) != -1) {
    switch (c) {
     case 'd':
      debug_level = strdup(optarg);
      break;
     case 't':
      test_type = strdup(optarg);
      break;
     case 'o':
      output_file = strdup(optarg);
      break;
     case '?':
      if (optopt == 'c') {
        fprintf(stderr, "Option -%c requires an argument\n", optopt);
      } else if (optopt == 't') {
        fprintf(stderr, "Option -%c requires an argument\n", optopt);
      } else if (isprint(optopt)) {
        fprintf(stderr, "Unknown option -%c\n", optopt);
      } else {
        fprintf(stderr, "Unkonwn option character \\x%x \n", optopt);
      }
    }
  }

  if (optind != argc - 1) {
    fprintf(stderr, "usage\n");
    exit(1);
  }
  yyin = fopen(argv[optind], "r");
  if (yyin == NULL) {
    fprintf(stderr, "Cannot open input file %s\n", argv[optind]);
    exit(1);
  }

  if (debug_level != NULL) {
    SetDebugForKey(optarg, true);
    free(debug_level);
  }
  if (test_type != NULL) {
    if (strcmp(test_type, "lexer") == 0) {
      kTestFlag = TEST_LEXER;
    } else if (strcmp(test_type, "parser") == 0) {
      kTestFlag = TEST_PARSER;
    } else if (strcmp(test_type, "semantic") == 0) {
      kTestFlag = TEST_SEMANT;
    } else {
      fprintf(stderr, "Unknown test option %s\n", optarg);
    }
    free(test_type);
  }
  if (output_file != NULL) {
    kOutputFile = fopen(output_file, "w");
  } else {
    if (kTestFlag == TEST_NONE) {
      kOutputFile = fopen(kDefaultOutputFile, "w");
    } else {
      kOutputFile = stdout;
    }
  }
  if (kOutputFile == NULL) {
    fprintf(stderr, "Cannot open output file.\n");
  }
}

#if __USE_CUST_XTOI < 1

int xtoi(const char *s) {
  long int n = strtol(s, NULL, 16);
  if (n == LONG_MAX || n >= INT32_MAX) {
    return INT32_MAX;
  }  else if (n == LONG_MIN || n <= INT32_MIN) {
    return INT32_MIN;
  }
  return (int) n;
}

#else

int xtoi(const char *s) {
  size_t slen = strlen(s);
  int32_t factor, n, i, front;
  long int result;

  if (slen <= 0) {
    return 0;
  }

  result = 0;
  factor = 1;

  front = (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) ? 2 : 0;

  for (i = slen - 1; i >= front; i--) {
    if (!isxdigit(*(s + i))) {
      return 0;
    }

    if (*(s + i) >= 97) {
      n = (*(s + i) - 97) + 10;
    } else if (*(s + i) >= 65) {
      n = (*(s + i) - 65) + 10;
    } else {
      n = *(s + i) - 48;
    }

    if ((result = result + (n * factor)) >= INT32_MAX) {
      return INT32_MAX;
    }

    factor *= 16;
  }

  return (int) result;
}

/* vim: set ai ts=2 sts=2 sw=2 et: */
#endif
