#include "planificador.h"

/* Lista interna de tareas a ejecutarse */
struct Task* _scheduled_tasks[MAX_TASKS];

tTime TimeNow()
{

	struct timespec tms;

	if (clock_gettime(CLOCK_MONOTONIC,&tms)) {
		return -1;
	}

	tTime now = (tms.tv_sec * 1000) + tms.tv_nsec/1000000;

	/* redondear hacia arriba */
    if (tms.tv_nsec % 1000000 > 500000)
        ++now;

	return now;
}

tTime TimePassed(tTime since)
{
	tTime now = TimeNow();

	return now - since;
}

bool SchedulerAddTask(struct Task* t)
{
	/* TODO: Agregar t a la lista interna de tareas */
	for(int i=0;i<MAX_TASKS;i++){
		if(_scheduled_tasks[i]==NULL){
			_scheduled_tasks[i]=t;
			return true;
		}
	}
	return false;
}

void SchedulerRun()
{
	/* TODO: Recorrer la lista interna de tareas y ejecutar una tarea habilitada con runNextAt expirado */
	
	for(int i=0;i<MAX_TASKS;i++){
		
		if(_scheduled_tasks[i]!=0){
			if(_scheduled_tasks[i]->enabled == true){
				if(_scheduled_tasks[i]->timeBetweenRuns == 0){
					if(_scheduled_tasks[i]->runNextAt <= TimeNow()){		
								_scheduled_tasks[i]-> callback();
								_scheduled_tasks[i]-> enabled = false;
								_scheduled_tasks[i] == NULL;
								free(_scheduled_tasks[i]);
							}
					}else{
					if(_scheduled_tasks[i]->runNextAt <= TimeNow()){
						_scheduled_tasks[i]-> callback();
						TaskResetPeriodic(_scheduled_tasks[i]);
					}
				}
			}
		}
	}
}


struct Task *TaskNew(tTime now, tTime timeFromNow, tTime timeBetweenRuns, TaskCallback callback)
{
	/* TODO: Crear una tarea en el heap, incializar la tarea */
		struct Task *puntero = calloc(1,sizeof(struct Task));
		puntero->runNextAt = timeFromNow + now;
		puntero->timeBetweenRuns = timeBetweenRuns;
		puntero->callback = callback;
		puntero->enabled = false;
		return puntero;
}

void TaskResetPeriodic(struct Task *t)
{
	t->runNextAt = TimeNow() + t->timeBetweenRuns;
}

void TaskSetNextTime(struct Task *t, tTime timeFromNow)
{
	t->runNextAt = TimeNow() + timeFromNow;
}

void TaskDisable(struct Task* t)
{
	t->enabled = false;
}

void TaskEnable(struct Task* t)
{
	t->enabled = true;
}
