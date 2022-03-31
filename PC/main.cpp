    /* 
 * Auteurs: Jean-Samuel Lauzon    
 * Date: Fevrier 2022
 * Projet S2ei
*/

/*------------------------------ Librairies ---------------------------------*/
#include <iostream>
#include <string>
using namespace std;

/*-------------------------- Librairies externes ----------------------------*/
//#include "include/serial/SerialPort.hpp"
//#include "include/json.hpp"
#include "SerialPort.hpp"
#include "json.hpp"
using json = nlohmann::json;

/*------------------------------ Constantes ---------------------------------*/
#define BAUD 115200           // Frequence de transmission serielle
#define MSG_MAX_SIZE 1024   // Longueur maximale d'un message


/*------------------------- Prototypes de fonctions -------------------------*/
bool SendToSerial(SerialPort *arduino, json j_msg);
bool RcvFromSerial(SerialPort *arduino, string &msg);


/*---------------------------- Variables globales ---------------------------*/
SerialPort * arduino; //doit etre un objet global!

/*----------------------------- Fonction "Main" -----------------------------*/
int main() {
    string raw_msg;

    // Initialisation du port de communication
    string com;
    cout << "Entrer le port de communication du Arduino: ";
    cin >> com;
    arduino = new SerialPort(com.c_str(), BAUD);
    
    if(!arduino->isConnected()) {
        cerr << "Impossible de se connecter au port "<< string(com) <<". Fermeture du programme!" <<endl;
        exit(1);
    }
    
    // Structure de donnees JSON pour reception
    int pot_value = 0;
    bool bouton1 = 0;
    bool bouton2 = 0;
    bool bouton3 = 0;
    bool bouton4 = 0;
    float joyStick_Value = 0;
    float joyStickY = 0;
    int acc_Value = 0;
    // Structure de donnees pour Envoie JSON
    int led_state_GREEN = 0;
    int led_state_RED1 = 0;
    int led_state_RED2 = 0;
    int led_state_RED3 = 0;
    int segment_Value = 0;

    json j_msg_send, j_msg_rcv;

    // Boucle infinie pour la communication bidirectionnelle Arduino-PC
    while(1) {
        j_msg_send["G"] = led_state_GREEN;      // Création du message à envoyer
        j_msg_send["1"] = led_state_RED1;
        j_msg_send["2"] = led_state_RED2;
        j_msg_send["3"] = led_state_RED3;
        j_msg_send["7"] = segment_Value;

        if(!SendToSerial(arduino, j_msg_send)) {    //Envoie au Arduino
            cerr << "Erreur lors de l'envoie du message. " << endl;
        }

        // Reception message Arduino
        j_msg_rcv.clear(); // effacer le message precedent
        if(!RcvFromSerial(arduino, raw_msg)) {
            cerr << "Erreur lors de la reception du message. " << endl;
        }
        
        // Impression du message de l'Arduino, si valide
        if(raw_msg.size()>0) {
            j_msg_rcv = json::parse(raw_msg);       // Transfert du message en json
            pot_value = j_msg_rcv["X"];        // Transfert dans la variable pot_value
            acc_Value = j_msg_rcv["A"];
            if(j_msg_rcv.contains("1"))
                led_state_GREEN = j_msg_rcv["1"];
            if(j_msg_rcv.contains("2"))
                led_state_RED1 = j_msg_rcv["2"];
            if(j_msg_rcv.contains("3"))
                led_state_RED2 = j_msg_rcv["3"];
            if(j_msg_rcv.contains("4"))
                led_state_RED3 = j_msg_rcv["4"];
            segment_Value = j_msg_rcv["Y"];
            /*pot_value = j_msg_rcv["analog"];        // Transfert dans la variable pot_value
            acc_Value = j_msg_rcv["ACC"];
            led_state_GREEN = j_msg_rcv["BTN1"];
            led_state_RED1 = j_msg_rcv["BTN2"];
            led_state_RED2 = j_msg_rcv["BTN3"];
            led_state_RED3 = j_msg_rcv["BTN4"];
            segment_Value = j_msg_rcv["analog"];*/
            //cout<<pot_value<<endl;
            cout << /*"Message de l'Arduino: " <<*/ j_msg_rcv << endl;
        }
        
        //led_state = !led_state;     //Changement de l'etat led
        //led_state_sec = !led_state_sec;
        /*led_state_GREEN = !led_state_GREEN;
        led_state_RED1 = !led_state_RED1;
        led_state_RED2 = !led_state_RED2;
        led_state_RED3 = !led_state_RED3;
        segment_Value = !segment_Value;*/

        // Bloquer le fil pour environ 1 sec
        Sleep(5); // 1000ms
    }
    return 0;
}


/*---------------------------Definition de fonctions ------------------------
Fonction d'envoi
Entrée : Port de communication, tampon de réception du message
Sortie : Code d'erreur, 1 = erreur, 0 = ok
Traitement : Réception du message
-----------------------------------------------------------------------------*/
bool SendToSerial(SerialPort *arduino, json j_msg) {
    // Return 0 if error
    string msg = j_msg.dump();
    bool ret = arduino->writeSerialPort(msg.c_str(), msg.length());
    return ret;
}


/*---------------------------Definition de fonctions ------------------------
Fonction de réception
Entrée : Port de communication, message à envoyer
Sortie : Code d'erreur, 1 = erreur, 0 = ok
Traitement : Envoie du message
-----------------------------------------------------------------------------*/
bool RcvFromSerial(SerialPort *arduino, string &msg) {
    // Return 0 if error
    // Message output in msg
    string str_buffer;
    char char_buffer[MSG_MAX_SIZE];
    int buffer_size;

    msg.clear(); // clear string
    // Read serialport until '\n' character (Blocking)
    while(msg.back()!='\n') {
        if(msg.size()>MSG_MAX_SIZE) {
            return false;
        }

        buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
        str_buffer.assign(char_buffer, buffer_size);
        msg.append(str_buffer);
    }

    msg.pop_back(); //remove '/n' from string
    return true;
}