#ifndef __SYS_ARCH_H__
#define __SYS_ARCH_H__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

typedef xSemaphoreHandle sys_sem_t;
typedef xSemaphoreHandle sys_mutex_t;
typedef xQueueHandle sys_mbox_t;
typedef xTaskHandle sys_thread_t;

#define sys_mbox_valid( x ) ( ( ( *x ) == NULL) ? pdFALSE : pdTRUE )
#define sys_mbox_set_invalid( x ) ( ( *x ) = NULL )
#define sys_sem_valid( x ) ( ( ( *x ) == NULL) ? pdFALSE : pdTRUE )
#define sys_sem_set_invalid( x ) ( ( *x ) = NULL )

#define LWIP_COMPAT_MUTEX 0

#if LWIP_NETCONN_SEM_PER_THREAD

sys_sem_t* sys_thread_sem_init(void);
void sys_thread_sem_deinit(void);
sys_sem_t* sys_thread_sem_get(void);
err_t sys_mutex_trylock(sys_mutex_t *pxMutex);

#define LWIP_NETCONN_THREAD_SEM_ALLOC() sys_thread_sem_init()
#define LWIP_NETCONN_THREAD_SEM_FREE()  sys_thread_sem_deinit()
#define LWIP_NETCONN_THREAD_SEM_GET()   sys_thread_sem_get()
#endif

#endif /* __SYS_ARCH_H__ */