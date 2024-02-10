// Define pin numbers for LED and meter
const byte LED_PIN = 13;  // Pin 13 is commonly connected to the built-in LED on Arduino boards
const byte METER_PIN = A4;  // Analog pin A4 is used to read a meter or sensor

void setup() {
  // Set the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
  // Set the meter pin as an input
  pinMode(METER_PIN, INPUT);
  
  // Start serial communication at 9600 baud rate
  Serial.begin(9600);
  
  // Initialize Timer1 for interrupt-based blinking
  // Clear Timer1 control registers
  TCCR1A = 0;
  TCCR1B = 0;
  // Initialize counter value to 0
  TCNT1 = 0;
  
  // Set Timer1 to CTC (Clear Timer on Compare Match) mode
  TCCR1B |= (1 << WGM12);
  
  // Set prescaler to 1024 and start the timer
  TCCR1B |= (1 << CS12) | (1 << CS10);
  
  // Calculate and set the compare match value for 2 seconds (16MHz / 1024 / 2 - 1)
  OCR1A = 7812;
  
  // Enable Timer1 compare match interrupt
  TIMSK1 |= (1 << OCIE1A);
}

void loop() {
  // Do nothing in the loop, as the LED will blink based on the interrupt
}

// Interrupt Service Routine for Timer1 compare match A
ISR(TIMER1_COMPA_vect) {
  // Toggle the LED by reading its current state and then writing the opposite state
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

