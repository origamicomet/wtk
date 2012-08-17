#include <wtk/wtk_app.h>
#include <wtk/wtk_window.h>

void* WTK_API wtk_alloc_callback( size_t num_bytes ) { return malloc(num_bytes); }
void* WTK_API wtk_realloc_callback( void* ptr, size_t num_bytes ) { return realloc(ptr, num_bytes); }
void WTK_API wtk_free_callback( void* ptr ) { free(ptr); }

static const struct wtk_allocator allocator = {
    &wtk_alloc_callback, &wtk_realloc_callback, &wtk_free_callback
};

static int WTK_API window_on_close( wtk_control* window, wtk_event event, void* event_data )
{
    wtk_quit();
    return FALSE;
}

int main( int argc, char** argv )
{
    wtk_window* window;
    if( !wtk_init(&allocator) ) return EXIT_FAILURE;

    window = wtk_window_create(0, 0, 800, 600, NULL);
    wtk_control_set_property((wtk_control*)window, WTK_CONTROL_PROP(Title), (wtk_property)"The Windowing Toolkit");
    wtk_control_set_callback((wtk_control*)window, WTK_EVENT(OnClose), &window_on_close);

    return wtk_run_app();
}