/*
 * Copyright (c) 2020 Nanjing Xiaoxiongpai Intelligent Technology Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ohos_init.h"
#include "cmsis_os2.h"
#include "PROJECT.h"

#define TASK_STACK_SIZE 1024 * 8
#define TASK_PRIO 25

PROJECT_Data_TypeDef PROJECT_Data;

static void Example_Task(void)
{
    PROJECT_Init();

    while (1)
    {
        printf("\r\n=======================================\r\n");
        printf("\r\n*************PROJECT***********\r\n");
        printf("\r\n=======================================\r\n");

        PROJECT_Read_Data();

        printf("\r\n现在光强是  %.2f\r\n", PROJECT_Data.Lux);



        if (PROJECT_Data.Lux > 800)
        {
            //Light_StatusSet(ON);
            printf("\r\n室内光线过亮，应减小玻璃透光度\r\n");   
        }
        else if (PROJECT_Data.Lux < 20)
        {
            //Light_StatusSet(OFF);
            printf("\r\n室内光线过暗，应增大玻璃透光度\r\n");  
        }
        else
        {
            printf("\r\n玻璃无需进行调节操作\r\n"); 
        }

        if(PROJECT_Data.Humidity > 50)
        {
            printf("\r\n感应到水滴\r\n");
        }
        else
        {
            printf("\r\n未感应到水滴\r\n");
        }
        //printf("\r\nHumidity is  %.2f\r\n", PROJECT_Data.Humidity);
        //printf("\r\nTemperature is  %.2f\r\n", PROJECT_Data.Temperature);

        if (PROJECT_Data.Temperature > 30)
        {
            printf("\r\n灰尘较多，应进行清洁。\r\n");
        }
        else
        {
            printf("\r\n灰尘较少，无需操作。\r\n");
        }

        usleep(10000000);
    }
}

static void ExampleEntry(void)
{
    osThreadAttr_t attr;

    attr.name = "Example_Task";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TASK_STACK_SIZE;
    attr.priority = TASK_PRIO;

    if (osThreadNew((osThreadFunc_t)Example_Task, NULL, &attr) == NULL)
    {
        printf("Falied to create Example_Task!\n");
    }
}

APP_FEATURE_INIT(ExampleEntry);