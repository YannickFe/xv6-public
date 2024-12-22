// test scheduler
#include "types.h"
#include "user.h"

void run(char *name, int duration) {

  int i;

  for (i = 0; i < duration; i++) {
    printf(1,name);
    sched_yield();
  }
}


void forkrun(char *name, int duration, int prio) {
  if (fork() == 0) {
    setpriority(prio);
    //printf(1,"\n+++ starting: %s prio: %d\n",name, prio);
    sched_yield();
    run(name, duration);
    //printf(1,"\n--- done:     %s\n",name);
    exit();
  }
  // do nothing in parent
}

int main (int argc, char *argv[])
{
  setpriority(10);  

  // run different processes with different priorities
  printf(1, "\n*** Test 1: equal priorities A=B=C=D=50 ***\n"); 
  forkrun("A", 10, 50);
  forkrun("B", 10, 50);
  forkrun("C", 10, 50);
  forkrun("D", 10, 50);
  // wait for all children to terminate 
  while (wait() != -1);

  printf(1, "\n*** Test 2: different priorities A=50,B=51,C=52,D=53***\n"); 
  forkrun("A", 10, 50);
  forkrun("B", 10, 51);
  forkrun("C", 10, 52);
  forkrun("D", 10, 53);
  // wait for all children to terminate 
  while (wait() != -1);

  printf(1, "\n*** Test 3: 2 priority groups A=B=C=60, D=E=F=50 ***\n"); 
  forkrun("A", 10, 60);
  forkrun("B", 10, 60);
  forkrun("C", 10, 60);
  forkrun("D", 10, 50);
  forkrun("E", 10, 50);
  forkrun("F", 10, 50);
  // wait for all children to terminate 
  while (wait() != -1);

  printf(1, "\n*** Test 4: higher priority starts later A=60,B=60,C=50 ***\n"); 
  forkrun("A", 40, 60);
  forkrun("B", 40, 60);
  sleep(1);
  forkrun("C", 10, 50);
  // wait for all children to terminate 
  while (wait() != -1);
  printf(1,"\n*** finished ***\n");
  exit();

}
