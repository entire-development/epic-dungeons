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
    void playSound(const std::string& sound_path) {
        soundBuffer = std::make_unique<sf::SoundBuffer>();
        sound = std::make_unique<sf::Sound>();

        if (soundBuffer->loadFromFile(sound_path)) {
            sound->setBuffer(*soundBuffer);
            sound->play();
        }
    }
private:
    SoundManager() = default;
    
    std::unique_ptr<sf::SoundBuffer> soundBuffer;
    std::unique_ptr<sf::Sound> sound;
};
}