#include <xc.h>
#include <string.h>
#include "cabecera.h"
#include "LCD.h"
#include "U1SERIAL.h"
#define _XTAL_FREQ 32000000UL


void configuro(void) {
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //configuracion de los puertos
    TRISC = 0X00;   //RC salidas
    ANSELC = 0XFE;  //RC digitales
    TRISB = 0XFF;   //RB entrada
    ANSELB = 0X00;  //RB digitales
    TRISFbits.TRISF3 = 0;    //RF3 salida
    ANSELFbits.ANSELF3 = 0;  //RF3 digital
    WPUB =0X1F;    //Pull up Botones RB0, RB1, RB4
    WPUF =0X08;    //Pull up Led RF3
    //configuraciones de la E/S de bluetooth
    TRISFbits.TRISF0 = 0;   //RF0 como salida TX
    ANSELFbits.ANSELF0 = 0; //RF0 como digital TX
    TRISFbits.TRISF1 = 1;   //RF1 como entrada RX
    ANSELFbits.ANSELF1 = 0; //RF1 como digital RX
    TRISD = 0X00;     //RD salidas LCD 16X2
    ANSELD = 0X00;    //RD digitales LCD 16X2
   
    LATFbits.LATF3=1; LED
    LATCbits.LATC0=0; //Buzzer
}


void main(void) {
    configuro();

    LCD_INIT();

    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Micro Semana 13");
    U1_INIT(BAUD9600);

    while(1){
        char valor = U1_DATA_RECIEVE();
        if(valor == '1'){
            LATFbits.LATF3=0;
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("Prendido");
        }else if(valor == '2'){
            LATFbits.LATF3=1;
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("Apagado");
        }
       
    }
}

