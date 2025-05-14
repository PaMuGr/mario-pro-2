/** @file finder.hh
 * @brief Especificació de les Funcions del Finder
 */

#include <map>
#include <set>
#include "utils.hh"


template <typename T>
class Finder {

private:

    //bastant segur de la primera estructura, la segona es una proba per veure si funcionaria
    std::map<const T*, pro2::Rect> objecteRectangle;

    std::map<pro2::Rect, const T*> rectanglesObjectes;

public:
    Finder() {}

    //n vegades
    void add(const T *t){
        pro2::Rect rect = t->get_rect();
        objecteRectangle[t] = rect;
        rectanglesObjectes[rect] = t;
    }

    //cada frame: n vegades
    //
    //Find amb map i actualitzar el segon element del map?
    //Guardem abans d'actualitzar i canviem primer element del segon map?
    void update(const T *t){

        auto it = objecteRectangle.find(t);
        //si existeix intercanviem
        if(it != objecteRectangle.end()){

            pro2::Rect rect = t->get_rect();

            //busquem al segon map el rectangle que haurem d'intercanviar
            auto it2 = rectanglesObjectes.find(it -> second);
            //mirem si existeix i si coincideix amb el iterador buscat
            if(it2 != rectanglesObjectes.end() && it2->second == t){
                rectanglesObjectes.erase(it2);
                //insertem després d'eliminar-ho amb el nou rectangle i mateix iterador
                rectanglesObjectes.insert({rect,t});
            }

            //canviat el rect del primer map per el que toca
            it -> second = rect;
        }

    }

    //quan l'agafes
    void remove(const T *t){
        auto it = objecteRectangle.find(t);
        //si existeix hem d'eliminar-lo i per aixo borrem el punter
        if (it != objecteRectangle.end()) {
            //guardem el rectangle que buscarem en el segon map
            pro2::Rect rect = it->second;
            //borrem
            objecteRectangle.erase(it); 

            auto it2 = rectanglesObjectes(rect);
            //mirem si existeix i si coincideix amb el iterador buscat
            if(it2 != rectanglesObjectes.end() && it2->second == t){
                //esborrem
                rectanglesObjectes.erase(it2);
            }
        }
    }

    /**
     * @brief Retorna el conjunt d'objectes amb rectangles 
     *        total o parcialment dins de `rect`.
     *
     * Si el nombre de rectangles del contenidor és `n`, el 
     * cost de l'algorisme ha de ser O(log n).
     *
     * @param rect El rectangle de cerca
     *
     * @returns Un conjunt de punters a objectes que tenen un 
     *          rectangle parcial o totalment dins de `rect`
     */

    //cada frame: 1 vegada
    //bucle recorrint tot el map i mirant si s'intersecciona amb rect
    //si, si. afegir al set resultat i retornar set

    //per fer-ho eficient compararem que el objecte bottom right > topleft de la cam, objecte top left < que bottom right
    //en el map ho tenim ordenat i doncs quan trobem un punt bottom right >= topleft doncs tots desde aquell cap al final estan dins
    //tindrem un iterador amb el moment on apuntem al punt >= topleft i un <= bottom right
    std::set<const T *> query(pro2::Rect rect) const;
};