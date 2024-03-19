#pragma once
#include <SFML/Audio.hpp>
#include <string>

namespace sound {
class SoundManager {
public:
    static SoundManager &getInstance() {
        static SoundManager instance;
        return instance;
    }
    void playSound(const std::string& sound_path, const float volume) {
        sound_buffer = std::make_unique<sf::SoundBuffer>();
        sound = std::make_unique<sf::Sound>();

        if (sound_buffer->loadFromFile(sound_path)) {
            sound->setBuffer(*sound_buffer);
            sound->setVolume(volume);
            sound->play();
        }
    }
private:
    SoundManager() = default;
    
    std::unique_ptr<sf::SoundBuffer> sound_buffer;
    std::unique_ptr<sf::Sound> sound;
};

static void playSound(const std::string& sound_path, float volume = 100.f) {
    sound::SoundManager::getInstance().playSound(sound_path, volume);
}
}
