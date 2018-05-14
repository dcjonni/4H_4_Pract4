#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, STVREN, NOLVP, NODEBUG,
#use delay(clock=16000000)
#use fast_io(B)
#use fast_io(C)
#use fast_io(D)

int contadorDosientosMS;
int contadorQuinientosMS;
int contadorSegundo;
int banderaUno, banderaDos, banderaTres;

#INT_TIMER0
VOID TIMER0_ISR(VOID){
   
   contadorDosientosMS++;
   contadorQuinientosMS++;
   contadorSegundo++;
   if(contadorDosientosMS==2){
      contadorDosientosMS=0;
      banderaUno=1;
   }
   if(contadorQuinientosMS==5){
      contadorQuinientosMS=0;
      banderaDos=1;
   }
   if(contadorSegundo==10){
      contadorSegundo=0;
      banderaTres=1;
   }
   set_timer0 (0x3CB0);
}

void main(){
   set_tris_b(0x00);
   set_tris_c(0x00);
   set_tris_d(0x00);
   output_b(0x00);
   output_c(0x00);
   output_d(0x00);
   setup_timer_0(RTCC_DIV_8 | RTCC_INTERNAL);
   set_timer0 (0x3CB0);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   int displayDosientosMS=0, displayQuinientosMS=0, displaySegundo=0;
   while(true){
      if(banderaUno){
         banderaUno=0;
         output_b(displayDosientosMS);
         displayDosientosMS++;
         if(displayDosientosMS==10){
            displayDosientosMS=0;
         }
      }
      if(banderaDos){
         banderaDos=0;
         output_c(displayQuinientosMS);
         displayQuinientosMS++;
         if(displayQuinientosMS==10){
            displayQuinientosMS=0;
         }
      }
      if(banderaTres){
         banderaTres=0;
         output_d(displaySegundo);
         displaySegundo++;
         if(displaySegundo==10){
            displaySegundo=0;
         }
      }
   }
}
