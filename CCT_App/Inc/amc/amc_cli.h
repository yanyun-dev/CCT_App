#ifndef AMC_CLI_H
#define AMC_CLI_H

#include "stm32f1xx_hal.h"


/** Register a batch of CLI commands
 *
 * Often, a module will want to register several commands.
 * 
 * \param[in] commands Pointer to an array of commands.
 * \param[in] num_commands Number of commands in the array.
 * \return 0 on success
 * \return 1 on failure
 */
int cli_register_commands(const struct cli_command *commands, int num_commands);

/** Unregister a batch of CLI commands
 *
 * \param[in] commands Pointer to an array of commands.
 * \param[in] num_commands Number of commands in the array.
 * \return 0 on success
 * \return 1 on failure
 */
int cli_unregister_commands(const struct cli_command *commands,
			    int num_commands);



void amc_cli_init(void);

#endif