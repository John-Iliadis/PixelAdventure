//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_SPRITE_SHEET_HPP
#define PLATFORMER_SPRITE_SHEET_HPP

#include <vector>
#include <cstdint>
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>


class SpriteSheet
{
public:
    class Frame
    {
    public:
        Frame() = default;
        Frame(int left, int top, int width, int height, const std::string& tag = "");
        Frame(const sf::IntRect& spritesheet_rect, const std::string& tag = "");

        void set_spritesheet_rect(const sf::IntRect& rect);
        void set_frame_tag(const std::string& tag);

        const sf::IntRect& get_spritesheet_rect() const;
        const std::string& get_frame_tag() const;

    private:
        sf::IntRect m_spritesheet_sub_rect;
        std::string m_frame_tag;
    };

    SpriteSheet() = default;
    SpriteSheet(int sprite_width, int sprite_height, uint32_t frame_count);

    void add_frame(const Frame& frame);
    void add_frame(const sf::IntRect& spritesheet_rect, const std::string& tag = "");

    void set_spritesheet_rect(size_t index, const sf::IntRect& rect);
    void set_frame_tag(size_t index, const std::string& tag);

    void clear_frames();

    const Frame& get_frame(size_t index) const;
    const sf::IntRect& get_frame_rect(size_t index) const;
    const std::string& get_frame_tag(size_t index) const;
    size_t frame_count() const;

private:
    std::vector<Frame> m_frames;
};


#endif //PLATFORMER_SPRITE_SHEET_HPP
