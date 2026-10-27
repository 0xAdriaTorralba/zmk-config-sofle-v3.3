#include <zephyr/kernel.h>
#include "profile.h"

// Line tops chosen so the glyphs of both fonts span rows 69-102 / 76-95, centred on row 85
#define PROFILE_NUMBER_Y (60 + BUFFER_OFFSET_MIDDLE)
#define PROFILE_USB_Y (71 + BUFFER_OFFSET_MIDDLE)

static void draw_profile_number(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &lv_font_montserrat_48, LV_TEXT_ALIGN_CENTER);

    char text[12] = {};

    snprintf(text, sizeof(text), "%d", state->active_profile_index + 1);
    lv_canvas_draw_text(canvas, 0, PROFILE_NUMBER_Y, BUFFER_SIZE, &label_dsc, text);
}

static void draw_usb(lv_obj_t *canvas) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &lv_font_montserrat_28, LV_TEXT_ALIGN_CENTER);

    lv_canvas_draw_text(canvas, 0, PROFILE_USB_Y, BUFFER_SIZE, &label_dsc, "USB");
}

void draw_profile_status(lv_obj_t *canvas, const struct status_state *state) {
    if (state->selected_endpoint.transport == ZMK_TRANSPORT_USB) {
        draw_usb(canvas);
    } else {
        draw_profile_number(canvas, state);
    }
}
