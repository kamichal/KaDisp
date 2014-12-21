/*
 * osd9616.c
 *
 *  Created on: Dec 7, 2014
 *      Author: kamichal
 */

#include "osd9616.h"
#include "usbstk5515_i2c.h"
#include "usbstk5515_gpio.h"
#include "platform_lcd_defines.h"

void SSD1780_init(void)
{
    /* Initialize LCD power */
    USBSTK5515_GPIO_setDirection(GPIO12, GPIO_OUT);
    USBSTK5515_GPIO_setOutput(GPIO12, 1);

    SSD1780_set_memory_addressing(mem_mode_page_addressing);

    SSD1780_set_PAM_column_start_addres(0);
    SSD1780_set_PAM_page_addres(0);

    SSD1780_set_display_start_line(0);

    SSD1780_set_contrast(0x2f);

    SSD1780_send_cmd(SSD1780_SET_SEGMENT_REMAP_COL0_TO_SEG0);   // 0xA0
    SSD1780_send_cmd(SSD1780_DISPLAY_NORMAL);                   // 0xA6
    SSD1780_send_cmd_val(SSD1780_SET_MULTIPLEX_RATIO, 0x3F);    // 0xA8

    SSD1780_send_cmd_val(SSD1780_SET_VERTICAL_OFFSET, 0x00);  // 0xD3 Not offset
    SSD1780_send_cmd_val(SSD1780_SET_CLOCK_DIV_RATIO, 0xf0); // 0xD5 Set divide ratio
    SSD1780_send_cmd_val(SSD1780_SET_PRE_CHARGE_PERIOD, 0x22);  // 0xD9
    SSD1780_send_cmd_val(SSD1780_SET_COM_PINS_HW_CONFIG, 0x02); // 0xDA
    SSD1780_send_cmd_val(SSD1780_SET_COMH_DESELECT_LEVEL, 0x49); // 0xDB 0.83*vref
    SSD1780_send_cmd_val(SSD1780_SET_CHARGE_PUMP, SSD1780_CHARGE_PUMP_ENABLED); // 0x8D

    SSD1780_send_cmd(SSD1780_TURN_DISP_ON); // 0xAF

    SSD1780_clear_graphic_ram();

    SSD1780_setup_default_scrolling();
}

Int16 SSD1780_send_cmd(Uint16 command)
{
    Uint8 cmd[2];
    cmd[0] = SSD1780_SEND_COMMAND;  // 0x00 D/#C low = it's a command
    cmd[1] = command;               // Command
    return USBSTK5515_I2C_write(OSD9616_I2C_ADDR, cmd, 2);
}

Int16 SSD1780_send_cmd_val(Uint8 command, Uint8 val)
{
    Uint8 cmd[3];
    cmd[0] = SSD1780_SEND_COMMAND;  // 0x00 D/#C low = it's a command
    cmd[1] = command;               // Command
    cmd[2] = val;               // Command

    return USBSTK5515_I2C_write(OSD9616_I2C_ADDR, cmd, 3);
}

Int16 SSD1780_send_data(Uint8 data)
{
    Uint8 dat[2];
    dat[0] = SSD1780_SEND_DATA; // 0x40 D/#C high = it's a data
    dat[1] = data;          // Data
    return USBSTK5515_I2C_write(OSD9616_I2C_ADDR, dat, 2);
}


Int16 SSD1780_set_PAM_column_start_addres(Uint8 addres_8b)
{
    /* This command is only for page addressing mode */
    /* The GDDRAM column address pointer is increased
     * by one automatically after each data write.
     * It's up to user to set the pointer before each write.
     * This command doesn't affect display window position,
     * just RAM write position.*/
    Int16 ret = 0;
    ret |= SSD1780_send_cmd(addres_8b & 0xF);           // Set low column address
    ret |= SSD1780_send_cmd((addres_8b >> 4) | 0x10);   // Set high column address
    return ret;
}

Int16 SSD1780_set_PAM_page_addres(Uint8 addres3b)
{
    /* This command is only for page addressing mode */
    return SSD1780_send_cmd(SSD1780_SET_PAM_PAGE_START_ADDRESS | (addres3b & 0x7)); //0xB0
}

Int16 SSD1780_set_VHAM_page_addres(Uint8 start_addres_3b, Uint8 end_addres_3b)
{
    /* This command is only for vertical and horizontal addressing mode */
    Uint8 cmd[4];
    cmd[0] = SSD1780_SEND_COMMAND;
    cmd[1] = SSD1780_SET_VHAM_PAGE_ADDRESS; //0x22
    cmd[2] = start_addres_3b & 0x7;
    cmd[3] = end_addres_3b & 0x7;
    return USBSTK5515_I2C_write(OSD9616_I2C_ADDR, cmd, 4);
}

Int16 SSD1780_set_VHAM_column_addres(Uint8 start_7b, Uint8 end_7b)
{
    /* This command is only for horizontal or vertical addressing mode.*/
    Uint8 cmd[4];
    cmd[0] = SSD1780_SEND_COMMAND;
    cmd[1] = SSD1780_SET_VHAM_COLUMN_ADDRESS; // 0x21
    cmd[2] = start_7b & 0x7F;
    cmd[3] = end_7b & 0x7F;
    return USBSTK5515_I2C_write(OSD9616_I2C_ADDR, cmd, 4);
}

