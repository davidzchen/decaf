/* File: utiliy.cc
 * ---------------
 * Implementation of simple printing functions to report failures or
 * debugging information triggered by keys.
 */

#define __STDC_LIMIT_MACROS

#include <config.h>
#include <stdarg.h>
#include <string.h>
#include <vector>
#include <stdint.h>
#include <ctype.h>
#include "utility.h"

using std::vector;

static vector<const char*> debugKeys;
static const int BufferSize = 2048;

void Failure(const char *format, ...) 
{
  va_list args;
  char errbuf[BufferSize];
  
  va_start(args, format);
  vsprintf(errbuf, format, args);
  va_end(args);
  fflush(stdout);
  fprintf(stderr,"\n*** Failure: %s\n\n", errbuf);
  abort();
}

int IndexOf(const char *key) 
{
  for (unsigned int i = 0; i < debugKeys.size(); i++)
    if (!strcmp(debugKeys[i], key)) 
      return i;

  return -1;
}

bool IsDebugOn(const char *key) 
{
  return (IndexOf(key) != -1);
}

void SetDebugForKey(const char *key, bool value) 
{
  int k = IndexOf(key);
  if (!value && k != -1)
    debugKeys.erase(debugKeys.begin() + k);
  else if (value && k == -1)
    debugKeys.push_back(key);
}

void PrintDebug(const char *key, const char *format, ...) 
{
  va_list args;
  char buf[BufferSize];

  if (!IsDebugOn(key))
    return;
  
  va_start(args, format);
  vsprintf(buf, format, args);
  va_end(args);
  printf("+++ (%s): %s%s", key, buf, buf[strlen(buf)-1] != '\n'? "\n" : "");
}

void ParseCommandLine(int argc, char *argv[])
{
  int c;
  char *dvalue = NULL;
  char *tvalue = NULL;

  while ((c = getopt(argc, argv, "d:t:")) != -1 || optind < argc)
    {
      switch (c)
        {
        case -1:
          //printf("Non-option argument %s\n", argv[optind]);
          optind++;
          break;
        case 'd':
          SetDebugForKey(optarg, true);
          break;
        case 't':
          tvalue = optarg;
          if (strcmp(optarg, "scanner") == 0)
            testFlag = TEST_SCANNER;
          else if (strcmp(optarg, "parser") == 0)
            testFlag = TEST_PARSER;
          else
            {
              fprintf(stderr, "Unknown test option %s\n", optarg);
            }
          break;
        case '?':
          if (optopt == 'c')
            fprintf(stderr, "Option -%c requires an argument\n", optopt);
          else if (optopt == 't')
            fprintf(stderr, "Option -%c requires an argument\n", optopt);
          else if (isprint(optopt))
            fprintf(stderr, "Unknown option -%c\n", optopt);
          else
            fprintf(stderr, "Unkonwn option character \\x%x \n", optopt);
        }
    }
}

#if __USE_CUST_XTOI < 1

int xtoi(const char *s)
{
  long int n = strtol(s, NULL, 16);

  if (n == LONG_MAX || n >= INT32_MAX) 
    {
      return INT32_MAX;
    } 
  else if (n == LONG_MIN || n <= INT32_MIN) 
    {
      return INT32_MIN;
    }

  return (int) n;
}

#else

int xtoi(const char *s)
{
  size_t slen = strlen(s);
  int32_t factor, n, i, front;
  long int result;
  
  if (slen <= 0)
    return 0;

  result = 0;
  factor = 1;
  
  front = (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) ? 2 : 0;

  for (i = slen - 1; i >= front; i--) 
    {
      if (!isxdigit(*(s + i)))
	return 0;

      if (*(s + i) >= 97) 
	{
	  n = (*(s + i) - 97) + 10;
	} 
      else if (*(s + i) >= 65) 
	{
	  n = (*(s + i) - 65) + 10;
	} 
      else 
	{
	  n = *(s + i) - 48;
	}

      if ((result = result + (n * factor)) >= INT32_MAX)
	return INT32_MAX;
      factor *= 16;
    }

  return (int) result;
}

#endif
