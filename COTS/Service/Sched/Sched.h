/*
 * Sched.h
 *
 *  Created on: Mar 19, 2023
 *      Author: Esraa Beshir
 */

#ifndef SERVICE_SCHED_SCHED_H_
#define SERVICE_SCHED_SCHED_H_


typedef void (*RunnableCBF_t)(void);

void Sched_Init(void);
void Sched_Start(void);

#endif /* SERVICE_SCHED_SCHED_H_ */
