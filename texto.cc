/** @file texto.cc
 * @brief Funcions del Text
 */

#include "texto.hh"

using namespace std;
using namespace pro2;

const int _ = -1;
const int r = 0x0000000; 

const int sprite_width = 4;  
const int sprite_height = 6; 

const vector<vector<vector<int>>> num_sprite_normal_ = {
    //0
    {
        {_, r, r, _},
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r},
        {_, r, r, _}
    },
    // 1
    {
        {_, _, r, _},
        {_, r, r, _},
        {r, _, r, _},
        {_, _, r, _},
        {_, _, r, _},
        {r, r, r, r}
    },
    //2
    {
        {_, r, r, _},
        {r, _, _, r},
        {_, _, _, r},
        {_, _, r, _},
        {_, r, _, _},
        {r, r, r, r}
    },
    // 3
    {
        {r, r, r, _},
        {_, _, _, r},
        {_, r, r, _},
        {_, _, _, r},
        {r, _, _, r},
        {_, r, r, _}
    },
    // 4
    {
        {_, _, r, _},
        {_, r, r, _},
        {r, _, r, _},
        {r, r, r, r},
        {_, _, r, _},
        {_, _, r, _}
    },
    //5
    {
        {r, r, r, r},
        {r, _, _, _},
        {r, r, r, _},
        {_, _, _, r},
        {r, _, _, r},
        {_, r, r, _}
    },
    // 6
    {
        {_, r, r, _},
        {r, _, _, _},
        {r, r, r, _},
        {r, _, _, r},
        {r, _, _, r},
        {_, r, r, _}
    },
    //7
    {
        {r, r, r, r},
        {_, _, _, r},
        {_, _, r, _},
        {_, r, _, _},
        {_, r, _, _},
        {_, r, _, _}
    },
    //8
    {
        {_, r, r, _},
        {r, _, _, r},
        {_, r, r, _},
        {r, _, _, r},
        {r, _, _, r},
        {_, r, r, _}
    },
    //9
    {
        {_, r, r, _},
        {r, _, _, r},
        {r, _, _, r},
        {_, r, r, r},
        {_, _, _, r},
        {_, r, r, _}
    }
};

