
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"data.h"
#include"memory.h"
#include"project_1.h"

#ifdef FRDM
 #define printf(...)
#endif

int main(void)
{
#ifndef switch_OFF
    project_1_report();
#endif

#ifdef switch_OFF
    printf("Project is turned OFF");
#endif
return 0;
}
