/*
 * File:   microoven.c
 * Author: kallu
 *
 * Created on 23 February, 2025, 3:08 PM
 */



#include "main.h"
extern int sec1, min1;
extern int flag ;
extern char sec[];
extern char min[];
extern int j, m ;
 extern unsigned char key;
   extern unsigned char once ;

void startscreen(){
    for (int i = 0; i < 16; i++) {

        clcd_putch(0xff, LINE1(i));
        __delay_ms(70);
    }
   clcd_print("powering on", LINE2(3));
   clcd_print("Microwave oven", LINE3(1));
       for (int i = 0; i < 16; i++) {

        clcd_putch(0xff, LINE4(i));
        __delay_ms(70);
    }
}
void clear_screen() {
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    __delay_us(500);
}
void set_time(){
    clcd_print("SET TIME <MM:SS>", LINE1(0));
            clcd_print("TIME", LINE2(0));
            clcd_print(min, LINE2(5));
            clcd_print(":", LINE2(7));
            clcd_print(sec, LINE2(8));
            clcd_print("     ",LINE2(10));
            clcd_print("* clear  # enter", LINE4(0));
            __delay_ms(10);

            if (key >= 0 && key <= 9) {
                if (j == 1) {
                    sec[j--] = key + '0';
                } else if (j == 0) {
                    sec[0] = sec[1];
                    sec[1] = key + '0';
                    j--;
                } else if (m == 1) {
                    min[m--] = key + '0';
                } else if (m == 0) {
                    min[0] = min[1];
                    min[1] = key + '0';
                    m--;
                }

            }
            if (key == '*') {
                strcpy(min, "00");
                strcpy(sec, "00");
                m = 1;
                j = 1;
            }
            if (key == '#') {
                m = 1;
                j = 1;
                clear_screen();
                sec1 = sec[0] - '0';
                sec1 = sec1 * 10 + sec[1] - '0';
                min1 = min[0] - '0';
                min1 = min1 * 10 + min[1] - '0';
                if(sec1>59){
                    sec1=sec1-59;
                    min1++;
                }
                RC2 = 1;
                TMR2IF = 1;
                flag = 5;
                if (sec1 == 0 && min1 == 0) {
                    flag = 0;
                    once = 1;
                }
                strcpy(min, "00");
                strcpy(sec, "00");




            }
            if (j >= 0) {
                clcd_print("  ", LINE2(8));
                __delay_ms(3);
            } else {
                clcd_print("  ", LINE2(5));
                __delay_ms(3);

            }



}