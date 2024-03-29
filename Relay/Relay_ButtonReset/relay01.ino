const int RLY_PIN = 4;
const int BTN_PIN = 7;

void setup(){
  Serial.begin(115200);
  Serial.println("setup()"); //called twice after flashing from Arduino IDE!!!???
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RLY_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
  digitalWrite(RLY_PIN, LOW);
}

void loop(){
  static unsigned relayState = 0;
  static int btnSt0 = 0;
  static unsigned long btnMs = 0;//last moment when the button was pressed
  int btnSt = digitalRead(BTN_PIN);
  if(btnSt && btnSt!=btnSt0 && millis()-btnMs>1000){//button was pressed (is ON after it was OFF ... but not too quick one after another)
    Serial.println("toggle");
    btnMs = millis();
    relayState = !relayState;
    digitalWrite(LED_BUILTIN, relayState);
    digitalWrite(RLY_PIN, relayState);
  }
  btnSt0 = btnSt;

  if(relayState == 0){//blink builtin led while relay is OFF
    static unsigned long prevMillis = 0;
    unsigned long currMillis = millis();
    if(currMillis-prevMillis >= 1000){
      static int ledState = LOW;
      prevMillis = currMillis;
      ledState = (ledState == LOW);
      digitalWrite(LED_BUILTIN, ledState);
    }
  }
}
