#include <Arduino.h>
#include <TFT_eSPI.h>
#include "menu-system.h"
#include "TouchLib.h"
#include "utility.h"
#include "touch-debounce.h"
#include "Wire.h"

// How frequent each menu should update itself (ms)
#define MENU_UPDATE_FREQUENCY 30

#define PIN_IIC_SDA 18
#define PIN_IIC_SCL 17
#define SLAVE_ADDRESS CTS816S_SLAVE_ADDRESS
#define PIN_TOUCH_RES -1

unsigned long prev_time;

TFT_eSPI tft = TFT_eSPI();

TouchLib touch(Wire, PIN_IIC_SDA, PIN_IIC_SCL, SLAVE_ADDRESS, PIN_TOUCH_RES);

// The menu controller
MenuSystem menu;

void setup(void)
{
   Serial.begin(115200);

   pinMode(15, OUTPUT); // to boot with battery...
   digitalWrite(15,1); // and/or power from 5v rail instead of USB

   // get saved intensity and time settings
   fetch_settings();

   // output pins setup
   setup_output();

   tft.init();
   tft.setRotation(3);

   Wire.begin(PIN_IIC_SDA, PIN_IIC_SCL);
    if (!touch.init()) {
        Serial.println("Touch IC not found");
    }

   // // origin = left,top landscape (USB left upper)
   menu.begin();  // sets the main menu as the screen menu

   prev_time = millis();
}

void loop()
{
   // update the current menu
   if(millis() - prev_time >= MENU_UPDATE_FREQUENCY)
   {
      prev_time = millis();
      menu.tick();
   }

  // check for LCD touches
   if (touch.read())
   {
      // map to the display configuration
      uint16_t x = touch.getPoint(0).y;
      uint16_t y = touch.getPoint(0).x;
      x = map(x, 0, 320, 320, 0);

      if(menu.last_touch_x != x && menu.last_touch_y != y)
      {
         menu.last_touch_x = x;
         menu.last_touch_y = y;
         menu.touch(x, y);
      }
   }
}