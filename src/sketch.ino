#include <IRremote.h>
IRrecv irrecv(11); // Receive on pin 11
decode_results results;
int last;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.value == 0xFFA857) { 
      Serial.println("DOWN"); 
      last = 1;
    }
    else if (results.value == 0xFF906F) { 
      Serial.println("UP"); 
      last = 2;
    }
    else if (results.value == 0xFFFFFFFF) {
      Serial.print("REPEAT ");
      switch ( last ) {
	case 0:
          Serial.println("IGNORE");
	  break;
	case 1:
          Serial.println("DOWN");
	  break;
	case 2:
          Serial.println("UP");
	  break;
      }
    }
    else {
      Serial.println("IGNORE");
      last = 0;
    }
    irrecv.resume(); // Continue receiving
  }
}
