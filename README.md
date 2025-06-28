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
    - Abre el archivo principal (Por ejemplo, `main.c`)
    - Abre la terminal integrada (`Terminal > Nueva Terminal`)
    - En la terminal *(De preferencia Git Bash)*, compila el programa con el siguiente comando:
        ```
        gcc -o game tdas/*.c game/*.c main.c -Igame -Itdas -Wno-unused-result -Werror
        ```
    - Una vez compilado, puedes ejecutar el programa en la misma terminal, con:
        ```
        ./game
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
> Si el usuario presiona muchas veces Enter, el programa los acumula y eso hace que se pierdan turnos o el juego avance rapido. Para manejar esto, se agrego una logica de juego para saltar animaciones con los Enter para no acumularlos.

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
> Esta pantalla se mostrará cada 9 eventos aleatorios o pasos (como batallas, comerciantes, bonus o fragmentos de la historia), presentando un nuevo escenario con una dificultad distinta. Después de repetir este ciclo tres veces, y al llegar al último evento, el jugador deberá enfrentarse al jefe final.

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
 2. Amuleto de Suerte (Atk+: 50, Def+: 10, Duración: 1)
╚═══════════════════════════════════════════════╝
Elige un item a usar (0 para cancelar): _
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
En caso contrario, si el jugador es derrotado durante el combate, se limpiara la pantalla y mostrara:
```
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠖⠶⣦⣄⡀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡶⠤⣤⣀⡀⢠⠏⠀⡄⠀⢹⣿⣷⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡟⣠⠀⠀⡉⠹⠏⠀⠀⠙⣆⣿⣿⠋⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣿⣀⠘⠳⡄⠘⡜⣄⡘⡜⡄⢌⢿⠛⠶⢤⣄⡀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠛⠶⢤⡔⠹⡜⣜⣞⣜⣎⢮⢣⡀⣰⣿⣿⠇⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠁⠱⡹⣼⣾⣾⣌⣧⢳⣳⣯⣿⠏⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⣼⠇⠀⠀⠐⣿⣿⡟⠈⠉⠛⠿⠾⠏⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠛⠉⠉⠉⠉⠉⠉⠉⠉⠙⠻⠷⢶⣶⣦⣴⣟⠀⠀⠀⣾⢧⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣼⣧⣀⣟⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠛⠿⢿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠁⠀⠀⠈⠿⣁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⢷⣿⡻⢶⣤⣀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠁⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⣿⣦⡉⠛⢷⣦⣄⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣴⠋⠹⣿⣯⢙⠺⣿⡷⡄⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⢸⠀⠀⢷⣿⣿⣟⢟⣿⣾⣆⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⠀⠀⠀⠀⢠⣤⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠁⠀⢠⡟⢎⠻⣷⣕⠼⢿⡆
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠃⠀⠀⠀⢀⣾⣾⣿⣿⣦⠀⠀⠀⢠⣄⣀⡀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠃⠈⠓⣌⢻⡳⣼⣧
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠀⠀⠀⠀⢀⣾⣽⣿⣬⣿⣿⠀⠀⢀⡿⢠⣹⠇⠀⠀⣼⣯⢿⣷⣦⡀⠀⠀⠀⠀⠀⢠⣿⠀⠀⢐⢌⠳⣝⣿⡟
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠃⠀⠀⠀⢀⣾⢉⣿⣿⣿⠿⠋⠀⠀⣼⠇⣛⡿⠀⠀⣼⠃⢹⠿⣧⣽⣷⡄⠀⠀⠀⠀⣸⡷⡄⠀⠈⠳⡑⣾⣿⣲⠆⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠇⠀⠀⠀⢀⡞⢀⡟⣿⢹⣷⠀⠀⠀⢠⡏⠀⣿⠃⠀⣸⠇⢡⣿⣿⣏⣬⣾⠃⠀⠀⠀⢀⣿⢄⠙⢄⠀⣀⣼⢿⣟⣿⡇⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡟⠀⠀⠀⠀⢼⣇⡾⠀⣿⡰⣿⠀⠀⠀⡼⠀⣼⠃⠀⢀⡏⠀⣿⡟⠛⠛⠋⠀⠀⠀⠀⠀⢸⠇⠀⠳⣬⣾⣻⣿⣿⣿⣿⡇⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠀⠀⠀⠀⠀⠀⠈⠁⠀⠛⠿⠿⠀⠀⠸⢷⣼⠏⠀⠀⣾⣠⣼⡟⠀⠀⠀⠀⠀⠀⠀⠀⢠⡟⠰⣠⣾⣿⣿⠛⢧⡘⢦⣽⡇⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠋⠛⠿⠁⠀⠀⠀⠀⠀⠀⠀⢀⣾⡇⣾⣿⣿⠉⣀⠑⢄⠙⠦⣿⠁⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⡾⠋⣻⡛⢻⡇⠀⠱⣌⢷⣄⠱⢤⡏
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⠔⠀⡟⠙⢮⣿⣄⠱⣜⢦⡙⢦⣼⡇
⠀⠀⠀⠀⠀⠀⠀⠀⢠⡟⢿⣇⠀⠀⠀⠀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣄⠠⠟⡀⠀⢰⣧⣀⢌⠻⣿⡧⣌⠣⡉⠲⣿⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣼⠃⠘⠿⠶⣶⡏⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢦⡀⠈⢢⣼⠁⠈⢦⡑⣿⣧⡈⠳⣌⢲⡏⠀
⠀⠀⠀⠀⠀⠀⠀⣰⠇⠈⠢⡀⠀⢻⣗⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⣄⠀⠙⣶⣼⣟⠂⠀⣄⠹⣝⣿⣟⢧⡈⣹⠇⠀
⠀⠀⠀⠀⠀⠀⢰⡟⣄⠀⠀⠈⠢⡘⠻⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠈⠳⣴⡟⢹⣿⢳⣄⣮⣳⣼⣿⡈⠳⣍⡿⠀⠀
⠀⠀⠀⠀⠀⢠⡿⠁⠈⠢⣄⠀⣀⠀⠀⠀⠀⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢢⡀⠓⢄⠸⣷⣯⣧⠘⢯⣻⣿⣟⣇⠙⢄⣸⡇⠀⠀
⠀⠀⠀⠀⠀⣾⠃⠀⠀⠀⠈⠳⣌⠳⢄⡈⠢⡀⠙⠢⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠳⣄⠀⠀⠙⢦⡈⣿⣿⡟⢧⡰⣄⠻⣿⢯⣫⡙⢦⣿⠁⠀⠀
⢀⣠⣤⣤⣼⣏⣀⣤⣤⣤⣤⣀⠈⠁⠀⣁⣦⠬⠶⠶⠾⣦⣤⣄⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⢌⠑⠄⠀⠀⣩⣿⡿⠁⠀⣕⢌⠳⡈⠳⣝⢭⢺⡟⠀⠀⠀
⠉⠁⠀⣀⣰⣯⣀⡀⠀⢠⠟⠉⠉⠉⠿⣧⠀⠀⠀⠀⠀⠀⢹⡌⠳⠄⠑⢦⡀⣀⡴⠖⠒⠻⠶⣵⣄⡁⠀⣿⢿⠉⠳⣔⣜⢮⡳⣝⢦⠘⢦⣿⣃⣀⣀⣀

╔════════════════════════════════════════╗
║ Has sido derrotado. ¿Qué deseas hacer? ║
╟────────────────────────────────────────╢
  [1] Volver a jugar desde el inicio      
  [2] Salir del juego                     
╚════════════════════════════════════════╝

