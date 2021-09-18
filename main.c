#include "funciones.h"
#include "planificador.h"
#include <signal.h>
#include <unistd.h>

#define YELLOW_TIMEOUT 2000 //Timeout estado YELLOW en milisegundos
#define BLINK_PERIOD 1000   //Periodo parpadeo luz roja en milisegundos
#define TICK 10             //System TICK del planificador en milisegundos

volatile STATE estado;
volatile EVENT evento;
struct Task *Task2;
struct Task *Task3;
bool parpadeo;

/* TODO: Crear callback para timeout estado YELLOW */
//TaskCallback amarilloCall = luz_amarilla;
TaskCallback tarea_roja = luz_roja;
/* TODO: Crear callback para parpadeo luz roja en estado EMERGENCY */
TaskCallback tarea_emergencia = parpadea_roja;

/* Handler señales */
void handler(int sig)
{
  switch(sig){
    case SIGUSR1:
      evento = GO_COMMAND;
      break;
    case SIGUSR2:
      evento = STOP_COMMAND;
      break;
    case SIGINT: //En una emergencia, ir directamente al estado emergencia
      estado = EMERGENCY;
      break;
    default:
      evento = NO_EVENT;
  }
}

int main(int argc, char const *argv[])
{
  
  estado=RED;
  evento=NO_EVENT;

  signal(SIGUSR1, handler); //SIGUSR1: GO_COMMAND
  signal(SIGUSR2, handler); //SIGUSR2: STOP_COMMAND
  signal(SIGINT, handler);  //SIGINT / Ctrl-C : EMERGENCY 

  printf("Programa iniciado, PID: %d\n", getpid());

  tTime yellowTimeStart = 0;

  luz_roja();
  
  Task3 = (struct Task*) TaskNew(TimeNow(),BLINK_PERIOD,1,tarea_emergencia);
  SchedulerAddTask(Task3); 
  
  while(estado){
    switch(estado){
      case RED:
     
        if(evento == GO_COMMAND){
        	estado = GREEN;
          luz_verde();
          
        }
        
        evento = NO_EVENT;
          
        break;
      case GREEN:
        if(evento == STOP_COMMAND){
        	estado = YELLOW;
          yellowTimeStart = TimeNow();
          luz_amarilla();
        }
        evento = NO_EVENT;
        break;
      case YELLOW:
        /* TODO: Modificar este estado para disparar el evento TIMER_TIMEOUT con una tarea  */
    
        
            Task2 = (struct Task*) TaskNew(yellowTimeStart,YELLOW_TIMEOUT,0,tarea_roja);
            if(SchedulerAddTask(Task2) == true){
              TaskEnable(Task2);
            }
            estado = RED;
        
        break;
      case EMERGENCY:
        /* TODO: Parpadear luz_roja usando una tarea */
        TaskEnable(Task3);
        /* TODO: Asegurar salida de este estado */
          if(evento==GO_COMMAND || evento==STOP_COMMAND){
            estado = RED;
            evento = NO_EVENT;
            luz_roja();
            TaskDisable(Task3);
          }
        
        break;
      default:
        estado = EXIT;
    }

    /* TODO: Correr el planificador */
    if (TimePassed(yellowTimeStart) > TICK){
      parpadeo =! parpadeo;    
      SchedulerRun();
    }
  }
}
