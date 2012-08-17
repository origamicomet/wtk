#include <wtk/wtk_app.h>
#include <wtk/wtk_font.h>
#include <wtk/wtk_window.h>
#include <wtk/wtk_label.h>
#include <wtk/wtk_button.h>

void* WTK_API wtk_alloc_callback( size_t num_bytes ) { return malloc(num_bytes); }
void* WTK_API wtk_realloc_callback( void* ptr, size_t num_bytes ) { return realloc(ptr, num_bytes); }
void WTK_API wtk_free_callback( void* ptr ) { free(ptr); }

static wtk_font*   font;
static wtk_window* window;
static wtk_label*  label;
static wtk_button* button;

static const struct wtk_allocator allocator = {
    &wtk_alloc_callback, &wtk_realloc_callback, &wtk_free_callback
};

static int WTK_API window_on_close( wtk_window* control, wtk_event event )
{
    wtk_quit();
    return FALSE;
}

static int WTK_API button_on_clicked( wtk_button* button, wtk_event event )
{
    wtk_control_set_property((wtk_control*)label, WTK_CONTROL_PROP(Text), "Hello, libwtk!");
    return TRUE;
}

int main( int argc, char** argv )
{
    if( !wtk_init(&allocator) ) return EXIT_FAILURE;

    font = wtk_font_create("Arial", 14, WTK_FONT_STYLE_DEFAULT);

    window = wtk_window_create(0, 0, 800, 600, NULL);
    wtk_control_set_property((wtk_control*)window, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_property((wtk_control*)window, WTK_CONTROL_PROP(Title), "The Windowing Toolkit");
    wtk_control_set_callback((wtk_control*)window, WTK_EVENT(OnClose), (wtk_event_callback)&window_on_close);

    label = wtk_label_create(16 + 1, 16, 75, 25, (wtk_control*)window);
    wtk_control_set_property((wtk_control*)label, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_property((wtk_control*)label, WTK_CONTROL_PROP(Text), "Hello, World!");

    button = wtk_button_create(16, 16 + 25, 75, 20, (wtk_control*)window);
    wtk_control_set_property((wtk_control*)button, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_property((wtk_control*)button, WTK_CONTROL_PROP(Text), "Change Text");
    wtk_control_set_callback((wtk_control*)button, WTK_EVENT(OnClicked), (wtk_event_callback)&button_on_clicked);

    return wtk_run_app();
}