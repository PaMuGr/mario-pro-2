#include "game.hh"
using namespace pro2;

Game::Game(int width, int height)
    : mario_({width / 2, 150}, Keys::Space, Keys::Left, Keys::Right),
      crosses_{
        Cross({-100, 235}),
        Cross({325, 134},{-1,0},30),
      },
      platforms_{
          Platform(-100, -85, 250, 261),
          Platform(0, 200, 250, 261),
          Platform(100, 300, 200, 211),
          Platform(250, 400, 150, 161),
      },
      finished_(false) {
    for (int i = 1; i < 20; i++) {
        int cy = randomizer(-3,3);
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150+cy*10, 161+cy*10));
        
        //afegim les crosses
        crosses_.push_back(Cross({
            (randomizer(380,100) + i * 200 + 400 + i * 200) / 2,  //x
            135 - randomizer(200,0)/4 + cy*10                //y
        }, {(i%2)*-1+1,(i%2)*-1}, 15));
    }
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
    if (window.was_key_pressed('P')) {
        paused_ = !paused_;
        return;
    }
}

void Game::update_objects(pro2::Window& window) {
    mario_.update(window, platforms_);

    pro2::Rect marHit = mario_.hitbox();
    auto it = crosses_.begin();
    while(it!=crosses_.end()) {
        (*it).update(window);
        if(!(*it).is_touched()){
            if (interseccionen(marHit, (*it).hitbox(cross_height_y_))) {
                (*it).touch();
                it = crosses_.erase(it);
                mario_.add_points();
            }
            it++;
        }
    }
}

void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos();
    const Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 4;
    const int right = cam.x + window.width() / 4;
    const int top = cam.y - window.height() / 4;
    const int bottom = cam.y + window.height() / 4;

    int dx = 0, dy = 0;
    if (pos.x > right) {
        dx = pos.x - right;
    } else if (pos.x < left) {
        dx = pos.x - left;
    }
    if (pos.y < top) {
        dy = pos.y - top;
    } else if (pos.y > bottom) {
        dy = pos.y - bottom;
    }
    
    window.move_camera({dx, dy});
}

void Game::update(pro2::Window& window) {
    
    process_keys(window);
    if(!paused_){
        update_objects(window);
        update_camera(window);
    } 
}

void Game::paint(pro2::Window& window) {
    if(!paused_){
        window.clear(sky_blue);
        pro2::Rect windowRect = window.camera_rect();

        for (const Platform& p : platforms_) {
            if(interseccionen(p.get_rect(), windowRect)){
                p.paint(window);
            }
        }

        for (const Cross& cross : crosses_) {
            if(interseccionen(cross.hitbox(), windowRect)){
                cross.paint(window, 1, cross.pos().x, cross.pos().y + cross_height_y_); 
            }        
        }

        //pinta el nombre total de punts
        paint_number(window, {window.camera_center().x - 230, window.camera_center().y - 150}, mario_.check_points());
        //pinta el text POINTS
        paint_text(window, {window.camera_center().x - 220, window.camera_center().y - 150}, "POINTS");
        mario_.paint(window);
    } else {
        window.clear(0x898989);
        //pinta el text PAUSED
        paint_text(window, {window.camera_center().x-20, window.camera_center().y}, "PAUSED");
    }
    
    //pintar recuadre
        int left = window.topleft().x;
        int right = window.topleft().x + window.width();
        int top = window.topleft().y;
        int bottom = window.topleft().y + window.height();
        pro2::Rect rectg({left, top, right, bottom});
        paint_empty_rect(window, rectg, black, 4);
}