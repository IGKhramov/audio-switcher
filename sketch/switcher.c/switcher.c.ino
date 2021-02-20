// Serial

int MAX_PORT = 21;

void reset()
// reset ports to zerro value
{
  for (int i = 2; i <= MAX_PORT; i++) {
    digitalWrite(i, 0);
  }
}

boolean  isNumber(String str) {
  if (str.length() == 0) {
    return false;
  }
  for (unsigned i = 0; i < str.length(); i++) {
    if (isDigit(str[i]) || str[i] == '-' || str[i] == '+') {
      continue;
    }
    return false;
  }
  return true;
}

void setup()
{
  Serial.begin(115200);  // initialize serial communications at 115200 bps
  for (int i = 2; i <= MAX_PORT; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, 0);
  }
}

void loop()
{
  while (!Serial.available()) {}

  String data;
  char c = Serial.read();
  if (c == '<') { // mesage start
    delay(1);
    while ( c != '>' ) { // mesage end
      c = Serial.read();
      if (c != '>') {
        data += c;
      }
    }
    int d = data.indexOf(":"); // message devider
    if (d > 0) {
      // devide message into port:value
      String sPort = data.substring(0, d);
      String sVal = data.substring(d + 1);

      if (isNumber(sPort) && isNumber(sVal)) {
        //port and value are numbers
        int port = sPort.toInt();
        int val = sVal.toInt();
        //        Serial.print(String(val) + "\n");
        if (val > 0) {
          val = 1;
        }
        else {
          val = 0;
        }

        if (port >= 0 && port <= (MAX_PORT - 2) * 4)
        {
          reset();
          if (val > 0) {
            digitalWrite(2, port & 1);
            digitalWrite(3, (port >> 1) & 1);
          }
          digitalWrite(4 + (port >> 2), val);
        }
      }
    }
  }
}