Tu elección: 
```
> La victoria permite avanzar y obtener recompensas, mientras que la derrota ofrece opciones claras para reiniciar o salir.

##### 💰 Evento Comerciante:
Cuando ocurra un evento relacionado con un comerciante, se mostrará el siguiente mensaje en pantalla:
```
    A la distancia ves una tienda

    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣧⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡀⠙⠳⢶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠛⣷⠰⡀⣦⠬⡙⠻⢷⣦⣄⣀⣠⣤⣶⣿⣏⡼⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡏⠀⢹⣇⢳⡙⣟⠲⡂⢳⢹⡿⣯⣍⣻⣿⣿⣋⣀⡈⢷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠀⠀⠀⢻⣆⢻⡙⡗⢳⡀⢳⣷⡀⠈⠉⢹⠀⡾⢿⣭⡹⡿⢶⣦⣤⣀⣰⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠁⠀⠀⠀⠀⢿⣆⢻⠻⡖⢳⡀⢻⢿⣄⠀⠘⠀⡧⣾⢼⠀⡏⣇⠱⡤⡈⢛⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⣴⡟⠀⠀SHOP ⠀⢻⣎⢻⠛⣖⠻⡆⢧⠙⠧⣤⣄⣷⣿⣾⠀⠿⣍⣯⡽⡝⢏⢾⣷⣀⣠⡆⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⣼⠏⠀⠀⣤⣤⣼⡤⠤⡄⠀⠹⣧⠳⡘⢷⠻⡖⠳⡀⢠⠉⠉⠉⢙⣷⣤⣼⠶⢷⠷⠾⠟⠛⣿⠟⣧⡀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⢠⡾⠁⠀⠀⠀⢹⡆⢸⡀⠀⡇⠀⠀⠈⢷⡙⢞⠳⡚⢖⠛⡄⠃⣀⣴⢟⣿⣿⢛⡶⢳⢔⡰⣢⡾⠁⠀⠈⢷⡄⠀⠀⠀⠀⠀
    ⠀⠀⠀⠰⢫⠀⠀⠀⠀⠀⢼⡧⢼⡇⠰⡇⠀⠀⠀⠀⠹⣦⣄⣁⣈⣃⣤⢞⣯⣗⡿⢻⠼⣯⣿⣿⣿⠿⣫⢤⠖⠲⣤⡈⠻⣦⡀⠀⠀⠀
    ⠀⠀⠀⢀⣿⣷⠀⠀⠀⠀⢸⠇⠘⡇⣀⣿⠀⠀⠀⠀⢀⠀⠈⠉⠉⠳⡶⣯⣬⣥⣬⣭⡿⠼⠟⠋⢁⠚⢣⣼⣼⡥⠊⣿⠀⠈⠛⢦⠀⠀
    ⠀⠀⣠⡾⠛⢿⡄⠀⠀⠀⠸⠿⠿⠿⠛⠋⠀⠀⠀⠀⢸⠀⣤⣤⡀⠀⢳⠀⢦⢬⣧⡀⠀⠀⡇⠀⢈⣉⣙⣛⣛⠒⠚⠋⠀⠀⡄⠀⠀⠀
    ⠀⣾⠋⠁⠀⠸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⣧⣾⡇⠀⢸⠀⢸⢬⣦⡇⠀⠀⡆⠀⠀⡄⠀⢹⠉⠉⢹⠀⠀⢠⠇⠀⠀⠀
    ⣴⠟⠀⠀⠀⣴⣿⠀⠀⠀⠀⣶⠚⢻⠉⠉⡇⠀⠀⠀⢸⠀⡇⣿⡇⠀⢸⠀⢸⢸⢈⡇⠀⠀⡇⠀⠀⡇⠀⢸⠀⠀⢸⠀⠀⢸⠀⠀⠀⠀
    ⠓⠢⣶⡿⡿⠋⢹⡆⠀⠀⠀⢻⣇⣸⣄⣤⡇⠀⠀⠀⢸⢀⣧⣿⡇⠀⢸⡀⣾⣸⣹⡇⠀⠀⡇⠀⢠⡇⠀⢸⠀⠀⡾⠀⠀⣿⠀⠀⠀⠀
    ⠀⠀⠀⠀⢹⠦⠼⡇⠀⠀⠀⢸⡏⢹⡇⠀⣧⠀⠀⠀⢸⢸⣿⣿⡇⠀⢸⢃⣿⣼⣼⠃⠀⠀⣷⠀⢸⠀⠈⠿⠉⠀⡇⠀⠀⣿⣤⡀⠀⠀
    ⠀⠀⢀⡾⠉⠀⠀⢹⠀⠀⠀⢸⣧⣴⣷⣲⡿⠀⠀⠀⢸⠈⠉⠉⠁⠀⣸⠀⠉⠉⠉⠀⠀⢀⡇⠀⡸⠀⠀⡆⠀⢀⡇⠀⢀⡏⠸⠥⣄⠀
    ⠀⠀⠋⠀⠀⠀⠀⠘⡄⠀⠀⢈⣛⣋⣉⣁⣀⣀⣠⠤⠬⠤⠤⠤⠤⠤⠷⠤⠤⠤⠤⠤⠤⢼⣧⣤⣥⣤⣀⣀⣀⣈⣀⠀⠸⠃⠀⠀⠈⣿
    ⠀⠀⠀⠀⠠⠤⠖⢒⣃⣉⠭⠭⡽⢿⣛⣿⣛⣯⠭⠥⠤⠤⠤⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢉⣷⠀⠀⠀⠈⠉⠹⢭⣙⠛⠓⠶⠦⠤⣬
    ⠀⠀⠀⠀⡒⣫⠉⠡⠤⠒⢒⣊⣉⡩⠥⠥⠄⢀⣀⣀⣀⣀⣤⣤⠤⠤⠤⠤⠤⠴⠶⠶⠒⠚⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠉⠲⡄⠀⠀⠀
    ⠀⠀⠀⠀⠀⠤⠖⠒⠊⢉⣁⣤⡤⠶⠶⠛⠛⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣶⠇⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⣠⠶⠛⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⡴⠶⠖⠛⠛⠉⠉⠉⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠻⠶⠤⠤⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡞⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠦⢤⣄⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠙⠓⠲⢄⣀⠀
    Vas camino hacia ella...
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
Tu eleccion: _
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
Tienes 714 oro restante.
──────────────────────────────────────────────────────────────
╔════════════════════════════════════════════════════════════════════════════════╗
   Items disponibles:                                                             
   (No hay ítems en venta en este momento.)
╚════════════════════════════════════════════════════════════════════════════════╝
Presiona ENTER para salir de la tienda...
╔──────────────────────────────────────────────────────────────╗
  La Oscuridad observa, paciente.
