#include <zephyr/kernel.h>
#include "battery.h"
#include "../assets/custom_fonts.h"

LV_IMG_DECLARE(bolt);

// Battery icon: 24x11 outline with a 2x5 terminal nub, 1 px gap, 20x7 fill area.
#define BATTERY_X 0
#define BATTERY_Y 20
#define BATTERY_W 24
#define BATTERY_H 11
#define BATTERY_NUB_W 2
#define BATTERY_NUB_H 5
#define BATTERY_FILL_W (BATTERY_W - 4)
#define BATTERY_FILL_H (BATTERY_H - 4)

static void draw_icon(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_rect_dsc_t rect_fg_dsc;
    init_rect_dsc(&rect_fg_dsc, LVGL_FOREGROUND);
    lv_draw_rect_dsc_t rect_bg_dsc;
    init_rect_dsc(&rect_bg_dsc, LVGL_BACKGROUND);

    // Outline: solid body, hollowed out by a background rectangle
    lv_canvas_draw_rect(canvas, BATTERY_X, BATTERY_Y, BATTERY_W, BATTERY_H, &rect_fg_dsc);
    lv_canvas_draw_rect(canvas, BATTERY_X + 1, BATTERY_Y + 1, BATTERY_W - 2, BATTERY_H - 2,
                        &rect_bg_dsc);
    lv_canvas_draw_rect(canvas, BATTERY_X + BATTERY_W, BATTERY_Y + (BATTERY_H - BATTERY_NUB_H) / 2,
                        BATTERY_NUB_W, BATTERY_NUB_H, &rect_fg_dsc);

    // Fill proportional to the level, rounded to the nearest pixel
    int level = state->battery > 100 ? 100 : state->battery;
    int fill_w = (level * BATTERY_FILL_W + 50) / 100;
    if (fill_w > 0) {
        lv_canvas_draw_rect(canvas, BATTERY_X + 2, BATTERY_Y + 2, fill_w, BATTERY_FILL_H,
                            &rect_fg_dsc);
    }
}

static void draw_level(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_label_dsc_t label_right_dsc;
    init_label_dsc(&label_right_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_RIGHT);

    char text[10] = {};

    sprintf(text, "%i%%", state->battery);
    lv_canvas_draw_text(canvas, 26, 19, 42, &label_right_dsc, text);
}

static void draw_charging_level(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);
    lv_draw_label_dsc_t label_right_dsc;
    init_label_dsc(&label_right_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_RIGHT);

    char text[10] = {};

    sprintf(text, "%i%%", state->battery);
    lv_canvas_draw_text(canvas, 26, 19, 35, &label_right_dsc, text);
    lv_canvas_draw_img(canvas, 62, 21, &bolt, &img_dsc);
}

void draw_battery_status(lv_obj_t *canvas, const struct status_state *state) {
    draw_icon(canvas, state);

    if (state->charging) {
        draw_charging_level(canvas, state);
    } else {
        draw_level(canvas, state);
    }
}
