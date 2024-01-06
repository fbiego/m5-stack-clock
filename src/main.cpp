/*
   MIT License

  Copyright (c) 2024 Felix Biego

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  ______________  _____
  ___  __/___  /_ ___(_)_____ _______ _______
  __  /_  __  __ \__  / _  _ \__  __ `/_  __ \
  _  __/  _  /_/ /_  /  /  __/_  /_/ / / /_/ /
  /_/     /_.___/ /_/   \___/ _\__, /  \____/
                              /____/

*/
#include <Arduino.h>

#include <lvgl.h>
#include <M5Unified.h>
#include <Timber.h>
#include <ChronosESP32.h>
#include "ui/ui.h"

#define SCR 10

ChronosESP32 watch("M5 Stack");

static const uint32_t screenWidth = 320;
static const uint32_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;

static lv_color_t disp_draw_buf[screenWidth * SCR];
static lv_color_t disp_draw_buf2[screenWidth * SCR];

ChronosTimer notify;

int nIndex = 0;

lv_img_dsc_t notificationIcons[] = {
    ui_img_sms_png,       // SMS
    ui_img_mail_png,      // Mail
    ui_img_penguin_png,   // Penguin
    ui_img_skype_png,     // Skype
    ui_img_whatsapp_png,  // WhatsApp
    ui_img_mail_png,      // Mail2
    ui_img_line_png,      // Line
    ui_img_twitter_png,   // Twitter
    ui_img_facebook_png,  // Facebook
    ui_img_messenger_png, // Messenger
    ui_img_instagram_png, // Instagram
    ui_img_weibo_png,     // Weibo
    ui_img_kakao_png,     // Kakao
    ui_img_viber_png,     // Viber
    ui_img_vkontakte_png, // Vkontakte
    ui_img_telegram_png,  // Telegram
    ui_img_wechat_png     // Wechat
};

lv_img_dsc_t weatherIcons[] = {
    ui_img_dy0_png,
    ui_img_dy1_png,
    ui_img_dy2_png,
    ui_img_dy3_png,
    ui_img_dy4_png,
    ui_img_dy5_png,
    ui_img_dy6_png,
    ui_img_dy7_png};

lv_img_dsc_t weatherNtIcons[] = {
    ui_img_nt0_png, // assets\nt-0.png
    ui_img_nt1_png, // assets\nt-1.png
    ui_img_nt2_png, // assets\nt-2.png
    ui_img_nt3_png, // assets\nt-3.png
    ui_img_nt4_png, // assets\nt-4.png
    ui_img_nt5_png, // assets\nt-5.png
    ui_img_nt6_png, // assets\nt-6.png
    ui_img_nt7_png, // assets\nt-7.png
};

bool isDay();
int getNotificationIconIndex(int id);
int getWeatherIconIndex(int id);
void showNotification(int index);

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  uint32_t wh = w * h;

  M5.Lcd.startWrite();
  M5.Lcd.setAddrWindow(area->x1, area->y1, w, h);
  while (wh--)
    M5.Lcd.pushColor(color_p++->full);
  M5.Lcd.endWrite();

  lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
}

int getWeatherIconIndex(int id)
{
  if (id >= 0 && id <= 7)
  {
    return id;
  }
  return 0;
}

int getNotificationIconIndex(int id)
{
  switch (id)
  {
  case 0x03:
    return 0;
  case 0x04:
    return 1;
  case 0x07:
    return 2;
  case 0x08:
    return 3;
  case 0x0A:
    return 4;
  case 0x0B:
    return 5;
  case 0x0E:
    return 6;
  case 0x0F:
    return 7;
  case 0x10:
    return 8;
  case 0x11:
    return 9;
  case 0x12:
    return 10;
  case 0x13:
    return 11;
  case 0x14:
    return 12;
  case 0x16:
    return 13;
  case 0x17:
    return 14;
  case 0x18:
    return 15;
  case 0x09:
    return 16;
  default:
    return 0;
  }
}

void notificationCallback(Notification notification)
{
  Timber.d("Notification Received from " + notification.app + " at " + notification.time);
  Timber.d(notification.message);
  lv_obj_t *scr = lv_disp_get_scr_act(lv_disp_get_default());
  if (scr != ui_messageScreen)
  {
    notify.duration = 4500;
    lv_scr_load_anim(ui_messageScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0, false);
  }
  showNotification(0);
  notify.active = true;
  notify.time = millis();
}

