/* 
 * Auteurs: Jean-Samuel Lauzon    
 * Date: Fevrier 2022
*/

/*------------------------------ Librairies ---------------------------------*/
#include <Arduino.h>
#include <ArduinoJson.h>
#include <TM1637Display.h>

/*------------------------------ Constantes ---------------------------------*/

#define BAUD 115200        // Frequence de transmission serielle
TM1637Display display(12,13);
/*---------------------------- Variables globales ---------------------------*/

volatile bool shouldSend_ = false;  // Drapeau prêt à envoyer un message
volatile bool shouldRead_ = false;  // Drapeau prêt à lire un message

int ledState_GREEN = 0;
int ledState_RED1 = 0;
int ledState_RED2 = 0;
int ledState_RED3 = 0;

int BTN1_val = 0;
int BTN2_val = 0;
int BTN3_val = 0;
int BTN4_val = 0;

int potValue = 0;
int accVal = 0;

#define pinLED_GREEN 7
#define pinLED_RED1 8
#define pinLED_RED2 9
#define pinLED_RED3 10

#define pinBTN_1 3
#define pinBTN_2 4
#define pinBTN_3 5
#define pinBTN_4 6 

#define pinPOT A0
#define pinACC A1

unsigned long startMillis;

int lastSecondes = 0;

/*------------------------- Prototypes de fonctions -------------------------*/
void sendMsg(); 
void readMsg();
void serialEvent();
void showTimeFromMs(unsigned long ms);
void checkRising();
/*---------------------------- Fonctions "Main" -----------------------------*/

void setup() {
  Serial.begin(BAUD);               // Initialisation de la communication serielle
  
  display.setBrightness(2);
  startMillis = millis();

  pinMode(pinLED_GREEN, OUTPUT);
  digitalWrite(pinLED_GREEN, ledState_GREEN);

  pinMode(pinLED_RED1,OUTPUT);
  digitalWrite(pinLED_RED1, ledState_RED1);

  pinMode(pinLED_RED2, OUTPUT);
  digitalWrite(pinLED_RED2, ledState_RED2);

  pinMode(pinLED_RED3, OUTPUT);
  digitalWrite(pinLED_RED3, ledState_RED3);

  pinMode(pinBTN_1, INPUT);
  pinMode(pinBTN_2, INPUT);
  pinMode(pinBTN_3, INPUT);
  pinMode(pinBTN_4, INPUT);
  pinMode(pinACC, INPUT);
}

/* Boucle principale (infinie) */
void loop() {

  if(shouldRead_){
    readMsg();
    sendMsg();
  }

  potValue = analogRead(pinPOT);
  BTN1_val = digitalRead(pinBTN_1);
  BTN2_val = digitalRead(pinBTN_2);
  BTN3_val = digitalRead(pinBTN_3);
  BTN4_val = digitalRead(pinBTN_4);
  accVal = (analogRead(pinACC))*5/3.3;
  //Serial.println(potValue);          // debug
  unsigned long time = (millis() - startMillis);
  //showTimeFromMs(time);
  //checkRising();
  delay(1);  // delais de 10 ms
}

/*---------------------------Definition de fonctions ------------------------*/

void serialEvent() { shouldRead_ = true; }


/*void checkRising()
{

}*/

/*---------------------------Definition de fonctions ------------------------
Fonction d'envoi
Entrée : Aucun
Sortie : Aucun
Traitement : Envoi du message
-----------------------------------------------------------------------------*/
void sendMsg() {
  StaticJsonDocument<500> doc;
  // Elements du message
  doc["time"] = millis();
  doc["analog"] = potValue;
  doc["ACC"] = accVal;
  doc["BTN1"] = BTN1_val;
  doc["BTN2"] = BTN2_val;
  doc["BTN3"] = BTN3_val;
  doc["BTN4"] = BTN4_val;
  // Serialisation
  serializeJson(doc, Serial);

  // Envoie
  Serial.println();
  shouldSend_ = false;
}

void showTimeFromMs(unsigned long ms){

  uint8_t centaines = ms % 100;
  int secondes = (ms/1000)%100;

  display.showNumberDecEx((secondes * 100) + centaines, 0/*0b01100000*/);
}

/*---------------------------Definition de fonctions ------------------------
Fonction de reception
Entrée : Aucun
Sortie : Aucun
Traitement : Réception du message
-----------------------------------------------------------------------------*/
void readMsg(){
  // Lecture du message Json
  StaticJsonDocument<500> doc;
  JsonVariant parse_msg;

  // Lecture sur le port Seriel
  DeserializationError error = deserializeJson(doc, Serial);
  shouldRead_ = false;

  // Si erreur dans le message
  if (error) {
    Serial.print("deserialize() failed: ");
    Serial.println(error.c_str());
    return;
  }
  
  // Analyse des éléments du message message
  parse_msg = doc["led_Green"];
  if (!parse_msg.isNull()) {
    // mettre la led a la valeur doc["led"]
    digitalWrite(pinLED_GREEN,doc["led_Green"].as<bool>());
  }

  parse_msg = doc["led_R1"];
  if (!parse_msg.isNull()) {
    // mettre la led a la valeur doc["led"]
    digitalWrite(pinLED_RED1,doc["led_R1"].as<bool>());
  }

  parse_msg = doc["led_R2"];
  if (!parse_msg.isNull()) {
    // mettre la led a la valeur doc["led"]
    digitalWrite(pinLED_RED2,doc["led_R2"].as<bool>());
  }

  parse_msg = doc["led_R3"];
  if (!parse_msg.isNull()) {
    // mettre la led a la valeur doc["led"]
    digitalWrite(pinLED_RED3,doc["led_R3"].as<bool>());
  }
  parse_msg = doc["7seg"];
  if (!parse_msg.isNull()) {
    // mettre la led a la valeur doc["led"]
    //digitalWrite(pinLED_RED3,doc["7seg"].as<bool>());
    display.showNumberDecEx(doc["7seg"], 0/*0b01100000*/);
  }
  
}