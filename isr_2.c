#include <xc.h>
#include "mian.h"
extern unsigned char sec;
extern unsigned char return_time;

void __interrupt() isr(void)
{
    static unsigned int count = 0;
    
    if (TMR2IF == 1)
    {
        if (++count == 1250)
        {
            count = 0;
            if(sec>0){
                sec--;
            }
            else if(return_time>0){
                return_time--;
            }
            
           // LED1 = !LED1;
        }
        
        TMR2IF = 0;
    }
}