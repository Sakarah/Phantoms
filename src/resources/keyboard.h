#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SFML/System/String.hpp>
#include <SFML/Window/Keyboard.hpp>

sf::String keyToChar(sf::Keyboard::Key key)
{
    switch(key)
    {
        case sf::Keyboard::A: return L"A";
        case sf::Keyboard::B: return L"B";
        case sf::Keyboard::C: return L"C";
        case sf::Keyboard::D: return L"D";
        case sf::Keyboard::E: return L"E";
        case sf::Keyboard::F: return L"F";
        case sf::Keyboard::G: return L"G";
        case sf::Keyboard::H: return L"H";
        case sf::Keyboard::I: return L"I";
        case sf::Keyboard::J: return L"J";
        case sf::Keyboard::K: return L"K";
        case sf::Keyboard::L: return L"L";
        case sf::Keyboard::M: return L"M";
        case sf::Keyboard::N: return L"N";
        case sf::Keyboard::O: return L"O";
        case sf::Keyboard::P: return L"P";
        case sf::Keyboard::Q: return L"Q";
        case sf::Keyboard::R: return L"R";
        case sf::Keyboard::S: return L"S";
        case sf::Keyboard::T: return L"T";
        case sf::Keyboard::U: return L"U";
        case sf::Keyboard::V: return L"V";
        case sf::Keyboard::W: return L"W";
        case sf::Keyboard::X: return L"X";
        case sf::Keyboard::Y: return L"Y";
        case sf::Keyboard::Z: return L"Z";
        case sf::Keyboard::Num0: return L"0";
        case sf::Keyboard::Num1: return L"1";
        case sf::Keyboard::Num2: return L"2";
        case sf::Keyboard::Num3: return L"3";
        case sf::Keyboard::Num4: return L"4";
        case sf::Keyboard::Num5: return L"5";
        case sf::Keyboard::Num6: return L"6";
        case sf::Keyboard::Num7: return L"7";
        case sf::Keyboard::Num8: return L"8";
        case sf::Keyboard::Num9: return L"9";
        case sf::Keyboard::Escape: return L"Esc";
        case sf::Keyboard::LControl: return L"LCtrl";
        case sf::Keyboard::LShift: return L"L⇧";
        case sf::Keyboard::LAlt: return L"LAlt";
        case sf::Keyboard::LSystem: return L"L⌘";
        case sf::Keyboard::RControl: return L"RCtrl";
        case sf::Keyboard::RShift: return L"R⇧";
        case sf::Keyboard::RAlt: return L"RAlt";
        case sf::Keyboard::RSystem: return L"R⌘";
        case sf::Keyboard::Menu: return L"Menu";
        case sf::Keyboard::LBracket: return L"[";
        case sf::Keyboard::RBracket: return L"]";
        case sf::Keyboard::SemiColon: return L";";
        case sf::Keyboard::Comma: return L",";
        case sf::Keyboard::Period: return L".";
        case sf::Keyboard::Quote: return L"\"";
        case sf::Keyboard::Slash: return L"/";
        case sf::Keyboard::BackSlash: return L"\\";
        case sf::Keyboard::Tilde: return L"~";
        case sf::Keyboard::Equal: return L"=";
        case sf::Keyboard::Dash: return L"_";
        case sf::Keyboard::Space: return L"␣";
        case sf::Keyboard::Return: return L"↵";
        case sf::Keyboard::BackSpace: return L"⌫";
        case sf::Keyboard::Tab: return L"↹";
        case sf::Keyboard::PageUp: return L"⇞";
        case sf::Keyboard::PageDown: return L"⇟";
        case sf::Keyboard::End: return L"↘";
        case sf::Keyboard::Home: return L"↖";
        case sf::Keyboard::Insert: return L"Ins";
        case sf::Keyboard::Delete: return L"Del";
        case sf::Keyboard::Add: return L"+";
        case sf::Keyboard::Subtract: return L"-";
        case sf::Keyboard::Multiply: return L"*";
        case sf::Keyboard::Divide: return L"/";
        case sf::Keyboard::Left: return L"←";
        case sf::Keyboard::Right: return L"→";
        case sf::Keyboard::Up: return L"↑";
        case sf::Keyboard::Down: return L"↓";
        case sf::Keyboard::Numpad0: return L"0";
        case sf::Keyboard::Numpad1: return L"1";
        case sf::Keyboard::Numpad2: return L"2";
        case sf::Keyboard::Numpad3: return L"3";
        case sf::Keyboard::Numpad4: return L"4";
        case sf::Keyboard::Numpad5: return L"5";
        case sf::Keyboard::Numpad6: return L"6";
        case sf::Keyboard::Numpad7: return L"7";
        case sf::Keyboard::Numpad8: return L"8";
        case sf::Keyboard::Numpad9: return L"9";
        case sf::Keyboard::F1: return L"F1";
        case sf::Keyboard::F2: return L"F2";
        case sf::Keyboard::F3: return L"F3";
        case sf::Keyboard::F4: return L"F4";
        case sf::Keyboard::F5: return L"F5";
        case sf::Keyboard::F6: return L"F6";
        case sf::Keyboard::F7: return L"F7";
        case sf::Keyboard::F8: return L"F8";
        case sf::Keyboard::F9: return L"F9";
        case sf::Keyboard::F10: return L"F10";
        case sf::Keyboard::F11: return L"F11";
        case sf::Keyboard::F12: return L"F12";
        case sf::Keyboard::F13: return L"F13";
        case sf::Keyboard::F14: return L"F14";
        case sf::Keyboard::F15: return L"F15";
        case sf::Keyboard::Pause: return L"Pause";
        default: return L"⚠";
    }
}

#endif // KEYBOARD_H
