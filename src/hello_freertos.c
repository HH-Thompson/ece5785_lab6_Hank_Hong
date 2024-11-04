/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

SemaphoreHandle_t semaphore;

void priorityInversionBoolean() {
    semaphore = xSemaphoreCreateBoolean();
    
}

void priorityInversionMutex() {
    semaphore = xSemaphoreCreateMutex();
}

int main( void )
{
    return 0;
}
