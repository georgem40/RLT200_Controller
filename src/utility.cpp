#include "menu-system.h"
#include "Preferences.h"

// RED and IR PWM pins
#define RED_PWM 10
#define IR_PWM  9

#define RED_CHANNEL 1
#define IR_CHANNEL  2
#define RED_PIN     2
#define IR_PIN      3

#define CHANNEL_RESOLUTION 8 // bits
#define CHANNEL_FREQUENCY  2000

#define FAN_PIN 1

// serial output buffer
static char buffer[32];

// value storage
Preferences preferences;

void save_settings()
{
    preferences.begin("RLT-Controller", false);
    
    preferences.putInt("time_on_timer", time_on_timer);
    preferences.putInt("red_intensity", red_intensity_val);
    preferences.putInt("IR_intensity", IR_intensity_val);

    preferences.end();
}
 
void fetch_settings()
{
    preferences.begin("RLT-Controller", false);

    time_on_timer = preferences.getInt("time_on_timer", 0);
    red_intensity_val = preferences.getInt("red_intensity", 0);
    IR_intensity_val = preferences.getInt("IR_intensity", 0);

    preferences.end();

    if(time_on_timer > 30)
        time_on_timer = 0;
    if(red_intensity_val > 99)
        red_intensity_val = 0;
    if(IR_intensity_val > 99)
        IR_intensity_val = 0;
}

void setup_output()
{
    ledcSetup(RED_CHANNEL, CHANNEL_FREQUENCY, CHANNEL_RESOLUTION);
    ledcAttachPin(RED_PIN, RED_CHANNEL);

    ledcSetup(IR_CHANNEL, CHANNEL_FREQUENCY, CHANNEL_RESOLUTION);
    ledcAttachPin(IR_PIN, IR_CHANNEL);

    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(FAN_PIN, LOW);
}

void send_intensity(uint8_t red, uint8_t IR, bool fan_state)
{
    red = map(red, 0, 99, 0, 255);
    IR = map(IR, 0, 99, 0, 255);

    // send red and IR intensities
    ledcWrite(RED_CHANNEL, red);
    ledcWrite(IR_CHANNEL, IR);

    // set fan status
    digitalWrite(FAN_PIN, fan_state);
}