╚──────────────────────────────────────────────────────────────╝
--- FIN DE EVENTO ---
Pasos restantes: 1
Presione Enter para continuar...
```
> Esta mecánica garantiza una experiencia de compra dinámica y controlada. El sistema valida la compra, descuenta el oro correspondiente y actualiza el inventario del jugador. Además, si el stock de ítems se agota, se informa al jugador, evitando acciones innecesarias y permitiendo continuar con el avance del juego.

##### ✨ Evento Bonus:
Cuando ocurra un evento de tipo bonus, se mostrará el siguiente mensaje en pantalla:
```
    Has encontrado un Cofre!

    ⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⣠⣾⣿⠿⢋⣡⣴⣶⣶⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⢀⣾⣿⡟⢁⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⠆⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀
    ⠀⢀⣾⣿⠏⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢁⣴⣾⣿⠟⠋⣀⣤⣤⡀⠀⠀
    ⠀⣼⣿⡟⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠁⣴⣿⣿⠟⢁⣴⣿⣿⣿⣿⣿⡄⠀
    ⠀⣉⠛⠃⠸⢿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢀⣾⣿⡿⠁⣰⣿⣿⣿⣿⣿⣿⣿⡧⠀
    ⠀⣿⣿⡆⢠⣤⠀⣉⠙⠛⠿⢿⣿⣿⠀⣾⣿⣿⠃⣼⣿⣿⣿⣿⠿⠛⢉⣡⣤⠀
    ⠀⣿⣿⡇⢸⣿⠀⣿⠿⠷⣶⠀⣈⡁⠀⠻⠿⡟⠀⠿⠟⠋⣁⣠⣴⣾⣿⣿⣿⠀
    ⠀⣿⣿⡇⢸⣿⠀⣿⡄⢠⣿⠀⣿⡇⠀⣶⣦⡄⠀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⠀
    ⠀⣿⣿⡇⢸⣿⠀⠿⢧⣾⣿⠀⣿⡇⠀⣿⣿⡇⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀
    ⠀⣿⣿⡇⢸⣿⣷⣶⣤⣄⣉⠀⣿⡇⠀⣿⣿⡇⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀
    ⠀⠉⠛⠃⢸⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⣿⣿⡇⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀
    ⠀⠀⠀⠀⠀⠀⠉⠙⠛⠿⣿⣿⣿⡇⠀⣿⣿⡇⠀⣿⣿⣿⣿⣿⣿⠿⠛⠉⠁⠀
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠀⠻⢿⡇⠀⣿⠿⠛⠉⠀⠀⠀⠀⠀⠀⠀

    Abriendo el tesoro...
```
Durante este evento, el jugador podrá encontrar objetos valiosos que mejoran su equipamiento o le otorgan alguna ventaja adicional. Un ejemplo de lo que puede suceder es el siguiente:
```
Amuleto de Ataque ha sido añadido al inventario.
Encontraste un Amuleto de Ataque!
╔──────────────────────────────────────────────────────────────╗
  'No olvides', dice la inscripcion.
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
Presione Enter para continuar...
```
> Estos fragmentos aportan profundidad al universo del juego. Estos no afectan directamente al combate o inventario, pero contribuyen al desarrollo del trasfondo y la ambientación, revelando partes del misterio que rodea el juego.

##### 💀 Evento Jefe Final
Cuando el jugador alcance el final del recorrido del mapa, se activará el evento del jefe final, mostrando la siguiente escena:
```
╔══════════════════════════════════════════════════════════════╗
  ¡Una presencia abrumadora se siente cerca...!
  El aire se vuelve denso y oscuro.
  ¡Tus instintos te gritan que te prepares para lo peor!
  Algo gigantesco se aproxima...
