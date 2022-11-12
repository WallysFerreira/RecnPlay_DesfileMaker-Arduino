/*
Código focado para receber e interagir com o site do Desfile Maker
Ao termino do codigo, juntar com a outra parte que terá as funçoes para o Manequim 
*/

/*
 * Esses includes ja estavam no codigo deles
#include <Arduino.h>
#include <ESP8266WiFi.h>          //para usar uma rede WiFi
#include <ESP8266WiFiMulti.h>     //usado para uma conexao WiFi mais forte
#include <ESP8266HTTPClient.h>    //utilizar uma API
#include <WiFiClient.h>           //
#include <ArduinoJson.h>          //
*/



//===============================================================================================================================================
/*
 * 1- Chamar WiFi
 * 2- Passar 3 Redes no Minimo para nao cair o site
 * 3- 
 */



//===============================================================================================================================================
// ---IMPORTANDO BIBLIOTECAS E CRIANDO STRUCT
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define NWIFIS 3                                                             // qtd de redes wifi = 3

struct redes  {                                                              //criaçao de struct para os wifi
  const char *ssid;
  const char *senha;
};

char *redeAtual;                                                             //variavel que vai receber o wifi que esta conectado

struct redes redeWifi[NWIFIS]={"SENAC-Mesh","09080706",
                               "iPhone de Arnott","arbbbe11",
                               "Vivo-Internet-E532", "6EFC366C"};            //struct dos wifis







//===============================================================================================================================================
// ---FUNCAO PARA CONECTAR NO PRIMEIRO WIFI DISPONIVEL
bool conectaWifi()
{
  bool conectou = false;
  int i=0;
  int qtd = 0;

  while( i < NWIFIS ){                                                       //faz a captura de cada uma das redes
    
      Serial.println("Conectando: wifi");
      Serial.println( redeWifi[i].ssid );
      WiFi.begin(redeWifi[i].ssid, redeWifi[i].senha);                       //passando os wifis do struct

      qtd = 0;
 
      while(WiFi.status() != WL_CONNECTED){                                  //se estiver conectado ele vai somar +1 no qtd
        delay(1000);
        Serial.print(".");
        qtd++;
        if(qtd > 4){
          break;
        }
      }
      
      if(WiFi.status() == WL_CONNECTED){                                     //se ele ainda estiver conectado com o a rede, aparece no monitor serial o IP
        Serial.println("Conectado com sucesso. IP: ");
        Serial.println(WiFi.localIP());      
        Serial.println( redeWifi[i].ssid );
        delay( 2000 );
        conectou = true;
        redeAtual = (char *)redeWifi[i].ssid;
        return conectou;
      }
      i++;
    }
  return conectou;
}



//===============================================================================================================================================
                   
void setup() {
  conectaWifi();                                                             //chamada da funcao que verifica qual wifi está pegando
}


void loop(){
  
}
