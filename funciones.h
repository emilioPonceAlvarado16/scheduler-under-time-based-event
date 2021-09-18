#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

typedef enum {EXIT = 0, RED, GREEN, YELLOW, EMERGENCY} STATE;
typedef enum {NO_EVENT = 0, STOP_COMMAND, GO_COMMAND, TIMER_TIMEOUT} EVENT;

void luz_verde();
void luz_roja();
void luz_amarilla();
void parpadea_roja();
