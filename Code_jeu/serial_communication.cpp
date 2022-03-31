#include "serial_communication.h"

/*---------------------------Definition de fonctions ------------------------
Fonction d'envoi
Entrée : Port de communication, tampon de réception du message
Sortie : Code d'erreur, 1 = erreur, 0 = ok
Traitement : Réception du message
-----------------------------------------------------------------------------*/
bool SerialCommunication::SendToSerial(SerialPort* arduino, json j_msg)
{
    // Return 0 if error
    std::string msg = j_msg.dump();
    bool ret = arduino->writeSerialPort(msg.c_str(), msg.length());
    return ret;
}


/*---------------------------Definition de fonctions ------------------------
Fonction de réception
Entrée : Port de communication, message à envoyer
Sortie : Code d'erreur, 1 = erreur, 0 = ok
Traitement : Envoie du message
-----------------------------------------------------------------------------*/
bool SerialCommunication::RcvFromSerial(SerialPort* arduino, std::string& msg)
{
    // Return 0 if error
    // Message output in msg
    std::string str_buffer;
    char char_buffer[MSG_MAX_SIZE];
    int buffer_size;
    char last;


    //buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
    //str_buffer.assign(char_buffer, buffer_size);
   // msg.append(str_buffer);


    msg.clear(); // clear string
    // Read serialport until '\n' character (Blocking)
    do {
        if (msg.size() > MSG_MAX_SIZE) {
            return false;
        }

        buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
        str_buffer.assign(char_buffer, buffer_size);
        msg.append(str_buffer);

        if (msg.size() > 0)
            last = msg.back();
        else
            last = NULL;

    } while (last != '\n');

    msg.pop_back(); //remove '/n' from string
    return true;
}
