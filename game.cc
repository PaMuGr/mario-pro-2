/** @file game.cc
 * @brief Funcions del Game
 */

#include "game.hh"
using namespace pro2;

/*CONSTRUCTOR GENERAL*/
Game::Game(int width, int height)
    : mario_({width / 2, 150}, Keys::Space, Keys::Left, Keys::Right, Keys::Down),
      //MARIO I PLATAFORMES PER SER DIBUIXADES EN LA PANTALLA D'INICI
      still_mario_({width / 2, 150}, Keys::Space, Keys::Left, Keys::Right, Keys::Down),
      still_platform_({0, 480, 150, 480}),
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
      game_state_(0),
      cross_height_y_(0) {
    
    //1.000.000 ITEMS -> Una mica lent al restart i al iniciar (pero molt eficient) (normal)
    //50.000 ITEMS -> Millor per playtesting  (100 000 plataformes i 50 000 crosses)
    generate_level_objects(50000);

    //Afegim a la constructora el .add de les plataformes
    for (Platform& p : platforms_) {
        finder_platforms_.add(&p);
    }

    //Afegim a la constructora el .add de les crosses
    for (Cross& c : crosses_) {
        finder_crosses_.add(&c);
    }
}

/*GENERADOR DEL MAPA RANDOMITZAT*/
void Game::generate_level_objects(int count) {
    for (int i = 1; i < count; i++) {
        int cy = randomizer(-3, 3);
        int random_height = randomizer(-3, 3);
        int y_offset = random_height * 10;
        int base_x = 250 + i * 200;
        int x_range = 400 + i * 200;

        // Plataforma d'abaix
        platforms_.push_back(Platform(
            base_x, x_range,
            150 + y_offset, 161 + y_offset
        ));

        int platforms_offset_x = 0;
        int platforms_offset_y = 0;
        if (randomizer(1, 0) == 0) {
            platforms_offset_x = 30;
            platforms_offset_y = 10;
        } else {
            platforms_offset_x = -30;
            platforms_offset_y = 0;
        }

        // Plataforma de dalt
        platforms_.push_back(Platform(
            base_x + platforms_offset_x, x_range + platforms_offset_x - 20,
            90 + y_offset - platforms_offset_y, 101 + y_offset - platforms_offset_y
        ));

        // Creu aleatòria
        if (randomizer(1, 0) == 0) {
            crosses_.push_back(Cross({
                (randomizer(380, 100) + i * 200 + x_range) / 2,
                120 + random_height * 10
            }, {1, 0}, 20));
        } else {
            crosses_.push_back(Cross({
                (randomizer(380, 100) + i * 200 + x_range) / 2,
                50 + random_height * 10
            }, {((i % 2) * -1 + 1), ((i % 2) * -1)}, 10));
        }
    }
}

/*PROCESSADOR DE TECLES*/
void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        game_state_ = 0;
        game_state_ = 4;  // exit
        return;
    }
    if (game_state_ == 1 && window.was_key_pressed('P')) {
        game_state_ = 6;  // pause
        return;
    }
    if ((game_state_ == 2 || game_state_ == 3 || game_state_ == 5) && window.is_key_down('R')) {
        int prev_mode = game_mode_;
        *this = Game(480, 320);
        game_mode_ = prev_mode;
        apply_game_mode_settings();
        game_state_ = 0;
        return;
    }
    if (window.was_key_pressed('B') && ascended_.can_activate()) {
        ascended_.activate({mario_.pos().x, mario_.pos().y});
    }
    if (window.was_key_pressed(Keys::Return)) {
        game_state_ = 1;
        return;
    }
}

void Game::apply_game_mode_settings() {
    switch (game_mode_) {
        case 1:  //Easy
            has_time_limit_ = false;
            timer_ = 0;
            crosses_to_get_ = 10;
            break;
        case 2:  //Medium
            has_time_limit_ = false;
            timer_ = 0;
            crosses_to_get_ = 20;
            break;
        case 3:  //Hard
            has_time_limit_ = false;
            timer_ = 0;
            crosses_to_get_ = 40;
            break;
        case 4:  //Speedrun
            has_time_limit_ = true;
            timer_ = 2880; 
            crosses_to_get_ = 9999;
            break;
        case 5:  //Dodge
            has_time_limit_ = false;
            timer_ = 0; 
            crosses_to_get_ = 9999;
            is_dodging_mode_ = true;
            break;
        default:
            game_state_ = 4;
            break;
    }
}

