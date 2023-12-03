#include <SoftwareSerial.h>   
//Connect the TX pin of the GSMSIM900 with D11 and RX pin with D10
SoftwareSerial GSMSIM900(11, 10); 
String textForSMS;

char mobile_no[] = ""; //change with phone number to which you want to call use the country code for example(+92XXXXXXXX)

int irsensor=3;

void setup() { 
  Serial.begin(9600);//Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  GSMSIM900.begin(9600); // original 19200
  pinMode(irsensor,INPUT); 
  Serial.println("Initializing....");
  initModule("AT", "OK", 1000);              //Once the handshake test is successful, it will back to OK

}

void loop() {

  if (digitalRead (irsensor) == 0)
  {
    callUp(mobile_no);
  }

  delay(5);
}


void callUp(char *number) {
  GSMSIM900.print("ATD + "); GSMSIM900.print(number); GSMSIM900.println(";"); //Call to the specific number, ends with semi-colon,replace X with mobile number
  delay(20000);       // wait for 20 seconds...
 GSMSIM900.println("ATH"); //hang up
  delay(100);
}

void initModule(String cmd, char *res, int t) {
  while (1) {
    Serial.println(cmd);
    GSMSIM900.println(cmd);
    delay(100);
    while (GSMSIM900.available() > 0) {
      if (GSMSIM900.find(res)) {
        Serial.println(res);
        delay(t);
        return;
      } else {
        Serial.println("Error");
      }
    }
    delay(t);
  }
}
