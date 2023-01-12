#include <SoftwareSerial.h>

#define OBD_Pin1 9
#define OBD_Pin7_KLINE 4
#define OBD_KlineTX 9
#define OBD_KlineRX 8

SoftwareSerial portOne(OBD_KlineRX, OBD_KlineTX);

void setup() {

	pinMode(OBD_Pin7, OUTPUT);
  digitalWrite(OBD_Pin7_KLINE, LOW);
  pinMode(OBD_Pin1, OUTPUT);
  digitalWrite(OBD_Pin1, HIGH);

    
    
	// Open serial communications and wait for port to open:
	Serial.begin(115200);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}


	// Start each software serial port
	portOne.begin(15625);
	//  portTwo.begin(15625);

	FiveBaudInit();
}

void loop() {
	// By default, the last intialized port is listening.
	// when you want to listen on a port, explicitly select it:
   // portOne.listen();

	while (portOne.available() > 1) {


		int inByte = portOne.read();
		Serial.print("MUT:");
		Serial.println(inByte, HEX);


		while (portOne.available() > 0) {
			int inByte = portOne.read();

			Serial.print("ECU:");
			Serial.println(inByte, HEX);

		}

    portOne.write(17);
		while (portOne.available() > 0) {
			int inByte = portOne.read();
			Serial.print("ARD:");
			Serial.println(inByte, HEX);

		}
	}
}

void FiveBaudInit()
{
	digitalWrite(OBD_Pin1, LOW);
  digitalWrite(OBD_Pin7_KLINE, HIGH);
 
	for (int i = 7; i > 0; i--)
	{
		digitalWrite(OBD_Pin7_KLINE, LOW);
		delay(200);
	}

	//stop bit
	digitalWrite(OBD_Pin7_KLINE, LOW);
	delay(200);

	digitalWrite(OBD_Pin7_KLINE, HIGH);

}
