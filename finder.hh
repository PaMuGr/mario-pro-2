/** @file finder.hh
 * @brief Especificació de les Funcions del Finder
 */

#include <map>
#include <set>
#include "geometry.hh"
#include "utils.hh"


template <typename T>
class Finder {

private:
    //Per cada punter tenim en quines quadricules (set de topleft's)
    std::map<const T*, std::set<pro2::Pt>> quadsOfObject;
    //Pt es el top left de la quadricula i el set correspon als objectes en la quadricula
    std::map<pro2::Pt, std::set<const T*>> objectsTopLeft;
    
    //Tamany de les quadricules en les quals es dividira el mon
    static const int QUADSIZE = 80;

    /**
     * @brief Retorna el conjunt de quadricules on es troba 
     *        l'objecte.
     *
     * @param rObj El rectangle del objecte
     *
     * @returns Un set de Pt's amb el topleft de les quadricules on està el objecte 
     */
    std::set<pro2::Pt> setPts(const pro2::Rect& rObj) const {
        std::set<pro2::Pt> result;
        //Si tenim objecte de topleft (524,17) llavors les quadricules van del topleft minim (500,0) al bottom right maxim, iterem com una matriu
        int left = (rObj.left / QUADSIZE) * QUADSIZE;
        int right = (rObj.right / QUADSIZE) * QUADSIZE;
        int top = (rObj.top / QUADSIZE) * QUADSIZE;
        int bottom = (rObj.bottom / QUADSIZE) * QUADSIZE;

        for (int x = left; x <= right; x += QUADSIZE) {
            for (int y = top; y <= bottom; y += QUADSIZE) {
                //Tots els top lefts dels quads on esta r (rect del objecte)
                result.insert({x, y});
            }
        }
        return result;
    }

public:
    Finder() {}
    
    /**
     * @brief Afegeix a quadsOfObject les quadricules on es troba t, també afegeix a
     *          objectsTopLeft els punters dins de cada quadricula
     *
     * @param t Punter al objecte
     *
     */
    void add(const T *t){
        pro2::Rect rect = t->get_rect();
        std::set<pro2::Pt> quadricules = setPts(rect);
        
        quadsOfObject[t] = quadricules;

        auto it = quadricules.begin();
        while(it != quadricules.end()){
            objectsTopLeft[*it].insert(t); 
            it++;
        }
    }

    /**
     * @brief Treu de quadsOfObject les quadricules on es trobava t, també treu de
     *          objectsTopLeft els punters dins de cada quadricula. 
     *
     * @param t Punter al objecte
     *
     */
    void remove(const T *t){
        auto it = quadsOfObject.find(t);

        if(it != quadsOfObject.end()){
            std::set<pro2::Pt> quadricules = it->second;
            auto it2 = quadricules.begin();

            while(it2 != quadricules.end()){
                objectsTopLeft[*it2].erase(t);
                if(objectsTopLeft[*it2].empty()){
                    objectsTopLeft.erase(*it2);
                }
                it2++;
            }
            quadsOfObject.erase(it);
        }
    }

    /**
     * @brief Treiem l'antic i fiquem el nou ja mogut
     *
     * @param t Punter al objecte
     *
     */
    void update(const T *t){
        remove(t);
        add(t);
    }


    /**
     * @brief Retorna el conjunt d'objectes amb rectangles 
     *        total o parcialment dins de `rect`.
     *
     * Si el nombre de rectangles del contenidor és `n`, el 
     * cost de l'algorisme ha de ser O(log n).
     *
     * Hem de primer trobar els elements en les quadricules i veure si aquestes estan dins del rectangle de la càmera
     * 
     * @param rect El rectangle de cerca
     *
     * @returns Un conjunt de punters a objectes que tenen un 
     *          rectangle parcial o totalment dins de `rect`
     */
    std::set<const T *> query(pro2::Rect rect) const{
        std::set<const T*> result;
        std::set<pro2::Pt> quadricules = setPts(rect);
        auto it = quadricules.begin();

        while(it != quadricules.end()){
            auto it2 = objectsTopLeft.find(*it);
            if(it2 != objectsTopLeft.end()){
                std::set<const T*> setPunters = it2->second;
                auto it3 = setPunters.begin(); 

                while(it3 != setPunters.end()){
                    if(interseccionen((*it3) -> get_rect(), rect)){
                        result.insert(*it3);
                    }
                    it3++;
                }
            }
            it++;
        }
        return result;
    }
};