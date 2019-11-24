#include "mbed.h"
/*
Base pour la reception de trame sur le bus CAN, code fonctionnel pour STM32
Pas besoin d'installer de librairie la librairie mbed.h à déjà du CAN
Si questions, voir P.A (kingovchouffe sur github) ou mail au pierre.anthony.legeay@gmail.com
*/

DigitalOut led(LED1);
// Définition du nom et des pins pour le bus CAN
CAN  can(PA_11, PA_12);   // NUCLEO     CAN Rx pin, CAN Tx pin
char counter = 0;

void send() {
    // envoie un compteur sur le bus CAN
    // CANMessage(id, message, taille)
    if(can.write(CANMessage(0x221, &counter, 1))) {
        counter++;
        printf("Message sent: %d\n", counter);
    }
    led = !led;
}

int main() {
    //printf("main()\n");
    led = 1;

    // Nom très mal choisi mais oui frequency correspond au baudrate du bus
    can.frequency(500000);
    // Définition du message à recevoir
    CANMessage msg;
    while(1) {
    send();
        if(can.read(msg)) {
            printf("Message received: %d\n", msg.data[0]);
            led = !led;
        }
        wait(0.2);

    }
}