╚══════════════════════════════════════════════════════════════╝
Presiona ENTER para presenciar tu final...
```
Para luego revelar al **JEFE FINAL**:
```
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⢟⢡⣿⣿⣿⣿⠶⡙⣿⡿⣿⣯⢛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢟⢝⣴⣿⠟⣿⣼⣭⣴⣶⣾⡇⡇⣿⣿⣷⣶⡏⡇⣟⣻⠿⣜⢭⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢟⣫⡝⣾⢞⣯⣷⣗⢻⣻⣿⣿⣿⣿⠓⢠⣿⣿⣿⡟⠍⢃⣿⣿⣿⡶⣸⡟⢿⣮⣽⣻⣿⣿⡟⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢻⢳⠟⣫⡥⡑⣹⣿⣿⠄⣣⣿⣿⣿⡇⣴⣿⣿⣿⣿⠇⣠⣿⣛⣿⣿⠃⢡⣼⣷⣟⠏⢷⢿⣿⣿⡙⢦⣟⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣴⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⠋⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣝⣾⡳⣕⢚⠗⡹⣰⢿⣿⣿⣾⣿⡿⠻⡡⣾⣮⣍⣻⣿⣿⣼⣿⣿⣿⣿⣇⣾⣿⣿⡿⠇⠰⣤⡻⣿⣿⣷⡈⢻⣷⣌⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣷⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡉⣉⠛⠙⠀⢀⡜⢁⣿⣿⣿⣿⣿⣿⠐⠇⢻⢋⣿⣿⣟⢿⣿⣿⢿⣿⣿⢿⣿⣍⠉⢑⣄⣴⣶⣿⣷⣝⠿⣿⣷⢠⢻⣿⣷⡌⣙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣻⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⡭⣢⣿⣿⣿⣇⣧⠘⣧⢊⣰⣷⣿⡿⠿⠟⠛⠹⠉⠁⠀⠈⣈⠄⠀⠀⠀⠀⠀⠀⠉⠀⠈⠑⢌⡻⣷⣦⣝⣿⣿⣿⣿⣾⣷⡈⢻⡇⡇⢿⣿⣿⡙⣷⣮⣙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣏⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢟⡽⣾⢏⣴⣿⣿⣿⣿⣿⣦⣄⣱⠾⡟⠉⠀⠀⠀⠐⠃⠆⠰⢿⣥⣆⣅⣄⠀⠀⠀⠀⠀⣀⣀⣀⡀⠀⠀⠈⣼⣿⣿⢸⣿⣿⣿⣿⣿⣷⡀⠑⣆⢹⣿⣿⣏⣈⠙⢿⣷⣬⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣣⣼⢟⣿⢇⣼⣿⣿⠿⢛⣿⣿⡿⣣⠄⠀⠀⠀⠀⠀⠀⢀⠘⠀⢀⠀⠻⣿⣿⣿⡄⠀⠀⢀⣣⣿⣿⣿⣧⡄⠀⢀⣿⣿⡟⣼⣿⣿⣿⣿⣿⣿⡇⠀⣼⢸⣿⣿⣿⢠⡇⡜⠿⣿⣿⡜⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣧⣹⣿⣿⣿⣿⣿⣿⣿⣿⡟⢹⣾⢟⣵⣿⢣⡿⣛⣭⡞⣱⣿⣿⠿⠳⡍⠀⠀⠀⠀⣤⣼⣶⡎⠀⠀⠈⠀⠐⢝⢿⣯⡀⠀⠁⣸⣿⣿⣿⣿⣿⡿⢀⣾⣿⣿⢳⣿⣿⣿⣿⣿⣿⢻⣿⠀⣛⠨⣿⣿⣿⡇⢳⠹⡄⢻⣿⣿⡸⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⡀⠀⣿⣿⡏⠗⣻⡽⢫⣾⠿⢋⣡⢾⣧⠹⡀⠀⠠⣤⣿⣿⡟⠁⡀⠁⠸⠀⠀⠀⢡⣿⣿⣶⠠⠧⠰⢰⢂⠮⠹⠴⠟⢿⣿⣿⣶⣝⣛⡛⢿⣿⣿⣼⣿⡇⢱⠀⣿⣿⣿⣿⠹⣆⢣⠘⣿⣿⣧⢲⣮⣙⢿⣿⣿⣿⣿⣿⣿
⣿⣿⣟⣟⣿⠩⢻⣿⣿⣿⣇⣏⠃⢰⣿⣿⢰⣿⢟⣵⣿⢧⣺⡿⣻⣿⣿⣇⣏⠀⠀⣩⣹⣴⢂⠃⠅⠀⡄⡀⠀⢀⣬⣿⣿⣿⣿⣦⣃⠃⢎⠞⢎⣦⡫⢚⢿⣿⣿⣿⣿⣿⣶⡿⣿⣿⣿⣷⢸⡧⣿⣿⣿⣿⡇⣜⡈⡂⢿⣿⣿⡆⣿⣿⡎⣿⣿⣿⣿⣿⣿
⣿⣿⡿⣟⣼⣿⣿⣿⣿⡟⣼⡹⠀⣾⣿⡏⣾⢿⠂⢠⣷⣿⢏⣾⣿⡿⡁⡤⠈⣈⣭⣶⣿⠋⠋⢀⢠⡀⠸⣷⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⡠⣨⡈⠉⠐⢦⣀⡻⠿⠿⠟⣿⢻⣟⣈⠻⠿⠍⣿⣇⣿⣿⣿⣿⣿⢻⣧⢋⢸⣿⣿⣿⠸⣿⣿⡜⣿⣿⣿⣿⣿
⣿⣿⢻⣿⣿⣿⣿⣿⣿⢣⣿⢧⣀⣿⣿⢣⡇⡏⡌⢸⣿⡟⣿⣿⡟⣴⢡⡇⠀⠹⣿⣿⡟⢠⠠⢏⣘⡙⠄⣰⣮⠃⣽⡿⠁⣙⢿⢿⣿⣿⣷⣯⡆⠀⠀⡀⠀⠉⢀⣼⣿⣿⣿⣿⣿⢟⣡⣾⣿⠟⠁⠉⡭⣛⣿⡟⡿⢸⡇⣿⣿⣿⣇⢿⣿⣷⢹⣿⣿⣿⣿
⣿⣿⡯⣿⣿⣿⣿⣿⡏⣾⡿⡌⢹⣿⣿⢸⣧⢡⠡⣿⣿⡝⣿⣿⣃⣸⡏⣡⠀⠉⠉⠈⠀⠈⢠⡇⢸⣿⡀⠿⠟⠁⣿⠇⠂⣿⡇⢀⣾⡁⢟⠹⠷⠀⠀⢠⣴⠠⣹⣿⣿⣿⣿⣿⣵⣿⣿⠟⠁⢀⡔⣬⣴⣿⠏⢣⣾⣿⣷⠿⠿⣿⣿⡸⣿⣿⣆⢿⣿⣿⣿
⣿⣿⣹⣿⣿⣿⣿⣿⢸⣿⣿⡿⣿⣿⣿⣦⣄⠺⢴⣿⣿⢘⡛⢃⡀⢙⢿⣝⣦⣄⡀⠀⠄⡆⡈⣁⠐⣷⠀⢹⡇⢼⣿⡰⢿⡏⣡⣝⡛⡧⢼⡞⣶⢠⢀⢸⢣⣰⣿⣿⣿⣿⣿⣿⣿⠟⠁⠀⡔⣈⣼⣿⡿⣧⣾⣿⡿⠋⠁⠂⢀⣴⡾⠇⣿⣿⣿⡜⣿⣿⣿
⣿⣿⡟⣿⣿⣿⣿⣧⢿⠩⢠⠀⠌⠻⢿⣿⣿⣿⣶⣬⣉⠃⢹⣭⣿⣯⣆⢿⣿⣿⠀⠤⠈⡤⠃⠸⡀⢋⡤⣉⣵⢪⣩⡔⢞⡅⡹⣿⡳⣿⠇⣬⡍⣘⡘⢇⢣⣿⣿⣿⣿⣿⣿⠹⠁⠀⠀⣀⣾⣿⣿⢟⢱⣿⠟⠋⠀⣔⣴⣶⡿⢏⣵⣦⢛⡿⠿⢷⢹⣿⣿
⣿⣿⣷⠻⣿⣿⣿⣿⢱⡝⢦⣇⠐⡀⠀⠉⠻⢿⣿⣿⣿⣷⡤⣏⣿⣿⣸⠀⠂⠀⢀⡅⢠⢰⢱⠆⠇⣹⡷⡡⣾⢔⢕⣅⡿⢃⠁⡻⢁⣾⣤⡹⠀⢯⡏⣄⣿⣿⣿⣿⣿⣿⣿⠀⢶⡓⣾⣿⣿⣿⢫⣾⠞⠁⠀⣠⣾⣿⡿⣯⡵⠟⢃⠔⢉⣼⡴⢋⣾⣿⣿
⣿⢳⣾⣿⣿⣿⣿⡇⡛⠁⠤⠙⢷⣦⡀⢄⠀⠀⠉⠻⣿⣿⢶⣻⣿⣿⣿⡆⠀⠀⠀⣂⠀⠉⠄⢀⡾⣮⣾⣾⣷⣷⣿⣾⣶⣭⣮⣒⠔⡩⢟⣞⣠⡟⣜⣾⣿⣿⣿⣿⣿⣿⡿⠰⠘⢿⣿⣿⣟⣵⣿⡟⠀⠨⣾⣿⡿⣫⠾⠋⡀⢀⣱⣶⠿⢫⢸⣿⣿⣿⣿
⣿⢸⣿⣿⣿⣿⣿⣿⣎⠢⠀⠄⠀⠙⢿⣶⣅⢀⣁⠀⢤⠙⣲⣿⣿⣿⡟⣇⠀⠀⢈⣽⢰⣢⣽⣷⣿⡿⠿⠿⠿⡟⢛⡛⢿⢿⣿⣿⣿⣿⣾⣿⢏⣜⣾⣿⣿⣿⣿⣿⣿⣿⡷⠰⠶⠊⢿⣿⣾⣿⣿⡏⠒⠁⢙⣿⣿⣿⠀⣾⣧⣾⠟⣡⠚⢀⣾⣿⣿⣿⣿
⣭⣾⣿⣿⣿⣿⣿⣿⣿⣷⣄⠂⡱⣄⠐⠙⢿⣿⣿⣦⠄⣰⣿⣿⣿⣿⣿⡹⡀⠀⠈⠑⡱⠟⢉⠑⠈⠐⠁⠀⠁⠁⠀⠉⠈⠀⠉⠙⠹⠻⡿⡣⣪⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠠⢀⢤⣾⣿⣿⣿⣿⡆⣉⠙⣾⣿⣿⡏⢆⡘⢫⠑⣷⠟⣴⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣜⢾⡗⣼⡇⠙⠻⠏⡰⣿⣽⣿⣿⣿⣿⣷⣣⠀⠀⠀⢘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣪⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣎⢳⣀⣾⣿⣿⣿⣿⣿⣥⣀⣽⣿⣿⣿⣧⢨⣱⣿⣧⢡⣾⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢱⣿⠁⠀⠀⣴⡿⣻⣿⣿⣿⣿⣿⣿⣷⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣼⣿⣿⣿⣿⣿⠿⠿⠿⠿⣿⣿⣿⣅⣱⣿⣿⣿⡎⠿⠿⠿⣿⣿⣿⣟⣻
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⣾⡇⠀⢀⢪⣡⢶⣯⣿⣿⣿⣿⣿⣿⣿⣿⣾⣥⣄⣀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⣶⣿⣿⡟⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠟⣋⣭⣴⣶⣶⣾⠿⠿⠷⠶⠮⢍⣙⣫⣭⣽⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⣿⢈⠁⢆⣹⢾⣷⡿⣉⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠏⢉⣰⣾⣿⣿⢿⡏⠉⠀⠀⠆⣉⣱⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿

╔══════════════════════════════════════════════════════════════╗
  ??? : Así que tú eres el héroe que ha llegado hasta aquí...   
  ??? : No tienes idea del poder al que te enfrentas.           
  ??? : ¡Prepárate para ser devorado por la oscuridad!          
