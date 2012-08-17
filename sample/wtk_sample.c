#include <wtk/wtk_app.h>
#include <wtk/wtk_window.h>
#include <wtk/wtk_button.h>

void* WTK_API wtk_alloc_callback( size_t num_bytes ) { return malloc(num_bytes); }
void* WTK_API wtk_realloc_callback( void* ptr, size_t num_bytes ) { return realloc(ptr, num_bytes); }
void WTK_API wtk_free_callback( void* ptr ) { free(ptr); }

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
    return TRUE;
}

int main( int argc, char** argv )
{
    wtk_window* window;
    wtk_button* button;

    if( !wtk_init(&allocator) ) return EXIT_FAILURE;

    window = wtk_window_create(0, 0, 800, 600, NULL);
    wtk_control_set_property((wtk_control*)window, WTK_CONTROL_PROP(Title), "The Windowing Toolkit");
    wtk_control_set_callback((wtk_control*)window, WTK_EVENT(OnClose), (wtk_event_callback)&window_on_close);

    button = wtk_button_create(16, 16, 100, 30, (wtk_control*)window);
    wtk_control_set_property((wtk_control*)button, WTK_CONTROL_PROP(Text), "Hello, World!");
    wtk_control_set_callback((wtk_control*)button, WTK_EVENT(OnClicked), (wtk_event_callback)&button_on_clicked);

    return wtk_run_app();
}