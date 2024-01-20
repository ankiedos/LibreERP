#ifndef KIENT_LIBREERP_MODULE_HPP
#define KIENT_LIBREERP_MODULE_HPP

#include<map>
#include<vector>
#include<string>

namespace kient::lerp
{
// TODO: Widget API
// Example:
// std::unique_ptr<LERP_widget> wdg = LERP_widget_new();

// Widget layout (p = padding)
//  p-5 -4 -3 -2 -1  0  1  2  3  4  5  p
//  ___________________________________
// / ICON             PREDEFBUTTONS####\
// +------------------------------------+  p
// |              TOPMOST               |  3
// |                                    |  2
// |                                    |  1
// | LEFTMOST     CENTER      RIGHTMOST |  0
// |                                    | -1
// |                                    | -2
// |              DOWNMOST              | -3
// +------------------------------------+  p

// LERP_widget_add_label(wdg, &text_tmpl, LERP_WDG_TOP, LERP_WDG_TOPMOST, LERP_WDG_CENTER);
// LERP_widget_add_2d_graph(wdg, &characteristics, LERP_WDG_GR_LINE, LERP_WDG_CENTER, LERP_WDG_CENTER);
// LERP_2d_graph_bind_data(wdg->graphs_2d[0], &data);
// LERP_widget_add_icon(wdg, "path/to/icon.ico");
// LERP_widget_add_image(wdg, "path/to/image.png", LERP_WDG_RIGHTMOST, LERP_WDG_CENTER, LERP_WDG_IMG_SCALE_APPROPRIATELY);
// std::vector<std::string> text_impl(auto data)
// {
//     std::string msg = "Here's some data for " + data;
//     return msg;
// }
// std::shared_ptr<LERP_2d_graph_characteristics> characteristics()
// {
//     std::shared_ptr<LERP_2d_graph_characteristics> gchars = new LERP_2d_graph_characteristics;
//     gchars->name = "Production in PLN by Time";
//     gchars->axis_x.descr = "Time";
//     gchars->axis_x.step = 50;
//     gchars->axis_x.unit = "mth";
//     gchars->axis_x.rotate_degs = 0;
//     gchars->axis_x.allow_negatives = TRUE;
//     gchars->axis_y.descr = "Production";
//     gchars->axis_y.step = 100;
//     gchars->axis_y.unit = "PLN";

//     rotation degrees:
//               0
//           -90   90
//              180

//     gchars->axis_y.rotate_degs = 90;
//     gchars->axis_y.allow_negatives = TRUE;
//     gchars->display_grid = TRUE;
//     return gchars;
// }
// std::shared_ptr<LERP_2d_graph_data> data()
// {
//     std::shared_ptr<LERP_2d_graph_data> gdata = new LERP_2d_graph_data;
//     gdata->series_x = new series2d;
//     gdata->series_x->name = "Product 1";
//     gdata->series_x->values.push_back(calloc(10, sizeof(point2d)));
//     gdata->colours.push_back(colour_rgba(255, 0, 0, 1));
//     return gdata;
// }

struct module_exports
{
    // What tables does this module operate on
    std::vector<std::string> tables;
    // What are the widgets users can use with this module
    std::vector<std::string> widgets;
    // What (auto)forms does this module exposes
    std::vector<std::string> forms, autoforms;
    std::vector<std::string> roles, role_descriptions;
    std::vector<std::string> addresses;
    // For themes and pagebuilders, what stylesheets they add (stored by file name)
    std::vector<std::string> stylesheets;
    // For themes and pagebuilders, what HTML templates they add
    std::vector<std::string> html_templates;
    // For themes and pagebuilders, what JS scripts they add
    std::vector<std::string> js_scripts;
    std::vector<std::string> external_auth_services;
    std::vector<std::string> taxes;
    std::vector<std::string> email_templates;
    std::vector<std::string> icons, images, recordings, videos;
    std::string localisation_language;
    std::string script_language;
};
struct modul
{
    std::string name;
    std::string base_url;
    std::string src;
    std::string proc_load, proc_unload,
          proc_serve,
          proc_open_widget, proc_close_widget,
          proc_move_widget, proc_scale_widget, proc_reset_widget;
    /* Can include the following:
    * erp (Generic - can include integrations with marketing services or external e-commerce platforms)
    * reports (New widgets)
    * theme
    * pagebuilder
    * roles
    * addresses
    * forms
    * extauth (External Authorisation)
    * taxes
    * e-mails (E-mail templates)
    * icons
    * localisation
    * metaplugin (A new language for plugins)
    */
    std::vector<std::string> tags;
    std::vector<module_exports> exports;
};
namespace modules
{
    std::map<std::string, std::vector<modul>> mods;
    std::size_t by_url(const std::string& URL);
}
}
#endif