void logCallback(Level level, unsigned long time, String message)
{
  Serial.print(message);
}

void setup()
{
  Serial.begin(115200);
  M5.begin();

  lv_init();

  if (!disp_draw_buf)
  {
    Timber.e("LVGL disp_draw_buf allocate failed!");
  }
  else
  {

    Timber.i("Display buffer size initialized ");

    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, disp_draw_buf2, screenWidth * SCR);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    ui_init();

    // lv_obj_t *label1 = lv_label_create(lv_scr_act());
    // lv_obj_align(label1, LV_ALIGN_TOP_MID, 0, 100);
    // lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);
    // lv_obj_set_width(label1, screenWidth - 30);
    // lv_label_set_text(label1, "Hello there!");

    // /*Create a slider below the label*/
    // lv_obj_t *slider1 = lv_slider_create(lv_scr_act());
    // lv_obj_set_width(slider1, screenWidth - 40);
    // lv_obj_align_to(slider1, label1, LV_ALIGN_OUT_BOTTOM_MID, 0, 50);

    Timber.i("Setup done");
  }

  // watch.setConnectionCallback(connectionCallback);
  watch.setNotificationCallback(notificationCallback);
  // watch.setConfigurationCallback(configCallback);
  watch.begin();
  watch.set24Hour(true);
}

void loop()
{
  // put your main code here, to run repeatedly:
  M5.update();
  watch.loop();

  lv_timer_handler(); /* let the GUI do its work */
  delay(5);

  lv_label_set_text(ui_hourText, watch.getHourZ().c_str());
  lv_label_set_text(ui_minuteText, watch.getTime("%M").c_str());
  lv_label_set_text(ui_dateText, watch.getTime("%d %a").c_str());

  lv_label_set_text(ui_cityText, watch.getWeatherCity().c_str());
  lv_label_set_text_fmt(ui_tempText, "%d°C", watch.getWeatherAt(0).temp);

  int bat = M5.Power.getBatteryLevel();
  bool charge = M5.Power.isCharging();
  watch.setBattery(bat, charge);
  lv_arc_set_value(ui_batteryArc, bat);

  if (isDay())
  {
    lv_img_set_src(ui_weatherIcon, &weatherIcons[getWeatherIconIndex(watch.getWeatherAt(0).icon)]);
  }
  else
  {
    lv_img_set_src(ui_weatherIcon, &weatherNtIcons[getWeatherIconIndex(watch.getWeatherAt(0).icon)]);
  }

  lv_obj_t *scr = lv_disp_get_scr_act(lv_disp_get_default());
  if (scr == ui_messageScreen)
  {
    if (notify.active)
    {
      if (notify.time + notify.duration < millis())
      {
        notify.active = false;
      }
    }
    else
    {
      lv_scr_load_anim(ui_timeScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0, false);
    }
  }

  if (M5.BtnA.wasReleased())
  {
  }

  if (M5.BtnB.wasReleased())
  {
    lv_obj_t *scr = lv_disp_get_scr_act(lv_disp_get_default());
    if (scr != ui_timeScreen)
    {
      lv_scr_load_anim(ui_timeScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0, false);
    }
  }

  if (M5.BtnC.wasReleased())
  {
    int count = watch.getNotificationCount();
    if (scr != ui_messageScreen)
    {
      lv_scr_load_anim(ui_messageScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0, false);
      if (count == 0)
      {
        lv_label_set_text(ui_messageText, "No notifications");
        lv_label_set_text(ui_messageTitle, "");
        lv_label_set_text(ui_messageTime, "");
      }
      else
      {
        nIndex = 0;
        showNotification(nIndex);
      }
    }
    else if (scr == ui_messageScreen)
    {
      nIndex++;
      if (nIndex >= count)
      {
        nIndex = 0;
      }
      showNotification(nIndex);
    }
    notify.active = true;
    notify.time = millis();
    notify.duration = 10000;
  }
}

void showNotification(int index)
{
  lv_img_set_src(ui_messageIcon, &notificationIcons[getNotificationIconIndex(watch.getNotificationAt(index).icon)]);
  lv_label_set_text(ui_messageText, watch.getNotificationAt(index).message.c_str());
  lv_label_set_text(ui_messageTitle, watch.getNotificationAt(index).app.c_str());
  lv_label_set_text(ui_messageTime, watch.getNotificationAt(index).time.c_str());
}

bool isDay()
{
  return watch.getHour(true) > 7 && watch.getHour(true) < 21;
}
