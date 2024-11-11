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

#include "unity_config.h"
#include <unity.h>

SemaphoreHandle_t semaphore;
SemaphoreHandle_t semaphore2;

TaskHandle_t firstThread;
TaskHandle_t secondThread;

void priorityInversionBinary() {
    xSemaphoreTake(semaphore, portMAX_DELAY);

    xTaskCreate(semaphore, "First", configMINIMAL_STACK_SIZE, "FirstThread", tskIDLE_PRIORITY+(1), &firstThread);
    vTaskDelay(100);

    xTaskCreate(semaphore2, "Second", configMINIMAL_STACK_SIZE, "SecondThread", tskIDLE_PRIORITY+(2), &secondThread);

    busy_wait_us(1000);

    xSemaphoreGive(semaphore);

    semaphore = xSemaphoreCreateBinary();
    vSemaphoreDelete(semaphore);
}

void priorityInversionMutex() {
    xSemaphoreTake(semaphore, portMAX_DELAY);

    xTaskCreate(semaphore, "First", configMINIMAL_STACK_SIZE, "FirstThread", tskIDLE_PRIORITY+(1), &firstThread);
    vTaskDelay(100);

    xTaskCreate(semaphore2, "Second", configMINIMAL_STACK_SIZE, "SecondThread", tskIDLE_PRIORITY+(2), &secondThread);

    busy_wait_us(1000);
    
    xSemaphoreGive(semaphore);

    semaphore = xSemaphoreCreateMutex();
    vSemaphoreDelate(semaphore);
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
    UNITY_BEGIN();
    RUN_TEST(testSamePriorityBothBusyBusy);
    RUN_TEST(testSamePriorityBothBusyYield);
    RUN_TEST(testSamePriorityBusyBusy_BusyYield);
    RUN_TEST(testDifferentPriorityBothBusyBusy);
    RUN_TEST(testDifferentPriorityBothBusyYield);
    UNITY_END();
}

int main( void )
{
    stdio_init_all();
    TaskHandle_t main_handle;
    xTaskCreate(tests, "Tests", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+10, &main_handle);
    vTaskStartScheduler();
    return 0;
}
