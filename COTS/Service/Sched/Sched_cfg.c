/*
 * Sched_cfg.c
 *
 *  Created on: Mar 19, 2023
 *      Author: Esraa Beshir
 */


#include "../../LIB/STD_TYPES.h"
#include "Sched.h"
#include "Sched_cfg.h"

/*extern void App1_Task(void);
extern void App2_Task(void);
extern void App3_Task(void);
extern void App4_Task(void);
extern void Switch_Task (void);*/
extern void LCD_Task(void);
extern void App5_Task(void);

const TasksInfo_t TasksInfo[Tasks_Number]={
		/*[0]={
				.name = "Led Toggle 250m",
				.runnable = App1_Task,
				.TaskPeriodms = 250,
				.StartDelayms =0,
		},
		[1]={
				.name = "Led Toggle 500m",
				.runnable = App2_Task,
				.TaskPeriodms = 500,
				.StartDelayms =0,
		},
		[2]={
						.name = "Led Toggle 1000m",
						.runnable = App3_Task,
						.TaskPeriodms = 1000,
						.StartDelayms =0,
		},
		[3]={
								.name = "Led Toggle by switch",
								.runnable = App4_Task,
								.TaskPeriodms = 50,
								.StartDelayms =0,
		},
		[4]={
										.name = "Led Toggle by switch",
										.runnable = Switch_Task,
										.TaskPeriodms = 5,
										.StartDelayms =0,
				},*/
		[0]={
				.name = "LCD_Task",
				.runnable = LCD_Task,
				.TaskPeriodms = 2,
				.StartDelayms =0,
			},
			[1]={
				.name = "APP 5",
				.runnable = App5_Task,
				.TaskPeriodms = 500,
				.StartDelayms =0,
			},

};
