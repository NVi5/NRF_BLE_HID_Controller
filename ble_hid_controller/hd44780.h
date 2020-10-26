#ifndef HD44780_H__
#define HD44780_H__

#include <stdint.h>
#include <stdbool.h>

#define LCD_PULSE_CLOCK do{nrf_gpio_pin_clear(LCD_PIN_CLK);nrf_delay_us(1);nrf_gpio_pin_set(LCD_PIN_CLK);nrf_delay_us(1);nrf_gpio_pin_clear(LCD_PIN_CLK);nrf_delay_us(1);}while(0)
#define LCD_CMD_FUNCTION_SET    0x20

#define LCD_CLK_SET                 nrf_gpio_pin_clear(LCD_PIN_CLK)
#define LCD_CLK_CLEAR               nrf_gpio_pin_set(LCD_PIN_CLK)
#define LCD_REGISTER_SELECT_COMMAND nrf_gpio_pin_clear(LCD_PIN_RS)
#define LCD_REGISTER_SELECT_DATA    nrf_gpio_pin_set(LCD_PIN_RS)

#define LCD_PIN_RS      (13)
#define LCD_PIN_CLK     (5)
#define LCD_PIN_B4      (6)
#define LCD_PIN_B5      (12)
#define LCD_PIN_B6      (14)
#define LCD_PIN_B7      (7)

void lcd_output_upper(uint8_t data);

void lcd_write8(uint8_t data);

void lcd_enable_4bit_mode(bool two_line_display, bool big_characters);

void lcd_clear_display(void);

void lcd_on_off_control(bool on, bool cursor_on, bool cursor_blink);

void lcd_set_cgram_address(uint8_t addr);

void lcd_set_ddram_address(uint8_t addr);

void lcd_write_string(char *string, uint32_t pos, bool lower_line);

void lcd_init(void);


#endif // HD44780_H__
