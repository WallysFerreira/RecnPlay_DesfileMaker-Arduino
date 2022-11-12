// codigo geral do dia
int LED = 11;

float sinVal;
int ledVal;



//--------------------------------FUNCAO GRADATIVAMENTE & ACELERA COM O TEMPO
void gradativamente(){
  for (int x=0; x<180; x++) {
    // converte graus para radianos e então obtém o valor do seno
    sinVal = (sin(x*(3.1412/180)));
    ledVal = int(sinVal*255);
    analogWrite(LED, ledVal);
    delay(25);
  }
 }



//--------------------------------FUNCAO SO ACENDER
 void apenasAcender(){
    digitalWrite(LED, HIGH);                                           //acender led
    delay(300);                                                        //após 300milisegundos
 }



//-------------------------------FUNCAO ACENDER E APAGAR RAPIDO
 void acenderApagar(){
    digitalWrite(LED, HIGH);                                           //acender led
    delay(300);                                                        //esperar 300milisegundos
    digitalWrite(LED, LOW);                                            //apagar led
    delay(300);                                                        //esperar 300milisegundos 
 }



//-------------------------------ACENDER E APAGAR DE FORMA GRADUAL
void gradual(){                                                        //Lembrar de conectar numa porta PWN para funcinar (a porta com o ~
  for(int i=0; i<=255; i++){                                           //acendendo o led conforme o number 'i' que vai de 0 - 255
    analogWrite(LED, i);
    delay(3);                                                          //espera cerca de 3milisigundos para voltar ao inicio do for e acender +1 ao led
  }
  delay(400);                                                          //tempo do termino de um for(acender) e inicio do for(apagar)
 
  for(int i=255; i>=0; i--){                                           //apagando o led confotme o number 'i' que vai de 0 - 255
    analogWrite(LED, i);
    delay(3);
  }
  delay(400);
}

//--------------------------------MAIN
void setup() 
{
  pinMode(LED, OUTPUT);                                                //especificando se é uma porta de entrada ou de saida
}
 
void loop() 
{

  gradativamente();                                                    //chamado da funcao que acende e apagua gradativamente e vai acelerando com o tempo
  apenasAcender();                                                     //chamado da funcao que apenas acende
  acenderApagar();                                                     //chamado da funcao que apenas acende e apaga
  gradual();                                                           //chamado da funcao que acende de forma gradual e apaga da mesma maneira
  /*lembrar de [usar/fazer/modificar] millis*/

}
