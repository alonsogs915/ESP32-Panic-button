// Define una constante que puede ser usada para identificar la versión del hardware
#define SIM800L_AXP192_VERSION_20200327

// DUMP_AT_COMMANDS: Activa la depuración para mostrar los comandos AT enviados y sus respuestas. 
// TINY_GSM_DEBUG: Define SerialMon como la salida para los mensajes de depuración.
#define DUMP_AT_COMMANDS
#define TINY_GSM_DEBUG          SerialMon

// Incluye un archivo de utilidades externa (libreria)
#include "utilities.h"

// SerialMon: Define Serial (puerto serie principal) como monitor para mensajes y depuración. SerialAT: Define Serial1 (puerto serie secundario) como la interfaz de comunicación con el módulo SIM800.
#define SerialMon Serial
#define SerialAT  Serial1

// TINY_GSM_MODEM_SIM800: Especifica que el módem utilizado es un SIM800. TINY_GSM_RX_BUFFER: Ajusta el tamaño del búfer de recepción a 1 KB.
#define TINY_GSM_MODEM_SIM800          // Modem is SIM800
#define TINY_GSM_RX_BUFFER      1024   // Set RX buffer to 1Kb

// Biblioteca
#include <TinyGsmClient.h>

// Si DUMP_AT_COMMANDS está definido, se activa el depurador StreamDebugger para mostrar los comandos AT y respuestas. Si no, el módem es inicializado directamente con SerialAT.
#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

// SMS_TARGET y CALL: Número de teléfono al que se enviarán los SMS o llamadas.
#define SMS_TARGET  "************"
#define CALL_TARGET "************"




void setup()
{
    SerialMon.begin(115200); // Inicia el monitor serie a 115200 baudios.

    delay(10); // Pausa breve para permitir la configuración inicial.

 // Llama a una función para configurar el módulo de gestión de energía (PMU). Si falla, imprime un error.
    if (setupPMU() == false) {
        Serial.println("Setting power error");
    }

    setupModem(); // Configura el módem (puede incluir inicialización de pines y ajustes AT).

    SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
    // Configura el puerto serie del módem a 115200 baudios con 8 bits de datos, sin paridad y 1 bit de parada.
    // `MODEM_RX` y `MODEM_TX` representan los pines para la comunicación serial.


    delay(6000);
}

void loop()
{

    SerialMon.println("Initializing modem...");
    modem.restart(); // Reinicia el módem GSM.


    delay(10000);

    String imei = modem.getIMEI(); // Obtiene el IMEI del módem.
    DBG("IMEI:", imei); // Muestra el IMEI en el monitor serie.

    bool res = modem.sendSMS(SMS_TARGET, String("Hola")); // Envía un SMS al número definido en `SMS_TARGET`
    DBG("SMS:", res ? "OK" : "fail"); // Muestra en el monitor serie si el envío del SMS fue exitoso ("OK") o fallido ("fail").

    while (true) {
        modem.maintain(); // Mantiene la comunicación con el módem para asegurarse de que sigue activo.
    }
}
