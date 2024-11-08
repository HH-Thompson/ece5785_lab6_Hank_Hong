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

void priorityInversionBinary() {
    xSemaphoreTake(semaphore, portMAX_DELAY);
    busy_wait_us(1000);
    xSemaphoreGive(semaphore);

    semaphore = xSemaphoreCreateBinary();
    vSemaphoreDelete(semaphore);
}

void priorityInversionMutex() {
    xSemaphoreTake(semaphore, portMAX_DELAY);
    busy_wait_us(1000);
    xSemaphoreGive(semaphore);

    semaphore = xSemaphoreCreateMutex();
    vSemaphoreDelete(semaphore);
}

void busy_busy(void) {
    for(int i = 0; ; i++) {

    }
}

void busy_yield(void) {
    for(int i = 0; ; i++) {
        taskYIELD();
    }
}

void testSamePriorityBothBusyBusy() {

}

void testSamePriorityBothBusyYield() {

}

void testSamePriorityBusyBusy_BusyYield() {

}

void testDifferentPriorityBothBusyBusy() {

}

void testDifferentPriorityBothBusyYield() {

}

void tests() {
    
}

int main( void )
{
    return 0;
}
