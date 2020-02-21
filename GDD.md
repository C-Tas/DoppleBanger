# DoppleGanger
## Resumen
- **Género**: Action Rpg
- **Modos**: Un jugador
- **Plataformas**: PC - Teclado y ratón
- **Lenguaje de programación**: C++
- **Público objetivo:** a partir de doce años

Desarrollado por ***CPlusPlusTas***
## 0.- Descripción

*Action RPG* con vista isométrica de temática pirata consistente en visitar, superar y saquear equipamiento y tesoros de distintos niveles visitables por el jugador siguiendo la estructura fundamental del género establecido. En el proceso se encontrará una variedad de enemigos que deben ser derrotados por el jugador para llegar al ob jetivo. Cada nivel jugable será una isla con una dificultad progresiva de manera que cada zona dentro de la misma sea más difícil que la anterior. La dificultad de las islas también aumenta de manera progresiva.

El juego se centrará especialmente en la jugabilidad, teniendo una historia ligera que sirva de contexto para dar lugar a la aventura. Se conservan muchos aspectos típicos del género como el concepto del inventario limitado, los objetos utilizables y la personalización del equipamiento.

La estética será colorida y suave, basada en pixelart más que en representaciones realistas del mundo. Música animada y acorde a la ambientación.

Producido usando C++ y bibliotecas del mismo como SDL. Narrativa original del equipo. Recursos propios o adquirido de lugares libres de derechos de copyright (artistas ajenos acreditados).

### 0.1.- Versiones del documento
    
    
## 1.- Menús e interfaz
### 1.1.- Menú de inicio
El menú de inicio del juego consistirá en una pantalla donde se observarán los siguientes botones:

- **Nueva partida:** para empezar a jugar desde cero. Muestra la **pantalla de selección de partida** para crear/sobreescribir la nueva partida.
- **Cargar partida:** muestra la **pantalla de selección de partida** para cargar una partida creada. En caso de no existir partidas guardadas se creará una nueva por defecto.
- **Controles:** muestra la **pantalla de controles**.
- **Créditos:** muestra la **pantalla de créditos**.
- **Audio:** para activar o desactivar el audio.(Estará representado con un icono)
#### 1.1.1.- Pantalla de selección de partida
Se mostrarán 3 botones que contienen información de la partida guardada en caso de la hubiera, si no es así, entonces se mostrarán botones que incluyan lo siguiente: _"Nueva Partida"_. Una vez se seleccione uno de los botones se cambiará la interfaz para mostrar el contedido del juego.

Hay un botón para volver al menú principal además de un fondo (gráfico y musical) coherente a la temática del juego.
####  1.1.1.- Pantalla de controles
Muestra una imagen con los controles.

Hay un botón para volver al menú principal además de un fondo (gráfico y musical) coherente a la temática del juego.
#### 1.1.2.- Pantalla de créditos
Muestra una lista de los nombres de los desarrolladores.

