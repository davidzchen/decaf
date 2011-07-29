
#include <config.h>
#include <getopt.h>
#include <cstdio>
#include <cstdlib>
#include <cctype>


int main(int argc, char **argv)
{
  int c;
  char *dvalue = NULL;
  char *tvalue = NULL;

  while ((c = getopt(argc, argv, "d:t:")) != -1 || optind < argc)
    {
      switch (c)
        {
        case -1:
          printf("Non-option argument %s\n", argv[optind]);
          optind++;
          break;
        case 'd':
          dvalue = optarg;
          printf("Debug key: %s\n", dvalue);
          break;
        case 't':
          tvalue = optarg;
          printf("Test: %s\n", tvalue);
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

  return EXIT_SUCCESS;
}
