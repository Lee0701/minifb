#include <MiniFB.h>
#include "WindowData.h"
#include "MiniFB_internal.h"

//-------------------------------------
short int g_keycodes[512] = { 0 };
//-------------------------------------

//-------------------------------------
struct mfb_window *
mfb_open(const char *title, unsigned width, unsigned height) {
    return mfb_open_ex(title, width, height, 0);
}

//-------------------------------------
mfb_update_state
mfb_update(struct mfb_window *window, void *buffer) {
    if (window == 0x0) {
        return STATE_INVALID_WINDOW;
    }

    SWindowData *window_data = (SWindowData *) window;

    return mfb_update_ex(window, buffer, window_data->buffer_width, window_data->buffer_height);
}

//-------------------------------------
void
mfb_set_active_callback(struct mfb_window *window, mfb_active_func callback) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        window_data->active_func = callback;
    }
}

//-------------------------------------
void
mfb_set_resize_callback(struct mfb_window *window, mfb_resize_func callback) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        window_data->resize_func = callback;
    }
}

//-------------------------------------
void
mfb_set_close_callback(struct mfb_window* window, mfb_close_func callback) {
    if (window != 0x0) {
        SWindowData* window_data = (SWindowData*)window;
        window_data->close_func = callback;
    }
}

//-------------------------------------
void
mfb_set_keyboard_callback(struct mfb_window *window, mfb_keyboard_func callback) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        window_data->keyboard_func = callback;
    }
}

//-------------------------------------
void
mfb_set_char_input_callback(struct mfb_window *window, mfb_char_input_func callback) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        window_data->char_input_func = callback;
    }
}

//-------------------------------------
void
mfb_set_mouse_button_callback(struct mfb_window *window, mfb_mouse_button_func callback) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        window_data->mouse_btn_func = callback;
    }
}

//-------------------------------------
void
mfb_set_mouse_move_callback(struct mfb_window *window, mfb_mouse_move_func callback) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        window_data->mouse_move_func = callback;
    }
}

//-------------------------------------
void
mfb_set_mouse_scroll_callback(struct mfb_window *window, mfb_mouse_scroll_func callback) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        window_data->mouse_wheel_func = callback;
    }
}

//-------------------------------------
void
mfb_set_user_data(struct mfb_window *window, void *user_data) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        window_data->user_data = user_data;
    }
}

//-------------------------------------
void *
mfb_get_user_data(struct mfb_window *window) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        return window_data->user_data;
    }

    return 0x0;
}

// [Deprecated]
//-------------------------------------
void
mfb_get_monitor_dpi(struct mfb_window *window, float *dpi_x, float *dpi_y) {
    mfb_get_monitor_scale(window, dpi_x, dpi_y);
}

//-------------------------------------
void
mfb_close(struct mfb_window *window) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        window_data->close = true;
    }
}

//-------------------------------------
void
keyboard_default(struct mfb_window *window, mfb_key key, mfb_key_mod mod, bool isPressed) {
    kUnused(mod);
    kUnused(isPressed);
    if (key == KB_KEY_ESCAPE) {
        SWindowData *window_data = (SWindowData *) window;
        if (!window_data->close_func || window_data->close_func((struct mfb_window*)window_data)) {
            window_data->close = true;
        }
    }
}

//-------------------------------------
bool
mfb_set_viewport_best_fit(struct mfb_window *window, unsigned old_width, unsigned old_height) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;

        unsigned new_width  = window_data->window_width;
        unsigned new_height = window_data->window_height;

        float scale_x = new_width  / (float) old_width;
        float scale_y = new_height / (float) old_height;
        if(scale_x >= scale_y)
            scale_x = scale_y;
        else
            scale_y = scale_x;

        unsigned finalWidth  = (old_width  * scale_x) + 0.5f;
        unsigned finalHeight = (old_height * scale_y) + 0.5f;

        unsigned offset_x = (new_width  - finalWidth)  >> 1;
        unsigned offset_y = (new_height - finalHeight) >> 1;

        mfb_get_monitor_scale(window, &scale_x, &scale_y);
        return mfb_set_viewport(window, offset_x / scale_x, offset_y / scale_y, finalWidth / scale_x, finalHeight / scale_y);
    }

    return false;
}

//-------------------------------------
bool
mfb_is_window_active(struct mfb_window *window) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        return window_data->is_active;
    }
    return false;
}

//-------------------------------------
unsigned
mfb_get_window_width(struct mfb_window *window) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        return window_data->window_width;
    }
    return 0;
}

//-------------------------------------
unsigned
mfb_get_window_height(struct mfb_window *window) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        return window_data->window_height;
    }
    return 0;
}

//-------------------------------------
int
mfb_get_mouse_x(struct mfb_window *window) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        return window_data->mouse_pos_x;
    }
    return 0;
}

//-------------------------------------
int
mfb_get_mouse_y(struct mfb_window *window) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        return window_data->mouse_pos_y;
    }
    return 0;
}

//-------------------------------------
float
mfb_get_mouse_scroll_x(struct mfb_window *window) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        return window_data->mouse_wheel_x;
    }
    return 0;
}

//-------------------------------------
float
mfb_get_mouse_scroll_y(struct mfb_window *window) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        return window_data->mouse_wheel_y;
    }
    return 0;
}

//-------------------------------------
const uint8_t *
mfb_get_mouse_button_buffer(struct mfb_window *window) {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        return window_data->mouse_button_status;
    }
    return 0;
}

//-------------------------------------
const uint8_t *
mfb_get_key_buffer(struct mfb_window *window)  {
    if(window != 0x0) {
        SWindowData *window_data = (SWindowData *) window;
        return window_data->key_status;
    }
    return 0;
}
