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
- Versión 1.0 22/02/2020

## 1.- Menús e interfaz
### 1.1.- Menú de inicio
El menú de inicio del juego consistirá en una pantalla donde se observarán los siguientes botones:

- **Nueva partida:** para empezar a jugar desde cero. Muestra la **pantalla de selección de partida** para crear/sobreescribir la nueva partida.
- **Cargar partida:** muestra la **pantalla de selección de partida** para cargar una partida creada. En caso de no existir partidas guardadas se creará una nueva por defecto.
- **Controles:** muestra la **pantalla de controles**.
- **Créditos:** muestra la **pantalla de créditos**.
- **Audio:** para activar o desactivar el audio.(Estará representado con un icono).

#### 1.1.1.- Pantalla de selección de partida
Se mostrarán 3 botones que contienen información de la partida guardada en caso de la hubiera, si no es así, entonces se mostrarán botones que incluyan lo siguiente: _"Nueva Partida"_. Una vez se seleccione uno de los botones se cambiará la interfaz para mostrar el contedido del juego.

Hay un botón para volver al menú principal además de un fondo (gráfico y musical) coherente a la temática del juego.

####  1.1.1.- Pantalla de controles
Muestra una imagen con los controles.

Hay un botón para volver al menú anterior(puede ser el menú principal o el menú de pausa) además de un fondo (gráfico y musical) coherente a la temática del juego.

#### 1.1.2.- Pantalla de créditos
Muestra una lista de los nombres de los desarrolladores.

Hay un botón para volver al menú principal además de un fondo (gráfico y musical) coherente a la temática del juego.

