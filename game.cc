/** @file game.cc
 * @brief Funcions del Game
 */

#include "game.hh"
using namespace pro2;

Game::Game(int width, int height)
    : mario_({width / 2, 150}, Keys::Space, Keys::Left, Keys::Right),
      sandglass_({200, 114}), 
      demon_({0, 0}),
      crosses_{
        Cross({-100, 235}),
        Cross({325, 134},{-1,0},30),
      },
      platforms_{
          Platform(-100, -70, 250, 261),
          Platform(0, 200, 250, 261),
          Platform(100, 300, 200, 211),
          Platform(250, 400, 150, 161),
      },
      paused_(false), 
      finished_(false),
      reset_(false),
      cross_height_y_(0) {
    for (int i = 1; i < 5000; i++) {
        int cy = randomizer(-3,3);
        platforms_.push_back(Platform(
            250 + i * 200, 400 + i * 200, //x
            150+cy*10, 161+cy*10));     //y
        
        //Afegim les crosses
        crosses_.push_back(Cross({
            (randomizer(380,100) + i * 200 + 400 + i * 200) / 2,  //x
            100 + cy*10                //y
        }, {((i%2)*-1+1),((i%2)*-1)}, 15));
    }

    //Afegim a la constructora el .add de les plataformes
    for (Platform& p : platforms_) {
        finder_platforms_.add(&p);
    }

    //Afegim a la constructora el .add de les crosses
    for (Cross& c : crosses_) {
        finder_crosses_.add(&c);
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
    if (reset_ && window.is_key_down('R')) {
        *this = Game(480, 320);
        reset_ = false;
        return;
    }
}

void Game::update_objects(pro2::Window& window) {

    mario_.update(window, platforms_);
    pro2::Rect marioRect = mario_.get_rect();

    //Comprovació si mario esta caigut de les plataformes --> TORNA A INICIAR JOC
    int floor = window.topleft().y + window.height() + 200;
    if(mario_.pos().y > floor) {
        reset_ = true;
        return;
    }

    auto visibles = finder_crosses_.query(window.camera_rect());
    sandglass_.update(window);

    //Mirem si estem tocant al sandglass
    if (!sandglass_.is_in_cooldown() && interseccionen(marioRect, sandglass_.get_rect())) {
        sandglass_.activate(960, 240); //5 segons d'efecte i 15 segons per apareixer
    }

    //Si el sanglass no en cooldown --> tot es mou
    if(!sandglass_.is_effect_active()){
        demon_.update(window);

        //Comprovació de si demon hauria de disparar
        if(demon_.should_shoot()){
            demon_.reset_cooldown();
            pro2::Pt fireball_pos = {demon_.pos().x + 8, demon_.pos().y + 16};
            pro2::Pt fireball_speed = {0, 5}; //Cap abaix
            fireballs_.push_back(Fireball(fireball_pos, fireball_speed)); //Afegim element nou amb propietats escollides
        }
        
        //Mirem si hi ha intersecció
        for (auto& fireball : fireballs_) {
            if (fireball.is_active() && interseccionen(marioRect, fireball.get_rect())) {
                fireball.deactivate();
                reset_ = true;
                return;
            }
        }

        //Iterem per les fireballs per veure si hem de borrar o no
        for (auto it = fireballs_.begin(); it != fireballs_.end(); ) {
            it->update();
            if (!it->is_active()) {
                it = fireballs_.erase(it);  
            } else {
                ++it;
            }
        }

        for(const Cross* c : visibles){
            //const_cast transforma el punter a un no const
            Cross* cc = const_cast<Cross*>(c);
            cc->update(window);
            finder_crosses_.update(c);
            if (interseccionen(marioRect, cc->get_rect(cross_height_y_))) {
                finder_crosses_.remove(c);
                mario_.add_points();
            }
        }

    } else{
        //Fem tot menys deixar que es moguin
        //Mirem si hi ha intersecció
        for (auto& fireball : fireballs_) {
            if (fireball.is_active() && interseccionen(marioRect, fireball.get_rect())) {
                fireball.deactivate();
                reset_ = true;
                return;
            }
        }

        for(const Cross* c : visibles){
            Cross* cc = const_cast<Cross*>(c);
            finder_crosses_.update(c);
            if (interseccionen(marioRect, cc->get_rect(cross_height_y_))) {
                finder_crosses_.remove(c);
                mario_.add_points();
            }
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
    if(!paused_ and !reset_){
        update_objects(window);
        update_camera(window);
    } 
}

void Game::paint(pro2::Window& window) {
    if(!paused_ and !reset_){
        if(!sandglass_.is_effect_active()){
            window.clear(sky_blue);
            sandglass_.paint(window);
        } else{
            window.clear(0xC2B280);
        }
        pro2::Rect windowRect = window.camera_rect();

        //Agafem totes les platforms visibles i per cada una en elles les pintem
        std::set<const Platform*> visibles = finder_platforms_.query(windowRect);
        for (const Platform* p : visibles) {
            p->paint(window);
        }

        auto visible_crosses = finder_crosses_.query(windowRect);
        for (const Cross* cross : visible_crosses) {
            cross->paint(window, 1 ,cross->pos().x, cross->pos().y + cross_height_y_);
        }
        
        demon_.paint(window);
    
        for (const auto& fireball : fireballs_) {
            fireball.paint(window);
        }

        //pinta el nombre total de punts
        paint_number(window, {window.camera_center().x - 230, window.camera_center().y - 150}, mario_.check_points());
        //pinta el text POINTS
        paint_text(window, {window.camera_center().x - 215, window.camera_center().y - 150}, "POINTS");
        
        mario_.paint(window);
    } else if(paused_){
        //pantalla en gris amb el text PAUSED
        window.clear(0x898989);
        //pinta el text PAUSED al mitg de la pantalla
        int pos_x = window.topleft().x + window.width()/2 - 20;
        int pos_y = window.topleft().y + window.height()/2 - 10;
        paint_text(window, {pos_x, pos_y}, "PAUSED");
    } else if(reset_){
         //pantalla en gris amb el text GAME OVER
        window.clear(0x7B1818);
        //pinta el text GAME OVER al mitg de la pantalla
        //a sota fiquem PRESS R TO RESTART
        int pos_x = window.topleft().x + window.width()/2 - 20;
        int pos_y = window.topleft().y + window.height()/2 - 10;
        paint_text(window, {pos_x, pos_y}, "GAME OVER", 0xFF5733);
        paint_text(window, {pos_x-25, pos_y+20}, "PRESS R TO RESTART", 0xFF5733);
        paint_text(window, {pos_x, pos_y+40}, "SCORE: ", 0xFF5733);
        paint_number(window, {pos_x+40, pos_y+40}, mario_.check_points());
    }
    
    //pintar recuadre
        int left = window.topleft().x;
        int right = window.topleft().x + window.width();
        int top = window.topleft().y;
        int bottom = window.topleft().y + window.height();
        pro2::Rect rectg({left, top, right, bottom});
        paint_empty_rect(window, rectg, black, 4);
}
