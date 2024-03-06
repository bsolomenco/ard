#if 0 //Relay activated by IN=LOW
- Arduino's GND <-> relay's GND
- Arduino's 5V  <-> relay's VCC
- load connected on relay's "NormalOpen"
#endif

//pins 2-7 are used by LCD16x2 shield
const int RLY_PIN = 8;  //Arduino pin connected to relay's IN; LOW => activate (NormalOpen->close)
const int BTN_PIN = 9;  //Arduino pin connected to button's OUT; user's interface to trigger relay's toggle

struct RelayLow{//relay activated by IN=LOW
  int inputPin;
  int state = 0;
  RelayLow(int inputPin)
    : inputPin{inputPin}
  {
    char buf[256]{};
    snprintf(buf, sizeof(buf), "RelayLow(inputPin=%d)", inputPin);
    Serial.println(buf);
  }
  void init(){
    Serial.println("RelayLow::init() ... turn OFF");
    pinMode(inputPin, OUTPUT);
    off();
  }
  void off(){
    state = 0;
    digitalWrite(inputPin, HIGH);
  }
  void on(){
    state = 1;
    digitalWrite(inputPin, LOW);
  }
  void toggle(){
    digitalWrite(inputPin, state);
    state = !state;
    char buf[256];
    snprintf(buf, sizeof(buf), "RelayLow::toggle(inputPin=%d) state=%d", inputPin, state);
    Serial.println(buf);
  }
};

RelayLow relay(RLY_PIN);

void info(){//display useful information
    char buf[256]{};
    snprintf(buf, sizeof(buf), "%s %s() RLY_PIN=%d BTN_PIN=%d", __FILE__, __FUNCTION__, RLY_PIN, BTN_PIN);
    Serial.println(buf);
}

void setup(){//called twice after flashing from Arduino IDE!!!???
  Serial.begin(115200);
  Serial.println("setup()");
  info();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
  relay.init();
}

void loop(){
  static int btnSt0 = 0;
  static unsigned long btnMs = 0;//last moment when the button was pressed
  int btnSt = digitalRead(BTN_PIN);

  if(btnSt && btnSt!=btnSt0 && millis()-btnMs>1000){//button was pressed (is ON after it was OFF ... but not too quick one after another)
    btnMs = millis();
    relay.toggle();
    digitalWrite(LED_BUILTIN, relay.state);
  }
  btnSt0 = btnSt;

  if(relay.state == 0){//blink builtin led while relay is OFF
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