/*UPDATE DE OBJECTES*/
bool Game::check_fallen_off_screen(const pro2::Window& window) {
    //Comprovació si mario esta caigut de les plataformes --> TORNA A INICIAR JOC
    int floor = window.topleft().y + window.height() + 200;
    if (mario_.pos().y > floor) {
        game_state_ = 5;  // gameover
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
    update_crosses(window, marioRect, true);
    if(demon_.check_fireball_collisions(marioRect,ascended_.get_rect())){
        game_state_ = 5;    // game over
    }
    
    int current_points = mario_.check_points();
    if (current_points >= 5 && current_points / 5 > last_blessed_points_ / 5) {
        ascended_.add_blessing();
        last_blessed_points_ = current_points;
    }
}

void Game::update_normal_mode(pro2::Window& window, const pro2::Rect& marioRect) {
    auto platforms_visibles = finder_platforms_.query(window.camera_rect());
    demon_.update(window,platforms_visibles);
    if(demon_.check_fireball_collisions(marioRect,ascended_.get_rect())){
        game_state_ = 5;    // game over
    }
    
    update_crosses(window, marioRect, false);
    
    check_blessing_points();
}

void Game::update_crosses(pro2::Window& window, const pro2::Rect& marioRect, bool timestoped) {
    auto visibles = finder_crosses_.query(window.camera_rect());
    for (const Cross* c : visibles) {
        Cross* cc = const_cast<Cross*>(c);
        
        if(!timestoped){
            cc->update(window);
            finder_crosses_.update(c);
        }
        
        if (interseccionen(marioRect, cc->get_rect(cross_height_y_))) {
            finder_crosses_.remove(c);
            mario_.add_points();
        }
    }
}



void Game::update_demon_state(pro2::Window& window){

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
    auto platforms_visibles = finder_platforms_.query(window.camera_rect());
    std::vector<Platform> visibles_vec;
    for (const Platform* p : platforms_visibles)
        visibles_vec.push_back(*p);  // Copia l'objecte

    mario_.update(window, visibles_vec);

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
    if (game_state_ == 1) {
        if (!sandglass_.is_effect_active()) {
            update_timer();
        }
        update_objects(window);
        update_camera(window);
        if (mario_.check_points() >= crosses_to_get_) {
            game_state_ = 2;  // won
        }
    }   
}

/*PAINTS DE CADA OBJECTE I PANTALLA DIFERENT*/
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
    //Si els punts del mario actuals son majors a la meitat --> demon canvia a "enraged/decayed"
    if(mario_.check_points() >= crosses_to_get_/2) demon_.decaying();
    demon_.paint(window);
    
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
    int center_x = window.topleft().x + window.width() / 2;
    int center_y = window.topleft().y + window.height() / 2;
    pro2::Pt centered = {center_x, center_y};
    
    center_text(window, centered, "GAME PAUSED",  -10);
    center_text(window, centered, "PRESS P TO CONTINUE", 10);
}

void Game::paint_gameover_screen(pro2::Window& window){
    //VERMELL
    window.clear(0x7B1818);
    //pinta el text GAME OVER al mitg de la pantalla
    //a sota fiquem PRESS R TO RESTART
    int center_x = window.topleft().x + window.width() / 2;
    int center_y = window.topleft().y + window.height() / 2;
    pro2::Pt centered = {center_x, center_y};
    
    center_text(window, centered, "GAME OVER",  -10);
    center_text(window, centered, "PRESS R TO RESTART", 10);
}

