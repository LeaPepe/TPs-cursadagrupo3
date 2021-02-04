# Firmware Básico para la EDU-CIAA-NXP

Este repositorio es una verisón simplificada de [firmware_v3](https://github.com/epernia/firmware_v3), el cual contiene el firmware para trabajar con la placa EDU-CIAA-NXP y se encuentra en desarrollo. 


## Utilización

**Importante:** Antes de clonar este repositorio, hay que tener asegurado que la instalación del software de la CIAA se haya completado existosamente. Esto puede hacerse siguiendo las instrucciones de [este](https://github.com/epernia/software) repositorio.

El *firmware* es un projecto Makefile, es decir, un conjunto de directorios con archivos de código en C/C++/assembly y una serie de instrucciones de compilación contenidas en el archivo [Makefile](./Makefile). Estas instrucciones permiten ensamblar y linkear todos estos archivos para formar un binario que sea posible descargar a la placa. **No se recomienda editar el archivo Makefile. Para argegar instrucciones, crear los archivos .mk auxiliares correspondientes**.

El directorio [libs](./libs) contiene los módulos o librerías que van a utilizar los programas. Para que un programa compile correctamente, se utilizan como punto de partida las librerías [CMSIS Core](./libs/cmsis_core) y [board](./libs/board), las cuales contienen las instrucciones para llamar a la rutina principal (*main*) y para inicializar la placa correctamente. Es posible agregar módulos propios a este directorio y utilizarlos en el programa, pero deben seguirse las instrucciones de [este](./libs/Readme.md) archivo.

El directorio [projects](./projects) contiene los proyectos que se van a ir desarrollando con el firmware. Para detalles sobre cómo crear y configurar un nuevo proyecto, ver [acá](./projects/Readme.md).
**El archivo `program.mk` contiene la dirección donde se encuentra el proyecto que se va a compilar**.

# Trabajos practicos

## Trabajo practico 1 - Maquina de estados / Yakindu

Se resolvieron problemas planteados en la catedra. Se detallan a continuacion.


### Generador de funciones (funcGen)

Tablero e interfaz de usuario para un generador de funciones. Posee un boton para cambiar la forma de la onda, un boton para seleccionar el modo de modificacion (frecuencia o tension), y 2 botones que suben o bajan la propiedad seleccionada.

#### Entradas
- Tec1: Cambio de forma.
- Tec2: Cambio de modo.
- Tec3: Up.
- Tec4: Down.

#### Salidas
- Led RGB: Forma de onda. R=Sin, G=Sqr, B=Tri.
- Led1: Modo de los botones up/down. ON = Tension, OFF = Frecuencia.
- Led2: Up. Subir F/V dependiendo del modo. Swap de estado indica evento.
- Led3: Down. Bajar F/V dependiendo del modo. Swap de estado indica evento.


### Puerta corrediza (slideDoor)

Control de una puerta corrediza automatica comandada por presencia. Si detecta una presencia, la puerta se abre y queda abierta hasta que pasen mas de 3 segundos sin detectar presencia. Al cerrarse, si detecta presencia se vuelve a abrir.

#### Entradas
- Tec1: Presencia
- Tec2: Final de carrera cerrado.
- Tec3: Final de carrera abierto.
- Tec4: --

#### Salidas
- Led RGB: -
- Led1: -
- Led2: Direccion del motor. ON = Abriendo, OFF = Cerrando. 
- Led3: Estado del motor. ON = encendido, OFF = Apagado


### Puerta de garage (garage)

Control de una puerta de garage comandado por un control remoto de un solo boton. Si se pulsa al estar cerrado se abre, si se pulsa al estar abierto se cierra, si se pulsa en movimiento cambia de sentido (con una espera intermedia para realizar la inversion). Si la puerta esta abierta, parpadea una luz en la vereda indicando precaucion.

#### Entradas
- Tec1: Presencia de vehiculo debajo del garage.
- Tec2: Control Remoto.
- Tec3: Final de carrera cerrado.
- Tec4: Final de carrera abierto.

#### Salidas
- Led RGB: -
- Led1: Luz de la vereda. Titla si el porton esta abierto.
- Led2: Direccion del motor. ON = Abriendo, OFF = Cerrando. 
- Led3: Estado del motor. ON = encendido, OFF = Apagado


### Escalera mecanica (mecStair)
Escalera mecanica bidireccional automatica. Cuando detecta una presion en la placa, se enciende para el lado correspondiente por un tiempo estipulado (previamente calculado para que la persona llegue al destino). Si se presiona nuevamente la placa, se reinicia el contador.

Existen varias formas de encarar esta escalera (contador de personas seria otra forma), pero esta fue la que me parecio mas simple y acorde.

#### Entradas
- Tec1: Presion abajo
- Tec2: Presion arriba
- Tec3: -
- Tec4: -

#### Salidas
- Led RGB: -
- Led1: -
- Led2: Direccion del motor. ON = Abriendo, OFF = Cerrando. 
- Led3: Estado del motor. ON = encendido, OFF = Apagado. 

### Microondas (microWave)

Control de microondas. Posibilidad de elegir 3 tipos de tiempos (1,2,3 segundos). Boton de start/stop para encender o detener el microondas. Si la puerta esta abierta, el microondas no enciende.

#### Entradas
- Tec1: Start / Stop
- Tec2: Detector de puerta abierta
- Tec3: -
- Tec4: -

### Salidas
- Led RGB: Modo de coccion. R=Pequeno, G=Mediano, B=Granade.
- Led1: Estado del generador de microondas
- Led2: -
- Led3: -

## Trabajo practico 2 - GPIO

Se realizo la libreria casera que inicializa las teclas y leds. Funciones: gpioInit, gpioWrite, gpioRead y se utilizo en un ejemplo con maquina de estados para probar que funciona correctamente.

## Trabajo practico 3 - UART / ADC y DAC

## Ejercicio 1 - Funciones de interes

Se detallan algunas funciones de interes para la realizacion del trabajo practico

- uartConfig( UART_USB, 115200 ): Configura e inicializa (inicializacion de puertos y configuracion del buffer FIFO y SCU) la UART_USB para que se comunique con un baudrate de 115200 Hz. Para configurar los bits de datos, stop y paridad es necesario redefinir la marco uartConfig a uartInit2.

- adcConfig( ADC_ENABLE ): Configura e inicializa el ADC con una tasa de 200kHz (MAX_SAMPLE/2).

- dacConfig( DAC_ENABLE ): Configura e inicializa el DAC. Update rate 400kHz y habilita el direct mem access DMA.

- delayConfig( &delay, 500 ): Configura un delay no bloqueante de 500ms.

- muestra = adcRead( CH1 ): Lee el canal 1 del ADC y lo almacena en muestra (uint16_t).

- uartReadByte( UART_USB, &dato ): Lee un caracter de la UART y lo almacena en dato (uint8_t)

- uartWriteByte( UART_USB, dato ): Escribe el caracter almacenado en dato (uint8_t) en la UART

- uartWriteString( UART_USB, "ADC CH1 value: " ): Escribe el string (NULL terminated) en la UART (char*) [Bloqueante]

- dacWrite( DAC, muestra ): Escribe el valor muestra (uint16_t) en el DAC, truncandolo en 1023.

- uartCallbackSet(UART_USB, UART_RECEIVE, onRx, NULL): Habilita una interrupcion por callback utilizando el evento UART_RECEIVE. Cuando se genere el callback se llama a onRx y adicionalmente se pueden agregar pararmetros, pero se deja en NULL.

- uartInterrupt(UART_USB, true): Habilita las interrupciones por llegada de datos de la UART


### Ejercicio 2 - Debounce

Se generan maquinas de estados con debounce para cada tecla, y se envia por UART cada vez que una tecla se presiona o se suelta. A su vez, cuando una tecla se presiona, se enciende el led correspondiente

`PULSADOR -> LED -> UART (USB).TX -> TERMINAL (PC) -> TEXTO(PANTALLA)`

```
Tecla apretada: TEC1
Tecla liberada: TEC1`
```

### Ejercicio 3 - Debounce + UART commands

Se generan maquinas de estados con debounce para cada tecla, y se envia por UART cada vez que una tecla se presiona o se suelta. A su vez, se pueden enviar comandos por uart para cambiar el estado de los leds.

Comandos disponibles:
```c
 typedef enum commandsEnum {
	COMMAND_LED1_TOGGLE = 'a',
	COMMAND_LED2_TOGGLE = 's',
	COMMAND_LED3_TOGGLE = 'd',
	COMMAND_LED4_TOGGLE = 'f'
} commands_t;
```

### Ejercicio 4 - PWM + UART commands

Se generan PWMs para controlar los led del led RGB. Cada uno de los colores se controla independientemente con commandos enviados por uart. 

Comandos disponibles:

```c
 typedef enum commandsEnum {
	COMMAND_LEDR_INC = 'q', // increment
	COMMAND_LEDR_MID = 'a', // set to half duty cycle
	COMMAND_LEDR_DEC = 'z', // decrement
	COMMAND_LEDG_INC = 'w',
	COMMAND_LEDG_MID = 's',
	COMMAND_LEDG_DEC = 'x',
	COMMAND_LEDB_INC = 'e',
	COMMAND_LEDB_MID = 'd',
	COMMAND_LEDB_DEC = 'c'
} commands_t;
```

### Ejercicio 5 - ADC + UART

Se realizo una lectura de la entrada analogica CH1 conectada a un divisor resistivo 2k2//2k2. Se imprime el resultado de la lectura por uart, mostrando:

`ADC CH1 value: 510. Max sample value: 1024`

### Ejercicio 6 - DAC + ADC + UART

Se realizo la escritura del DAC mediante el envio de los caracteres 0 a 9, utilizando la funcion `valueDAC = (uint16_t)(((float)uartCharRx - 48.0)*1024.0/10.0);`

Se observa cada uno de los resultados con los distintos caracteres enviados:
```
ADC CH1 value: 0. Max sample value: 1024    // 0
ADC CH1 value: 101. Max sample value: 1024 
ADC CH1 value: 203. Max sample value: 1024 
ADC CH1 value: 306. Max sample value: 1024 
ADC CH1 value: 408. Max sample value: 1024 
ADC CH1 value: 511. Max sample value: 1024 
ADC CH1 value: 613. Max sample value: 1024 
ADC CH1 value: 715. Max sample value: 1024 
ADC CH1 value: 818. Max sample value: 1024 
ADC CH1 value: 920. Max sample value: 1024  // 9
```

### Ejercicio 7 - UARTS Loopback Ej 2 y 3


### Ejercicio 7 - UARTS Loopback 2

##3 Utilizacion para el TPF

Se utilizaran ampliamente estas funcionalidades en el trabajo final. El puerto UART se utilizara para recibir y transmitir datos o comandos hacia el webserver. Por otro lado se utilizaran 2 canales del ADC para leer 
senales analogicas correspondientes a la tension y corriente normalizada de 0 a 3.3v