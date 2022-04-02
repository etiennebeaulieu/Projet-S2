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

int PAST_BTN1_val = 0;
int PAST_BTN2_val = 0;
int PAST_BTN3_val = 0;
int PAST_BTN4_val = 0;

float joyX = 0;
int joyY = 0;
float accVal = 0;

float accX = 0;
float accY = 0;
float accZ = 0;


#define pinLED_GREEN 7
#define pinLED_RED1 8
#define pinLED_RED2 9
#define pinLED_RED3 10

#define pinBTN_1 3
#define pinBTN_2 4
#define pinBTN_3 5
#define pinBTN_4 6 

#define pinX A5
#define pinY A1
#define pinACC A2

//#define pinACCX
//#define pinACCY
//#define pinACCZ
//TODO : Ajouter les pin ACCX, ACCY et ACCZ

unsigned long startMillis;

int lastSecondes = 0;

/*------------------------- Prototypes de fonctions -------------------------*/
void sendMsg(); 
void readMsg();
float traitementACC(float x, float y, float z);
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
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinACC, INPUT);

}

/* Boucle principale (infinie) */
void loop() {

  if(shouldRead_){
    readMsg();
    sendMsg();
  }

  joyX = analogRead(pinX);
  joyY = analogRead(pinY);

  //accX = (analogRead(pinACCX))*5/3.3;
  //accY = (analogRead(pinACCY))*5/3.3;
  //accZ = (analogRead(pinACCZ))*5/3.3;
  //accVal = traitementAcc(accX, accY, accZ);


  //À retirer une fois que traitement ACC est fait
  accVal = (analogRead(pinACC))*5/3.3;

  

  //Changement de la valeur analogique à un angle entre -90 et 90 degrés
  joyX = ((joyX-512)/512)*90;


  //1 quand par en haut
  //0 quand dans la zone centrale
  //-1 quand par en bas
  if(joyY >= 900)
    joyY = 1;
  else if(joyY <= 100)
    joyY = -1;
  else
    joyY = 0;


  //+1%2 pour inverser les bouton vu que normaly close
  if(PAST_BTN1_val != (digitalRead(pinBTN_1)+1)%2)
  {
    BTN1_val = (digitalRead(pinBTN_1)+1)%2;
  }
  if(PAST_BTN2_val != (digitalRead(pinBTN_2)+1)%2)
  {
    BTN2_val = (digitalRead(pinBTN_2)+1)%2;
  }
  if(PAST_BTN3_val != (digitalRead(pinBTN_3)+1)%2)
  {
    BTN3_val = (digitalRead(pinBTN_3)+1)%2;
  }
  if(PAST_BTN4_val != (digitalRead(pinBTN_4)+1)%2)
  {
    BTN4_val = (digitalRead(pinBTN_4)+1)%2;
  }
  

  
  
  unsigned long time = (millis() - startMillis);
 
  delay(1);  // delais de 10 ms
}

/*---------------------------Definition de fonctions ------------------------*/

void serialEvent() { shouldRead_ = true; }


/*---------------------------Definition de fonctions ------------------------
Fonction d'envoi
Entrée : Aucun
Sortie : Aucun
Traitement : Envoi du message
-----------------------------------------------------------------------------*/
void sendMsg() {
  StaticJsonDocument<500> doc;
  
  doc["X"] = joyX;
  doc["A"] = accVal;
  doc["Y"] = joyY;
  doc["1"] = BTN1_val;
  doc["2"] = BTN2_val;
  doc["3"] = BTN3_val;
  doc["4"] = BTN4_val;
  
 
  if(BTN1_val!=PAST_BTN1_val)
  {
    PAST_BTN1_val=BTN1_val;
    doc["1"] = BTN1_val;
  }
  if(BTN2_val!=PAST_BTN2_val)
  {
    PAST_BTN2_val=BTN2_val;
    doc["2"] = BTN2_val;
  }  
  if(BTN3_val!=PAST_BTN3_val)
  {
    PAST_BTN3_val=BTN3_val;
    doc["3"] = BTN3_val;
  }
  if(BTN4_val!=PAST_BTN4_val)
  {
    PAST_BTN4_val=BTN4_val;
    doc["4"] = BTN4_val;
  }
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

  // Lecture sur le port Serial
  DeserializationError error = deserializeJson(doc, Serial);
  shouldRead_ = false;

  // Si erreur dans le message
  if (error) {
    Serial.print("deserialize() failed: ");
    Serial.println(error.c_str());
    return;
  }
  
  // Analyse des éléments du message message
  parse_msg = doc["G"];
  if (!parse_msg.isNull()) {
    // mettre la led a la valeur doc["led"]
    digitalWrite(pinLED_GREEN,doc["G"].as<bool>());
  }

  parse_msg = doc["1"];
  if (!parse_msg.isNull()) {
    // mettre la led a la valeur doc["led"]
    digitalWrite(pinLED_RED1,doc["1"].as<bool>());
  }

  parse_msg = doc["2"];
  if (!parse_msg.isNull()) {
    // mettre la led a la valeur doc["led"]
    digitalWrite(pinLED_RED2,doc["2"].as<bool>());
  }

  parse_msg = doc["3"];
  if (!parse_msg.isNull()) {
    // mettre la led a la valeur doc["led"]
    digitalWrite(pinLED_RED3,doc["3"].as<bool>());
  }
  parse_msg = doc["S"];
  if (!parse_msg.isNull()) {
    // mettre la led a la valeur doc["led"]
    //digitalWrite(pinLED_RED3,doc["7seg"].as<bool>());
    display.showNumberDecEx(doc["S"], 0/*0b01100000*/);
  }
  
}


float traitementAcc(float x, float y, float z){

    //TODO : faire les maths pour avoir un angle en degrés entre -90 et 90 à partir de des données de l'accéléromètre
    return x;


}