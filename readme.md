@mainpage

# Juego Platformer 2D

Un juego 2D donde juegas como Jesús, coge cruces, evita morir por caída o por las bolas de fuego demoniacas. El juego incluye poderes como el de parar el tiempo con el RELOJ DE ARENA y un escudo activando el BLESSER.

## Controls

- **Arrow Keys**: Para mover al personaje de Derecha a Izquierda
- **Down Key**: Para bajar al personaje a la plataforma de abajo (o al vacio)
- **Spacebar**: Saltar
- **B**: Activate Blesser shield (if available)

## Game Features

- **Cross**: Cógelas para ganar el juego. Cogiendo 5, te proporciona un escudo.
- **Sandglass**: Temporalmente para el juego y los enemigos
- **Demon**: Crea bolas de fuego que hacen aparecer fuegos a todo lo que tocan.
- **Ascended**: Un escudo que es proporcionado si se clica B al haber conseguido 5 crosses.

### Main Files

- `main.cc`: Inicia el joc
- `game.hh` / `game.cc`: Maneja el bucle del juego y actualiza los objetos.
- `mario.hh` / `mario.cc`: Personaje principal
- `demon.hh` / `demon.cc`: Funciones del demon y todo lo que hace.
- `cross.hh` / `cross.cc`: Las cruces colecionables.
- `sandglass.hh` / `sandglass.cc`: Implementación del reloj de arena.
- `ascended.hh` / `ascended.cc`: El escudo y su implementación usando punteros y la classe stack.
- `platform.hh` / `platform.cc`: Las plataformas y sus funciones.
- `stack.hh`: Stack de punteros

## Build Instructions

1. Recuerda tener un compilador de C++ y la libreria SDL2.
2. Run `make` para compilar.
3. Run `./mario_pro_2` para empezar a jugar.

## Notes

- El Sandglass tiene 10 segundos de cooldown
- Las bolas de fuego pueden ser aturadas o bloqueadas usando poderes.
- Si consigues la mitad de la puntuación para matar el demon este se enfadara y ira más rápido.

Creado por Pau Muras Grané
