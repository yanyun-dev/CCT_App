#include "amc_cli.h"

#define INBUF_SIZE 32
#define OUTBUF_SIZE 32

struct cli_st {  
	uint8_t inbuf_head_pos;
	uint8_t inbuf_tail_pos;
	uint8_t outbuf_head_pos;
	uint8_t outbuf_tail_pos;
  char inbuf[INBUF_SIZE];
  char outbuf[OUTBUF_SIZE];
  const struct cli_command *commands[MAX_COMMANDS];
  unsigned int num_commands;
  int echo_disabled;
} ;

struct cli_command {
	/** The name of the CLI command */
	const char *name;
	/** The help text associated with the command */
	const char *help;
	/** The function that should be invoked for this command. */
	void (*function) (char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
};


