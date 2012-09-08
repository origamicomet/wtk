#include <wtk/wtk.h>

void* WTK_API wtk_alloc_callback( size_t num_bytes ) { return malloc(num_bytes); }
void* WTK_API wtk_realloc_callback( void* ptr, size_t num_bytes ) { return realloc(ptr, num_bytes); }
void WTK_API wtk_free_callback( void* ptr ) { free(ptr); }

static wtk_font* font;
static wtk_icon* app_icon;
static wtk_label* mirror_label;
static wtk_checkbox* mirror_checkbox;
static wtk_textbox* mirror_textbox;

static const struct wtk_allocator allocator = {
    &wtk_alloc_callback, &wtk_realloc_callback, &wtk_free_callback
};

static int WTK_API exit_on_clicked( wtk_menu_item* menu_item, wtk_event event )
{
    wtk_quit();
    return TRUE;
}

static int WTK_API window_on_close( wtk_window* window, wtk_event event )
{
    wtk_quit();
    return TRUE;
}

static int WTK_API checkbox_on_value_changed( wtk_checkbox* checkbox, wtk_event event )
{
    wtk_checkbox_state state;
    wtk_control_get_property((wtk_control*)mirror_checkbox, WTK_CONTROL_PROP(Value), &state);

    if( state == WTK_CHECKBOX_STATE(Checked) ) {
        const char* text = NULL;
        wtk_control_get_property((wtk_control*)mirror_textbox, WTK_CONTROL_PROP(Text), &text);
        wtk_control_set_property((wtk_control*)mirror_label, WTK_CONTROL_PROP(Text), text);
    }

    return TRUE;
}

static int WTK_API textbox_on_value_changed( wtk_textbox* textbox, wtk_event event )
{
    wtk_checkbox_state state;
    wtk_control_get_property((wtk_control*)mirror_checkbox, WTK_CONTROL_PROP(Value), &state);

    if( state == WTK_CHECKBOX_STATE(Checked) ) {
        const char* text = NULL;
        wtk_control_get_property((wtk_control*)textbox, WTK_CONTROL_PROP(Text), &text);
        wtk_control_set_property((wtk_control*)mirror_label, WTK_CONTROL_PROP(Text), text);
    }

    return TRUE;
}

static int WTK_API listbox_on_create( wtk_listbox* listbox, wtk_event event )
{
    wtk_listbox_item to_replace;

    wtk_listbox_insert(listbox, "Hello, World!", NULL);
    to_replace = wtk_listbox_insert(listbox, "...", NULL);
    wtk_listbox_insert(listbox, "wtk_listbox_insert", NULL);
    wtk_control_set_child_property((wtk_control*)listbox, WTK_CONTROL_PROP(Text), (wtk_child)to_replace, "wtk_control_set_child_property");

    return TRUE;
}

static int WTK_API combobox_on_create( wtk_combobox* combobox, wtk_event event )
{
    wtk_combobox_item to_replace;

    wtk_combobox_insert(combobox, "Option 1", NULL);
    to_replace = wtk_combobox_insert(combobox, "...", NULL);
    wtk_combobox_insert(combobox, "Option 2", NULL);
    wtk_control_set_child_property((wtk_control*)combobox, WTK_CONTROL_PROP(Text), (wtk_child)to_replace, "Option 1b");
	wtk_control_set_property((wtk_control*)combobox, WTK_CONTROL_PROP(Value), to_replace);

    return TRUE;
}

static int WTK_API combobox_on_selection_changed( wtk_combobox* combobox, wtk_event event, unsigned int count )
{
	wtk_combobox_item selected;
    wtk_control_get_property((wtk_control*)combobox, WTK_CONTROL_PROP(Value), &selected);

    return TRUE;
}

static wtk_image_list* listview_image_list()
{
    wtk_icon* icon;
    wtk_image_list* img_list = wtk_image_list_create(16, 16, 3);
    wtk_image_list_id id;

    icon = wtk_icon_create_from_file("compile.ico", 16, 16);
    id = wtk_image_list_add_icon(img_list, icon);
    wtk_icon_destroy(icon);

    icon = wtk_icon_create_from_file("compile-warning.ico", 16, 16);
    id = wtk_image_list_add_icon(img_list, icon);
    wtk_icon_destroy(icon);

    icon = wtk_icon_create_from_file("compile-error.ico", 16, 16);
    id = wtk_image_list_add_icon(img_list, icon);
    wtk_icon_destroy(icon);

    return img_list;
}

static int WTK_API listview_on_create( wtk_listview* listview, wtk_event event )
{
    wtk_listview_column icon_column;
    wtk_listview_column text_column;
    wtk_listview_row row;

    icon_column = wtk_listview_insert_column(listview, "", 24);
    text_column = wtk_listview_insert_column(listview, "Text", 148);

    wtk_control_set_property((wtk_control*)listview, WTK_CONTROL_PROP(ImageList), listview_image_list());

    row = wtk_listview_insert_row(listview);
    wtk_control_set_child_property((wtk_control*)listview, WTK_CONTROL_PROP(Icon), (wtk_child)row, icon_column, 1);
    wtk_control_set_child_property((wtk_control*)listview, WTK_CONTROL_PROP(Text), (wtk_child)row, text_column, "compile.ico");

    row = wtk_listview_insert_row(listview);
    wtk_control_set_child_property((wtk_control*)listview, WTK_CONTROL_PROP(Icon), (wtk_child)row, icon_column, 2);
    wtk_control_set_child_property((wtk_control*)listview, WTK_CONTROL_PROP(Text), (wtk_child)row, text_column, "compile-warning.ico");

    row = wtk_listview_insert_row(listview);
    wtk_control_set_child_property((wtk_control*)listview, WTK_CONTROL_PROP(Icon), (wtk_child)row, icon_column, 3);
    wtk_control_set_child_property((wtk_control*)listview, WTK_CONTROL_PROP(Text), (wtk_child)row, text_column, "compile-error.ico");

    return TRUE;
}