const vector<vector<vector<int>>> letter_sprite_normal_ = {
    // a
    {
        {_, r, r, _},
        {r, _, _, r},
        {r, _, _, r},
        {r, r, r, r},
        {r, _, _, r},
        {r, _, _, r}
    },
    // b
    {
        {r, r, r, _},
        {r, _, _, r},
        {r, r, r, _},
        {r, _, _, r},
        {r, _, _, r},
        {r, r, r, _}
    },
    // c
    {
        {_, r, r, r},
        {r, _, _, _},
        {r, _, _, _},
        {r, _, _, _},
        {r, _, _, _},
        {_, r, r, r}
    },
    // d
    {
        {r, r, r, _},
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r},
        {r, r, r, _}
    },
    // e
    {
        {r, r, r, r},
        {r, _, _, _},
        {r, r, r, _},
        {r, _, _, _},
        {r, _, _, _},
        {r, r, r, r}
    },
    // f
    {
        {r, r, r, r},
        {r, _, _, _},
        {r, r, r, _},
        {r, _, _, _},
        {r, _, _, _},
        {r, _, _, _}
    },
    // g
    {
        {_, r, r, r},
        {r, _, _, _},
        {r, _, _, _},
        {r, _, r, r},
        {r, _, _, r},
        {_, r, r, r}
    },
    // h
    {
        {r, _, _, r},
        {r, _, _, r},
        {r, r, r, r},
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r}
    },
    // i
    {
        {r, r, r, r},
        {_, _, r, _},
        {_, _, r, _},
        {_, _, r, _},
        {_, _, r, _},
        {r, r, r, r}
    },
    // j
    {
        {_, _, _, r},
        {_, _, _, r},
        {_, _, _, r},
        {r, _, _, r},
        {r, _, _, r},
        {_, r, r, _}
    },
    // k
    {
        {r, _, _, r},
        {r, _, r, _},
        {r, r, _, _},
        {r, r, _, _},
        {r, _, r, _},
        {r, _, _, r}
    },
    // l
    {
        {r, _, _, _},
        {r, _, _, _},
        {r, _, _, _},
        {r, _, _, _},
        {r, _, _, _},
        {r, r, r, r}
    },
    // m
    {
        {r, _, _, r},
        {r, r, r, r},
        {r, _, r, r},
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r}
    },
    // n
    {
        {r, _, _, r},
        {r, r, _, r},
        {r, _, r, r},
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r}
    },
    // o
    {
        {_, r, r, _},
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r},
        {_, r, r, _}
    },
    // p
    {
        {r, r, r, _},
        {r, _, _, r},
        {r, r, r, _},
        {r, _, _, _},
        {r, _, _, _},
        {r, _, _, _}
    },
    // q
    {
        {_, r, r, _},
        {r, _, _, r},
        {r, _, _, r},
        {r, _, r, r},
        {r, _, _, r},
        {_, r, r, r}
    },
    // r
    {
        {r, r, r, _},
        {r, _, _, r},
        {r, r, r, _},
        {r, _, r, _},
        {r, _, _, r},
        {r, _, _, r}
    },
    // s
    {
        {_, r, r, r},
        {r, _, _, _},
        {_, r, r, _},
        {_, _, _, r},
        {r, _, _, r},
        {_, r, r, _}
    },
    // t
    {
        {r, r, r, r},
        {_, _, r, _},
        {_, _, r, _},
        {_, _, r, _},
        {_, _, r, _},
        {_, _, r, _}
    },
    // u
    {
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r},
        {_, r, r, _}
    },
    // v
    {
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r},
        {_, r, r, _},
        {_, _, r, _}
    },
    // w
    {
        {r, _, _, r},
        {r, _, _, r},
        {r, _, _, r},
        {r, _, r, r},
        {r, r, r, r},
        {r, _, _, r}
    },
    // x
    {
        {r, _, _, r},
        {r, _, _, r},
        {_, r, r, _},
        {_, r, r, _},
        {r, _, _, r},
        {r, _, _, r}
    },
    // y
    {
        {r, _, _, r},
        {r, _, _, r},
        {_, r, r, _},
        {_, _, r, _},
        {_, _, r, _},
        {_, r, _, _}
    },
    // z
    {
        {r, r, r, r},
        {_, _, _, r},
        {_, _, r, _},
        {_, r, _, _},
        {r, _, _, _},
        {r, r, r, r}
    }
};

void paint_digit(Window& window, Pt pos_, int digit){
    const Pt top_left = {pos_.x - sprite_width/2 , pos_.y - sprite_height/2 + 1};
    paint_sprite(window, top_left, num_sprite_normal_[digit], false);
}

void paint_letter(Window& window, Pt pos_, char letter) {
    const Pt top_left = {pos_.x - sprite_width/2 , pos_.y - sprite_height/2 + 1};
    paint_sprite(window, top_left, letter_sprite_normal_[letter - 'A'], false);
}

void paint_number(pro2::Window& window, pro2::Pt pos, int  number){

    vector<int> digits;

    if (number == 0) digits.push_back(0);

    while(number > 0){
        digits.push_back(number % 10);
        number /= 10;
    }

    //distancia del width del sprite + 2, un offset
    int offset = static_cast<int>(sprite_width + 2);
    for(int i = 0; i < digits.size(); i++){
            paint_digit(window, {pos.x + i * offset, pos.y}, digits[digits.size() - 1 - i]);
    }
}

void paint_text(Window& window, Pt pos, const string& text) {

    int offset = static_cast<int>(sprite_width + 2);  
    for (int i = 0; i < text.size(); ++i) {
        paint_letter(window, {pos.x + i * offset, pos.y}, text[i]);
    }
}