void Game::paint_winning_screen(pro2::Window& window){
    //VERMELL
    window.clear(0x454B1B);
    //pinta el text GAME OVER al mitg de la pantalla
    //a sota fiquem PRESS R TO RESTART
    int center_x = window.topleft().x + window.width() / 2;
    int center_y = window.topleft().y + window.height() / 2;
    pro2::Pt centered = {center_x, center_y};
    
    center_text(window, centered, "YOU WIN",  -20);
    center_text(window, centered, "PRESS R TO RESTART", 0);
    center_text(window, centered, "OR PRESS ESC TO PLAY ANOTHER MODE", 20);
}

void Game::paint_speedrun_screen(pro2::Window& window){
    //VERMELL
    window.clear(0x454B1B);
    //pinta el text GAME OVER al mitg de la pantalla
    //a sota fiquem PRESS R TO RESTART
    int center_x = window.topleft().x + window.width() / 2;
    int center_y = window.topleft().y + window.height() / 2;
    pro2::Pt centered = {center_x, center_y};
    
    center_text(window, centered, "SPEEDRUN ENDED",  -20);
    
    // Calculate the total width of "CROSSES COLLECTED: " plus the number
    std::string crosses_text = "CROSSES COLLECTED: ";
    int text_width = crosses_text.length() * (4 + 2); // Each character is 4 pixels wide + 2 spacing
    int number_width = std::to_string(mario_.check_points()).length() * (4 + 2);
    int total_width = text_width + number_width;
    
    // Calculate starting position for centered text
    int start_x = center_x - total_width / 2;
    
    // Paint "CROSSES COLLECTED: "
    paint_text(window, {start_x, center_y}, crosses_text);
    
    // Paint the number right after the text
    paint_number(window, {start_x + text_width, center_y}, mario_.check_points());
    
    center_text(window, centered, "PRESS R TO RESTART", 20);
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

void Game::center_text(pro2::Window& window, pro2::Pt center, const std::string& text, int y_offset) {
    //4 correspon a l'amplada dels sprites
    int text_pixel_width = static_cast<int>(text.length() * (4 + 2));
    int start_x = center.x - text_pixel_width / 2;
    paint_text(window, {start_x, center.y + y_offset}, text);
}

void Game::paint_starting_screen(pro2::Window& window){
    window.clear(sky_blue);
    int center_x = 240;
    int center_y = 160;
    pro2::Pt centered = {center_x, center_y};

    still_mario_.paint(window);
    still_platform_.paint(window);
    center_text(window, centered, "JESUS X MARIO GAME", -100);
    center_text(window, centered, "PRESS ENTER TO START", -80);
    center_text(window, centered, "TIP: WHEN BLESSINGS AVAILABLE PRESS B", -60);
    paint_text(window, {10, 10}, "PAU MURAS");
}

void Game::paint_timer(pro2::Window& window){
    if (ascended_.is_active()) {
        ascended_.paint(window);
    }
    paint_text(window, {window.camera_center().x + 170, window.camera_center().y - 130}, "TIMER:");
    paint_number(window, {window.camera_center().x + 210, window.camera_center().y - 130}, timer_/48);
}

/*PAINT GENERAL*/
void Game::paint(pro2::Window& window) {
    if (game_state_ == 0) {
        window.set_camera_topleft({0,0});
        paint_starting_screen(window);
    } else if (game_state_ == 2) {
        paint_winning_screen(window);
    } else if (game_state_ == 6) {
        paint_paused_screen(window);
    } else if (game_state_ == 5) {
        paint_gameover_screen(window);
    } else if (game_state_ == 3) {
        paint_speedrun_screen(window);
    } else if (is_dodging_mode_) {
        window.clear(sky_blue);
        paint_demon_objects(window);
        paint_platforms(window);
        mario_.paint(window);
    } else {
        if (!sandglass_.is_effect_active()) {
            window.clear(sky_blue);
            sandglass_.paint(window);
        } else {
            window.clear(0xC2B280);
            paint_number(window, {window.camera_center().x, window.camera_center().y}, sandglass_.cooldown());
        }
        paint_timer(window);
        paint_platforms(window);
        paint_crosses(window);
        paint_demon_objects(window);
        paint_blessings(window);
        mario_.paint(window);
        paint_points(window);
    }
    paint_game_frame(window);

}