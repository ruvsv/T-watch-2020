// Dan Geiger's app menu code
//
// heavily modified by W.F.Dudley Jr.

#include "config.h"
#include "DudleyWatch.h"

void dummyTime(void) {}

void switch_menu(void) {
  if(app_menu_ptr == &watch_apps[0]) {
    app_menu_ptr = &watch_apps2[0];
    app_label_ptr = &app_labels2[0];
    Serial.println(F("switch to page 2"));
  }
  else {
    app_menu_ptr = &watch_apps[0];
    app_label_ptr = &app_labels[0];
    Serial.println(F("switch to page 1"));
  }
}

uint8_t modeMenu(void) {
int mSelect;
  draw_keyboard(12, app_label_ptr, 1, true, "pick an app");
  while(1) {
    mSelect = poll_swipe_or_menu_press(12); // poll for touch or gesture
    if (mSelect > -1 && mSelect < NODIR) {
      int row, col;
      row = mSelect / 3;
      col = mSelect % 3;
      flash_keyboard_item(app_label_ptr, 1, true, row, col);
      Serial.printf("poll_swipe_or_menu_press -> %d, app should be %s\n",
	mSelect, app_menu_ptr[mSelect].name);
      if(app_menu_ptr[mSelect].next_menu) {
	return mSelect;
      }
      else {	// no function to run, so return <ESC> so we're run Clock
	return 0x1b;
      }
    }
    my_idle();
  }
}