╚══════════════════════════════════════════════════════════════╝
Presiona ENTER para derrotarlo...
```

###### ⚔️ Combate Final – Fase 1
Al comenzar el enfrentamiento, se muestra la primera fase del jefe final:
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
Tu elección: 1
» Asesino ataca al El Devorador de Mundos y le inflige 636 de daño. «
⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦
⇦  ¡El Devorador de Mundos contraataca con poder abismal!
⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦
El Devorador de Mundos ataca con sus garras del vacío.
« El Devorador de Mundos inflige 7 de daño devastador. »
──────────────────────────────────────────────────────────────       
Presione Enter para continuar...
```
Tras debilitar al jefe en esta primera fase, este se enfada y se muestra el siguiente dialogo:
```
╔══════════════════════════════════════════════════════════════╗
  ??? : !Tu no puedes DERROTARME!.                              
  ??? : No eres nada para mi.                                   
╚══════════════════════════════════════════════════════════════╝
Presiona ENTER...
```
Luego el jefe llama a sus subditos oscuros al campo de batalla mostrando lo siguiente:
```
⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣿⣿⣿⣿⣿⣿⣛⡛⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣹⣽⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⣷⣦⣌⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣯⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⡹⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⣴⣿⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣌⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⣾⣷⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣿⣿⡬⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣻⣿⣿⡈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠟⣿⣉⣭⣭⣭⡿⣿⣻⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⣿⡏⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⣿⣿⣧⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⣿⣿⣿⣿⡿⢋⣤⢶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢹⣷⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠛⠻⠿⠿⢿⣿⣿⣟⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⣿⣿⣿⠏⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⡏⢹⣿⣿⣿⡿⠟⠛⠛⠿⣿⣿⣿⣿⣿⠀⠐⠛⠛⠃⠀⢢⠀⢹⣿⡟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⣿⣿⡏⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣹⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⢸⡟⣿⠀⣿⡿⠋⠀⠂⠀⠀⠀⠹⣿⡖⣿⣿⠀⠀⠀⠀⠀⠀⢸⠿⠀⣿⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⣿⡏⢠⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⢳⣻⣶⡟⠀⠀⠀⠀⠀⢸⠃⠀⣿⠧⠛⢿⣄⡀⠀⠀⣀⢀⠾⠀⢸⣿⣶⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⣿⠁⠋⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠹⣻⡇⠀⠀⠀⠀⠀⠘⠀⣰⡏⠀⠀⠀⠻⣿⣶⣤⣉⣉⣠⣴⣿⣿⣿⢁⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⣿⡇⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣿⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠱⢾⡄⠀⠀⠀⠀⠀⣠⣿⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⣿⡍⢡⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⣿⠀⢰⠋⠉⠀⠀⠀⠀⠈⣿⣿⣿⡿⠿⢿⣿⣿⣿⡿⣡⣿⡟⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⢾⣿⣶⣀⣀⣶⣿⣿⣿⣦⣀⣤⢦⣤⣿⣿⣿⣿⣿⠟⢋⡿⢇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⡿⠃⡄⠀⠀⠀⠰⠀⠀⣠⡯⣽⡛⠀⠀⡀⠈⠻⣿⡧⣾⠏⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡌⠿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣿⠃⢸⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⡇⠸⣿⣦⡀⠀⣀⣠⣾⠟⠃⢿⣧⠀⠀⠁⠘⠀⠘⣇⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⡀⠘⢿⡿⣿⣿⣿⣿⣿⣿⠻⣿⣿⣿⡟⢃⣡⡧⠀⣾⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⣿⣿⣿⣿⣿⡶⢈⢛⣿⣿⣿⡿⠋⢀⡆⢸⣿⡀⠀⠦⠄⠀⣸⡇⣴⣿⣿⣿⣿⣿⣿⣿⣿⣛⣿⣷⣶⣷⣶⣾⣍⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⠀⠈⠓⠿⡿⣿⡟⣻⢩⣯⣽⣷⠙⠃⠈⠁⢠⠴⡞⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢀⠸⣿⣿⣿⣿⠃⡼⢻⣿⣿⣟⣣⣀⡈⠁⢸⣿⣿⣿⣶⣾⢯⣿⢻⣿⣿⣿⣿⣿⣿⣿⢳⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡌⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠁⠑⡓⠛⠃⠉⣈⠉⠀⠀⠀⠀⠀⣀⣾⣾⡐⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⠸⠆⢻⣿⣿⡟⢰⣷⠀⠪⢝⡻⢿⣿⣿⣿⣿⣿⣿⢿⣩⡷⢂⣼⣿⣿⣿⣿⣿⣿⡟⠉⠋⠁⠈⢿⣿⠃⠀⠈⠙⢿⣿⣿⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣀⠀⠀⢳⣀⠀⡀⢀⠀⣀⣠⣖⢺⣟⣛⢸⣿⠁⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⠀⠀⢸⣿⣿⣧⠘⣿⣇⢀⠀⠁⠘⠐⠗⠾⠿⠿⠧⣼⣿⠇⣾⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⣠⣀⣀⣹⣷⡀⠀⠀⠀⠀⢻⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠐⣍⣧⣽⣬⣧⣼⣿⣿⣿⣿⣿⡿⠟⠀⡛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢸⢃⣸⣿⣿⣿⣧⠸⣿⣿⣤⣀⣆⠠⢠⠤⠤⣤⣶⣼⡟⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⡌⡹⠋⠉⠽⠿⣿⣿⡄⠺⠣⠀⣾⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠹⣾⣿⣿⣿⣿⣿⣿⣿⠟⠋⠀⣠⡞⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⠘⣸⣿⣿⣿⣿⣿⣆⠻⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⢉⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡁⠀⠀⠀⠀⠈⠙⠃⠀⣇⡐⠃⣼⣿⣿⣿⣿⢿⣷⣦⣍⣻⡛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⡯⣝⣿⣿⣷⣶⣶⠛⣿⣿⣧⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣿⣟⣻⣟⠛⠛⠿
⢰⣿⣿⣿⣿⣿⣿⣿⣷⠀⢩⣟⡛⠿⠿⠛⢉⣠⡔⠒⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⡄⢠⠀⠀⠀⠀⢸⠟⠉⠈⣿⣿⣿⣿⠇⣘⣻⣻⣿⢻⣿⣷⡿⠿⡛⢿⣟⣿⣿⣿⡿⣛⣻⣿⡇⠉⠀⠀⠉⠁⢠⣿⡏⢹⣿⣷⣾⣿⣍⢻⣿⣿⣿⣿⣿⡿⢿⣿⣿⣿⣿⣿⣷
⢨⣭⣉⣿⡿⠟⠋⠐⠺⠂⣿⣤⣏⢙⣿⣿⣿⠛⠃⠀⠻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⠁⠈⠀⠀⠀⢠⡾⢶⠋⡀⢹⣿⣿⣏⣿⣿⣿⣿⣿⣉⡁⠹⣿⡌⣿⣿⡿⠉⠉⠀⣀⣀⡀⠈⠁⠨⠀⠀⠀⠀⠊⠙⢃⠈⠍⠉⣿⣿⡿⠟⠛⠛⠛⢉⣉⣭⣿⣿⣿⡆⢉⠉⠁
⠈⠻⢿⣟⠁⠀⠀⠀⠀⠒⠈⠙⠻⠿⣿⣿⣿⠏⠉⠉⠑⢶⣦⡉⢻⣿⣿⣿⣿⡿⠿⠿⣿⣿⡀⠀⠀⠃⢀⣾⡏⠉⠙⠀⠈⣿⣿⣇⣹⣿⣿⣿⣿⣏⠀⠂⢸⣿⣿⣼⠀⠀⠀⠀⠀⠠⠄⠀⠀⠀⣀⣀⣀⡀⠂⢀⣩⣴⣶⠿⠛⠉⠀⢠⣤⡄⠯⣾⣿⣿⣿⣿⣿⠇⠀⠻ 
⠀⠀⣀⠙⣿⣶⣤⣀⡈⢀⣿⣿⣶⣶⣤⣴⣾⠀⠀⠀⠀⠀⣻⣿⣤⣿⣷⣶⣿⣿⣿⣷⣷⣦⣥⠆⣠⣾⣿⠟⠓⠀⠀⡀⠀⠈⠍⠛⢉⣿⣿⣿⣿⣿⡆⠀⣶⡻⣿⡿⠙⢻⣿⣶⣿⣶⣶⣶⣤⣾⣿⣿⣿⣿⣿⠿⠛⡉⠀⠀⠀⠊⢀⣼⣿⠻⣿⣿⣿⣿⣿⣿⣿⡀⠀⠀⡀
⢀⠀⢻⣇⠙⣽⠛⠿⢿⣾⣿⣿⣿⣿⣿⡏⢀⣤⣴⣾⣿⣿⣿⣿⣿⡛⠋⠉⠉⠉⠉⠛⣿⣿⣿⡁⢈⠉⢁⣀⠀⠀⠘⠒⢂⡀⠄⠉⢹⣿⠿⠟⠛⠁⠀⠀⢻⣷⡆⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⠹⠿⠿⠛⠉⠀⠐⠋⠡⠀⡀⠀⣠⣾⡟⢻⣷⣿⣿⣿⣿⣿⣿⣿⣷⡀⠀⠁
⠀⠀⠈⠛⣷⣤⣀⡀⣾⣿⣿⣿⣿⣿⣿⣧⠸⡿⠟⠛⠉⠁⢠⣿⣿⠃⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⠀⠈⣿⣿⡷⠉⢙⣩⠅⢠⣤⣤⣿⣿⠆⣠⠀⠀⡀⠀⠀⠹⣷⡀⠙⢿⣿⣿⣿⣿⣿⠏⢁⡀⠀⠀⠀⠀⠀⠀⢀⣐⣉⣴⣾⣿⠟⠀⠀⣿⣿⣧⣿⣿⣿⣫⠟⢻⣷⠀⠀
⠀⠀⠀⠀⢌⠙⠻⣿⡏⠁⣀⠀⠙⠛⠋⠁⠀⠀⠀⢀⣠⣴⣿⣿⠃⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣃⣀⣀⠙⠟⢀⣀⡀⠀⣀⡸⢿⣿⣿⠇⣼⣷⣇⣰⠀⠀⠀⠀⠻⢷⡀⠈⢿⣿⠛⠛⠁⢠⣾⣿⣿⣿⡿⠻⡿⠿⠟⠛⣉⠙⢉⣀⣀⠀⢸⣿⡗⢸⣿⣿⡿⠃⡄⣿⣿⣇⠈
⢸⣦⣀⠀⠀⠀⠀⠈⣷⣿⣿⣿⣷⣦⢿⣿⣶⡿⠿⠟⠛⠋⠉⢳⣧⠀⠀⠀⡠⠖⠋⣿⡿⣿⣿⠈⢍⠻⣿⠇⠘⠀⠈⠉⠀⢠⣾⣿⡏⠀⣿⣿⡿⢿⣀⡀⠀⣀⣠⣤⣧⣤⡀⠀⠀⠀⠐⠟⠛⠉⠁⠀⠀⠀⠂⠘⠓⠚⢁⠔⠀⠀⠈⢁⣼⣿⠟⡿⣿⡏⢀⣾⣇⢸⣿⣿⡄
⠈⢿⠿⢿⣦⣤⡀⠺⠛⠿⢿⣿⡿⠋⠀⣀⠘⠉⠀⠀⠀⠀⠀⣸⣿⠀⢀⠎⣠⣾⢰⣿⡽⣿⣿⠀⠤⠠⣤⡆⠀⠲⠶⢶⣶⣾⣿⣿⣥⣞⡁⢹⣷⣈⣿⣷⣿⣿⣿⣿⣿⣿⣿⣷⣶⡦⠀⢠⡶⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠐⢃⣸⣶⣿⣿⣯⡿⣱⣿⡇⢼⣿⣿⢸⣿⣿⡷
⠐⠢⠀⠀⠉⠉⠛⣷⣦⣄⣸⣥⣀⣠⣦⣤⣤⣤⣤⣶⣦⣾⣿⡿⠃⢀⡌⢰⣿⡿⢸⣿⡇⣿⣿⣇⣀⣀⠈⠉⠀⣀⡀⠀⢠⣿⣿⡏⢨⢹⣷⢸⣿⣿⡌⠙⠿⠿⢿⣿⣏⣿⣿⣿⣧⠀⡆⢸⣿⣄⠀⠀⠀⠀⠈⢓⣀⣤⣴⣾⣿⣿⡿⣿⠟⠁⠀⢹⣿⣿⡌⣿⣿⢸⣿⣿⡇

El devorador, ruge y sus subditos renacen. ¡Su ataque aumenta!

Quieres continuar? Presiona ENTER
```
###### ☠️ Combate Final – Fase 2
Ahora se muestra la Fase 2 del combate final, donde el enemigo revela una forma más poderosa y peligrosa.
```
╔═══════════════════════════════════════════════╗
║           COMBATE FINAL - FASE 2              ║
╠═══════════════════════════════════════════════╣
  Asesino HP: 186/200  (Atk: 218, Def: 1001)
  El Devorador de Mundos HP: 394/666 (Fase 2)
╚═══════════════════════════════════════════════╝
⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨
⇨  ¡Tu turno!
⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨
  [1] Atacar
  [2] Usar Ítem (Inventario)
──────────────────────────────────────────────────────────────
Tu elección: 1
» Asesino ataca al El Devorador de Mundos y le inflige 136 de daño. «
⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦
⇦  ¡El Devorador de Mundos contraataca con poder abismal!
⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦
El Devorador de Mundos ataca con sus garras del vacío.
« El Devorador de Mundos inflige 8 de daño devastador. »
──────────────────────────────────────────────────────────────     
Presione Enter para continuar...
```
Luego de debilitar al jefe final, este se enfada aún mas mostrando el siguiente dialogo:
```
╔══════════════════════════════════════════════════════════════╗
  ??? : !Ahora si, no tienes escapatoria!.                      
╚══════════════════════════════════════════════════════════════╝
Presiona ENTER...
```
Posteriormente podemos ver a nuestro héroe en una situacion complicada:
```
 Te ves a ti mismo, exhausto. Te rendiras?                  
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⢶⡦⢦⣤⣀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣇⣸⣧⣾⣯⣻⢶⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣷⣻⣿⣭⠟⠛⠻⢾⣸⣿⡀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡍⠈⠉⠀⠀⠀⠀⢉⣾⢹⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣄⠀⠀⠀⣀⣶⡿⠃⢻⣆⢀⡀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⠶⠶⠾⠋⠒⠀⣀⣾⣿⣿⣿⣆⠀⢀⣀⡀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠿⣷⣶⣶⠁⠀⠴⣱⣿⢟⣿⡿⠟⠉⠉⠉⠉⢶⣦⡀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⠛⣿⢿⣧⣴⡾⣋⣷⠿⣻⠃⢀⣤⣶⢶⢿⣿⢿⣿⣄⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢴⡛⣿⠀⠈⣧⣿⣯⠞⠉⣡⣶⣿⣷⡟⢿⠉⢮⡀⠙⣆⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀    
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠷⣜⢷⠀⣿⣽⡟⢀⣶⣋⣽⣿⣿⣷⣌⢷⣀⣿⡿⡿⢿⢿⡹⡀⠀⠀⠀⠀⠀⠀        
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣄⠈⠻⣿⣿⣿⠦⢿⣭⣶⣿⣹⣿⣿⡟⠻⣿⢻⡹⡝⣌⢶⢷⡹⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀    
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣷⣾⠋⣧⠉⣏⡻⠋⢙⣿⣿⣿⣿⣿⡀⣿⠆⢹⡙⡝⣎⢦⢷⡽⠆⠀⠀⠀⠀⠀⠀⠀     
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣉⣿⣿⣿⠀⣿⢀⠟⠀⡴⠏⡇⢈⣿⣿⣿⣷⠸⡎⠆⢻⣙⣼⣾⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀    
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡏⠉⣿⣿⣇⡿⠋⣠⠞⡇⠀⣇⠀⠻⣻⣿⣿⣷⡿⠾⠛⠋⠉⠹⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀    
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣦⣀⣿⣿⣯⣄⡶⢹⠀⣿⠀⣿⠀⠀⢙⣿⣿⣿⣦⡀⠀⣀⡠⠖⠻⣿⡆⠀⣠⣶⢦⡀⠀⠀⠀    
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣿⠋⣿⣿⣿⣿⣆⠈⡄⢹⠀⢸⠀⣤⣾⣿⣿⣿⣿⣷⣉⣁⡀⠀⠀⣹⣿⡾⠟⣧⢿⣇⠀⠀⠀    
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣿⣿⣸⣿⣿⡿⣿⣿⣷⣄⡀⣀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⣠⠞⠁⢸⣿⡆⠀⠀    
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⢁⣟⣿⣿⣷⣿⣿⣍⠉⠛⠟⠿⠿⠿⠿⠿⠛⠿⣿⣿⣿⣿⣻⡿⠋⢀⡞⠁⠀⠀⢸⣿⣧⠀⠀    
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⠻⣿⡏⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣶⣶⣶⣶⣶⣶⢿⡟⣻⣿⣿⠟⠁⡰⠋⠀⠀⠀⠀⢸⣿⣿⡄⠀    
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣆⠙⠷⠿⣿⢏⣿⣿⣛⡷⢾⣇⣀⠼⣏⠉⠉⡉⠁⠀⠀⣿⣼⡿⠃⣠⠞⠁⠀⠀⠀⠀⠀⢸⣿⣿⡇⠀    
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣏⠈⠳⣄⣿⣿⣷⣿⠋⡻⢿⣷⣿⣁⣀⣼⣤⣶⣶⣶⠶⣿⣿⠟⢀⡼⠁⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⢣⠀    
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠯⣕⣶⣾⣿⡻⣿⡿⣤⠃⣴⣿⠋⣿⢿⢸⣉⣉⣉⣀⣴⣿⠃⣠⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣼⠀    
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡏⢠⣌⠙⣿⣿⣿⣿⣤⣯⣶⣿⣏⣀⣿⠈⠈⡉⠙⢿⣿⡿⠁⣠⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣯⣼⣿⡄    

Presiona ENTER...
```
###### 👿 Combate Final – Fase 3
Ahora se muestra la fase final del Jefe, donde el enemigo revela una forma aún más poderosa y peligrosa.
```
╔═══════════════════════════════════════════════╗
║           COMBATE FINAL - FASE 3              ║
╠═══════════════════════════════════════════════╣
  Asesino HP: 193/200  (Atk: 1017, Def: 1001)
  El Devorador de Mundos HP: 30/666 (Fase 3 - FURIA)
╚═══════════════════════════════════════════════╝
⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨
⇨  ¡Tu turno!
⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨
  [1] Atacar
  [2] Usar Ítem (Inventario)
──────────────────────────────────────────────────────────────
Tu elección:
```
> El combate contra el jefe final se compone de tres fases consecutivas, cada una más desafiante que la anterior. Las estadísticas del jefe evolucionan en cada fase, exigiendo al jugador adaptar su estrategia y gestionar cuidadosamente sus recursos hasta el desenlace final del juego. La victoria dependerá de todas las decisiones tomadas a lo largo de la aventura.