Int16 SSD1780_set_display_start_line(Uint8 line_6b)
{
    return SSD1780_send_cmd(SSD1780_SET_DISPLAY_START_LINE | (line_6b & 0x3F)); //0x40
}

void SSD1780_setup_horizontal_scroll(
                                     Uint8 start_page,
                                     Uint8 end_page,
                                     SSD1780_scroll_interval_e interval,
                                     SSD1780_H_scroll_direction_e dir)
{
    Uint8 cmd[8];
    cmd[0] = SSD1780_SEND_COMMAND;
    cmd[1] = (dir & 1) | SSD1780_SCROLL_H_RIGHT;
    cmd[2] = SSD1780_DUMMY_ZERO;
    cmd[3] = start_page & 0x7;    //first page which the setup is addressed to
    cmd[4] = (Uint8) interval;
    cmd[5] = end_page & 0x7;      // last page which the setup is addressed to
    cmd[6] = SSD1780_DUMMY_ZERO;
    cmd[7] = SSD1780_DUMMY_FF;
    USBSTK5515_I2C_write(OSD9616_I2C_ADDR, cmd, 8);
}

void SSD1780_setup_vertical_and_horizontal_scroll(
                                                  Uint8 start_page,
                                                  Uint8 end_page,
                                                  SSD1780_scroll_interval_e interval,
                                                  SSD1780_VH_scroll_direction_e dir,
                                                  Uint8 V_offset)
{
    Uint8 cmd[7];
    if (V_offset < 1)
        V_offset = 1;
    else if (V_offset > 0x37)
        V_offset = 0x3F;

    cmd[0] = SSD1780_SEND_COMMAND;
    cmd[1] = (dir & 3) | SSD1780_SCROLL_VH_BITMASK;
    cmd[2] = SSD1780_DUMMY_ZERO;
    cmd[3] = start_page & 0x7;    //first page which the setup is addressed to
    cmd[4] = (Uint8) interval;
    cmd[5] = end_page & 0x7;      // last page which the setup is addressed to
    cmd[6] = V_offset & 0x3F;
    USBSTK5515_I2C_write(OSD9616_I2C_ADDR, cmd, 7);
}

Int16 SSD1780_set_memory_addressing(SSD1780_mem_mode_e mode)
{
    return SSD1780_send_cmd_val(SSD1780_SET_MEM_ADDRESSING_MODE, mode & 0x3); //0x20
}

void SSD1780_set_contrast(Uint8 contrast_value)
{
    /*The default contrast value is 0x1f or 0x7F */
    Uint8 cmd[3];
    cmd[0] = SSD1780_SEND_COMMAND;
    cmd[1] = SSD1780_SET_CONSTRAST;
    cmd[2] = contrast_value;
    USBSTK5515_I2C_write(OSD9616_I2C_ADDR, cmd, 3);
}

void SSD1780_set_vertical_scroll_area(Uint8 fixed_height, Uint8 floating_height)
{
    unsigned char cmd[10];
    /* Keep first 8 rows from vertical scrolling  */
    cmd[0] = SSD1780_SEND_COMMAND;
    cmd[1] = SSD1780_SET_V_SCROLL_AREA; // Set Vertical Scroll Area
    cmd[2] = fixed_height & 0x3F; // Set No. of rows in top fixed area
    cmd[3] = floating_height & 0x7F; // Set No. of rows in scroll area
    USBSTK5515_I2C_write(OSD9616_I2C_ADDR, cmd, 4);
}

Int16 SSD1780_clear_graphic_ram(void)
{
    Int16 ret = 0;
    Uint16 page;
    Uint16 column;
    for (page = 0; page < SSD1780_PAGE_COUNT; page++)
    {
        SSD1780_set_PAM_page_addres(page);
        SSD1780_set_PAM_column_start_addres(0);
        for (column = 0; column < SSD1780_PAGE_WIDTH; column++)
        {
            ret |= SSD1780_send_data(0x00);
        }
        USBSTK5515_waitusec(10000);
    }

    return ret;
}


void SSD1780_setup_default_scrolling(void)
{
#if !scrols_vert
    SSD1780_setup_horizontal_scroll(0, 1, interval_64_frames, scroll_left);

#elif scrols_vert_one_line

    SSD1780_setup_vertical_and_horizontal_scroll(0, 1, interval_128_frames,
            scroll_vert_left, 2);
    /* Keep first 8 rows from vertical scrolling  */
    SSD1780_set_vertical_scroll_area(8,8);
#else //scrolls whole window
    SSD1780_setup_vertical_and_horizontal_scroll(0, // start page
                                                 SSD1780_PAGE_COUNT, // end page
                                                 interval_128_frames,
                                                 scroll_vert_left,
                                                 1); //v_offset
    /* Keep first 8 rows from vertical scrolling  */
    SSD1780_set_vertical_scroll_area(0, SSD1780_PAGE_COUNT * 8);
#endif

#if !scrols
    SSD1780_send_cmd(SSD1780_DISABLE_SCROLLING);
#else
    SSD1780_send_cmd(SSD1780_ENABLE_SCROLLING);
#endif
}
