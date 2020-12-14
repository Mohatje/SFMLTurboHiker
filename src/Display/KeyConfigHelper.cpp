#include "KeyConfigHelper.h"


namespace turbohikerSFML {
    KeyConfigHelper::KeyConfigHelper() {
        #define INSERT_INTO_KEYMAP(keyIdentifier) this->keyMap[#keyIdentifier] = sf::Keyboard::keyIdentifier

        {
            INSERT_INTO_KEYMAP(Unknown);
            INSERT_INTO_KEYMAP(Escape);
            INSERT_INTO_KEYMAP(F1);
            INSERT_INTO_KEYMAP(F2);
            INSERT_INTO_KEYMAP(F3);
            INSERT_INTO_KEYMAP(F4);
            INSERT_INTO_KEYMAP(F5);
            INSERT_INTO_KEYMAP(F6);
            INSERT_INTO_KEYMAP(F7);
            INSERT_INTO_KEYMAP(F8);
            INSERT_INTO_KEYMAP(F9);
            INSERT_INTO_KEYMAP(F10);
            INSERT_INTO_KEYMAP(F11);
            INSERT_INTO_KEYMAP(F12);
            INSERT_INTO_KEYMAP(F13);
            INSERT_INTO_KEYMAP(F14);
            INSERT_INTO_KEYMAP(F15);
            INSERT_INTO_KEYMAP(Tilde);
            INSERT_INTO_KEYMAP(Num1);
            INSERT_INTO_KEYMAP(Num2);
            INSERT_INTO_KEYMAP(Num3);
            INSERT_INTO_KEYMAP(Num4);
            INSERT_INTO_KEYMAP(Num5);
            INSERT_INTO_KEYMAP(Num6);
            INSERT_INTO_KEYMAP(Num7);
            INSERT_INTO_KEYMAP(Num8);
            INSERT_INTO_KEYMAP(Num9);
            INSERT_INTO_KEYMAP(Num0);
            INSERT_INTO_KEYMAP(Dash);
            INSERT_INTO_KEYMAP(Equal);
            INSERT_INTO_KEYMAP(A);
            INSERT_INTO_KEYMAP(B);
            INSERT_INTO_KEYMAP(C);
            INSERT_INTO_KEYMAP(D);
            INSERT_INTO_KEYMAP(E);
            INSERT_INTO_KEYMAP(F);
            INSERT_INTO_KEYMAP(G);
            INSERT_INTO_KEYMAP(H);
            INSERT_INTO_KEYMAP(I);
            INSERT_INTO_KEYMAP(J);
            INSERT_INTO_KEYMAP(K);
            INSERT_INTO_KEYMAP(L);
            INSERT_INTO_KEYMAP(M);
            INSERT_INTO_KEYMAP(N);
            INSERT_INTO_KEYMAP(O);
            INSERT_INTO_KEYMAP(P);
            INSERT_INTO_KEYMAP(Q);
            INSERT_INTO_KEYMAP(R);
            INSERT_INTO_KEYMAP(S);
            INSERT_INTO_KEYMAP(T);
            INSERT_INTO_KEYMAP(U);
            INSERT_INTO_KEYMAP(V);
            INSERT_INTO_KEYMAP(W);
            INSERT_INTO_KEYMAP(X);
            INSERT_INTO_KEYMAP(Y);
            INSERT_INTO_KEYMAP(Z);
            INSERT_INTO_KEYMAP(LControl);
            INSERT_INTO_KEYMAP(LShift);
            INSERT_INTO_KEYMAP(LAlt);
            INSERT_INTO_KEYMAP(LSystem);
            INSERT_INTO_KEYMAP(RControl);
            INSERT_INTO_KEYMAP(RShift);
            INSERT_INTO_KEYMAP(RAlt);
            INSERT_INTO_KEYMAP(RSystem);
            INSERT_INTO_KEYMAP(Menu);
            INSERT_INTO_KEYMAP(LBracket);
            INSERT_INTO_KEYMAP(RBracket);
            INSERT_INTO_KEYMAP(SemiColon);
            INSERT_INTO_KEYMAP(Comma);
            INSERT_INTO_KEYMAP(Period);
            INSERT_INTO_KEYMAP(Quote);
            INSERT_INTO_KEYMAP(Slash);
            INSERT_INTO_KEYMAP(BackSlash);
            INSERT_INTO_KEYMAP(Space);
            INSERT_INTO_KEYMAP(Return);
            INSERT_INTO_KEYMAP(BackSpace);
            INSERT_INTO_KEYMAP(Tab);
            INSERT_INTO_KEYMAP(PageUp);
            INSERT_INTO_KEYMAP(PageDown);
            INSERT_INTO_KEYMAP(End);
            INSERT_INTO_KEYMAP(Home);
            INSERT_INTO_KEYMAP(Insert);
            INSERT_INTO_KEYMAP(Delete);
            INSERT_INTO_KEYMAP(Add);
            INSERT_INTO_KEYMAP(Subtract);
            INSERT_INTO_KEYMAP(Multiply);
            INSERT_INTO_KEYMAP(Divide);
            INSERT_INTO_KEYMAP(Left);
            INSERT_INTO_KEYMAP(Right);
            INSERT_INTO_KEYMAP(Up);
            INSERT_INTO_KEYMAP(Down);
            INSERT_INTO_KEYMAP(Numpad0);
            INSERT_INTO_KEYMAP(Numpad1);
            INSERT_INTO_KEYMAP(Numpad2);
            INSERT_INTO_KEYMAP(Numpad3);
            INSERT_INTO_KEYMAP(Numpad4);
            INSERT_INTO_KEYMAP(Numpad5);
            INSERT_INTO_KEYMAP(Numpad6);
            INSERT_INTO_KEYMAP(Numpad7);
            INSERT_INTO_KEYMAP(Numpad8);
            INSERT_INTO_KEYMAP(Numpad9);
            INSERT_INTO_KEYMAP(Pause);
        }
    }

    sf::Keyboard::Key KeyConfigHelper::keyboardFromString(const std::string &keyIndentifier) {

        return getInstance().keyMap.at(keyIndentifier);
    }

    KeyConfigHelper &KeyConfigHelper::getInstance() {
        static KeyConfigHelper helperInstance;
        return helperInstance;
    }
}