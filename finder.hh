/** @file finder.hh
 * @brief Especificació de les Funcions del Finder
 */

template <typename T>
class Finder {
    //mapa
public:
    Finder() {}

    //n vegades
    void add(const T *t);

    //cada frame: n vegades
    //Find amb map i actualitzar el segon element del map
    void update(const T *t);

    //quan l'agafes
    void remove(const T *t);

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