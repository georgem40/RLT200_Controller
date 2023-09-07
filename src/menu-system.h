#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include "menu.h"

// Color definitions
#define ILI9341_BLACK 0x0000       ///<   0,   0,   0
#define ILI9341_NAVY 0x000F        ///<   0,   0, 123
#define ILI9341_DARKGREEN 0x03E0   ///<   0, 125,   0
#define ILI9341_DARKCYAN 0x03EF    ///<   0, 125, 123
#define ILI9341_MAROON 0x7800      ///< 123,   0,   0
#define ILI9341_PURPLE 0x780F      ///< 123,   0, 123
#define ILI9341_OLIVE 0x7BE0       ///< 123, 125,   0
#define ILI9341_LIGHTGREY 0xC618   ///< 198, 195, 198
#define ILI9341_DARKGREY 0x7BEF    ///< 123, 125, 123
#define ILI9341_BLUE 0x001F        ///<   0,   0, 255
#define ILI9341_GREEN 0x07E0       ///<   0, 255,   0
#define ILI9341_CYAN 0x07FF        ///<   0, 255, 255
#define ILI9341_RED 0xF800         ///< 255,   0,   0
#define ILI9341_MAGENTA 0xF81F     ///< 255,   0, 255
#define ILI9341_YELLOW 0xFFE0      ///< 255, 255,   0
#define ILI9341_WHITE 0xFFFF       ///< 255, 255, 255
#define ILI9341_ORANGE 0xFD20      ///< 255, 165,   0
#define ILI9341_GREENYELLOW 0xAFE5 ///< 173, 255,  41
#define ILI9341_PINK 0xFC18        ///< 255, 130, 198

class MenuSystem
{
   public:
      void setMenu(WMenuBase& menu);
      void prevMenu(void);
      // void paintChangeControls(bool back=false) const;
      bool isMainMenu() const;

      inline void begin(void)
      {
         setMenu( main_menu );
      }

      inline void tick()
      {
         current->tick();
      }

      inline void touch(uint16_t x, uint16_t y)
      {
         current->touch(x, y);
      }

      uint16_t last_touch_x, last_touch_y;

   private:
      WMenuBase *current;
      WMenuBase *previous;
};

extern MenuSystem menu;
extern uint8_t red_intensity_val, IR_intensity_val, time_on_timer;
extern uint8_t prev_red_intensity_val, prev_IR_intensity_val, prev_time_on_timer;
extern uint16_t time_on_timer_in_seconds, countdown_time_in_seconds;
extern unsigned int countdown_prev_time;

#endif /* MENU_SYSTEM_H */
