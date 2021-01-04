### Funciones de interes

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
