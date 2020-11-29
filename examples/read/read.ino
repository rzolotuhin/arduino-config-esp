#include <config-esp.h>

// attention, first use the example "write"
void setup() {
  Serial.begin(115200);

  config.begin();

  // creating config variables with default values
  config.add("test_var1", "001");
  config.add("test_var2", "002");
  config.add("test_var3", "003");

  // reading values from flash memory
  // if a variable is found, its value will be overwritten in RAM
  config.read();

  // displaying the contents of the config
  config.print(Serial);
}

void loop() {
  
}