int main( int argc, char** argv )
{
    wtk_menu*      menu;
    wtk_menu_item* menu_item;
    wtk_window*    window;
    wtk_label*     label;
    wtk_frame*     frame;
    wtk_button*    button;
    wtk_checkbox*  checkbox;
    wtk_textbox*   textbox;
    wtk_listbox*   listbox;
    wtk_listview*  listview;
    wtk_combobox*  combobox;

    if( !wtk_init(&allocator) ) return EXIT_FAILURE;

    font = wtk_font_create("MS Sans Serif", 12, WTK_FONT_STYLE_DEFAULT);
    app_icon = wtk_icon_create_from_file("color-swatch.ico", WTK_ICON_SIZE_DEFAULT, WTK_ICON_SIZE_DEFAULT);

    menu = wtk_menu_create();
    menu_item = wtk_menu_append((wtk_control*)menu, "File");
    menu_item = wtk_menu_append((wtk_control*)menu_item, "Exit");
    wtk_control_set_callback((wtk_control*)menu_item, WTK_EVENT(OnClicked), (wtk_event_callback)&exit_on_clicked);

    window = wtk_window_create(WTK_WINDOW_CENTER, WTK_WINDOW_CENTER, 344, 375, NULL);
    wtk_control_set_property((wtk_control*)window, WTK_CONTROL_PROP(Menu), menu);
    wtk_control_set_property((wtk_control*)window, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_property((wtk_control*)window, WTK_CONTROL_PROP(Icons), app_icon, app_icon);
    wtk_control_set_property((wtk_control*)window, WTK_CONTROL_PROP(Title), "The Windowing Toolkit");
    wtk_control_set_property((wtk_control*)window, WTK_CONTROL_PROP(Resizable), FALSE);
    wtk_control_set_property((wtk_control*)window, WTK_CONTROL_PROP(Hidden), FALSE);
    wtk_control_set_callback((wtk_control*)window, WTK_EVENT(OnClose), (wtk_event_callback)&window_on_close);

    label = wtk_label_create(16, 16, 100, 18, (wtk_control*)window);
    wtk_control_set_property((wtk_control*)label, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_property((wtk_control*)label, WTK_CONTROL_PROP(Text), "Hello, World!");
    wtk_control_set_property((wtk_control*)label, WTK_CONTROL_PROP(TextAlign), WTK_ALIGN(Left));
    mirror_label = label;

    frame = wtk_frame_create(200, 16, 128, 128, (wtk_control*)window);
    wtk_control_set_property((wtk_control*)frame, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_property((wtk_control*)frame, WTK_CONTROL_PROP(Text), "wtk_frame");

    button = wtk_button_create(15, 44, 40, 40, (wtk_control*)window);
    wtk_control_set_property((wtk_control*)button, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_property((wtk_control*)button, WTK_CONTROL_PROP(Icon), app_icon);

    button = wtk_button_create(61, 44, 130, 40, (wtk_control*)window);
    wtk_control_set_property((wtk_control*)button, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_property((wtk_control*)button, WTK_CONTROL_PROP(Text), "wtk_button");
    // wtk_control_set_property((wtk_control*)button, WTK_CONTROL_PROP(AutoFill), TRUE);
    // wtk_control_set_property((wtk_control*)button, WTK_CONTROL_PROP(Margins), 16, 16, 16, 16);

    checkbox = wtk_checkbox_create(124, 16, 50, 18, (wtk_control*)window);
    wtk_control_set_property((wtk_control*)checkbox, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_property((wtk_control*)checkbox, WTK_CONTROL_PROP(Text), "Mirror?");
    wtk_control_set_property((wtk_control*)checkbox, WTK_CONTROL_PROP(Value), WTK_CHECKBOX_STATE(Checked));
    wtk_control_set_callback((wtk_control*)checkbox, WTK_EVENT(OnValueChanged), (wtk_event_callback)&checkbox_on_value_changed);
    mirror_checkbox = checkbox;

    textbox = wtk_textbox_create(16, 102, 174, 18, FALSE, (wtk_control*)window);
    wtk_control_set_property((wtk_control*)textbox, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_property((wtk_control*)textbox, WTK_CONTROL_PROP(Text), "Hello, World!");
    wtk_control_set_callback((wtk_control*)textbox, WTK_EVENT(OnValueChanged), (wtk_event_callback)&textbox_on_value_changed);
    mirror_textbox = textbox;

    listbox = wtk_listbox_create(200, 156, 128, 100, (wtk_control*)window);
    wtk_control_set_property((wtk_control*)listbox, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_callback((wtk_control*)listbox, WTK_EVENT(OnCreate), (wtk_event_callback)&listbox_on_create);

    listview = wtk_listview_create(16, 140, 174, 200, (wtk_control*)window);
    wtk_control_set_property((wtk_control*)listview, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_callback((wtk_control*)listview, WTK_EVENT(OnCreate), (wtk_event_callback)&listview_on_create);

    combobox = wtk_combobox_create(200, 256, 128, 40, (wtk_control*)window);
    wtk_control_set_property((wtk_control*)combobox, WTK_CONTROL_PROP(Font), font);
    wtk_control_set_callback((wtk_control*)combobox, WTK_EVENT(OnCreate), (wtk_event_callback)&combobox_on_create);
    wtk_control_set_callback((wtk_control*)combobox, WTK_EVENT(OnSelectionChanged), (wtk_event_callback)&combobox_on_selection_changed);

    return wtk_run_app();
}
