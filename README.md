# ⚔️ FinalQuest 1

## 📌 Descripción:

**FinalQuest 1** es un juego de rol (RPG) por turnos con estilo clásico, en el que el jugador controla a un héroe que avanza de forma lineal a través de distintos escenarios. A lo largo del recorrido, deberá enfrentarse a enemigos, encontrar tiendas y atravesar eventos aleatorios, gestionando de manera eficiente su inventario y recursos.

El objetivo principal es alcanzar el enfrentamiento contra el jefe final, tomando decisiones estratégicas durante cada combate, compra o uso de ítems para aumentar las probabilidades de éxito. Las batallas por turnos exigen planificación táctica, mientras que la correcta administración del oro y la selección de equipamiento son clave para progresar.

Durante la aventura, el jugador podrá mejorar su equipo, adquirir armas, armaduras y consumibles en tiendas, y participar en eventos especiales que otorgan bonificaciones o ítems únicos. Cada elección realizada a lo largo del juego tendrá un impacto directo en la preparación y desempeño del héroe en el combate final.

¿Estás listo para sobrevivir y vencer al jefe final?

## ⚙️ Como compilar y ejecutar:

Este programa fue desarrollado integramente en el lenguaje de **Programacion C** y puede implementarse facilmente usando **Visual Studio Code** junto con una extensión para C/C++, como C/C++ Extension Pack de Microsoft.

Para comenzar a trabajar con el sistema en tu equipo local, asegúrate de tener lo siguiente:

> #### ✅ Requisitos Previos

