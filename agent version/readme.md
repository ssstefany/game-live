# Juego de la Vida. Versión implementada bajo el paradigma de Simulación basada en Agentes

Documentación en el directorio ```docs```. 

Este es una implementación del Juego de la vida [Conway, J. (1970). The game of life. Scientific American, 223(December 2010), 120–123], basado en Agentes.

La idea es simple. Cada célula es un agente que puede estar vivo o muerto. Además, cada uno de ellos tiene sus reglas de sobrevivencia según la cantidad de agentes vivos que están en su vecindad de Moore. Los agentes están inmersos en un ambiente, el que tiene la estructura geométrica del juego.

Ejemplo de uso. Tablero (ambiente) con 10x20 células (agentes), 30 iteraciones, probabilidad de que las células vivan en t=0, 20%.
```
./gol++ -r 10 -c 20 -i 30 -s .2
```

Ejemplo de salida:

```
╔════════════════════╗
║                    ║
║                    ║
║                    ║
║  ▊            ▊    ║
║ ▊   ▊        ▊ ▊   ║
║ ▊ ▊         ▊   ▊  ║
║ ▊          ▊   ▊   ║
║ ▊▊   ▊▊      ▊     ║
║  ▊▊▊▊▊    ▊  ▊     ║
║   ▊▊▊     ▊▊       ║
╚════════════════════╝
Generación: 10, Células vivas: 30
```
