#include <VirtualWire.h>

#define BAUD 9600
#define RF_BAUD 4000
#define TX_PIN 12

bool isDone = false;

#define left 0
#define right 1
#define fwd 2
#define bwd 3


bool fwd_pushed = false;
bool left_pushed = false;
bool right_pushed = false;
bool bwd_pushed = false;

#define DELAY_BOUNCE 250

#define DELIMITER ";"

#define numberOfButtons 4

#define input(pin) (pinMode(pin, INPUT_PULLUP))

bool isPushed(int pin){
	return (digitalRead(pin) == LOW);
}

void send_data(String in){
  for (int i = 0; i < 3; i++)
  {
    const char* msg = in.c_str();
    Serial.println("msg: " + String(msg));
    vw_send((uint8_t*) in.c_str(), in.length());
    vw_wait_tx();
  }
}

uint8_t buttons[numberOfButtons] = {10, 9, 8, 7};

String push_sequence = "";

void setup(){
	Serial.begin(BAUD);
  vw_set_ptt_inverted(true);
	vw_set_tx_pin(TX_PIN);
  vw_setup(RF_BAUD);
	for (uint8_t i = 0; i < numberOfButtons; i++) input(buttons[i]);
}

void loop(){
	if (isPushed(buttons[left]) && !left_pushed){
		push_sequence += String("L");
    Serial.println(push_sequence);
		left_pushed = true;
	}

	if (isPushed(buttons[right]) && !right_pushed){
		push_sequence += String("R");
    Serial.println(push_sequence);
		right_pushed = true;
	}

	if (isPushed(buttons[fwd]) && !fwd_pushed){
		push_sequence += String("F");
    Serial.println(push_sequence);
		fwd_pushed = true;
	}

	if (isPushed(buttons[bwd]) && !bwd_pushed){
    push_sequence += String(DELIMITER);
    bwd_pushed = true;
    fwd_pushed = false;
    right_pushed = false;
    left_pushed = false;
    Serial.println(push_sequence);
	}

  if (bwd_pushed) {
    send_data(push_sequence);
    push_sequence = "";
    bwd_pushed = false;
  }

}

