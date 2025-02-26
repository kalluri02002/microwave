#include "main.h"
extern int sec1;
extern int min1;
extern int flag;

void __interrupt() isr(void)
{
    static unsigned int count = 0;
    
    if (TMR2IF == 1)  // Check if Timer2 caused the interrupt
    {
        if (++count == 1250)  // Adjust count based on Timer2 overflow rate
        {
            count = 0;
            
            if (sec1 > 0)
            {
                sec1--;
                
                if (sec1 == 0)
                {
                    if (min1 > 0)
                    {
                        min1--;
                        sec1 = 59;
                    }
                    else if(flag==10){
                        //clear_screen();
                        flag=2;
                         
                    }
                    else
                    {
                       //clear_screen();
                        flag = 12;  // Indicate timer expiration
                    }
                }
            }
        }

        TMR2IF = 0;  // ? Always clear the Timer2 interrupt flag
    }
}
