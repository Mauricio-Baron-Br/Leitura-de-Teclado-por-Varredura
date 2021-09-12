/*****************************************************************************/
/*RB0 EM ROW1 ATRAVES DE UM PULL-UP / RB4 EM COL3*/
/*RB1 EM ROW2 ATRAVES DE UM PULL-UP / RB5 EM COL2*/
/*RB2 EM ROW3 ATRAVES DE UM PULL-UP / RB6 EM COL1*/
/*RB3 EM ROW4 ATRAVES DE UM PULL-UP*/
/*****************************************************************************/
#include<16f877.h>
#use delay(clock=4000000)
#fuses NOWDT, XT, PUT, NOPROTECT, NOBROWNOUT, NOLVP, NOCPD, NOWRT
//defines
/*****************************************************************************/
#define tecla_0 0x00 //define um identificador para a tecla 0
#define tecla_1 0x01 //define um identificador para a tecla 1
#define tecla_2 0x02 //define um identificador para a tecla 2
#define tecla_3 0x03 //define um identificador para a tecla 3
#define tecla_4 0x04 //define um identificador para a tecla 4
#define tecla_5 0x05//define um identificador para a tecla 5
#define tecla_6 0x06 //define um identificador para a tecla 6
#define tecla_7 0x07 //define um identificador para a tecla 7
#define tecla_8 0x08 //define um identificador para a tecla 8
#define tecla_9 0x09 //define um identificador para a tecla 9
#define tecla_Sustenido  0x0A //define um identificador para a tecla #
#define tecla_Asterisco  0x0B //define um identificador para a tecla *
#define nenhuma_Tecla    0xFF //define um identificador para nada precionado
#define nadaDisplay      0x0C //define um identificador limpar display
/*****************************************************************************/
//mascara para simbolos numericos para display de sete segmentos
   int Disp7Seg[13]={
                     0b11111100, //posicao 0 --> 0 no dip
                     0b01100000, //posicao 1 --> 1 no dip
                     0b11011010, //posicao 2 --> 2 no dip
                     0b11110010, //posicao 3 --> 3 no dip
                     0b01100110, //posicao 4 --> 4 no dip
                     0b10110110, //posicao 5 --> 5 no dip
                     0b10111110, //posicao 6 --> 6 no dip
                     0b11100000, //posicao 7 --> 7 no dip
                     0b11111110, //posicao 8 --> 8 no dip
                     0b11110110, //posicao 9 --> 9 no dip
                     0b11000100, //posicao 10 --> # no dip
                     0b00111000, //posicao 11 --> * no dip
                     0b00000000, //posicao 12 --> desliga
   };
/*****************************************************************************/
//funcoes
//funcao de escrita no display
void EscreveDisplay(int ValorDisplay)
{
   output_d(Disp7Seg[ValorDisplay]);
}
//funcao de varedura do teclado
char Le_Teclado()
{
   output_low(pin_b6); //habilita a leitura da primeira coluna
   output_high(pin_b5);
   output_high(pin_b4);
   //realiza o teste em cada linha
   if(input(pin_b3)==0)
   {
      return(tecla_Sustenido);//tecla sustenido
      while(input(pin_b3)==0); // fica aqui ate soltar a tecla
   }
   if(input(pin_b2)==0)
   {
      return(tecla_7);//tecla 7
      while(input(pin_b2)==0); // fica aqui ate soltar a tecla
   }
   if(input(pin_b1)==0)
   {
      return(tecla_4);//tecla 4
      while(input(pin_b1)==0); // fica aqui ate soltar a tecla
   }
   if(input(pin_b0)==0)
   {
      return(tecla_1);//tecla 1
      while(input(pin_b0)==0); // fica aqui ate soltar a tecla
   }
   
   output_high(pin_b6); //habilita a leitura da segunda coluna
   output_low(pin_b5);
   output_high(pin_b4);
   //realiza o teste em cada linha
   if(input(pin_b3)==0)
   {
      return(tecla_0);//tecla 0
      while(input(pin_b3)==0); // fica aqui ate soltar a tecla
   }
   if(input(pin_b2)==0)
   {
      return(tecla_8);//tecla 8
      while(input(pin_b2)==0); // fica aqui ate soltar a tecla
   }
   if(input(pin_b1)==0)
   {
      return(tecla_5);//tecla 5
      while(input(pin_b1)==0); // fica aqui ate soltar a tecla
   }
   if(input(pin_b0)==0)
   {
      return(tecla_2);//tecla 2
      while(input(pin_b0)==0); // fica aqui ate soltar a tecla
   }
   
   output_high(pin_b6); //habilita a leitura da primeira coluna
   output_high(pin_b5);
   output_low(pin_b4);
   //realiza o teste em cada linha
   if(input(pin_b3)==0)
   {
      return(tecla_Asterisco);//tecla asterisco
      while(input(pin_b3)==0); // fica aqui ate soltar a tecla
   }
   if(input(pin_b2)==0)
   {
      return(tecla_9);//tecla 9
      while(input(pin_b2)==0); // fica aqui ate soltar a tecla
   }
   if(input(pin_b1)==0)
   {
      return(tecla_6);//tecla 6
      while(input(pin_b1)==0); // fica aqui ate soltar a tecla
   }
   if(input(pin_b0)==0)
   {
      return(tecla_3);//tecla 3
      while(input(pin_b0)==0); // fica aqui ate soltar a tecla
   }
   return(nenhuma_Tecla);//nehuma tecla precionada
}
/*****************************************************************************/
//programa principal
void main()
{
   char teclaPressionada;
   set_tris_d(0);          //configura o PORTD como saida
   set_tris_b(0b00001111); //configura RB0 a RB3 como entrada
   set_tris_c(0);          //configura PORTC como saida
   output_d(0);            //inicializa o display apagado
   while(1)
   {
      teclaPressionada = Le_Teclado();//realiza a varredura do teclado
      if(teclaPressionada == nenhuma_Tecla)
      {
         EscreveDisplay(nadaDisplay);//nenhuma tecla pressionada
         delay_ms(10);
      }
      else
      {
         EscreveDisplay(teclaPressionada); //caso alguma tecla seja pressionada o valor e mostrado no display
         delay_ms(10);
      }
   }
}
