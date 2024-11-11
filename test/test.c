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

TaskHandle_t firstThread;
TaskHandle_t secondThread;

TaskFunction_t primary;
TaskFunction_t secondary;

void setUp(void) {
}

void tearDown(void) {
}

void priorityInversionBinary() {
    xSemaphoreTake(semaphore, portMAX_DELAY);

    semaphore = xSemaphoreCreateBinary();

    xTaskCreate(primary, "First", configMINIMAL_STACK_SIZE, "FirstThread", tskIDLE_PRIORITY+(1), &firstThread);
    vTaskDelay(100);

    xTaskCreate(secondary, "Second", configMINIMAL_STACK_SIZE, "SecondThread", tskIDLE_PRIORITY+(2), &secondThread);

    busy_wait_us(1000);

    xSemaphoreGive(semaphore);

    vSemaphoreDelete(semaphore);
}

void priorityInversionMutex() {
    xSemaphoreTake(semaphore, portMAX_DELAY);

    semaphore = xSemaphoreCreateMutex();

    xTaskCreate(primary, "First", configMINIMAL_STACK_SIZE, "FirstThread", tskIDLE_PRIORITY+(1), &firstThread);
    vTaskDelay(100);

    xTaskCreate(secondary, "Second", configMINIMAL_STACK_SIZE, "SecondThread", tskIDLE_PRIORITY+(2), &secondThread);

    busy_wait_us(1000);

    xSemaphoreGive(semaphore);

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
    TEST_ASSERT_EQUAL_INT(1, 1);
}

void testSamePriorityBothBusyYield() {
    TEST_ASSERT_EQUAL_INT(1, 1);

}

void testSamePriorityBusyBusy_BusyYield() {
    TEST_ASSERT_EQUAL_INT(1, 1);

}

void testDifferentPriorityBothBusyBusy() {
    TEST_ASSERT_EQUAL_INT(1, 1);

}

void testDifferentPriorityBothBusyYield() {
    TEST_ASSERT_EQUAL_INT(1, 1);

}

void tests() {
    UNITY_BEGIN();
    RUN_TEST(testSamePriorityBothBusyBusy);
    RUN_TEST(testSamePriorityBothBusyYield);
    RUN_TEST(testSamePriorityBusyBusy_BusyYield);
    RUN_TEST(testDifferentPriorityBothBusyBusy);
    RUN_TEST(testDifferentPriorityBothBusyYield);
    UNITY_END();
    vTaskDelay(1000);
}

int main( void )
{
    stdio_init_all();
    TaskHandle_t main_handle;
    xTaskCreate(tests, "Tests", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+10, &main_handle);
    vTaskStartScheduler();
    return 0;
}
