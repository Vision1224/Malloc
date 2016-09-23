#include "stdio.h"
#include "stdlib.h"
#include "myAllocator.h"
#include "sys/time.h"
#include <sys/resource.h>
#include <unistd.h>

double diffTimeval(struct timeval *t1, struct timeval *t2) {
  double d = (t1->tv_sec - t2->tv_sec) + (1.0e-6 * (t1->tv_usec - t2->tv_usec));
  return d;
}

void getutime(struct timeval *t)
{
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  *t = usage.ru_utime;
}

int main() 
{
  void *p1, *p2, *p3, *p4,*p5,*p6,*p7,*p8,
    *p9,*p10,*p11, *p12,*p13,*p14,*p15,*p16, *p17, *p18;
   //  p =bestFitAllocRegion(65520);
  p1 =bestFitAllocRegion(65512);
  p2 =bestFitAllocRegion(65504);
  p3 =bestFitAllocRegion(65496);
  p4 =bestFitAllocRegion(65488);
  p5 =bestFitAllocRegion(65480);
  p6 =bestFitAllocRegion(65472);
  p7 =bestFitAllocRegion(65464);
  p8 =bestFitAllocRegion(65456);
  p9 =bestFitAllocRegion(65448);
  p10 =bestFitAllocRegion(65440);
  p11=bestFitAllocRegion(65432);
  p12 =bestFitAllocRegion(65424);
  p13 =bestFitAllocRegion(65416);
  p14 =bestFitAllocRegion(65408);
  p15 =bestFitAllocRegion(65400);
  p16 =bestFitAllocRegion(65392);
  printf("finished allocating \n");
  arenaCheck(); 
  printBlockInfo();
  
  printf("freeing p%d\n",2);
  freeRegion(p2);  
  printf("freeing p%d \n",4);
  freeRegion(p4);  
  printf("freeing p%d \n",6);
  freeRegion(p6);  
  printf("freeing p%d \n",8);
  freeRegion(p8);  
  printf("freeing p%d \n",10);
  freeRegion(p10);  
  
  freeRegion(p16);  
  freeRegion(p15);  
  freeRegion(p7);  
  freeRegion(p14);  
  
  printBlockInfo();
  arenaCheck();


  p17 =bestFitAllocRegion(6554);

  p18= resizeRegion(p1, 300000);
   
  printBlockInfo();
  arenaCheck();
  printf("pppppppppp \n");
  free(p4);
  free(p3);
  free(p5);
  free(p1);
  {                             /* measure time for 10000 mallocs */
    struct timeval t1, t2;
    int i;
    getutime(&t1);
    
    // can only reach 43690 because (2^20)\(sizeof(prefix) + sizeof(suffix) + 8)
    //where 8 is the size that is allocated for any value of 1-8
    for(i = 0; i < 10000; i++)
      if (malloc(4) == 0) 
        break;
    getutime(&t2);
    printf("%d malloc(4) required %f seconds\n", i, diffTimeval(&t2, &t1));
  }
  return 0;
}



/*
int main() 
{
  void *p1, *p2, *p3;
  arenaCheck();
  p1 = malloc(950);
  arenaCheck();
  printf("P1:[%llx] \n", (long long)p1);
  free(p1);
  arenaCheck();  // p1 = malloc(254);
  printf("P1:[%llx] \n", (long long)p1);
  p2 = malloc(25400);
  arenaCheck();
  p3 = malloc(254);
  


  //printf("%llx %llx %llx\n", (long long)p1, (long long)p2, (long long)p3);
  printf("P1:[%llx] P2:[%llx]  P2:[%llx]\n", (long long)p1, (long long)p2, (long long)p3);
  arenaCheck();
  free(p2);
  arenaCheck();
  free(p3);
  arenaCheck();
  free(p1);
  arenaCheck();  // p1 = malloc(254);

  {                             // measure time for 10000 mallocs 
    struct timeval t1, t2;
    int i;
    getutime(&t1);
    for(i = 0; i < 10000; i++)
      if (malloc(4) == 0) 
        break;
    getutime(&t2);
    printf("%d malloc(4) required %f seconds\n", i, diffTimeval(&t2, &t1));
  }
  return 0;
}


*/
