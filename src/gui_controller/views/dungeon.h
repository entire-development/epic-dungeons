#pragma once
#include "dungeon/dungeon.h"
#include "gui_controller/view.h"
#include "renderer/sfml_renderer/sfml_renderer.h"

namespace gui {

class Dungeon : public View {
public:
    virtual void bindDungeon(const std::shared_ptr<dungeon::Dungeon> &dungeon) {
        m_dungeon = dungeon;
    }

private:
    std::weak_ptr<dungeon::Dungeon> m_dungeon;
};

}   // namespace gui