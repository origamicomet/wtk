#include <wtk/wtk_app.h>
#include <wtk/wtk_align.h>
#include <wtk/wtk_font.h>
#include <wtk/wtk_image.h>
#include <wtk/wtk_mouse.h>
#include <wtk/wtk_window.h>
#include <wtk/wtk_label.h>
#include <wtk/wtk_button.h>

void* WTK_API wtk_alloc_callback( size_t num_bytes ) { return malloc(num_bytes); }
void* WTK_API wtk_realloc_callback( void* ptr, size_t num_bytes ) { return realloc(ptr, num_bytes); }
void WTK_API wtk_free_callback( void* ptr ) { free(ptr); }

static wtk_font* font;
static wtk_icon* app_icon;

static const struct wtk_allocator allocator = {
    &wtk_alloc_callback, &wtk_realloc_callback, &wtk_free_callback
};

static int WTK_API window_on_close( wtk_window* control, wtk_event event )
{
    wtk_quit();
    return FALSE;
}

int main( int argc, char** argv )
{
    wtk_window* window;
    wtk_label*  label;
    wtk_button* button;

    if( !wtk_init(&allocator) ) return EXIT_FAILURE;

    font = wtk_font_create("Arial", 14, WTK_FONT_STYLE_DEFAULT);
    app_icon = wtk_icon_create_from_file("color-swatch.ico", WTK_ICON_SIZE_DEFAULT, WTK_ICON_SIZE_DEFAULT);

    window = wtk_window_create(0, 0, 800, 600, NULL);
    wtk_control_set_property((wtk_control*)window, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_property((wtk_control*)window, WTK_CONTROL_PROP(Icons), app_icon, app_icon);
    wtk_control_set_property((wtk_control*)window, WTK_CONTROL_PROP(Title), "The Windowing Toolkit");
    wtk_control_set_callback((wtk_control*)window, WTK_EVENT(OnClose), (wtk_event_callback)&window_on_close);

    label = wtk_label_create(16, 16, 100, 40, (wtk_control*)window);
    wtk_control_set_property((wtk_control*)label, WTK_CONTROL_PROP(Font), wtk_font_create("Arial", 16, WTK_FONT_STYLE_BOLD));
    wtk_control_set_property((wtk_control*)label, WTK_CONTROL_PROP(Text), "Hello, World!");
    wtk_control_set_property((wtk_control*)label, WTK_CONTROL_PROP(TextAlign), WTK_ALIGN(Left));

    button = wtk_button_create(16, 16 + 25, 40, 40, (wtk_control*)window);
    wtk_control_set_property((wtk_control*)button, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_property((wtk_control*)button, WTK_CONTROL_PROP(Icon), app_icon);

    return wtk_run_app();
}