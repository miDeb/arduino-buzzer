int const DIT_DURATION = 200;
int const DAH_DURATION = 3 * DIT_DURATION;
int const SIGNAL_DELAY = DIT_DURATION;
int const CHAR_DELAY = 3 * DIT_DURATION;
int const WORD_DELAY = 7 * DIT_DURATION;
int const REPEAT_DELAY = 2 * WORD_DELAY;

constexpr char const *const text = "Michael";

int const buzzer_pin = 12;
int const led_pins[5] = {
    6, 7, 8, 9, 10,
};

void turn_on_pin(int const pin) { digitalWrite(pin, HIGH); }

void turn_off_pin(int const pin) { digitalWrite(pin, LOW); }

void blink_long() {
  turn_on_pin(buzzer_pin);
  for (int i = 0; i < 5; i++) {
    turn_on_pin(led_pins[i]);
  }
  delay(DAH_DURATION);
  turn_everything_off();
}

void blink_short() {
  turn_on_pin(buzzer_pin);
  turn_on_pin(led_pins[0]);
  delay(DIT_DURATION);
  turn_everything_off();
}

void turn_everything_off() {
  turn_off_pin(buzzer_pin);
  for (int i = 0; i < 5; i++) {
    turn_off_pin(led_pins[i]);
  }
}

void show_char(char const c, bool const add_leading_delay) {
  // handle special cases
  switch (c) {
  case ' ':
    delay(WORD_DELAY);
    return;
  }
  // handle alphabetic letters
  if (add_leading_delay) {
    delay(CHAR_DELAY);
  }
  auto signals = get_signals_for_char(c);
  for (char const *s = signals; *s; s++) {
    if (s != signals) {
      delay(SIGNAL_DELAY);
    }
    switch (*s) {
    case '-':
      blink_long();
      break;
    case '.':
      blink_short();
      break;
    }
  }
}

char const *const get_signals_for_char(char c) {
  char const *const codes[]{
      ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.",  "....", "..",
      ".---", "-.-",  ".-..", "--",   "-.",  "---",  ".--.", "--.-", ".-.",
      "...",  "-",    "..-",  "...-", ".--", "-..-", "-.--", "--..",
  };
  if (isUpperCase(c)) {
    c -= ('A' - 'a');
  }
  int index = c - 'a';
  if (index < 0 || index >= (sizeof(codes) / sizeof(*codes))) {
    Serial.print("failed to get encoding for '");
    Serial.print(c);
    Serial.println("'.");
    return "";
  }
  return codes[index];
}

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  for (int i = 0; i < 5; i++) {
    pinMode(led_pins[i], OUTPUT);
  }
}

int index = 0;
void loop() {
  if (!text[index]) {
    static_assert(text != "", "text must not be empty");
    index = 0;
    delay(REPEAT_DELAY);
  }
  show_char(text[index], index != 0);
}