Hay un botón para volver al menú principal además de un fondo (gráfico y musical) coherente a la temática del juego.
### <a name = "mapa"></a>1.2.- Interfaz de selección de nivel
Muestra una mapa con las islas disponibles, pudiéndose viajar a cualquiera de ellas. Para acceder a esta interfaz hay que interactuar con el objeto del [barco](#barco) existente para ello.

- **Mapatata:** mapamundi visible solo desde el barco. En un principio estará incompleto y cada isla terminada desbloquea un cacho nuevo del mapa. El último trozo del mapa muestra una isla desconocida en la que se encuentra el tesoro objetivo.

### 1.3.- Interfaz durante el *gameplay*

El HUD en pantalla estará compuesto por los siguientes elementos:

Definir
<!-- ![HUD](https://i.imgur.com/tvf0qrx.jpg) -->

### 1.4.- Menú de pausa
Reanudar, Menú principal, Mute, Controles
### <a name = "puerta"></a>1.5.- Menú de guardado
Muestra una pantalla en la que existen dos botones.
- **Guardar:** habilita una pantalla similar a la **pantalla de selección de partida** donde el jugador podrá guardar su progreso pulsando uno de los 3 botones habilitados para ello. Una vez se pulse , si no existe partida, se pedirá un código para identificativo y, en caso de que exista, se advertirá al jugador de va a sobreescribir una partida existente.


Hay un botón para volver al menú principal y otro para reanudar la partida además de un fondo (gráfico y musical) coherente a la temática del juego.

### <a name = "skill_menu"></a>1.6.- Menú de habilidades
Muestra una pantalla donde se podrán observar las distintas ramas de habilidades mejorables. En caso de que el jugador posea los [puntos de hazaña](#puntos_h) suficientes para usar en alguna habilidad y ésta no haya sido desbloqueada, el botón para su mejora estará habilitado y al pulsarse se preguntará al jugador si está seguro de su elección. En caso afirmativo se desbloqueará la habilidad en cuestión y posteriormente podrá ser equipada en una de las teclas de habilidad disponibles.

### 1.7.- Inventario
Equipamento y objetos juntos
Para equipar hacer click en las opciones.

## 2.- Jugabilidad
La jugabilidad gira en torno a la superación de zonas plagadas de enemigos, haciendo uso de distintos tipos de habilidades y ataques para lograrlo. Según se avance en el juego se proveerá de nuevo y mejorado equipamiento al jugador para dar sensación de progreso y refrescar el _gameplay_ con estilos de juego distintos.

### 2.1.- Mecánicas
- **Click izquierdo:** movimiento y ataque cuerpo a cuerpo (sobre un enemigo).
- **Click derecho del ratón:** ataque a distancia.
- **Teclas de habilidad:** utiliza una [habilidad](#skills). Se usarán 3 teclas por defecto, no configurables, que se pueden asignar a distintas habilidades. Además existe una cuarta tecla que solo podrá asignar habilides de la rama del clon.
- **Tecla de grito:** ejecuta un efecto sonoro diciendo _YAAARR_.
- **Teclas de objeto:** utiliza un [objeto](#items). Se usarán 2 teclas por defecto, no configurables, que se pueden asignar a distintos objetos.
- **Tecla de inventario:** abre el [inventario](#inventario).
- **Tecla de árbol de habilidades::** habilita un [menú](#skill_) donde se pueden ver las habilidades equipadas, desbloqueadas y bloqueadas.
#### <a name = "puntos_h"></a>2.1.1.- Puntos de hazaña
Son puntos que sirven para subir de nivel las [habilidades](#skills).
Se consiguen matando enemigos y completando [misiones secundarias](#quest_2) y se pueden usar cuando el jugador pulse la tecla de habilidades.

#### <a name = "stats"></a>2.1.2.- Características y propiedades del personaje
    
Las características varían en función de los [objetos](#items) encontrados a lo largo del juego, partiendo de una base (sin objetos equipados). Algunas pueden aumentar con las ramas de habilidades.

- **Vida:** representa los puntos de vida del jugador. Se pierde vida cuando se reciben ataques de los enemigos y se recupera usando [pociones de vida](#poc_vida) o al entrar en el [barco](#barco). La vida máxima puede variar con [pechera](#pechera).

- **Maná:** representa la cantidad de maná del jugador. Se gasta al usar [habilidades](#skills) y se recupera en función del tiempo y con [pociones de maná](#poc_mana).

- **Regeneración de maná:** es la cantidad de maná que recupera el jugador en función del tiempo.

- **Defensa:** representa la reducción del daño del jugador. Puede variar con [armaduras](#armaduras) y [pociones de defensa](#poc_defensa).

- **Daño:** es el daño que inflige el jugador con los ataques básicos(melee y a distancia). Puede aumentar con [_Invencible_](#invencible) y variar con [armas cuerpo a cuerpo](#arma_melee) y [pociones de daño](#poc_dmg).

- **Crítico:** probabilidad de infligir una cantidad mayor de daño realizar ataques básicos (melee y a distancia). Puede aumentar con [_Invencible_](#invencible) y variar con [guantes](#guantes) y [pociones de crítico](#poc_critico).

- **Velocidad de movimiento:** representa la velocidad a la que el jugador se podrá mover durante el juego. Puede variar con [calzado](#calzado) y con [pociones de velocidad](#poc_vel).

- **Velocidad melee:** es la velocidad de ataque cuerpo a cuerpo.

- **Cadencia:** es la velocidad de ataque a distancia. Puede aumentar con [_Pistolero raudo_](#pistolero) y variar con [armas a distancia](#arma_dist).

### 2.2.- Dinámicas

#### 2.2.1.- Objetivo principal
El objetivo es encontrar el tesoro que se encuentra en la última isla, para acceder a ella es necesario completar primero el mapa a través del recorrido de las islas anteriores.

#### 2.2.3. Ganar
El jugador ganará cuando cumpla el objetivo.

#### <a name = "perder"></a>2.2.2. Perder
Cuando los puntos de salud del jugador llegan a cero, se pierde todo el oro que lleves en el inventario y vuelves al [barco](#barco) (atracado en la isla actual). El dinero que hubiese guardado en el barco se mantiene, así como el resto de objetos.

#### 2.2.4.- Guardar y cargar
Para guardar partida es necesario estar en el barco, se guardará el estado actual del juego, eso incluye: la isla actual, el alijo, el inventario, habilidades equipadas, las teclas asignadas a las habilidades y objetos (atajos de teclado), misiones completadas, islas desbloqueadas y la rama de habilidades y puntos de hazaña no usados.

Se podrán crear 3 partidas distintas sobre el juego, en el menú de selección de partida se preguntará cual de las tres se quiere cargar y se jugará sobre ella.

#### <a name = "alijo"></a>2.2.5.- Alijo
Situado en el barco y sirve para guardar los objetos y el oro que no quiera llevar encima el jugador, de esta manera, si el jugador es derrotado no se pierde el oro del alijo.

#### <a name = "inventario"></a>2.2.6.- Inventario
Lleva una lista de los objetos que haya conseguido el jugador y el equipamento actual (pechera, calzado, guantes, arma cuerpo a cuerpo, arma a distancia, habilidades y objetos consumibles). Cada vez que el jugador adquiere un objeto se añade inmediatamente al invertario. El inventario se puede abrir en cualquier momento de la partida, así como hacer uso de sus objetos.

Se podrán mover objetos del inventario al alijo cuando se esté en el barco.

#### <a name = "chest"></a>2.2.7.- Cofres
 A lo largo del juego se podrán encontrar baúles que contengan [objetos](#items) útiles para el jugador. Los baúles se generan en posiciones aleatorias de la zona cuando se haya acabado con todos los enemigos. Los objetos también serán aleatorios acordes al nivel de la [isla](#isla) y de la zona.

#### <a name = "skills"></a>2.2.8.- Habilidades
Todas las habilidades gastan [maná](#stats).

Se distinguen dos tipos de habilidades:

    Activa: Necesitan la intervención del jugador para su activación.
    Pasiva: Se ejecutan automáticamente al desbloquearse. 

|Rama| Activa| Pasiva| Activa|
|-|-|-|-|
|Clon| Parálisis| Reflejo| Autodestrucción|
|Combate| Golpe fuerte| Invencible| Torbellino| 
|Precisión| Perforación| Pistolero raudo| Rebote|   

Cada vez que el jugador mate a un enemigo conseguirá [puntos de hazaña](#puntos_h) que puede invertir en tres ramas.

- **Rama clon:** por defecto, se tiene una habilidad que se tiene desde el principio del juego. Al ejecutar esta habilidad se invoca a ún fantasma inmóvil que atrae a los enemigos (como señuelo). Es la rama que se centra en la mejora del fantasma. 
    - Ataca con los stats al 50% del jugador
    - Ataca con lo stats al 100% del jugador.
    - **Autodestrucción:** inflige una cantidad concreta de daño a los enemigos dentro del área de efecto. Tras ello, el fantasma desaparece. 

- **Rama combate:** se centra en el combate cuerpo a cuerpo.
    - **Golpe fuerte:** carga daño al siguiente ataque básico.
    - <a name = "invencible"></a>**Invencible:** aumenta el [daño](#stats) y el [crítico](#stats) del jugador de manera permanente.
    - **Torbellino:** realiza un ataque circular infligiendo daño a los enemigos que se encuentren cerca.

- **Rama precisión:** se centra en el combate a distancia.
    - **Perforación:** el siguiente disparo con el arma a distancia atraviesa unidades infligiendo daño a todos los enemigos que haya en el recorrido de la bala.
    - <a name = "pistolero"></a>**Pistolero raudo:** aumenta la [cadencia](#stats) de disparo del jugador de manera permanente.
    - **Rebote:** durante un tiempo los disparos rebotan un número limitado de veces entre los enemigos cercanos.



#### <a name = "shop"></a>2.2.9.- Tienda
Es la zona del [barco](#items) en la que se pueden comprar diversos [objetos](#items) en función de la última isla desbloqueada, de manera que los objetos se actualicen cada vez que se desbloquee una nueva isla. Además, todos los objetos del juego se pueden vender a cambio de oro.

- **Oro:** el oro se consigue matando enemigos y mediante [cofres](#chest). Se usa para poder comprar [objetos](#items) en la tienda.

## 3.-Contenido
### 3.1.- Historia
#### <a name = "personajes"></a>3.1.1.- Personajes
- **Protagonista:** <!--Definir.-->

- **Mercader:** polizona del barco. En la ciudad el negocio no le fue bien dado el cuestionable origen de sus productos, así que pensó que piratas podrían apreciar más sus buenos precios. Se encarga de la [tienda](#shop).

- **El viejo:** es el que te vendió el barco y te hizo buen precio si a cambio le dejabas ver mundo en él. Cada vez que descubres una isla te habla sobre la historia de la misma y sobre algún ítem raro en cada una de ellas.

- <a name = "cocinero"></a>**El cocinero:** aparece en la primera isla al principio del nivel. Trabajaba de chef en un crucero de lujo hasta que lo ascendieron a “cocinero prescindible ejecutivo” y lo dejaron en la isla. Al completar [_Gallego en problemas_](#quest_coc) se une a la tripulación.

- <a name = "ghost"></a>**Morty, el fantasma:** Aparece en la [isla fantasmal](#fantasmal) Es un tío tan chill que casi no lo maldicen pero pensaron que maldecir a todos menos uno estaba feo. Murió siendo un pirata pero solo porque sus padres lo presionaron para serlo. Promete recompensas a cambio de hacerle un favor, completando [_Papeles siniestros_](#quest_morty).

<!-- - **El loro:** Se encuentra en algún lugar de la [isla caribeña](#caribe) (¿segunda isla?). Es un loro y quiere un pirata. Su misión va de traerle yo qué sé cualquier tontería depende de los enemigos que haya. -->

<!-- - **La pirata:** Da igual en qué isla aparezca, supongo que la cuarta. Era una pirata intrépida dispuesta a saquear la isla pero le metieron un flechazo en la rodilla y ahora necesita quedarse en un lugar seguro hasta que se recupere. Su misión va de mates a todos los arqueros para que pueda vengarse. -->

#### 3.1.2.- Enemigos
- Barra visible sólo para los bosses.
- Los comunes no tienen habilidades especiales, solo los bosses.

- <a name = "respawn"></a>**Reiniciable:** cuando un enemigo es derrotado puede volver a aparecer una vez se pase por el barco.

- <a name = "enem-comun"></a> **Enemigo común:** se trata de un tipo de enemigo que puede aparecer en diversas zonas. Reiniciable.

- <a name = "enem_power"></a> **Enemigo poderoso:** se trata de un tipo de _Enemigo común_ con más poder y mayor tamaño. Reiniciable.

- <a name = "finalBoss"></a> **Enemigo final:** se trata de un tipo de enemigo único que se encuentra sólo al final de cada isla. Derrotarlo desbloquea el acceso al siguiente nivel si lo hubiere. No reiniciable.

<!-- - 6 enemigos comunes
- 3 bosses
- Cuerpo a cuerpo
- Distancia
- Boss -->

### 3.1.3.- Tabla de características
Se insertará una tabla con las características principales del personaje principal y de los enemigos.

### 3.3.- Instancias
Las instancias son los lugares accesibles por el jugador; habrá un total de 4 instancias: 3 islas y el barco. 

#### <a name = "isla"></a>3.3.1- Islas
Las islas estarán divididas por zonas. Cada zona tiene un [enemigo poderoso](#enem_power) y cada isla tiene un [enemigo final](#finalBoss) en la última zona.

Las zonas serán accesibles de forma lineal, es decir, no se puede acceder a la zona 2 sin haber pasado por la 1. Al cambiar de zona se resaurarán los enemigos y los [cofres](#chest). 

Las islas estarán diseñadas por diversass temáticas:

<a name = "carbie"></a>**Caribe:** Definir.

<a name = "fantasmal"></a>**Fantasmal:** Definir.

**Volcánica:** Definir

5 enemigos comunes (los enemigos poderosos son versiones potenciadas de estos) + 3 bosses incluyendo el boss final.

- **1ª isla (Temática del caribe):**    
    |Zona| Enemigos comunes| Enemigos poderosos| Enemigo final|
    |-|-|-|-|
    |1| 2| 1| 0|
    |2| 3| 1| 0|
    |3| 3| 0| 1|
- **2ª isla (Temática fantasmal):**
    |Zona| Enemigos comunes| Enemigos poderosos| Enemigo final|
    |-|-|-|-|
    |1| 2| 1| 0|
    |2| 3| 1| 0|
    |3| 4| 0| 1|

- **3ª isla (Temática volcánica):** 
    - Zona única con un Enemigo final.

#### <a name = "barco"></a>3.3.2.- Barco
Es la instancia de reinicio donde el jugador revive cuando [pierde](#perder) y en la que el jugador podrá hacer uso del [alijo](#alijo),  acceder al [mapa](#mapa) mediante la interacción con el timón y guardar partida interactuando con la puerta de la habitación, mostrando la [interfaz](#puerta) correspondiente. Además se podrán encontrar diversos [personajes](#personajes) en el barco, así como la [tienda](#shop). Cada vez que el jugador entre en el barco se restablecerá toda la [vida](#stats) y se restablecerán los enemigos [reiniciables](#respawn).

### <a name = "items"></a>3.4.- Objetos
Son elementos del juego que otorgan beneficios al jugador. Todos los objetos se pueden vender a través de la [tienda](#shop).

Existen 3 tipos de objetos: [armaduras](#armaduras), [armas](#armas) y [pociones](#pociones). Dentro de cada tipo existen varios objetos que otorgan cualidades distintas.

A continuación se muestra una tabla de los objetos con la siguiente información:
- **Consumible**: indica que una vez se usa, se destruye
- **Cómo conseguir:** define la forma en la que se consigue el objeto. Puede ser a través de la [tienda](#shop) o de [cofres](#chest).
- **Stats:** el tipo de [característica](#stats) que se ve afectada por el objeto.

|Nombres|Consumible|Cómo conseguir|Stats|
|-|-|-|-|-|-|
|[Pechera](#pechera)| No| Tienda| defensa, resitencia mágica, vida|
|[Calzado](#calzado)| No| Tienda| defensa, resistencia mágica, velocidad de movimiento|
|[Guantes](#guantes)| No| Tienda| defensa, resitencia mágica, critico|
|[Espada](#espada)| No| Tienda| Daño físico, crítico|
|[Sable](#sable)| No| Tienda| Daño físico, crítico|
|[Pistola](#pistola)| No| Tienda|Daño físico|
|[Trabuco](#trabuco)| No| Tienda|Daño físico|
|[Pociones de vida](#poc_vida)| Sí| Cofres y Tienda| vida|
|[Pociones de maná](#poc_mana)| Sí| Cofres y Tienda| maná|
|[Pociones de velocidad](#poc_vel)| Sí| Cofres y Tienda| velocidad de movimiento|
|[Pociones de daño](#poc_dmg)| Sí|Cofres y Tienda| daño físico|
|[Pociones de defensa](#poc_defensa)| Sí| Cofres y Tienda | defensa, resitencia mágica|
|[Pociones de crítico](#poc_critico)| Sí| Cofres y Tienda | crítico|

#### <a name = "armaduras"></a>3.4.1.- Armaduras
Es el tipo de objeto que aumenta [defensa](#stats) y [resistencia mágica](#stats).
- <a name = "pechera"></a>**Pechera:** equipamento de armadura que aumenta la [vida](#stats).

- <a name = "guantes"></a>**Guantes:** equipamento de armadura que aumenta el [crítico](#stats).

- <a name = "calzado"></a>**Calzado:** equipamento de armadura que aumenta la [velocidad de movimiento](#stats).

Ver [Tabla de objetos](#items) para más información.
#### <a name = "armas"></a>3.4.2.- Armas
Es el tipo de objeto que aumenta el [daño](#stats).
- <a name = "arma_melee"></a>**Cuerpo a cuerpo:** permiten al jugador atacar con un alcance corto. Aumentan el [crítico](#stats).

    - <a name = "espada"></a>**Espada:** su robustez compensa su falta de agilidad con un daño considerable produciendo más daño que crítico.

    - <a name = "sable"></a>**Sable:** su ligereza permite al usuario asestar golpes con mayor precisión, potenciando la probabilidad de crítico, compensando así su fragilidad y su carencia de daño.

- <a name = "arma_dist"></a>**A distancia:** permiten al jugador con un alcance largo.

    - <a name = "pistola"></a>**Pistola:** las balas consiguen llegar más lejos gracias a su potencia de disparo y a la fluidez de los poyectiles, los cuales recorren una trayectoria lineal.

    - <a name = "trabuco"></a>**Trabuco:** es un arma tan potente que los proyectiles explotan al disparar, generando un arco de perdigones que recorren pocas distancias, pero infligiendo daños elevados a distancias cortas.

Ver [Tabla de objetos](#items) para más información

#### <a name = "pociones"></a>3.4.3.- Pociones
Todas las pociones aplican efectos temporales.
- <a name = "poc_vida"></a>**Poción de vida:** medicina de hierbas divinas que curan las heridas regenerando una cantidad de la [vida](#stats).

- <a name = "poc_mana"></a>**Poción de maná:** agua de mar tratada con magia que regenera una cantidad del [maná](#stats).

- <a name = "poc_vel"></a>**Poción de velocidad:** ron mezclado con aceite de trucha que producen hiperactividad, aumentando la [velocidad de movimiento](#stats).

- <a name = "poc_dmg"></a>**Poción de daño:** fluidos de demonio que fortalece la musculatura haciendo que el que la bebe inflija más [daño](#stats) con sus golpes.

- <a name = "poc_defensa"></a>**Poción de defensa:** sangre de gorila tratado con alquimia avanzada que aumenta la resistencia otorgando una [defensa](#stats) mayor.

- <a name = "poc_critico"></a>**Poción de crítico:** sangre de águila virgen que aumenta la precisión otorgando mayor probabilidad de [crítico](#stats). 

Ver [Tabla de objetos](#items) para más información.

### 3.5.- Misiones
- **Principales:** Son obligatorias y necesarias para completar el juego.
    
- <a name = "quest_2"></a>**Secundarias:** Son opcionales, no son necesarias para completar el juego.
    - <a name = "quest_coc"></a>**Gallego en problemas:** es la misión que desbloquea al [cocinero](#cocinero). El cocinero le pedirá al jugador que consiga los ingredientes para hacerle un cocido gallego. Para ello, el jugador deberá matar un número determinado de enemigos de un tipo en concreto (Definir). Tras ello, el cocinero se unirá a la tripulación, además de conseguir [puntos de hazaña](#puntos_h) y oro.
    - <a name = "quest_morty"></a>**Papeles siniestros:** es la misión relacionada con [Morty, el fantasma](#ghost). El expirata Morty tiene miedo de las demás criaturas de la isla, a pesar de ser un fantasma, por lo que le pide al jugador que despeje la zona 2 de la [isla fantasmal](#fantasmal) llena de enemigos para poder atravesarla y así conseguir su tan asiado papelde liar, no agaunta el mono. Tras completarla, el juagdor recibirá [puntos de hazaña](#puntos_h) y oro.
   
## 4.Referencias

    Diablo Saga
    Children of Morta
    League of legends
    Path of Exile
    The Witcher 3

## 5.Bibliografía