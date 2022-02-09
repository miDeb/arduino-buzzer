const int buzzer_pin = 12;
size_t index = 0;
const size_t lengths_size = 25;
const int SHORT = 300;
const int LONG = 600;
const int BREAK = -600;
const int SHORT_BREAK = -200;
const int lengths[lengths_size]{
  LONG,
  LONG,
  BREAK,
  SHORT,
  SHORT,
  BREAK,
  LONG,
  SHORT,
  LONG,
  SHORT,
  BREAK,
  SHORT,
  SHORT,
  SHORT,
  SHORT,
  BREAK,
  SHORT,
  LONG,
  BREAK,
  SHORT,
  BREAK,
  SHORT,
  LONG,
  SHORT,
  SHORT,
};
const int led_pins[5] = {
  6,
  7,
  8,
  9,
  10,
};
void setup() {
  pinMode(buzzer_pin, OUTPUT);
  for (int i = 0; i < 5; i++) {
    pinMode(led_pins[i], OUTPUT);
  }
}

bool was_enabled = false;
void blink(int amount) {
  if (amount == SHORT) {
    digitalWrite(led_pins[0], HIGH);
    digitalWrite(buzzer_pin, HIGH);
  } else {
    for (int i = 0; i < 5; i++) {
      digitalWrite(led_pins[i], HIGH);
    }
    digitalWrite(buzzer_pin, HIGH);
  }
  delay(amount);

  for (int i = 0; i < 5; i++) {
    digitalWrite(led_pins[i], LOW);
  }
  digitalWrite(buzzer_pin, LOW);
}
void loop() {
  if (index == lengths_size) {
    index = 0;
    delay(1000);
  }
  int next_value = lengths[index];
  if (was_enabled && next_value > 0) {
    delay(-SHORT_BREAK);
  }
  if (next_value < 0) {
    delay(-next_value);
    was_enabled = false;
  } else {
    blink(next_value);
    was_enabled = true;
  }
  index++;
}