> - Tener instalado [Visual Studio Code](https://code.visualstudio.com/)
> - Instalar la extensión [C/C++ (Microsoft)](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
> - Contar con un compilador de C (como **gcc**). 
>   En Windows, se recomienda instalar [MinGW](https://www.mingw-w64.org/)

### 🚀 Pasos para Compilar y Ejecutar:

1. Descarga y descomprime el archivo `.zip` en tu entorno de trabajo.
2. Abre el proyecto en **Visual Studio Code**
    - Inicia _Visual Studio Code_.
    - Selecciona `Archivo > Abrir carpeta...` y selecciona la carpeta donde descomprimiste el proyecto _(Paso 1)_
3. Compila y Ejecuta el codigo
    - Abre el archivo principal (Por ejemplo, `tarea3.c`)
    - Abre la terminal integrada (`Terminal > Nueva Terminal`)
    - En la terminal *(De preferencia Git Bash)*, compila el programa con el siguiente comando:
        ```
        gcc -o proyecto tdas/*.c game/*.c main.c -Igame -Itdas -Wno-unused-result -Werror
        ```
    - Una vez compilado, puedes ejecutar el programa en la misma terminal, con:
        ```
        ./proyecto
        ```

## 🧠 Funcionalidades:

### ✅ Funcionando Correctamente

- 📜 Avance lineal por escenarios de dificultad progresiva.
- ⚔️ Sistema de combate por turnos.
- 🛒 Tiendas para comprar ítems.
- 🎲 Eventos aleatorios.
- 🎒 Gestión de inventario.
- 💰 Administración de oro y compras estratégicas.
- 👑 Enfrentamiento contra el jefe final.

> #### ⚠️ Sin Problemas Conocidos

## Ejemplo de Uso:

### 👾 FinalQuest 1:
#### 📌 Comienza eligiendo la clase de tu héroe
Antes de comenzar a jugar FinalQuest 1, deberás elegir cuidadosamente la clase de tu héroe. Cada clase tiene características únicas que influirán en tu forma de combatir y avanzar en el juego. Esta decisión será clave para enfrentar a los distintos enemigos y alcanzar al jefe final.
``` 
╔══════════════════════════════════════╗
║            FinalQuest 1              ║
╚══════════════════════════════════════╝

╔══════════════════════════════════════╗
║      BIENVENIDO A TU AVENTURA        ║
╟──────────────────────────────────────╢
║ ELIGE TU CLASE:                      ║
║ 1. Guerrero                          ║
║ 2. Tanque                            ║
║ 3. Asesino                           ║
╚══════════════════════════════════════╝
Ingresa el número de tu clase: _
```

> El jugador tendrá la posibilidad de elegir entre tres clases distintas para su héroe. Cada una presenta estadísticas únicas que influyen directamente en el rendimiento durante los combates por turnos. Por lo tanto, la elección de clase representa un aspecto clave para el desarrollo y la estrategia del juego.


#### 🎮 Cargando aventura.
Una vez seleccionada la clase del héroe, el sistema procederá a cargar automáticamente los datos necesarios para iniciar la partida.
```
╔════════════════════════════════════════════╗
║              FinalQuest 1                  ║
╚════════════════════════════════════════════╝

╔════════════════════════════════════════════╗
║        ¡Héroe creado exitosamente!         ║
╠════════════════════════════════════════════╣
║ Clase: Guerrero                            ║
║ Vida: 100   Ataque: 10    Defensa: 5       ║
║ Oro inicial: 200                           ║
╚════════════════════════════════════════════╝
Cargando datos del juego [■■■■■] 100%
══════════════════════════════════════════════
¡Has recibido tu equipo inicial!
──────────────────────────────────────────────
- Espada de Aprendiz (+12 Atk, equipada)      
- Armadura Acolchada (+6 Def, equipada)
- Pocion de Novato (añadido al inventario)
- Amuleto de Suerte (añadido al inventario)
══════════════════════════════════════════════
Los items se equiparan automaticamente.
Presione Enter para continuar...       
```
> El programa se encargará de cargar automáticamente los archivos CSV que contienen la información necesaria para el desarrollo del juego, incluyendo los datos de enemigos, escenarios, ítems iniciales según la clase seleccionada e ítems disponibles en las tiendas. La clase elegida por el jugador determinará tanto los ítems iniciales como las estadísticas del personaje. Este proceso se realiza de manera automática al iniciar la partida, garantizando una experiencia personalizada desde el comienzo. 

#### 🎮 Inicio del juego.
Una vez que los datos del juego se hayan cargado por completo, se mostrará la pantalla de portada junto con una breve historia para contextualizar al jugador.
```
╔─────────────────────────────────────────────────────╗

▒█▀▀▀ ░▀░ █▀▀▄ █▀▀█ █░░ ▒█▀▀█ █░░█ █▀▀ █▀▀ ▀▀█▀▀   ▄█░ 
▒█▀▀▀ ▀█▀ █░░█ █▄▄█ █░░ ▒█░▒█ █░░█ █▀▀ ▀▀█ ░░█░░   ░█░ 
▒█░░░ ▀▀▀ ▀░░▀ ▀░░▀ ▀▀▀ ░▀▀█▄ ░▀▀▀ ▀▀▀ ▀▀▀ ░░▀░░   ▄█▄ 

           __...--~~~~~-._   _.-~~~~~--...__
         //      Aqui     `V'      Tu       \\
        //     Empieza     |     Aventura    \\        
       //__...--~~~~~~-._  |  _.-~~~~~~--...__\\       
      //__.....----~~~~._\ | /_.~~~~----.....__\\      
     ====================\\|//====================     
                         `---`
╔─────────────────────────────────────────────────────╗
  Despiertas en un mundo envuelto en sombras. Una 
  marca arde en tu mano, pero no recuerdas su origen. 
  Voces antiguas susurran tu nombre, y un peso 
  invisible te acompana. Eres el Heraldo, destinado 
  a enfrentar la Oscuridad. Podras descubrir la 
  verdad antes de que todo se repita una vez mas?
╚─────────────────────────────────────────────────────╝
Presione Enter para continuar...
```


#### 📊 Resumen detallado del escenario y del estado del jugador
A continuación, se presentará en pantalla un resumen completo que incluye la información del escenario actual y el estado del jugador, mostrando datos relevantes para el progreso de la partida.
```
╔════════════════════════════════════════════╗
║              FinalQuest 1                  ║
╚════════════════════════════════════════════╝

╔════════════════════════════════════════════╗
║ ESCENARIO: El Abismo Olvidado              ║
╟────────────────────────────────────────────╢
║ Un lugar profundo y aislado, donde el eco  ║
║ de viejas leyendas resuena entre las       ║
║ piedras y criaturas olvidadas se ocultan   ║
║ en las sombras.                            ║
╚════════════════════════════════════════════╝

╔══════════════════════════════════════════════════════════════╗
║ RESUMEN DEL JUGADOR                                          ║
╟──────────────────────────────────────────────────────────────╢
║ Clase: Guerrero             Enemigos derrotados: 0           ║
║ Vida:  100/100   Atk: 22    Def: 11    Oro: 200              ║
║ Arma equipada: Espada de Aprendiz       (+12 Atk)            ║
║ Armadura equipada: Armadura Acolchada   (+ 6 Def)            ║
╟──────────────────────────────────────────────────────────────╢
║ Slots disponibles de inventario: 8                           ║
╚══════════════════════════════════════════════════════════════╝
Presione Enter para continuar...
```
> Esta pantalla se mostrará cada 9 eventos aleatorios (como batallas, comerciantes, bonus o fragmentos de la historia), presentando un nuevo escenario con una dificultad distinta. Después de repetir este ciclo tres veces, y al llegar al último evento, el jugador deberá enfrentarse al jefe final.

#### 🎲 Eventos Aleatorios.
Durante el transcurso del juego se presentarán eventos aleatorios que afectarán el desarrollo de la partida. Estos eventos pueden ser de cuatro tipos: combates, comerciantes, bonus o fragmentos de historia.
##### 🔪 Evento combate:
Cuando ocurra un evento de combate, se mostrará un mensaje destacado que alerta al jugador sobre la aparición inminente de un enemigo:
```
╔══════════════════════════════════════════════════════════════╗
║                  ¡ENEMIGO INESPERADO APARECE!                ║
╠══════════════════════════════════════════════════════════════╣
║        ¡Prepárate para la batalla, valiente aventurero!      ║
╚══════════════════════════════════════════════════════════════╝
```
A continuación, se desplegará el estado actual del combate, mostrando la información relevante tanto del jugador como del enemigo:
```
╔══════════════════════════════════════════════════════════════╗
║ ¡COMBATE INICIADO!   Guerrero vs Rata Gigante                ║
╚══════════════════════════════════════════════════════════════╝
╔═══════════════════════════════════════════════╗
║           --- ESTADO DE COMBATE ---           ║
╠═══════════════════════════════════════════════╣
  Guerrero HP: 100/100  (Atk: 22, Def: 11)
  Rata Gigante HP: 40
╚═══════════════════════════════════════════════╝
⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨
⇨  ¡Tu turno!
⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨
  [1] Atacar
  [2] Usar Ítem (Inventario)
──────────────────────────────────────────────────────────────
Tu elección: _
```
> El jugador dispondrá de dos opciones principales durante el combate: atacar o usar ítems. El uso estratégico de ítems puede proporcionar ventajas significativas, tales como aumentar el daño, mejorar la defensa o recuperar vida, agregando profundidad táctica a las batallas.

Si el jugador decide atacar, se mostrará el siguiente mensaje en pantalla:
```
╔═══════════════════════════════════════════════╗
║           --- ESTADO DE COMBATE ---           ║
╠═══════════════════════════════════════════════╣
  Guerrero HP: 100/100  (Atk: 22, Def: 11)
  Rata Gigante HP: 40
╚═══════════════════════════════════════════════╝
⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨
⇨  ¡Tu turno!
⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨
  [1] Atacar
  [2] Usar Ítem (Inventario)
──────────────────────────────────────────────────────────────
Tu elección: 1
» Guerrero ataca a Rata Gigante y le inflige 22 de daño. «    
──────────────────────────────────────────────────────────────
⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦
⇦  Es el turno de Rata Gigante!
⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇦⇦⇦⇦⇦⇦⇦⇦
« Rata Gigante ataca a Guerrero y le inflige 4 de daño. »
──────────────────────────────────────────────────────────────
Presione Enter para continuar...
```
En cambio, si el jugador opta por usar un ítem desde el inventario, se mostrará la siguiente secuencia:
```
╔═══════════════════════════════════════════════╗
║           --- ESTADO DE COMBATE ---           ║
╠═══════════════════════════════════════════════╣
  Guerrero HP: 96/100  (Atk: 22, Def: 11)
  Rata Gigante HP: 18
╚═══════════════════════════════════════════════╝
⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨
⇨  ¡Tu turno!
⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨
  [1] Atacar
  [2] Usar Ítem (Inventario)
──────────────────────────────────────────────────────────────
Tu elección: 2
╔═══════════════════════════════════════════════╗
║              --- INVENTARIO ---               ║
╠═══════════════════════════════════════════════╣
 1. Pocion de Novato (Cura: 50)
 2. Amuleto de Suerte (Cura: 10, Atk+: 50, Def+: 10, Duración: 1)
╚═══════════════════════════════════════════════╝
Elige un item a usar (0 para cancelar):
```
> Estos dos caminos permiten al jugador tomar decisiones estratégicas durante el combate. Atacar es directo y simple, mientras que el uso de ítems puede modificar significativamente las condiciones del enfrentamiento, ofreciendo ventajas temporales pero cruciales en momentos clave.

Si el jugador logra vencer al enemigo, se mostrará el siguiente mensaje en pantalla:
```
═══════════════════════════════════════════════════════════════
🏅  Rata Gigante ha caído en combate. ¡Recompensa: 153 oro!
═══════════════════════════════════════════════════════════════
╔──────────────────────────────────────────────────────────────╗
  Las paginas estan en blanco, pero sientes que cuentan 
  tu historia.
╚──────────────────────────────────────────────────────────────╝
--- FIN DE EVENTO ---
Pasos restantes: 5
Presione Enter para continuar...
```
En caso contrario, si el jugador es derrotado durante el combate:
```
═══════════════════════════════════════════════════════════════
  ☠️  Has sido derrotado. ¿Qué deseas hacer?
═══════════════════════════════════════════════════════════════
  [1] Volver a jugar desde el inicio
  [2] Salir del juego
Tu elección:
```
> Estos mensajes marcan un punto de inflexión en la experiencia del jugador. La victoria permite avanzar y obtener recompensas, mientras que la derrota ofrece opciones claras para reiniciar o salir, manteniendo una dinámica justa y coherente con la naturaleza de los juegos de rol por turnos.
##### 💰 Evento Comerciante:
Cuando ocurra un evento relacionado con un comerciante, se mostrará el siguiente mensaje en pantalla:
```
Un mercader aparece en tu camino...
```
Luego, se desplegará la interfaz de la tienda con los ítems disponibles y el oro actual del jugador:
```
╔════════════════════════════════════════════════════════════╗
║ Bienvenido a la tienda! Tienes 200   de oro                ║
╚════════════════════════════════════════════════════════════╝
╔════════════════════════════════════════════════════════════════════════════════╗
   Items disponibles:
   [9] Amuleto de Defensa   (Comun ) - Costo: 60   oro. Defensa Boost: +25 Def por 3 turnos. 
   [4] Armadura Ligera      (Comun ) - Costo: 60   oro. Defensa: 18 .
╚════════════════════════════════════════════════════════════════════════════════╝
╔════════════════════════════════════════════════════════════╗
║                  ¿Qué deseas hacer?                        ║
╟────────────────────────────────────────────────────────────╢
║ 1. Comprar Item                                            ║
║ 2. Salir de la tienda                                      ║
╚════════════════════════════════════════════════════════════╝
Tu eleccion:
```
> Durante esta fase, el jugador puede adquirir ítems utilizando el oro obtenido en combates. El sistema verificará automáticamente si el nuevo ítem ofrece mejores estadísticas que el actualmente equipado. En caso contrario, se notificará al jugador que el ítem es inferior y no será añadido al inventario. Esta mecánica busca fomentar decisiones estratégicas y evitar compras innecesarias, manteniendo el equilibrio en el progreso del juego.

Cuando el jugador decide comprar un ítem, se muestra la siguiente secuencia en pantalla:
```
╔════════════════════════════════════════════════════════════╗
║ Bienvenido a la tienda! Tienes 200   de oro                ║
╚════════════════════════════════════════════════════════════╝
╔════════════════════════════════════════════════════════════════════════════════╗
   Items disponibles:
   [9] Amuleto de Defensa   (Comun ) - Costo: 60   oro. Defensa Boost: +25 Def por 3 turnos. 
   [4] Armadura Ligera      (Comun ) - Costo: 60   oro. Defensa: 18 .
╚════════════════════════════════════════════════════════════════════════════════╝
╔════════════════════════════════════════════════════════════╗
║                  ¿Qué deseas hacer?                        ║
╟────────────────────────────────────────────────────────────╢
║ 1. Comprar Item                                            ║
║ 2. Salir de la tienda                                      ║
╚════════════════════════════════════════════════════════════╝
Tu eleccion: 1
Ingresa el ID del item a comprar: 9
Amuleto de Defensa ha sido añadido al inventario.
¡Compra exitosa!
Presione Enter para continuar...
```
Si la tienda ya no dispone de ítems en venta, el sistema mostrará lo siguiente:
```
╔════════════════════════════════════════════════════════════════════════════════╗
   Items disponibles:
   (No hay ítems en venta en este momento.)
╚════════════════════════════════════════════════════════════════════════════════╝
╔════════════════════════════════════════════════════════════╗
║                  No hay ítems disponibles.                 ║
╠════════════════════════════════════════════════════════════╣
║ 1. Salir de la tienda                                      ║
╚════════════════════════════════════════════════════════════╝
Tu eleccion: 1
Gracias por tu visita! Vuelve pronto.
╔──────────────────────────────────────────────────────────────╗
  Los Heraldos luchan juntos, pero uno cae en la sombra.
╚──────────────────────────────────────────────────────────────╝
--- FIN DE EVENTO ---
Pasos restantes: 5
Presione Enter para continuar...
```
> Esta mecánica garantiza una experiencia de compra dinámica y controlada. El sistema valida la compra, descuenta el oro correspondiente y actualiza el inventario del jugador. Además, si el stock de ítems se agota, se informa al jugador, evitando acciones innecesarias y permitiendo continuar con el avance del juego. Esto refuerza la inmersión y mantiene el flujo narrativo en equilibrio.

##### ✨ Evento Bonus:
Cuando ocurra un evento de tipo bonus, se mostrará el siguiente mensaje en pantalla:
```
╔══════════════════════════════════════════════════════════════╗
            ¡Has descubierto algo interesante!
╚══════════════════════════════════════════════════════════════╝
   _________
  /        /\
 /        /  \
/________/____\
|        |    |
|        | 💰 |
|________|____|

Buscando...
```
Durante este evento, el jugador podrá encontrar objetos valiosos que mejoran su equipamiento o le otorgan alguna ventaja adicional. Un ejemplo de lo que puede suceder es el siguiente:
```
¡Has cambiado a una armadura mejor!
Has equipado Coraza Tiempo Oscuro. (+70 Def)
Encontraste un Coraza Tiempo Oscuro!        
╔──────────────────────────────────────────────────────────────╗
  Forman un circulo antiguo. Al pisarlas, escuchas un susurro: 
  'El ciclo continua'.
╚──────────────────────────────────────────────────────────────╝
Presione Enter para continuar...
```
> Estos eventos representan momentos de descubrimiento dentro del juego, brindando recompensas inesperadas al jugador. Las mejoras obtenidas pueden marcar una diferencia clave en combates futuros, por lo que explorar y aprovechar estos bonus aporta profundidad estratégica a la experiencia.

##### 📖 Fragmentos de historia:
Cuando ocurra un evento relacionado con fragmentos de historia, se mostrará el siguiente mensaje en pantalla:
```
Recuerdos vienen hacia ti...
```
A continuación, se desplegará uno de los textos narrativos disponibles, seleccionados de forma aleatoria. Un ejemplo de esto es:
```
╔──────────────────────────────────────────────────────────────╗
  Un ser de piedra te observa. 'Solo los dignos recordaran', 
  dice. Tras la puerta, ves simbolos y nombres de Heraldos 
  olvidados. El guardian te permite pasar, pero advierte: 
  recordar tiene un precio. Sientes que cada paso te acerca 
  a una revelacion dolorosa.
╚──────────────────────────────────────────────────────────────╝
```
> Estos fragmentos aportan profundidad al universo del juego y ofrecen una experiencia narrativa más rica. No afectan directamente al combate o inventario, pero contribuyen al desarrollo del trasfondo y la ambientación, revelando partes del misterio que rodea a los Heraldos y su destino.

##### 💀 Evento Jefe Final
cuando ocurra el evento del jefe final que es cuando llegamos al final del recorrido del mapa se mostrara lo siguiente:
```
╔═══════════════════════════════════════════════════════════════════════════╗
║                                                                           ║
║                          ¡BOSS FINAL APARECE!                             ║
║                                                                           ║
╚═══════════════════════════════════════════════════════════════════════════╝

                            ░░░░░░░░░░░░░░░░░░░░░░░░░░
                          ░░██████████████████████░░
                        ░░████████████████████████░░
                      ░░██████████████████████████░░
                      ░░██████████████████████████░░
                      ░░██████████████████████████░░
                      ░░██████░░░░░░░░░░░░██████░░
                      ░░██████░░  ████  ░░██████░░
                      ░░██████░░  ████  ░░██████░░
                      ░░██████░░░░░░░░░░░░██████░░
                      ░░██████████████████████████░░
                      ░░██████████████████████████░░
                      ░░██████████░░░░██████████░░
                      ░░██████████░░░░██████████░░
                      ░░██████████████████████████░░
                        ░░████████████████████░░
                          ░░██████████████░░

    ╔══════════════════════════════════════════════════════════════════╗
    ║   "¡Has llegado hasta aquí, mortal! Pero tu viaje termina aquí." ║
    ║              "¡Prepárate para enfrentar tu destino!"             ║
    ╚══════════════════════════════════════════════════════════════════╝

La oscuridad se intensifica...
¡EL COMBATE FINAL COMIENZA!
Presione Enter para continuar...
```
para luego mostrar
```
╔═══════════════════════════════════════════════════════════════╗
║              ÚLTIMA OPORTUNIDAD DE PREPARACIÓN                ║
╠═══════════════════════════════════════════════════════════════╣
║  ¿Quieres usar algún ítem de tu inventario antes del combate? ║
║                    [1] Sí  [2] No, estoy listo                ║
╚═══════════════════════════════════════════════════════════════╝
Tu elección:
```
si el jugador pone que si se mostrara:
```
xd hay que arreglarlo
```
si no: 
```
╔═══════════════════════════════════════════════════════════════╗
║                     ESTADÍSTICAS FINALES                      ║
╠═══════════════════════════════════════════════════════════════╣
║  Héroe: Asesino               Enemigos Derrotados: 7          ║
║  HP: 999/999  ATK: 1029  DEF: 1001  Oro: 3339                 ║
╚═══════════════════════════════════════════════════════════════╝

¡Que el destino esté de tu lado!...
¡El Devorador de Mundos despierta con toda su furia!

Presione Enter para continuar...
```
luego mostrara el combate final con las distintas fases del jefe
```
╔═══════════════════════════════════════════════╗
║           COMBATE FINAL - FASE 1              ║
╠═══════════════════════════════════════════════╣
  Asesino HP: 999/999  (Atk: 1029, Def: 1001)
  El Devorador de Mundos HP: 666/666 (Fase 1)
╚═══════════════════════════════════════════════╝
⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨
⇨  ¡Tu turno!
⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨
  [1] Atacar
  [2] Usar Ítem (Inventario)
──────────────────────────────────────────────────────────────
Tu elección: 
```

```
```

```
```

```
```
## Contribuciones

### Elias Manríquez
- **Desarrollo de la función principal del juego**: Implementó la lógica central de la aplicación, incluyendo la carga del laberinto desde un archivo CSV y la ejecución de la partida tanto en modo solitario como multijugador.

- **Implementación de funciones clave**: Desarrolló funciones esenciales como avanzar entre escenarios, recoger y descartar ítems, reiniciar la partida, y gestionar el tiempo y el inventario.

- **Documentación básica**: Añadió comentarios al código fuente y contribuyó a la elaboración inicial del `README.md`.

> Auto-evaluación: 5/5 (Aporte Excelente)

### Maximiliano Rodríguez
- **Diseño del menú principal**: Creó la estructura de navegación del menú principal, facilitando el acceso a las distintas funcionalidades del juego.

- **Manejo de errores y validaciones**: Implementó validaciones de entrada del usuario y control de errores para evitar fallos durante la ejecución del juego.

- **Mejoras en la experiencia de usuario**: Refinó la interacción del jugador en la interfaz de texto, con mensajes más claros y un flujo de juego más intuitivo.

- **Redacción final del README**: Redactó y organizó el contenido del archivo `README.md`, documentando detalladamente el funcionamiento, modos de juego y estructura técnica del programa.

> Auto-evaluación: 5/5 (Aporte excelente)

### Lukas Navarro
- **Diseño del menú principal**: Creó la estructura de navegación del menú principal, facilitando el acceso a las distintas funcionalidades del juego.

- **Manejo de errores y validaciones**: Implementó validaciones de entrada del usuario y control de errores para evitar fallos durante la ejecución del juego.

- **Mejoras en la experiencia de usuario**: Refinó la interacción del jugador en la interfaz de texto, con mensajes más claros y un flujo de juego más intuitivo.

- **Redacción final del README**: Redactó y organizó el contenido del archivo `README.md`, documentando detalladamente el funcionamiento, modos de juego y estructura técnica del programa.

> Auto-evaluación: 5/5 (Aporte excelente)