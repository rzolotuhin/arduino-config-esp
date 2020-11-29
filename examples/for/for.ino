#include <config-esp.h>

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

  // config size output
  // it can change if the config contains more parameters in the Flash memory
  Serial.printf("size: %d\n", config.list().size());

  // getting all config data
  for(auto &cfg: config.list()) {
    Serial.printf("var: %s, val: %s\n", cfg.first, cfg.second);
  }
}

void loop() {
  
}