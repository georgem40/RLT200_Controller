#include "menu-system.h"
#include "utility.h"

static WLabel red_intensity(2, 100, 5, 3);
static WLabel IR_intensity(2, 240, 5, 3);
static WLabel timer_minutes_counter(2, 178, 45, 4);
static WLabel timer_seconds_counter(2, 237, 45, 4);
static WLabel stop_button(8, 85, 95, 3, 60);

static double minutes_left, seconds_left, prev_minutes_left, prev_seconds_left;

void WRunMenu::tick()
{
    send_intensity(red_intensity_val, IR_intensity_val, true);

    // count down the timer
    double elasped_time = (millis() - countdown_prev_time) / 1000.0;
    minutes_left = (time_on_timer_in_seconds - elasped_time) / 60.0;
    seconds_left = (minutes_left - floor(minutes_left)) * 60;

    // only update the screen if the values change - avoids flicker
    // casting gets rid of negligable differences in the values
    if(int(prev_minutes_left) != int(minutes_left) || elasped_time <= 0.5)
        timer_minutes_counter.paint_two_digits(uint8_t(minutes_left), ILI9341_WHITE, ILI9341_BLACK);
    if(int(prev_seconds_left) != int(seconds_left) || elasped_time <= 0.5)
        timer_seconds_counter.paint_two_digits(uint8_t(seconds_left), ILI9341_WHITE, ILI9341_BLACK);

    prev_minutes_left = minutes_left;
    prev_seconds_left = seconds_left;

    // return to main menu once the time is up
    if(uint16_t(elasped_time) == time_on_timer_in_seconds)
    {
        timer_minutes_counter.paint_two_digits(0, ILI9341_WHITE, ILI9341_BLACK);
        timer_seconds_counter.paint_two_digits(0, ILI9341_WHITE, ILI9341_BLACK);
        send_intensity(0, 0, false);
        menu.setMenu(main_menu);
    }
}

void WRunMenu::paint()
{
    WLabel::paint(F("RED "),   40, 5, ILI9341_RED, ILI9341_BLACK, 3);
    WLabel::paint(F("IR "),   190, 5, ILI9341_WHITE, ILI9341_BLACK, 3);

    red_intensity.paint_two_digits(red_intensity_val, ILI9341_RED, ILI9341_BLACK);
    IR_intensity.paint_two_digits(IR_intensity_val, ILI9341_WHITE, ILI9341_BLACK);

    WLabel::paint(F("TIMER: "), 25, 45, ILI9341_WHITE, ILI9341_BLACK, 4);
    WLabel::paint(F(":"), 222, 45, ILI9341_WHITE, ILI9341_BLACK, 4);

    stop_button.paint(F("STOP"), ILI9341_BLACK, ILI9341_RED);
}

void WRunMenu::touch(uint16_t x, uint16_t y)
{
    if(stop_button.hit(x, y))
        menu.setMenu(main_menu);
}