### <a name = "mapa"></a>1.2.- Interfaz de selección de nivel
Muestra una pantalla en la que se observa el [_Mapatata_](#map_tata), mapamundi accesible solo desde el [barco](#barco). Muestra las islas disponibles y al hacer click izquierdo en una de ellas se reanudará partida en la isla pulsada.

### 1.3.- Interfaz durante el *gameplay*
El HUD en pantalla estará compuesto por los siguientes elementos:

- **Maná:** muestra la cantidad de maná disponible. 
- **Vida:** indica la vida restante del jugador.
- **Habilidades:** indica la configuración de botones de las habilidades activas y su atajo de teclado.
- **Obj:** indica la configuración de botones de los objetos y su atajo de teclado.
- **Puntos de hazaña:** muestra los puntos de hazaña totales.

![HUD](https://i.imgur.com/QhU2S1D.png)

### <a name = "pause_state"></a>1.4.- Menú de pausa
Muestra el menú de pausa donde se observan los siguientes botones:
- **Reanudar:** reanuda la partida actual
- **Menú principal:** se sale de la partida actual sin guardar y vuelve al menú inicial.
- **Mute:** activa/desactiva el audio del juego.
- **Controles:** muestra la pantalla de controles.

### <a name = "puerta"></a>1.5.- Menú de guardado
Muestra una pantalla similar a la **pantalla de selección de partida** donde el jugador podrá guardar su progreso pulsando uno de los 3 botones habilitados para ello. Una vez se pulse , si no existe partida, se pedirá un código identificativo y, en caso de que exista, se advertirá al jugador de va a sobreescribir una partida existente.

Hay un botón para volver al menú principal y otro para reanudar la partida además de un fondo (gráfico y musical) coherente a la temática del juego.

### <a name = "skill_menu"></a>1.6.- Menú de habilidades
Este menú estará dividido en dos partes: 
- **Árbol:** situado en la parte izquierda, muestra las distintas ramas de habilidades mejorables. Encima suya se muestra la cantidad de [puntos de hazaña](#puntos_h) totales. En caso de que el jugador posea los puntos de hazaña suficientes para usar en alguna habilidad y ésta no haya sido desbloqueada, el botón para su mejora estará habilitado y al pulsarse se preguntará al jugador si está seguro de su elección. En caso afirmativo se desbloqueará la habilidad en cuestión y posteriormente podrá ser equipada en una de las teclas de habilidad disponibles.

- **Descripción:** situado en la parte derecha, muestra una descripción sobre la habilidad pulsada en la parte superior. En la parte inferior se mostrará la configuración de controles de las habilidades, que pueden ser modificados desde este menú.

![SkillsMenu](https://i.imgur.com/lMUw85t.png)

### 1.7.- Menú de Inventario
Este menú estará dividido en dos partes:
- **Equipamento:** ocupará la parte izquierda de la pantalla y mostrará los objetos que se hayan equipado. Justo de bajo de esto se podrá observar información sobre el estado del jugador(vida, maná, velocidad de movimiento...).

- **Lista de objetos:** ocupará la parte derecha de la pantalla  mostrará los objetos no equipados. Al hacer click izquierdo sobre uno de ellos se podrá ver informacción sobre él en la parte inferior de la pantalla y con el click derecho se equipará. Esta información muestra los efectos que tendrá el objeto sobre el jugador y una breve descripción sobre él.

También hrabrá un botón para reanudar la partida.

![InventoryMenu](https://i.imgur.com/4U1sn5a.png)

### 1.8.- Menú de Alijo
Muestra la lista de objetos y la cantidad de oro que se haya guardado en el [alijo](#stash). Al hacer click izquierdo sobre uno de los objetos se podrá ver información detalla sobre él además de darle la opción al jugador de moverlo a inventario.

También habrá un botón para reanudar partida.

### 1.9.- Menú de la tienda
Muestra la lista de los objetos que se venden en la [tienda](#shop). Cada objeto visible es un botón que al pulsarse mostrará información sobre él en el panel de descripción de objetos. Esta información dependerá del objeto escogido, pero en general muestra el precio, los efectos que tendrá sobre el jugador y una breve descripción sobre él.

También habrá un botón para reanudar la partida.

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
- **Tecla de pausa:** habilita el [menú de pausa](#pause_state).
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

#### <a name = "stash"></a>2.2.5.- Alijo
Situado en el barco y sirve para guardar los objetos y el oro que no quiera llevar encima el jugador, de esta manera, si el jugador es derrotado no se pierde el oro del alijo.

#### <a name = "inventario"></a>2.2.6.- Inventario
Lleva una lista de los objetos que haya conseguido el jugador y el equipamento actual (pechera, calzado, guantes, arma cuerpo a cuerpo, arma a distancia, habilidades y objetos consumibles). Cada vez que el jugador adquiere un objeto se añade inmediatamente al invertario. El inventario se puede abrir en cualquier momento de la partida, así como hacer uso de sus objetos.

Se podrán mover objetos del inventario al alijo cuando se esté en el barco.

#### <a name = "chest"></a>2.2.7.- Cofres
 A lo largo del juego se podrán encontrar baúles que contengan [objetos](#items) útiles para el jugador. Los baúles se generan en posiciones aleatorias de la zona cuando se haya acabado con todos los enemigos. Los objetos también serán aleatorios acordes al nivel de la [isla](#isla) y de la zona.

#### <a name = "map_tata"></a>2.2.8.- Mapatata
Mapamundi accesible solo desde el barco. En un principio estará incompleto y cada isla terminada desbloquea un cacho nuevo del mapa. El último trozo del mapa muestra una isla desconocida en la que se encuentra el tesoro objetivo.

#### <a name = "skills"></a>2.2.9.- Habilidades

Se distinguen dos tipos de habilidades:

    Activa: Necesitan la intervención del jugador para su activación.
    Pasiva: Se ejecutan automáticamente al desbloquearse. 

Todas las habilidades activas gastan [maná](#stats).

|Rama| Activa| Pasiva| Activa|
|-|-|-|-|
|Clon| Parálisis| Reflejo| Autodestrucción|
|Combate| Golpe fuerte| Invencible| Torbellino| 
|Precisión| Perforación| Pistolero raudo| Rebote|   

Cada vez que el jugador mate a un enemigo conseguirá [puntos de hazaña](#puntos_h) que puede invertir en tres ramas.

- **Rama clon:** por defecto, se tiene una habilidad que se tiene desde el principio del juego. Al ejecutar esta habilidad se invoca a ún fantasma inmóvil que atrae a los enemigos (como señuelo). Es la rama que se centra en la mejora del fantasma. 
    - **Liberación I:** ataca con los stats al 50% del jugador
    - **Autodestrucción:** inflige una cantidad concreta de daño a los enemigos dentro del área de efecto. Tras ello, el fantasma desaparece. 
    - **Liberación II:** ataca con lo stats al 100% del jugador.

- **Rama combate:** se centra en el combate cuerpo a cuerpo.
    - **Golpe fuerte:** carga daño al siguiente ataque básico.
    - <a name = "invencible"></a>**Invencible:** aumenta el [daño](#stats) y el [crítico](#stats) del jugador de manera permanente.
    - **Torbellino:** realiza un ataque circular infligiendo daño a los enemigos que se encuentren cerca.

- **Rama precisión:** se centra en el combate a distancia.
    - **Perforación:** el siguiente disparo con el arma a distancia atraviesa unidades infligiendo daño a todos los enemigos que haya en el recorrido de la bala.
    - <a name = "pistolero"></a>**Pistolero raudo:** aumenta la [cadencia](#stats) de disparo del jugador de manera permanente.
    - **Rebote:** durante un tiempo los disparos rebotan un número limitado de veces entre los enemigos cercanos, si no hay se acaba el rebote del proyectil.

#### <a name = "shop"></a>2.2.10.- Tienda
Es la zona del [barco](#items) en la que se pueden comprar diversos [objetos](#items) en función de la última isla desbloqueada, de manera que los objetos se actualicen cada vez que se desbloquee una nueva isla. Además, todos los objetos del juego se pueden vender a cambio de oro.

- **Oro:** el oro se consigue matando enemigos y mediante [cofres](#chest). Se usa para poder comprar [objetos](#items) en la tienda.

## 3.-Contenido
### 3.1.- Historia
Este es el comienzo de una legendaria pirata que dejó su huella el mundo tras años y años de saqueos, pillajes y violencia desmedida. Era una joven muchacha cuando encontró su primer tesoro, el comienzo de todo. Además de recibir un gran botín de armas y oro, encontró un mapa que la llevaría hasta su primera gran aventura, pero lo más importante que consiguió es un anillo misterioso. Sin saber para qué servía, lo probó pensando en él como no más que una baratija, sin embargo, empezó a oír voces en su cabeza, incomprensibles, y al cabo de unos segundos apareció una sombra, un figura, que copiaba su forma; un döppleganger. Asustada tras lo sucedido, se lo quitó del dedo, pero motivada por la misteriosa naturaleza del espectro decidió volver a ponérselo. Empezó a descubrir los poderes de su doble, y conforme lo hacía surgían en su mente pensamientos de grandeza y poder, tal vez no desencaminados. Así pues, gracias al oro del botín, decidió comprarse un barco para ir en busca del tesoro marcado en el mapa, aunque incompleto. Al vendedor del barco, un viejo erudito y curtido en mil batallas, le llama la atención la joven pirata y la convence para que lo deje viajar con ella; al fin y al cabo podría resultar útil que un experto en barcos forme parte de la tripulación. Éste también sugiere la busca de algún que otro camarada con el objetivo de lograr sus fines.

Tras unos días de búsqueda, encontró por las calles de la ciudad a una vendedora ambulante que llama su atención. Pese a no tener mucho éxito en sus ventas por la zona debido al "cuestionable" origen de su mercancía, parecía una persona capaz y ruda que podría servir en su aventura. Unas cervezas más tarde, y debido a que la mayor parte de su clientela son piratas y en alta mar puede que sus servicios fueran más agradecidos, acepta a unirse a la tripulación, pero deja clara una cosa: a pesar de tener una capitana, ella también tendría que pagar por sus productos porque "los negocios son negocios".

El viejo y la mercader parecían ya suficientes personas para navegar un barco, y con el anillo la capitana estaba segura de que no había campo de batalla que no pudiera conquistar, así que decidió embarcarse en su aventura.

Tras unos días llegaron a la isla marcada en el trozo del mapa. Ni esta ni ninguna de las islas visibles del archipiélago aparecen en ningún mapa que nadie en el barco haya visto. Esto, junto a la peculiar geografía de esta isla, le permite especular sobre su historia. El viejo no conocía de primera mano la isla caribeña, pero había leído y oído sobre ella. Se lleva siglos hablando de la leyenda de un capitán infame conocido por su tremenda riqueza, saqueos, sádica violencia y brutales carnicerías y masacres llamado Cleón, quien mató a cada cartógrafo que conociera el archipiélago donde se encontrara su base y quemó cada mapa que lo tuviera dibujado. Para cuando el pirata murió ya nadie conocía la existencia de estas islas más allá de una leyenda que describe sus costas abruptas y plagadas de acantilados, justo como estas. Dejando a la limitada tripulación a cargo de proteger el barco, la capitana desembarca sola, valiente y poseedora de un nuevo poderosa habilidad. Tras una serie de mortales desafíos, la pirata llega hasta el punto marcado solo para encontrar a una criatura enorme, y aunque vegetal temible, que se interponía entre la ella y su tesoro. Tras un breve pero intenso combate, la planta es derrotada y se descubre el tesoro. Ansiosa e impaciente abre el cofre del merecido botín, solo para encontrar otro trozo faltante del mapa incompleto que ya tenía. Aunque decepcionada, con un nuevo objetivo renueva su moral y decide ir al siguiente punto marcado. 

La segunda isla, pese a pertenecer al mismo archipiélago que la isla anterior, era distinta, más lúgubre y siniestra, estremecedora e intimidante. El camarada de la capitana le había hablado de la leyenda del capitán Cleón, pero nunca contó su final. Siglos atrás, cuando la leyenda del infame pirata se estaba formando, existían ciertas personas con un profundo conocimiento sobre fuerzas que a día de hoy solo existen en canciones, cuentos y leyendas. Cleón y sus seguidores representaban tal amenaza y temor que se recurrió al contrato de un cazarrecompensas con estos poderes para remediar la situación. El problema con estas habilidades es que eran peligrosas, tanto para el enemigo como para el usuario y todo aquel en su influencia. Por este motivo se rechazaba y perseguía a sus usuarios, por lo que era una medida drástica que el estado contratara a uno. El cazarrecompensas logró encontrar la ubicación de la isla, probablemente gracias a algún marinero que todavía conocía esa zona del mar, y a partir de aquí el final de la historia depende de quién la esté contando. El más frecuente es que Magordito se alza victorioso ante el cazarrecompensas, pero este antes de ser desmembrado por el pirata invocó todas su fuerzas con el fin de maldecir toda la isla como venganza, maldiciéndose a sí mismo en el proceso, para hacerles sufrir por toda la eternidad en una isla olvidada.


El desarrollo de los eventos fue similar al de la isla anterior, pero esta vez con amenazas mayores, como lobos, esqueletos vivientes, bombas y explosiones. Tras luchas de vida o muerte la capitana llegó a lo más profundo de la isla, encontrado en el corazón de la misma al poderoso cazarrecompensas que encantó las tierras y maldijo a sus habitantes antes de morir, condenándose a sí mismo en el proceso: Magordito.

Con gran temple, destreza en armas blancas y de fuego y un poder cada vez más controlado, logró vencer al cazarrecompensas, llegando así al cofre del tesoro. En él encontró nada menos que otro fragmento del mapa, Con la diferencia de que esta vez el mapa se completaba, guiando a la pirata a la última isla del archipiélago.

La última isla era distinta a las demás. A diferencia de las anteriores, que a parte de ser mayores en tamaño y que mostraban formas de vida naturales o aborrecibles, esta parecía desolada y hueca. No tardó mucho la pirata en explorarla, encontrando en lo más profundo al enemigo más temible y peligroso de su aventura hasta el momento: el capitán Cleón, delante suya en carne y hueso, o lo que quedaba de ellas tras la maldición del cazarrecompensas y tantos años de decadencia. El espíritu de Cleón parecía haber decidido pasar la eternidad en soledad, acompañado solo por su tesoro. No solo por defender su botín, sino también por el placer de escuchar una vez más la dulce agonía de sus enemigos, Cleón se lanza a la batalla. Una vez acabado el duelo, y el temible pirata derrotado, la capitana se alza vencedora reclamando así el infame botín de Cleón y forjando así su propia leyenda.

#### <a name = "personajes"></a>3.1.1.- Personajes
- **Protagonista:** <!--Definir.-->

- **Mercader:** polizona del barco. En la ciudad el negocio no le fue bien dado el cuestionable origen de sus productos, así que pensó que piratas podrían apreciar más sus buenos precios. Se encarga de la [tienda](#shop).

- **El viejo:** es el que te vendió el barco y te hizo buen precio si a cambio le dejabas ver mundo en él. Cada vez que descubres una isla te habla sobre la historia de la misma y sobre algún ítem raro en cada una de ellas.

- **La cartógrafa:** Aparece en la isla del boss final. Se encuentra antes de la arena del boss final, tumbada en el suelo, herida. Vino al archipiélago con la intención de encontrar la isla donde se encontraba la base del infame capitán pirata ___, para así añadir esa isla y las cercanas que no constaran en el mapa para ganar una pequeña fortuna. Fue dibujando cada isla en su libreta pero cuando llegó a está algo la atacó que la dejó hecha un cristo.

- <a name = "cocinero"></a>**El cocinero:** aparece en la primera isla al principio del nivel. Trabajaba de chef en un crucero de lujo hasta que lo ascendieron a “cocinero prescindible ejecutivo” y lo dejaron en la isla. Al completar [_Gallego en problemas_](#quest_coc) se une a la tripulación.

- <a name = "ghost"></a>**Morty, el fantasma:** Aparece en la [isla fantasmal](#fantasmal) Es un tío tan chill que casi no lo maldicen pero pensaron que maldecir a todos menos uno estaba feo. Murió siendo un pirata pero solo porque sus padres lo presionaron para serlo. Promete recompensas a cambio de hacerle un favor, completando [_Papeles siniestros_](#quest_morty), además de unirse a la tripulación.

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

<a name = "carbie"></a>**Caribe:**  

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
Es la instancia de reinicio donde el jugador revive cuando [pierde](#perder) y en la que el jugador podrá hacer uso del [alijo](#stash), acceder al [mapa](#mapa) mediante la interacción con el timón y guardar partida interactuando con la puerta de la habitación, mostrando la [interfaz](#puerta) correspondiente. Además se podrán encontrar diversos [personajes](#personajes) en el barco, así como la [tienda](#shop). Cada vez que el jugador entre en el barco se restablecerá toda la [vida](#stats) y se restablecerán los enemigos [reiniciables](#respawn).

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