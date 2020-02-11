/*
  Deep Sleep with External Wake Up
  =====================================
  This code displays how to use deep sleep with
  an external trigger as a wake up source and how
  to store data in RTC memory to use it over reboots

  This code is under Public Domain License.

  Hardware Connections
  ======================
  Push Button to GPIO 33 pulled down with a 10K Ohm
  resistor

  NOTE:
  ======
  Only RTC IO can be used as a source for external wake
  source. They are pins: 0,2,4,12-15,25-27,32-39.

  Author:
  Pranav Cherukupalli <cherukupallip@gmail.com>
*/
// tes github
// tes branch
#define BUTTON_PIN_BITMASK 0x8014 // 2^33 in hex

RTC_DATA_ATTR int bootCount = 0;

/*
  Method to print the reason by which ESP32
  has been awaken from sleep
*/

void setup() {
  pinMode(23, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(2, OUTPUT)
  Serial.begin(115200);
  // esp_err_t rtc_gpio_deinit(GPIO_NUM_33);
  delay(1000); //Take some time to open up the Serial Monitor

  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  /*
    First we configure the wake up source
    We set our ESP32 to wake up for an external trigger.
    There are two types for ESP32, ext0 and ext1 .
    ext0 uses RTC_IO to wakeup thus requires RTC peripherals
    to be on while ext1 uses RTC Controller so doesnt need
    peripherals to be powered on.
    Note that using internal pullups/pulldowns also requires
    RTC peripherals to be turned on.
  */

  //  esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 1); //1 = High, 0 = Low
  //  esp_sleep_enable_ext0_wakeup(GPIO_NUM_5, 1);
  //If you were to use ext1, you would use it like
  esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK, ESP_EXT1_WAKEUP_ANY_HIGH);

  // activate resistor pulldown
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
  gpio_pullup_dis(GPIO_NUM_2);
  gpio_pulldown_en(GPIO_NUM_2);
  gpio_pullup_dis(GPIO_NUM_4);
  gpio_pulldown_en(GPIO_NUM_4);
  gpio_pullup_dis(GPIO_NUM_15);
  gpio_pulldown_en(GPIO_NUM_15);

}

void loop() {
  //This is not going to be called

  //wakeup reason
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();

  if (ESP_SLEEP_WAKEUP_EXT1 == wakeup_reason) {
    if (
    Serial.println("Ade");
    delay(1000);
    Serial.println("Rohdiana");
    delay(1000);
    Serial.println("Oke");
    delay(1000);
    esp_deep_sleep_start();
  }
  else if (ESP_SLEEP_WAKEUP_EXT1 != wakeup_reason) {
    //Go to sleep now
    Serial.println("Going to sleep now");
    esp_deep_sleep_start();
    Serial.println("This will never be printed");
    delay (1000);
  }
}