###### 🏆 Si el jefe final es derrotado:
Si el jugador gana la batalla final se mostrará lo siguiente:
```
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢀⣀⣠⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡜⣩⡟⠉⠀⠀⢈⠉⠲⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⣱⠋⠁⠀⣀⠀⣼⣀⠀⠃⢻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣳⠏⠀⠀⢰⣿⣤⣏⣿⡶⡇⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡿⠃⠀⠀⠀⠈⣿⣿⣿⡿⣰⣧⣤⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⠆       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣄⠰⣆⠀⠀⠀⣀⡴⠋⠀⠀⠀⠀⢀⣀⣿⣷⣾⣟⣃⡹⠋⠀⠀⠀⠀⠀⠀⠀⢀⣠⣼⠟⠋⠁⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡹⣟⠺⢭⡔⠋⠉⠀⠀⠀⠀⠀⢀⣼⣯⣿⡿⣅⣤⣿⣤⣄⠀⠀⠀⠀⠀⢀⣴⣾⠟⠃⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢾⡽⢦⣄⣀⠀⠀⠀⠀⢰⣾⣿⡿⣿⣯⣽⡷⣿⣽⣿⣿⢧⡄⠀⣠⣴⡿⠟⠁⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠒⣶⣤⣀⣀⣀⡀⠾⣿⣿⣿⢶⣬⣯⣿⣿⣿⣿⣿⣿⣤⣾⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠀⠀⢠⣿⣿⣦⣝⡋⣿⡌⠘⢿⣿⣿⣿⣿⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣧⣉⢳⣿⣽⣤⣽⣿⢿⠟⢿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣶⣾⣯⣿⣿⣿⣿⣿⣿⣯⣸⠀⡾⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⡄⠀⠀⠀⢸⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡾⣺⣅⠀⠀⢀⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡾⠇⢹⣻⣷⣀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⠀⣤⣿⣿⣿⣽⡟⠋⣿⣿⣟⣻⢻⣿⣻⣿⡿⡍⠿⠛⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠞⠀⣠⣾⡿⣿⣿⣿⡿⢿⣦⣿⠋⢛⠿⢾⢹⠿⣿⣿⣮⣦⡀⠙⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡾⠁⣠⡾⠟⣹⣾⣿⣟⣿⡿⠟⠛⣿⡷⠿⣿⠾⠷⠶⠟⣿⣻⣿⣿⣧⡈⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⠀⢀⡴⢋⣤⣾⢋⣴⣾⢟⢃⡾⠛⠁⠀⠀⢸⡟⢻⡷⡏⠀⠀⠀⠀⢻⡟⠛⡋⠹⣝⠊⢇⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⠀⠀⣴⠏⣴⠿⣿⣾⠿⢻⣷⠶⠋⠀⠀⠀⠀⠀⢸⡇⣰⣻⣤⠤⠤⠤⠤⣀⣳⠀⣇⢀⣼⣦⠘⣧⠀⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⠀⠀⣠⠞⠁⣼⣿⠿⣛⣅⡼⠋⠁⢠⡀⠀⠀⠀⠀⠀⢸⢡⣿⠟⠛⢙⣿⣖⣤⣌⠉⣧⣟⠉⠀⣹⣴⣾⡆⠀⠀⠀⠀⠀⠀⠀       
      ⠀⠀⢀⡼⠁⢀⡴⠋⢉⡿⠟⠁⠀⠀⠀⣘⣷⠦⣄⣀⣀⣤⣿⣿⣥⠖⠋⠁⠀⠀⠉⠓⠯⣿⣿⣤⣴⣿⣼⠛⠁⠀⠀⠀⠀⠀⠀⠀       
      ⠀⣴⢟⣡⠖⢩⣴⠖⠉⠀⠀⠀⠀⠀⠘⠿⣾⠤⠴⠒⣉⣽⣿⣿⣄⡀⣀⣀⣀⣀⣀⢀⣀⢨⣿⠿⣅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       
      ⣴⣿⠿⠷⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠺⠿⢿⣿⣿⣿⣿⡟⠿⠟⠿⠛⠛⠿⢿⣿⡿⠿⠿⠿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       
 ╔═════════════════════════════════════════════════════════╗ 
 ║    Has derrotado al Devorador de Mundos y salvado       ║ 
 ║           el reino de la oscuridad eterna.              ║ 
 ║                                                         ║ 
 ║              ¡Eres el héroe definitivo!                 ║ 
 ╚═════════════════════════════════════════════════════════╝ 

¡JUEGO COMPLETADO!

Presione ENTER para finalizar...
```
Para finalmente mostrar el utlimo fragmento de historia:
```
╔──────────────────────────────────────────────────────────────╗
  Cuando la Oscuridad cae y el ultimo eco de la batalla 
  se apaga, todos los fragmentos y recuerdos se unen en 
  tu mente. Comprendes, al fin, que la Oscuridad no era 
  un enemigo externo, sino la suma de los miedos, traiciones 
  y sacrificios de todos los Heraldos. Cada ciclo, cada 
  olvido, fue una defensa para no enfrentar la verdad: tu 
  eres la Oscuridad y la Luz, el Heraldo y el Olvidado. 
  El ciclo solo termina cuando aceptas cada parte de ti, 
  y solo entonces el mundo puede renacer libre del eterno 
  retorno.
╚──────────────────────────────────────────────────────────────╝

--- FIN DEL JUEGO ---
```
> ¡Felicidades has completado FinalQuest 1!
###### ❌ En caso de perder:
Si el jugador es derrotado por el Jefe final se mostrará lo siguiente:
```
╔══════════════════════════════════════════════════════════════╗
  ??? : Eres debil...                                           
╚══════════════════════════════════════════════════════════════╝
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣯⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⢺⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡏⣧⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢶⣿⣋⣟⠭⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣿⣭⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡏⢮⣳⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡿⣦⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⠢⣽⣅⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡆⢤⣿⡇⠀⠀⠀⠀⣸⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢷⠸⣞⡇⠀⠀⠀⠀⡏⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡄⣿⣷⠀⠀⠀⠀⢻⡈⢣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⢸⣿⡆⠀⠀⠀⠀⢳⣬⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡈⣿⣧⠀⠀⢠⡄⣸⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡇⢹⣿⡀⠀⢸⢧⠟⢹⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠸⣿⡇⣠⠋⢾⣾⢸⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡖⠀⠸⣿⣶⣿⣷⡏⢰⡿⢿⠏⣸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⣴⢋⣿⣿⣿⠇⡟⠁⣏⠀⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡞⣏⢦⠇⢸⡿⢿⠋⢀⣤⣀⡘⢦⡟⢸⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⠃⢀⣴⡆⠀⠀⠈⣹⣿⡷⠆⠀⣧⠈⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠜⢁⡴⠋⡀⠙⢄⠀⣰⣿⣟⠓⠀⠀⢉⣴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⢰⡏⡠⠊⢀⡴⣇⠀⢀⡞⠉⠛⠀⡀⢀⣄⣩⠌⠙⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⢣⠶⠖⠊⢀⣈⠉⣹⡷⢀⣴⡯⠔⣛⡵⠁⣠⡏⠸⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢹⡿⢿⠟⠀⣰⡞⠉⣿⡷⠇⠃⣠⢴⣶⣾⡋⢀⡴⣽⠁⠀⠘⣏⣀⢰⣆⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⣠⣶⣶⣅⣠⣶⠀⠒⠟⢁⡴⠋⠀⠀⠀⢹⣿⣿⡋⣧⢸⡇⡏⣀⣀⠀⠙⣿⣉⠙⢤⡄⠀⠀⠀
⠀⠀⣠⣴⣺⢿⣿⣿⡛⠛⠿⠿⣯⣷⡲⣶⣟⣻⡀⠀⣠⣿⣿⣖⣸⣨⣿⠿⠛⣻⣿⣶⣾⣾⠇⠀⠻⣄⠀⠀
⠀⣾⢟⠿⠿⢶⣮⡙⢏⢢⡀⢠⡌⣿⣿⡿⠟⡿⢳⣼⣿⣿⣿⣾⣿⣧⣤⣤⣤⣿⣿⣭⣿⠁⠀⠀⣀⣈⣧⠀
⢺⣥⢿⠾⠿⠿⠿⡿⠚⢋⣠⠯⣿⢉⢉⠻⠾⠛⢿⣿⠻⠿⢛⢋⣤⣯⣭⠽⠶⣾⣻⢿⣻⢿⠶⢛⣻⡿⢽⠄

¿Tendrás lo necesario para intentarlo de nuevo?

Presiona ENTER...
```
Para luego darle otra oportunidad para reiniciar el juego y volver a intentarlo
> ¡No te rindas! ¡Puedes intentarlo denuevo!

