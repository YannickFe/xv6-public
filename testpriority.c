#include "types.h"
#include "user.h"
#define PRIO_MIN 0
#define PRIO_MAX 99
#define PRIO_DEFAULT 50

int fails = 0; // global number of test fails

// document failed test
void fail(int test, char *explanation){
  fails++;
  printf(1,"Failed test %d: %s\n",test,explanation); 
}

int main (int argc, char *argv[])
{
  int p;

  printf(1,"Starting setpriority test\n");

  // test initial priority
  p = setpriority((int)PRIO_DEFAULT);
  if (p != PRIO_DEFAULT) fail(1,"default priority");

  // test lower limit
  p = setpriority(PRIO_MIN-1);
  if (p != -1) fail(2,"prio too low");
  p = setpriority(PRIO_MIN);
  if (p == -1) fail(3,"min prio");

  // test upper limit
  p = setpriority(PRIO_MAX+1);
  if (p != -1) fail(4,"prio too high");
  p = setpriority(PRIO_MAX);
  if (p == -1) fail(5,"max prio");

  // set to different priorities
  p = setpriority(20);
  if (p != PRIO_MAX) fail (6,"old value ");
  p = setpriority(30);
  if (p != 20) fail(7,"setting to 20");
  p = setpriority(80);
  if (p != 30) fail(8,"setting to 30");
  p = setpriority(88);
  if (p != 80) fail(9,"setting to 80");

  // fork test last - only child continues
  
  if (fork() == 0) {
    // check if child has prio 88
    p = setpriority(PRIO_DEFAULT);
    if (p != 88) fail(10,"fork");
    printf(1,"Finished setpriority test with %d fails\n",fails);
    exit();
  } else {
    wait();
  }

  exit();
}
