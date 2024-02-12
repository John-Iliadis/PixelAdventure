//
// Created by Gianni on 9/01/2024.
//

#include "utils.hpp"


namespace utils
{
    float get_distance(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
    {
        return std::hypot(vec2.x - vec1.x, vec2.y - vec1.y);
    }

    void set_origin(sf::Sprite& sprite, Origin origin)
    {
        auto sprite_rect = sprite.getLocalBounds();

        switch (origin)
        {
            case Origin::TOP_LEFT:
                sprite.setOrigin(0, 0);
                break;

            case Origin::CENTER:
                sprite.setOrigin(static_cast<int>(sprite_rect.width / 2.f), static_cast<int>(sprite_rect.height / 2.f));
                break;

            case Origin::CENTER_BOTTOM:
                sprite.setOrigin(static_cast<int>(sprite_rect.width / 2.f), static_cast<int>(sprite_rect.height));
                break;

            case Origin::CENTER_TOP:
                sprite.setOrigin(static_cast<int>(sprite_rect.width / 2.f), 0);
                break;

            case Origin::CENTER_LEFT:
                sprite.setOrigin(0, static_cast<int>(sprite_rect.height / 2.f));
                break;

            case Origin::CENTER_RIGHT:
                sprite.setOrigin(static_cast<int>(sprite_rect.width), static_cast<int>(sprite_rect.height / 2.f));
                break;

            default:
                assert(false);
        }
    }

    void set_origin(sf::Text& text, Origin origin)
    {
        auto local_bounds = text.getLocalBounds();

        switch (origin)
        {
            case Origin::TOP_LEFT:
            {
                text.setOrigin(0, 0);
                break;
            }

            case Origin::CENTER:
            {
                sf::Vector2i text_origin {
                        static_cast<int>(local_bounds.left + local_bounds.width / 2.f),
                        static_cast<int>(local_bounds.top + local_bounds.height / 2.f)
                };

                text.setOrigin(text_origin.x, text_origin.y);
                break;
            }


            case Origin::CENTER_BOTTOM:
            {
                sf::Vector2i text_origin {
                        static_cast<int>(local_bounds.left + local_bounds.width / 2.f),
                        static_cast<int>(local_bounds.top + local_bounds.height)
                };

                text.setOrigin(text_origin.x, text_origin.y);
                break;
            }

            case Origin::CENTER_TOP:
            {
                sf::Vector2i text_origin {static_cast<int>(local_bounds.left + local_bounds.width / 2.f), 0};

                text.setOrigin(text_origin.x, text_origin.y);
                break;
            }

            case Origin::CENTER_LEFT:
            {
                sf::Vector2i text_origin {0,static_cast<int>(local_bounds.top + local_bounds.height / 2.f)};

                text.setOrigin(text_origin.x, text_origin.y);
                break;
            }

            case Origin::CENTER_RIGHT:
            {
                sf::Vector2i text_origin {
                        static_cast<int>(local_bounds.left + local_bounds.width),
                        static_cast<int>(local_bounds.top + local_bounds.height / 2.f)
                };

                text.setOrigin(text_origin.x, text_origin.y);
                break;
            }

            default:
                assert(false);
        }
    }

    float to_radians(float degrees)
    {
        return degrees * M_PI / 180;
    }

    float to_degrees(float radians)
    {
        return radians * 180 / M_PI;
    }

    int random(int min, int max)
    {
        static std::random_device m_random_device;
        static std::mt19937 m_engine(m_random_device());
        static std::uniform_int_distribution<int> m_int_distribution;

        if (min > max) std::swap(min, max);

        if (min != m_int_distribution.min() || max != m_int_distribution.max())
            m_int_distribution = std::uniform_int_distribution<int>(min, max);

        return m_int_distribution(m_engine);
    }

    std::string key_to_string(sf::Keyboard::Key key)
    {
        #define KEYTOSTRING_CASE(KEY) case sf::Keyboard::KEY: return #KEY;

        switch (key)
        {
            KEYTOSTRING_CASE(Unknown)
            KEYTOSTRING_CASE(A)
            KEYTOSTRING_CASE(B)
            KEYTOSTRING_CASE(C)
            KEYTOSTRING_CASE(D)
            KEYTOSTRING_CASE(E)
            KEYTOSTRING_CASE(F)
            KEYTOSTRING_CASE(G)
            KEYTOSTRING_CASE(H)
            KEYTOSTRING_CASE(I)
            KEYTOSTRING_CASE(J)
            KEYTOSTRING_CASE(K)
            KEYTOSTRING_CASE(L)
            KEYTOSTRING_CASE(M)
            KEYTOSTRING_CASE(N)
            KEYTOSTRING_CASE(O)
            KEYTOSTRING_CASE(P)
            KEYTOSTRING_CASE(Q)
            KEYTOSTRING_CASE(R)
            KEYTOSTRING_CASE(S)
            KEYTOSTRING_CASE(T)
            KEYTOSTRING_CASE(U)
            KEYTOSTRING_CASE(V)
            KEYTOSTRING_CASE(W)
            KEYTOSTRING_CASE(X)
            KEYTOSTRING_CASE(Y)
            KEYTOSTRING_CASE(Z)
            KEYTOSTRING_CASE(Num0)
            KEYTOSTRING_CASE(Num1)
            KEYTOSTRING_CASE(Num2)
            KEYTOSTRING_CASE(Num3)
            KEYTOSTRING_CASE(Num4)
            KEYTOSTRING_CASE(Num5)
            KEYTOSTRING_CASE(Num6)
            KEYTOSTRING_CASE(Num7)
            KEYTOSTRING_CASE(Num8)
            KEYTOSTRING_CASE(Num9)
            KEYTOSTRING_CASE(Escape)
            KEYTOSTRING_CASE(LControl)
            KEYTOSTRING_CASE(LShift)
            KEYTOSTRING_CASE(LAlt)
            KEYTOSTRING_CASE(LSystem)
            KEYTOSTRING_CASE(RControl)
            KEYTOSTRING_CASE(RShift)
            KEYTOSTRING_CASE(RAlt)
            KEYTOSTRING_CASE(RSystem)
            KEYTOSTRING_CASE(Menu)
            KEYTOSTRING_CASE(LBracket)
            KEYTOSTRING_CASE(RBracket)
            KEYTOSTRING_CASE(SemiColon)
            KEYTOSTRING_CASE(Comma)
            KEYTOSTRING_CASE(Period)
            KEYTOSTRING_CASE(Quote)
            KEYTOSTRING_CASE(Slash)
            KEYTOSTRING_CASE(BackSlash)
            KEYTOSTRING_CASE(Tilde)
            KEYTOSTRING_CASE(Equal)
            KEYTOSTRING_CASE(Dash)
            KEYTOSTRING_CASE(Space)
            KEYTOSTRING_CASE(Return)
            KEYTOSTRING_CASE(BackSpace)
            KEYTOSTRING_CASE(Tab)
            KEYTOSTRING_CASE(PageUp)
            KEYTOSTRING_CASE(PageDown)
            KEYTOSTRING_CASE(End)
            KEYTOSTRING_CASE(Home)
            KEYTOSTRING_CASE(Insert)
            KEYTOSTRING_CASE(Delete)
            KEYTOSTRING_CASE(Add)
            KEYTOSTRING_CASE(Subtract)
            KEYTOSTRING_CASE(Multiply)
            KEYTOSTRING_CASE(Divide)
            KEYTOSTRING_CASE(Left)
            KEYTOSTRING_CASE(Right)
            KEYTOSTRING_CASE(Up)
            KEYTOSTRING_CASE(Down)
            KEYTOSTRING_CASE(Numpad0)
            KEYTOSTRING_CASE(Numpad1)
            KEYTOSTRING_CASE(Numpad2)
            KEYTOSTRING_CASE(Numpad3)
            KEYTOSTRING_CASE(Numpad4)
            KEYTOSTRING_CASE(Numpad5)
            KEYTOSTRING_CASE(Numpad6)
            KEYTOSTRING_CASE(Numpad7)
            KEYTOSTRING_CASE(Numpad8)
            KEYTOSTRING_CASE(Numpad9)
            KEYTOSTRING_CASE(F1)
            KEYTOSTRING_CASE(F2)
            KEYTOSTRING_CASE(F3)
            KEYTOSTRING_CASE(F4)
            KEYTOSTRING_CASE(F5)
            KEYTOSTRING_CASE(F6)
            KEYTOSTRING_CASE(F7)
            KEYTOSTRING_CASE(F8)
            KEYTOSTRING_CASE(F9)
            KEYTOSTRING_CASE(F10)
            KEYTOSTRING_CASE(F11)
            KEYTOSTRING_CASE(F12)
            KEYTOSTRING_CASE(F13)
            KEYTOSTRING_CASE(F14)
            KEYTOSTRING_CASE(F15)
            KEYTOSTRING_CASE(Pause)
            case sf::Keyboard::KeyCount:
                assert(false);
            default:
                assert(false);
        }
    }

    sf::Keyboard::Key string_to_key(const std::string& str)
    {
        static const std::unordered_map<std::string, sf::Keyboard::Key> key_map {
                {"Unknown", sf::Keyboard::Unknown},
                {"A", sf::Keyboard::A},
                {"B", sf::Keyboard::B},
                {"C", sf::Keyboard::C},
                {"D", sf::Keyboard::D},
                {"E", sf::Keyboard::E},
                {"F", sf::Keyboard::F},
                {"G", sf::Keyboard::G},
                {"H", sf::Keyboard::H},
                {"I", sf::Keyboard::I},
                {"J", sf::Keyboard::J},
                {"K", sf::Keyboard::K},
                {"L", sf::Keyboard::L},
                {"M", sf::Keyboard::M},
                {"N", sf::Keyboard::N},
                {"O", sf::Keyboard::O},
                {"P", sf::Keyboard::P},
                {"Q", sf::Keyboard::Q},
                {"R", sf::Keyboard::R},
                {"S", sf::Keyboard::S},
                {"T", sf::Keyboard::T},
                {"U", sf::Keyboard::U},
                {"V", sf::Keyboard::V},
                {"W", sf::Keyboard::W},
                {"X", sf::Keyboard::X},
                {"Y", sf::Keyboard::Y},
                {"Z", sf::Keyboard::Z},
                {"Left", sf::Keyboard::Left},
                {"Right", sf::Keyboard::Right},
                {"Up", sf::Keyboard::Up},
                {"Down", sf::Keyboard::Down},
                {"Space", sf::Keyboard::Space},
                {"Enter", sf::Keyboard::Enter}
        };

        if (auto itr = key_map.find(str);
            itr != key_map.end())
        {
            return itr->second;
        }

        assert(false);
    }
}
