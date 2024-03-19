#pragma once
#include "color.h"
#include "sprite.h"
#include "static_data/game_config.h"
#include "vector2d/vector2d.h"
#include <chrono>
#include <iostream>
#include <memory>

namespace graphics {

class Animation {
public:
    Animation(const std::string &path);
    const uint32_t getFramesCount() const;
    SpritePtr getFrame() const;

    static const std::shared_ptr<graphics::Animation> load(const std::string &path) {
        return std::make_shared<graphics::Animation>(path);
    }

private:
    std::string m_path;
    std::vector<std::shared_ptr<graphics::Sprite>> m_frames;
    uint32_t m_frames_count = 0;
};

typedef std::shared_ptr<graphics::Animation> AnimationPtr;

}   // namespace graphics
