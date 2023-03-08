const char ADDR[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52}; //A15 on Pin 22 through A0 on Pin 52
const char DATA[] = {39, 41, 43, 45, 47, 49, 51, 53};  // D7 on Pin 39 through D0 on Pin 53
byte REG[] = {0, 0, 0, 0};

#define CLOCK 2
#define READ_WRITE 3

void setup() {
  for (int n = 0; n < 16; n += 1) {
    pinMode(ADDR[n], INPUT);
  }
  for (int n = 0; n < 8; n += 1) {
    pinMode(DATA[n], INPUT);
  }
  pinMode(CLOCK, INPUT);
  pinMode(READ_WRITE, INPUT);

  attachInterrupt(digitalPinToInterrupt(CLOCK), onClock, RISING);
  
  Serial.begin(57600);
}

void onClock() {
  char output[15];
  char output2[45];
  unsigned int address = 0;
  for (int n = 0; n < 16; n += 1) {
    int bit = digitalRead(ADDR[n]) ? 1 : 0;
    Serial.print(bit);
    address = (address << 1) + bit;
  }
  
  Serial.print("   ");
  
  unsigned int data = 0;
  for (int n = 0; n < 8; n += 1) {
    int bit = digitalRead(DATA[n]) ? 1 : 0;
    Serial.print(bit);
    data = (data << 1) + bit;
  }

  switch (address) {
      case 0x6000:
        REG[0] = data;
        break;
      case 0x6001:
        REG[1] = data;
        break;
      case 0x6002:
        REG[2] = data;
        break;
      case 0x6003:
        REG[3] = data;
        break;
    }

  sprintf(output, "   %04x  %c %02x", address, digitalRead(READ_WRITE) ? 'r' : 'W', data);
  Serial.print(output);  
  sprintf(output2, "   Data(B): %02x Inst(A): %02x DDRB: %02x DDRA: %02x", REG[0], REG[1], REG[2], REG[3]);
  Serial.println(output2);
}

void loop() {
}
