/** @file game.cc
 * @brief Funcions del Game
 */

#include "game.hh"
using namespace pro2;

/*CONSTRUCTOR GENERAL*/
Game::Game(int width, int height)
    : mario_({width / 2, 150}, Keys::Space, Keys::Left, Keys::Right, Keys::Down),
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
    
    for (int i = 1; i < 10000; i++) {
        int cy = randomizer(-3,3);
        int random_height = randomizer(-3, 3);
        int y_offset = random_height * 10;
        int base_x = 250 + i * 200;
        int x_range = 400 + i * 200;

        //Plataformes d'abaix
        platforms_.push_back(Platform(
            base_x, x_range,             // x 
            150 + y_offset, 161 + y_offset  // y 
        ));

        int platforms_offset_x = 0;
        int platforms_offset_y = 0;
        if(randomizer(1,0)==0){
            platforms_offset_x = 30;
            platforms_offset_y = 10;
        } else{
            platforms_offset_x = -30;
            platforms_offset_y = 0;
        }

        platforms_.push_back(Platform(
            base_x + platforms_offset_x, x_range + platforms_offset_x - 20,            // x 
            90 + y_offset - platforms_offset_y, 101 + y_offset - platforms_offset_y // y 
        ));

        if(randomizer(1,0)==0){ //si es 0 les fiquem abaix sino adalt -> randomitzat
            crosses_.push_back(Cross({
            (randomizer(380,100) + i * 200 + x_range) / 2,  //x
            120 + random_height*10                //y
            }, {1,0}, 20)); 
        } else{
            crosses_.push_back(Cross({
            (randomizer(380,100) + i * 200 + x_range) / 2,  //x
            50 + random_height*10                //y
            }, {((i%2)*-1+1),((i%2)*-1)}, 10)); 
        }
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

/*PROCESSADOR DE TECLES*/
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
    if (window.was_key_pressed('B') and ascended_.can_activate()) {
        ascended_.activate({mario_.pos().x, mario_.pos().y});
    }
}

/*UPDATE DE OBJECTES*/
bool Game::check_fallen_off_screen(const pro2::Window& window) {
    //Comprovació si mario esta caigut de les plataformes --> TORNA A INICIAR JOC
    int floor = window.topleft().y + window.height() + 200;
    if (mario_.pos().y > floor) {
        reset_ = true;
        return true;
    }
    return false;
}

void Game::handle_sandglass_interaction(const pro2::Rect& marioRect) {
    if (!sandglass_.is_in_cooldown() && interseccionen(marioRect, sandglass_.get_rect())) {
        mario_.collect_sandwatch();
        sandglass_.activate(960, 240);
    }
}

void Game::update_time_stoped_mode(pro2::Window& window, const pro2::Rect& marioRect) {
    update_fireball_collisions(marioRect, true);
    update_crosses(window, marioRect);
    update_fire_collisions(marioRect, true);

    if (mario_.check_points() % 5 == 0) {
        ascended_.add_blessing();
    }
}

void Game::update_normal_mode(pro2::Window& window, const pro2::Rect& marioRect) {
    demon_.update(window);
    try_shoot_fireball();

    update_fireballs();
    update_fireball_collisions(marioRect, false);

    update_crosses(window, marioRect);
    update_fires();
    update_fire_collisions(marioRect, false);

    check_blessing_points();
}

void Game::try_shoot_fireball() {
    if(demon_.should_shoot()){
        demon_.reset_cooldown();
        pro2::Pt fireball_pos = {demon_.pos().x + 8, demon_.pos().y + 16};
        pro2::Pt fireball_speed = {0, 5}; //Cap abaix
        fireballs_.push_back(Fireball(fireball_pos, fireball_speed)); //Afegim element nou amb propietats escollides
    }
}

void Game::update_fireballs() {
    for (auto it = fireballs_.begin(); it != fireballs_.end();) {
        (*it).update();

        if (!(*it).is_active() || check_fireball_hits_platform(*it)) {
            it = fireballs_.erase(it);
        } else {
            ++it;
        }
    }
}

bool Game::check_fireball_hits_platform(Fireball& fireball) {
    pro2::Rect fireballRect = fireball.get_rect();

    for (const Platform& platform : platforms_) {
        if (interseccionen(fireballRect, platform.get_rect())) {
            fireball.deactivate();

            //Creació de focs 
            if (randomizer(0, 4) < 6) {
                pro2::Rect fireballRect = fireball.get_rect();
                pro2::Rect platformRect = platform.get_rect();
                Pt fire_pos = {
                    (fireballRect.left + fireballRect.right) / 2 - 4,  
                    platformRect.top - 7  
                };
                fires_.push_back(Fire(fire_pos, 120));
            }

            break;
        }
    }

    return false;
}

void Game::update_crosses(pro2::Window& window, const pro2::Rect& marioRect) {
    auto visibles = finder_crosses_.query(window.camera_rect());
    for (const Cross* c : visibles) {
        Cross* cc = const_cast<Cross*>(c);
        cc->update(window);
        finder_crosses_.update(c);
        if (interseccionen(marioRect, cc->get_rect(cross_height_y_))) {
            finder_crosses_.remove(c);
            mario_.add_points();
        }
    }
}

void Game::update_fires() {
    for (auto it = fires_.begin(); it != fires_.end();) {
        (*it).update();
        if (!(*it).is_active()) {
            it = fires_.erase(it);
        } else {
            ++it;
        }
    }
}

