#include <max31329.h>

Max31329 rtc(&Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin(26,27);

  delay(200);

  rtc.reset();

  // setting config
  max31329_config_t config;
  config.config1 = 0x01;
  config.config2 = 0x0;
  uint16_t ret = rtc.set_config_reg(config);
  Serial.print("config update:");
  Serial.println(ret);

  delay(1);

  // setting time and date
  max31329_time_t time;
  max31329_calendar_t date;
  
  time.hours=21;
  time.minutes=35;
  time.seconds=0;
  rtc.set_time(time);
  date.day=1;
  date.date=12;
  date.month=12;
  date.year=22;
  rtc.set_calendar(date);
  delay(1000);
}

void print_current_date_time(){
  max31329_time_t time;
  max31329_calendar_t date;

  // Get Time and date from MAX31329
  if(rtc.get_time(&time) || rtc.get_calendar(&date)){
    Serial.println("ERROR: Cannot get time.");
    return;
  }

  max31329_config_t config;
  if(rtc.get_config_reg(&config)) {
    Serial.println("ERROR: Cannot get config.");
    return;
  }

  // print config
  Serial.print("RTC Config: ");
  Serial.print(config.config1, BIN);
  Serial.println(config.config2, BIN);

  Serial.print("RTC Time: ");

  // Print date
  Serial.print(date.month);
  Serial.print("/");
  Serial.print(date.date);
  Serial.print("/");
  Serial.print(date.year + 2000);
  Serial.print(" - ");
  // Print time
  Serial.print(time.hours);
  Serial.print(":");
  Serial.print(time.minutes);
  Serial.print(":");
  Serial.println(time.seconds);
}

void loop() {
  long current_millis = millis();
  static long previous_millis = current_millis-5000;

  // Print date/time once every five seconds
  if( current_millis - previous_millis > 5000){
    print_current_date_time();
    previous_millis = current_millis;
  }
}