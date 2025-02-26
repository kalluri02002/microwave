/*
 * File:   main.c
 * Author: kalluri Naveen
 *
 * Created on 23 February, 2025, 1:12 PM
 */

#include "main.h"
#pragma config WDTE = OFF 

void init_config() {
    // seting the fan is output
    TRISC2 = 0;
    //intializing timer to
    init_timer2();
    // setting the buzzer out put
    TRISC1 = 0;
    //init clcd to intilzing clcd
    init_clcd();
    // intilizing the matrix key pad 
    init_matrix_keypad();
    // intializing  interutp peripage and global interrupt
    PEIE = 1;
    GIE = 1;
}
// used to track sec and min
int sec1 = 0, min1 = 0;
// used track sreeen
int flag = 0;
// which used to print in clcd min and sec
char sec[] = "00";
char min[] = "00";
// track sec and min
int j = 1, m = 1;
// input and of matrix key pad
unsigned char key;
// which used to blaock keys s
unsigned char once = 1;

void main(void) {
    init_config();
    // tempearature
    unsigned char temp[] = "000";
    // it is start screen
    startscreen();


    // for tempearure value
    char k = 2;
    // temp number for 
    int temp1 = 0;





    clear_screen();
    while (1) {
        // input from matrix key pad
        key = read_matrix_keypad(STATE);
        // checking four options
        if (key == 1 && once == 1) {
            flag = 1;
            clear_screen();
            clcd_print("Power = 900 W", LINE2(2));
            __delay_ms(450);
            clear_screen();
            once = 0;
            key = 0xff;

        } else if (key == 2 && once == 1) {
            flag = 2;
            clear_screen();
            once = 0;
            key = 0xff;
        } else if (key == 3 && once == 1) {
            flag = 3;
            clear_screen();
            once = 0;
            key = 0xff;

        } else if (key == 4 && once == 1) {
            flag = 4;
            clear_screen();
            once = 0;
            key = 0xff;
        }
        // main menu
        if (flag == 0) {


            clcd_print("1.Micro", LINE1(0));
            clcd_print("2.Grill", LINE2(0));
            clcd_print("3.Convection", LINE3(0));
            clcd_print("4.Start", LINE4(0));

        }
            // screen for micro
        else if (flag == 1) {


            set_time();

        }            // screen for grill
        else if (flag == 2) {
            set_time();

        }
            // screen for covectional
        else if (flag == 3) {
            clcd_print("Set Temp   <*c>", LINE1(0));
            clcd_print("Temp =", LINE2(0));
            clcd_print(temp, LINE2(7));
            clcd_print("* clear  # enter", LINE4(0));
            if (key >= 0 && key <= 9) {
                if (k == 2) {
                    temp[k--] = key + '0';
                    temp1 = key;
                } else if (k == 1) {
                    temp[1] = temp[2];
                    temp[2] = key + '0';
                    k--;
                    temp1 = temp1 * 10 + key;
                } else if (k == 0) {
                    temp[0] = temp[1];
                    temp[1] = temp[2];
                    temp[2] = key + '0';
                    k--;
                    temp1 = temp1 * 10 + key;

                }


            }
            if (key == '*') {
                k = 2;
                strcpy(temp, "000");

            }
            if (key == '#') {
                if (temp1 <= 180) {
                    strcpy(temp, "000");
                    flag = 10; // pre heating
                    sec1 = 60;
                    k = 2;
                    clear_screen();

                } else {
                    strcpy(temp, "000");
                    flag = 102; // pre heating
                    //sec1=60;
                    k = 2;
                    clear_screen();

                }


            }

        }
            // screen for start
        else if (flag == 4) {
            sec1 = 30;
            flag = 5;
        }            // which is used to time screen for all screeans
        else if (flag == 5) {

            clcd_print("TIME =", LINE1(3));
            //clcd_print("sec", LINE(13));
            clcd_print("5.Start/resume", LINE2(0));
            clcd_print("6.Pause", LINE3(0));
            clcd_print("7.Stop", LINE4(0));

            clcd_putch((min1 / 10) + '0', LINE1(10));
            clcd_putch((min1 % 10) + '0', LINE1(11));
            clcd_putch(':', LINE1(12));
            clcd_putch((sec1 / 10) + '0', LINE1(13));
            clcd_putch((sec1 % 10) + '0', LINE1(14));




            if (key == 5) {
                //clear_screen();
                // used add 30 sec and start time
                if (TMR2ON == 1) {
                    sec1 += 30;
                    if (sec1 > 59) {
                        sec1 = sec1 - 59;
                        min1++;
                    }

                }
                TMR2ON = 1;

            }
            // used to time of
            if (key == 6) {
                // clear_screen();
                TMR2ON = 0;
            }
            // stop all the fuction goto menu
            if (key == 7) {
                clear_screen();
                flag = 0;
                RC2 = 0;
                sec1 = 0;
                min1 = 0;
                once = 1;

            }
        }            // screen for 60 sec count
        else if (flag == 10) {
            clcd_print("Pre-Heating", LINE1(2));
            clcd_print("time left : 0", LINE2(0));
            clcd_putch((sec1 / 10) + '0', LINE2(13));
            clcd_putch((sec1 % 10) + '0', LINE2(14));


        }            // used to last screen
        else if (flag == 12) {
            RC1 = 1;

            clear_screen();
            clcd_print("Time up", LINE2(3));
            clcd_print("enjoy your meal", LINE3(0));
            RC2 = 0;
            __delay_ms(900);
            flag = 0;
            once = 1;
            RC1 = 0;
            clear_screen();
        } else if (flag == 102) {
            RC1 = 1;
            clear_screen();
            clcd_print("Temperature high", LINE2(0));
            //  clcd_print("enjoy your meal", LINE3(0));
            //  RC2 = 0;
            __delay_ms(1500);
            flag = 0;
            once = 1;
            RC1 = 0;
            clear_screen();
        }
    }
}
