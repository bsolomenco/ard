//pins 2-7 are used by LCD16x2 shield
const int RLY_PIN = 8;  //Arduino pin connected to relay's IN
const int BTN_PIN = 9;  //Arduino pin connected to button's OUT

void info(){//display useful information
    char buf[256]{};
    snprintf(buf, sizeof(buf), "%s %s() RLY_PIN=%d BTN_PIN=%d", __FILE__, __FUNCTION__, RLY_PIN, BTN_PIN);
    Serial.println(buf);
}

void setup(){//called twice after flashing from Arduino IDE!!!???
  Serial.begin(115200);
  info();

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
