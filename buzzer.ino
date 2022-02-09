void turn_on_pin(int pin)
{
  digitalWrite(pin, HIGH);
}
void turn_off_pin(int pin)
{
  digitalWrite(pin, LOW);
}

const int LONG_DURATION = 600;
const int SHORT_DURATION = 200;
const int CHAR_DELAY = 500;
const int REPEAT_DELAY = 2000;

void blink_long()
{
  turn_on_pin(buzzer_pin);
  for (int i = 0; i < 5; i++)
  {
    turn_on_pin(led_pins[i]);
  }
  delay(SHORT_DURATION);
  turn_everything_off();
}

void blink_short()
{
  turn_on_pin(buzzer_pin);
  turn_on_pin(led_pins[0]);
  delay(SHORT_DURATION);
  turn_everything_off();
}

void turn_everything_off()
{
  turn_off_pin(buzzer_pin);
  for (int i = 0; i < 5; i++)
  {
    turn_off_pin(led_pins[i]);
  }
}

enum Signal
{
  Short,
  Long,
};
class Letter
{
public:
  size_t instruction_len;
  Signal instructions[5];

  void print()
  {
    for (int i = 0; i < instruction_len; i++)
    {
      switch (instructions[i])
      {
      case Long:
        blink_long();
        break;
      case Short:
        blink_short();
        break;
      }
    }
    delay(CHAR_DELAY);
  }
};

Letter get_letter_for_char(char c)
{
  switch (c)
  {
  case 'm':
    return Letter{2, {Long, Long}};
  case 'i':
    return Letter{2, {Short, Short}};
  case 'c':
    return Letter{4, {Long, Short, Long, Short}};
  case 'h':
    return Letter{4, {Short, Short, Short, Short}};
  case 'a':
    return Letter{2, {Short, Long}};
  case 'e':
    return Letter{1, {Short}};
  case 'l':
    return Letter{4, {Short, Long, Short, Short}};
  default:
    /*Serial.print("Failed to get code for character: ");
    Serial.println(c);*/
    return Letter{0};
  }
}

char *text = "michael";

const int buzzer_pin = 12;
const int led_pins[5] = {
    6,
    7,
    8,
    9,
    10,
};
void setup()
{
  pinMode(buzzer_pin, OUTPUT);
  for (int i = 0; i < 5; i++)
  {
    pinMode(led_pins[i], OUTPUT);
  }
}

int index = 0;
void loop()
{
  if (!text[index])
  {
    index = 0;
    delay(REPEAT_DELAY);
  }
  auto letter = get_letter_for_char(text[index]);
  letter.print();
}