### Makefile para compilar codigos usados por FREDI
### COPIAR ESTE ARCHIVO EN LA CARPETA DEL CODIGO QUE SE QUIERA
### COMPILAR

### Librerias usadas
ARDUINO_LIBS = Wire FREDI SPI RF24 Adafruit_INA219

### Directorio del proyecto (ASEGURARSE!!)
PROJECT_DIR       = ../..

### Directorio de Arduino	(ASEGURARSE!!)
ARDUINO_DIR       = C:/Arduino

### Puerto donde se conecta arduino (ASEGURARSE!!)
MONITOR_PORT      = com5

### BOARD_TAG	(uno o nano)
BOARD_TAG         = uno

### Directorio del Makefile global
ARDMK_DIR         = $(PROJECT_DIR)/include/Arduino-Makefile

### Librerias del usuario, usadas en el proyecto (3rd party & FREDI's)
USER_LIB_PATH    :=  $(PROJECT_DIR)/libraries

### Baud rate de la comunicacion serial
MONITOR_BAUDRATE  = 9600

### AVR_TOOLS_DIR
AVR_TOOLS_DIR = C:/Arduino/hardware/tools/avr

### AVRDUDE
AVRDUDE       = C:/Arduino/hardware/tools/avr/bin

### CURRENT_DIR
### Do not touch - used for binaries path
CURRENT_DIR       = $(shell basename $(CURDIR))

### OBJDIR
### This is where you put the binaries you just compile using 'make'
#OBJDIR            = $(PROJECT_DIR)/bin/$(BOARD_TAG)/$(CURRENT_DIR)

### Do not touch - the path to Arduino.mk, inside the ARDMK_DIR
include $(ARDMK_DIR)/Arduino.mk
