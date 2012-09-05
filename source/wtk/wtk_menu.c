// =============================================================================
// This file is part of the Windowing Toolkit.
// Copyright (C) 2012 Michael Williams <devbug@bitbyte.ca>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// =============================================================================

#include <wtk/wtk_menu.h>

#include "_wtk_windows.h"
#include "_wtk_controls.h"

#include <wtk/wtk_mm.h>
#include <wtk/wtk_font.h>

int WTK_API wtk_menu_init()
{
    return TRUE;
}

int WTK_API wtk_menu_item_init()
{
    return TRUE;
}

struct wtk_menu* WTK_API wtk_menu_create()
{
    struct wtk_menu* menu = NULL;
    const MENUINFO menu_info = { sizeof(MENUINFO), MIM_STYLE, MNS_NOTIFYBYPOS, 0, };

    HMENU hMenu = CreateMenu();
    if( !hMenu ) return NULL;


    menu = wtk_alloc(sizeof(struct wtk_menu));
    memset((void*)menu, 0, sizeof(struct wtk_menu));
    menu->control.type = WTK_CONTROL_TYPE(Menu);
    menu->control.hWnd = NULL;
    menu->control.font = wtk_font_default();
    menu->window = NULL;
    menu->hMenu = hMenu;

    // Send WM_MENUCOMMAND instead of WM_COMMAND:
    SetMenuInfo(hMenu, &menu_info);
    return menu;
}

void WTK_API wtk_menu_destroy( struct wtk_menu* menu )
{
    unsigned int i = 0;
    const unsigned int num_menu_items = GetMenuItemCount(menu->hMenu);
    MENUITEMINFO menu_item_info = { sizeof(MENUITEMINFO), MIIM_ID | MIIM_SUBMENU, 0, };

    while( GetMenuItemInfo(menu->hMenu, i++, TRUE, &menu_item_info) ) {
        wtk_control_destroy((struct wtk_control*)menu_item_info.wID);
    }

    DestroyMenu(menu->hMenu);
    wtk_free(menu);
}

static HMENU wtk_get_hmenu( struct wtk_control* control )
{
    WTK_ASSERT((
        control->type == WTK_CONTROL_TYPE(Menu) ||
        control->type == WTK_CONTROL_TYPE(MenuItem)
    ));

    switch( control->type ) {
        case WTK_CONTROL_TYPE(Menu): {
            return ((struct wtk_menu*)control)->hMenu;
        } break;

        case WTK_CONTROL_TYPE(MenuItem): {
            return ((struct wtk_menu_item*)control)->hMenu;
        } break;
    }

    return NULL;
}

struct wtk_menu_item* WTK_API wtk_menu_append( struct wtk_control* control, const char* text )
{
    HMENU hAppendMenu;
    struct wtk_menu_item* menu_item;

    WTK_ASSERT((
        control->type == WTK_CONTROL_TYPE(Menu) ||
        control->type == WTK_CONTROL_TYPE(MenuItem)
    ));

    switch( control->type ) {
        case WTK_CONTROL_TYPE(Menu): {
            struct wtk_menu* parent = (struct wtk_menu*)control;
            hAppendMenu = parent->hMenu;
        } break;

        case WTK_CONTROL_TYPE(MenuItem): {
            struct wtk_menu_item* parent = (struct wtk_menu_item*)control;

            if( !parent->hMenu ) {
                HMENU hMenu = wtk_get_hmenu(parent->parent);
                MENUITEMINFO menu_item_info = { sizeof(MENUITEMINFO), MIIM_SUBMENU, 0, };
                menu_item_info.hSubMenu = parent->hMenu = CreatePopupMenu();
                SetMenuItemInfo(hMenu, (UINT)parent, FALSE, &menu_item_info);
            }

            hAppendMenu = parent->hMenu;
        } break;
    }

    menu_item = wtk_alloc(sizeof(struct wtk_menu_item));
    memset((void*)menu_item, 0, sizeof(struct wtk_menu_item));
    menu_item->control.type = WTK_CONTROL_TYPE(MenuItem);
    menu_item->control.hWnd = NULL;
    menu_item->control.font = wtk_font_default();
    menu_item->parent = control;
    menu_item->text = text;

    AppendMenu(hAppendMenu, MF_STRING, (UINT_PTR)menu_item, text);
    return menu_item;
}

void WTK_API wtk_menu_item_destroy( struct wtk_menu_item* menu_item )
{
    if( menu_item->hMenu ) {
        unsigned int i = 0;
        const unsigned int num_menu_items = GetMenuItemCount(menu_item->hMenu);
        MENUITEMINFO menu_item_info = { sizeof(MENUITEMINFO), MIIM_ID | MIIM_SUBMENU, 0, };

        while( GetMenuItemInfo(menu_item->hMenu, i++, TRUE, &menu_item_info) ) {
            wtk_control_destroy((struct wtk_control*)menu_item_info.wID);
        }

        DestroyMenu(menu_item->hMenu);
    }

    wtk_free(menu_item);
}