## Contribuciones 🔥

### Elias Manríquez 👿
- **Diseño e implementación de estructuras clave**: Definió y programó las estructuras `Player`, `Item`, `Enemy` y `Scenario`, fundamentales para el funcionamiento del juego.

- **Implementación de TDAs y lógica principal**: Desarrolló los Tipos de Datos Abstractos utilizados en el juego y organizó los archivos cabecera para mantener una arquitectura modular. También implementó funcionalidades esenciales como el sistema de combate, la lógica de la tienda y el manejo del jugador.

- **Narrativa y dinámica**: Programó la visualización de fragmentos de historia y lore, enriqueciendo el contenido narrativo y la experiencia general del jugador.

> Auto-evaluación: 5/5 (Aporte Excelente)

### Maximiliano Rodríguez 😎
- **Estructuración de archivos CSV**: Organizó y normalizó los datos utilizados en el juego, creando una base coherente y clara para `enemigos`, `ítems` y `escenarios`.

- **Mejoras en la interfaz del usuario**: Introdujo colores en la consola, optimizó menús iniciales y el módulo de tienda, haciendo la experiencia más visual e intuitiva.

- **Narrativa y personalización de la tienda**: Aportó contenido narrativo adicional e implementó mejoras en la lógica de la tienda, incluyendo una historia específica asociada al módulo, aportando profundidad al universo del juego.

