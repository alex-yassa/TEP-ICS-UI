#ifndef PC_SIMULATOR

#include "app_hardware.h"
#include "shared_memory.h"
#include "main.h"
#include <string.h>

void app_set_inverter_state(bool run)
{
    // Target Cortex-M4 GPIO control or write to Shared SRAM3
    (void)run;
}

void app_log_event(const char *message)
{
    // Target Cortex-M4 UART logger or circular debug log buffer
    (void)message;
}

void app_set_login_state(const char *username, uint8_t access_level)
{
    if (HAL_HSEM_Take(HSEM_ID_SHARED_MEM, 0) == HAL_OK)
    {
        volatile SharedBuffer_t *shared = SHARED_BUFFER;
        strncpy((char*)shared->login_username, username, sizeof(shared->login_username) - 1);
        shared->login_username[sizeof(shared->login_username) - 1] = '\0';
        shared->login_access_level = access_level;
        HAL_HSEM_Release(HSEM_ID_SHARED_MEM, 0);
    }
}

#endif
