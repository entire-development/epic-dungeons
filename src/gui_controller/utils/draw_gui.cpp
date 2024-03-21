#include "engine/engine.h"
#include "gui_controller/utils.h"
#include "static_data/game_config.h"

namespace gui {
namespace utils {
void drawGUI(const std::shared_ptr<graphics::Renderer> &renderer, const std::shared_ptr<engine::Engine> &engine) {
    // Draw the map
    // const float upper = cfg::WINDOW_HEIGHT * 5 / 6;
    // const float menu_height = cfg::WINDOW_HEIGHT - upper;
    // const int v_cells = 2;
    // const int h_cells = 8;
    // const float cell_size = menu_height / v_cells;
    // for (int i = 0; i < v_cells; i++) {
    //     for (int j = 0; j < h_cells; j++) {
    //         renderer->drawRec(
    //             {j * cell_size, upper + i * cell_size, cell_size, cell_size, {0, 0, 0, 0}, -2, {255, 255, 255, 255}});
    //     }
    // }
}

}   // namespace utils
}   // namespace gui