- **Redacción final del README**: Redactó y organizó el contenido del archivo `README.md`, documentando detalladamente el funcionamiento, modos de juego y estructura técnica del programa.

> Auto-evaluación: 5/5 (Aporte excelente)

### Lukas Navarro 🤑
- **Carga y parseo de datos desde archivos CSV**: Implementó la lógica que permite leer e interpretar correctamente los archivos con `enemigos`, `ítems` y `escenarios`, asegurando una integración adecuada al sistema y facilitando la escalabilidad del juego.

- **Progresión por escenarios y eventos aleatorios**: Desarrolló el sistema de avance lineal utilizando una cola, así como la generación de eventos aleatorios (`combates`, `tiendas`, `bonus` y `fragmentos de historia`).

- **Balance y depuración**: Ajustó las recompensas obtenidas por el jugador para mantener un equilibrio durante la partida. También se encargó de la depuración y optimización del código, mejorando su estabilidad y mantenibilidad.

> Auto-evaluación: 5/5 (Aporte excelente)

> **A lo largo de todo el proceso, los tres integrantes colaboraron de manera activa y constante en la revisión cruzada de módulos, la toma de decisiones de diseño, la resolución de problemas y la elaboración del codigo. Por lo tanto consideramos que cada integrante trabajo de manera óptima y eficiente**.