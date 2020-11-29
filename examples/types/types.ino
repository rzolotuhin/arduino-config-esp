#include <config-esp.h>

void setup() {
  Serial.begin(115200);

  config.begin();

  // you can use different types when creating a config, but they will all be converted to the String type
  config.add("test_var1", 123);
  config.add("test_var2", 3.14);
  config.add("test_var3", String("password"));
  config.add("test_var4", "1111");

  // convert type to INT
  uint16_t a = 77;
  Serial.println(a + config.get("test_var1").toInt());

  // convert type to FLOAT
  if (config.get("test_var2").toFloat() > 2.8) {
    Serial.println("test_var2 > 2.8\n");
  }

  // as with any String type, you can try converting it to the type you want
  Serial.println(config.get("test_var4").toInt());
}

void loop() {
  
}