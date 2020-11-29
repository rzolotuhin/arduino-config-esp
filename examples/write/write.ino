#include <config-esp.h>

// attention, after use the example "read"
void setup() {
  Serial.begin(115200);

  config.begin();

  // creating config variables with default values
  config.add("test_var1", "qwe");
  config.add("test_var2", "asd");
  config.add("test_var3", "zxc");

  // write from RAM to Flash
  config.write();

  // displaying the contents of the config
  config.print(Serial);
}

void loop() {
  
}