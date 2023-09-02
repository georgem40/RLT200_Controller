#ifndef UTILITY_H
#define UTILITY_H

void save_settings();
void fetch_settings();

void setup_output();
void send_intensity(uint8_t red, uint8_t IR, bool fan_state);

#endif /*UTILITY_H*/