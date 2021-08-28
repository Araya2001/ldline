#include "../lib/libldline.h"
#include <argp.h>
#include <stdlib.h>

const char *argp_program_version = "ldline 1.0";
const char *argp_program_bug_address = "<araya2001@outlook.es>";

/* Program documentation. */
static char doc[] =
    "ldline -- get the last duplicated ldline(s) from a single file.";

/* A description of the arguments we accept. */
static char args_doc[] = "FILE TO READ";

/* The options we understand. */
static struct argp_option options[] = {
    {"erasedupe", 'e', 0, 0, "Erases the last duplicated ldline"},
    {"showdupe", 's', 0, 0, "Shows the last duplicated ldline"},
    {"from", 'f', "CHAR NUMBER [FIRST TO COMPARE]", 0,
     "Compare from a specified character position"},
    {"to", 'c', "CHAR NUMBER [LAST TO COMPARE]", 0,
     "Compare a specified amount of characters"},
    {0}};

/* Used by main to communicate with parse_opt. */
struct arguments {
  char *arg[1]; /* arg1 */
  int erasedupe, showdupe, from, to;
};

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  int base = 10;
  char *endptr;

  switch (key) {
  case 'e':
    arguments->erasedupe = 1;
  case 's':
    arguments->showdupe = 1;
    break;
  case 'f':
    if (strtol(arg, &endptr, base) != 0) {
      arguments->from = (int)strtol(arg, &endptr, base);
    } else {
      return ARGP_ERR_UNKNOWN;
    }
    endptr = NULL;
    break;
  case 't':
    if (strtol(arg, &endptr, base) != 0) {
      arguments->to = (int)strtol(arg, &endptr, base);
    } else {
      return ARGP_ERR_UNKNOWN;
    }
    endptr = NULL;
    break;
  case ARGP_KEY_ARG:
    if (state->arg_num >= 1)
      /* Too many arguments. */
      argp_usage(state);
    arguments->arg[state->arg_num] = arg;
    break;
  case ARGP_KEY_END:
    if (state->arg_num < 1)
      /* Not enough arguments. */
      argp_usage(state);
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

/* Our argp parser. */
static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char *argv[]) {
  struct arguments arguments;
  const char *filename;

  /* Default values. */
  arguments.from = 0;
  arguments.to = 0;
  arguments.showdupe = 0;
  arguments.erasedupe = 0;

  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
  argp_parse(&argp, argc, argv, 0, 0, &arguments);
  filename = arguments.arg[0];

  if (arguments.erasedupe == 1) {
    readLineErased(filename, arguments.from, arguments.to);
  }

  if (arguments.showdupe == 1) {
    readLineSaved(filename, arguments.from, arguments.to);
  }

  exit(0);
}
