# Directorio con los Proyectos hechos para la EDU-CIAA

Este es el directorio de los proyectos implementados para la EDU-CIAA.

Cada proyecto debe contener un directorio `src` donde se encuentran los archivos *.c*, *.cpp* y *.s* , es decir, los archivos donde se implementan todas las funciones que serán utilizadas por el programa.

Además, cada proyecto debe incluir un directorio `inc`, donde se encuentran los encabezados (archivos *.h*) de las funciones y estructuras públicas a implementar en el directorio `src`.

Al compilarse el proyecto, se genera automáticamente un directorio `out` en la carpeta del proyecto que incluye todos archivos generados por los pasos intermedios de la compilación. Estos archivos pueden resultar de mucha utilidad para debuggear el programa.

## Generador de funciones (funcGen)

Tablero e interfaz de usuario para un generador de funciones. Posee un boton para cambiar la forma de la onda, un boton para seleccionar el modo de modificacion (frecuencia o tension), y 2 botones que suben o bajan la propiedad seleccionada.

### Entradas
- Tec1: Cambio de forma.
- Tec2: Cambio de modo.
- Tec3: Up.
- Tec4: Down.

### Salidas
- Led RGB: Forma de onda. R=Sin, G=Sqr, B=Tri.
- Led1: Modo de los botones up/down. ON = Tension, OFF = Frecuencia.
- Led2: Up. Subir F/V dependiendo del modo. Swap de estado indica evento.
- Led3: Down. Bajar F/V dependiendo del modo. Swap de estado indica evento.


## Puerta corrediza (slideDoor)

Control de una puerta corrediza automatica comandada por presencia. Si detecta una presencia, la puerta se abre y queda abierta hasta que pasen mas de 3 segundos sin detectar presencia. Al cerrarse, si detecta presencia se vuelve a abrir.

### Entradas
- Tec1: Presencia
- Tec2: Final de carrera cerrado.
- Tec3: Final de carrera abierto.
- Tec4: --

### Salidas
- Led RGB: -
- Led1: -
- Led2: Direccion del motor. ON = Abriendo, OFF = Cerrando. 
- Led3: Estado del motor. ON = encendido, OFF = Apagado


## Puerta de garage (garage)

Control de una puerta de garage comandado por un control remoto de un solo boton. Si se pulsa al estar cerrado se abre, si se pulsa al estar abierto se cierra, si se pulsa en movimiento cambia de sentido (con una espera intermedia para realizar la inversion). Si la puerta esta abierta, parpadea una luz en la vereda indicando precaucion.

### Entradas
- Tec1: Presencia de vehiculo debajo del garage.
- Tec2: Control Remoto.
- Tec3: Final de carrera cerrado.
- Tec4: Final de carrera abierto.

### Salidas
- Led RGB: -
- Led1: Luz de la vereda. Titla si el porton esta abierto.
- Led2: Direccion del motor. ON = Abriendo, OFF = Cerrando. 
- Led3: Estado del motor. ON = encendido, OFF = Apagado


## Escalera mecanica (mecStair)
Escalera mecanica bidireccional automatica. Cuando detecta una presion en la placa, se enciende para el lado correspondiente por un tiempo estipulado (previamente calculado para que la persona llegue al destino). Si se presiona nuevamente la placa, se reinicia el contador.

Existen varias formas de encarar esta escalera (contador de personas seria otra forma), pero esta fue la que me parecio mas simple y acorde.

### Entradas
- Tec1: Presion abajo
- Tec2: Presion arriba
- Tec3: -
- Tec4: -

### Salidas
- Led RGB: -
- Led1: -
- Led2: Direccion del motor. ON = Abriendo, OFF = Cerrando. 
- Led3: Estado del motor. ON = encendido, OFF = Apagado. 

## Microondas (microWave)

Control de microondas. Posibilidad de elegir 3 tipos de tiempos (1,2,3 segundos). Boton de start/stop para encender o detener el microondas. Si la puerta esta abierta, el microondas no enciende.

### Entradas
- Tec1: Start / Stop
- Tec2: Detector de puerta abierta
- Tec3: -
- Tec4: -

### Salidas
- Led RGB: Modo de coccion. R=Pequeno, G=Mediano, B=Granade.
- Led1: Estado del generador de microondas
- Led2: -
- Led3: -