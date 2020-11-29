#include <config-esp.h>

void setup() {
  Serial.begin(115200);

  config.begin();

  config.add("test_var1", 123);

  if (config.is("test_var1", 123)) Serial.println("First test passed");
  if (config.is("test_var1", "123")) Serial.println("Second test passed");
}

void loop() {
  
}