void Game::update_fireball_collisions(const pro2::Rect& marioRect, bool timeStoped) {
    for (auto& fireball : fireballs_) {
        if (fireball.is_active()) {
            if (timeStoped && interseccionen(ascended_.get_rect(), fireball.get_rect())) {
                fireball.deactivate();
            } else if (interseccionen(marioRect, fireball.get_rect())) {
                fireball.deactivate();
                reset_ = true;
                return;
            }
        }
    }
}

void Game::update_fire_collisions(const pro2::Rect& marioRect, bool timeStoped) {
    for (auto& fire : fires_) {
        if (fire.is_active()) {
            if (timeStoped && interseccionen(ascended_.get_rect(), fire.get_rect())) {
                fire.deactivate_fires();
            } else if (interseccionen(marioRect, fire.get_rect())) {
                fire.deactivate_fires();
                reset_ = true;
                return;
            }
        }
    }
}

void Game::check_blessing_points() {
    int current_points = mario_.check_points();
    if (current_points >= 5 && current_points / 5 > last_blessed_points_ / 5) {
        ascended_.add_blessing();
        last_blessed_points_ = current_points;
    }
}

/*UPDATE DELS OBJECTES EN GENERAL*/
void Game::update_objects(pro2::Window& window) {
    mario_.update(window, platforms_);
    ascended_.update(mario_.pos());
    pro2::Rect marioRect = mario_.get_rect();

    if (check_fallen_off_screen(window)) return;

    sandglass_.update(window);
    handle_sandglass_interaction(marioRect);

    if (sandglass_.is_effect_active()) {
        update_time_stoped_mode(window, marioRect);
    } else {
        update_normal_mode(window, marioRect);
    }
}

/*UPDATE DE LA CAMERA*/
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

/*UPDATE GENERAL*/
void Game::update(pro2::Window& window) {
    process_keys(window);
    if(!paused_ and !reset_){
        update_objects(window);
        update_camera(window);
    } 
}

void Game::paint_platforms(pro2::Window& window){
    pro2::Rect windowRect = window.camera_rect();
    std::set<const Platform*> visibles = finder_platforms_.query(windowRect);
    for (const Platform* p : visibles) {
        p->paint(window);
    }
}

void Game::paint_crosses(pro2::Window& window){
    pro2::Rect windowRect = window.camera_rect();
    auto visible_crosses = finder_crosses_.query(windowRect);
    for (const Cross* cross : visible_crosses) {
        cross->paint(window, 1 ,cross->pos().x, cross->pos().y + cross_height_y_);
    }
}

void Game::paint_demon_objects(pro2::Window& window){
    demon_.paint(window);
    
    for (const auto& fireball : fireballs_) {
        fireball.paint(window);
    }

    for (auto it = fires_.begin(); it != fires_.end(); ++it) {
        (*it).paint(window);
    }
}

void Game::paint_blessings(pro2::Window& window){
    if (ascended_.is_active()) {
        ascended_.paint(window);
    }
    paint_text(window, {window.camera_center().x + 170, window.camera_center().y - 150}, "BLESSINGS:");
    paint_number(window, {window.camera_center().x + 230, window.camera_center().y - 150}, ascended_.size());
}

void Game::paint_points(pro2::Window& window){
    //pinta el nombre total de punts
    paint_number(window, {window.camera_center().x - 230, window.camera_center().y - 150}, mario_.check_points());
    //pinta el text POINTS
    paint_text(window, {window.camera_center().x - 215, window.camera_center().y - 150}, "POINTS");
}

void Game::paint_paused_screen(pro2::Window& window){
    //pantalla en gris amb el text PAUSED
    window.clear(0x898989);
    //pinta el text PAUSED al mitg de la pantalla
    int pos_x = window.topleft().x + window.width()/2 - 20;
    int pos_y = window.topleft().y + window.height()/2 - 10;
    paint_text(window, {pos_x, pos_y}, "PAUSED");
}

void Game::paint_gameover_screen(pro2::Window& window){
    //VERMELL
    window.clear(0x7B1818);
    //pinta el text GAME OVER al mitg de la pantalla
    //a sota fiquem PRESS R TO RESTART
    int pos_x = window.topleft().x + window.width()/2 - 20;
    int pos_y = window.topleft().y + window.height()/2 - 10;
    
    paint_text(window, {pos_x, pos_y}, "GAME OVER");
    paint_text(window, {pos_x-25, pos_y+20}, "PRESS R TO RESTART");
    paint_text(window, {pos_x, pos_y+40}, "SCORE: ");
    paint_number(window, {pos_x+40, pos_y+40}, mario_.check_points());
}

void Game::paint_game_frame(pro2::Window& window){
    //pintar recuadre
    int left = window.topleft().x;
    int right = window.topleft().x + window.width();
    int top = window.topleft().y;
    int bottom = window.topleft().y + window.height();
    pro2::Rect rectg({left, top, right, bottom});
    paint_empty_rect(window, rectg, black, 4);
}

/*PAINT GENERAL*/
void Game::paint(pro2::Window& window) {
    if(!paused_ and !reset_){
        if(!sandglass_.is_effect_active()){
            window.clear(sky_blue);
            sandglass_.paint(window);
        } else{
            window.clear(0xC2B280);
            paint_number(window, {window.camera_center().x, window.camera_center().y}, sandglass_.cooldown());
        }
        
        paint_platforms(window);
        paint_crosses(window);
        paint_demon_objects(window);
        paint_blessings(window);
        mario_.paint(window);
        paint_points(window);

    } else if(paused_) paint_paused_screen(window);
    else if(reset_) paint_gameover_screen(window);
    
    paint_game_frame(window);
}