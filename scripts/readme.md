# Código fuente para FREDI
En esta carpeta se organizan todos los códigos, librerias y tests usados por FREDI. La estructura es como sigue:

- **bin**: archivos binarios resultado de compilaciones
- **include**: librerias usadas para la compilacion. Por ahora solamente *Arduino-Makefile* de *sudar*
- **libraries**: librerias usadas por FREDI en los scripts. Aquí se encuentran los headers para hacer *#include "---.h"*
- **src**: códigos fuentes principales usados por FREDI. Estos son los archivos *.ino* que se compilarán
- **test**: códigos fuentes para testing

## Uso
### Linux
Los archivos de Arduino para FREDI se encuentran en la carpeta *src*. Para compilarlos y subirlos al MCU se debe checkear que:

1. Cada archivo *.ino* se encuentre en una carpeta con el mismo nombre dentro de *src*. Por ejemplo, el archivo *fredi.ino* debería estar en */scr/fredi/*
2. Contar con un Makefile para compilar el archivo en la misma carpeta donde se encuentra. Un ejemplo de Makefile se muestra en */src/fredi/*
3. Compilar con *make*:

```
make        // compila archivo
make upload // compila y sube a MCU
make clean  // limpia carpeta
```
