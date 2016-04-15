#define BAUD 9600
#define RX_PIN 12
#define RF_BAUD 4000
#include <VirtualWire.h>

String uint8_tToString(uint8_t* s, char delimeter){
	int i  = 0;
	String temp = "";
	while(s[i] != uint8_t(delimeter)){
		char t = (char) s[i];
		temp += String(t);
		i++;
	}
	return temp;
}

void setup()
{
	Serial.begin(BAUD);
	vw_set_ptt_inverted(true);
	vw_set_rx_pin(RX_PIN);
	vw_setup(RF_BAUD);
  vw_rx_start();
}


void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen))
  {
      Serial.println("msg received");
      Serial.println(uint8_tToString(buf, ';'));
  }

}
