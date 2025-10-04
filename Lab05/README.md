# LabTO-Lab05

# Mario Bros en Smalltalk
Una recreación del clásico Mario Bros de 1985 programado en Pharo Smalltalk

## 📖 ¿Qué es este proyecto?
Este es un juego de Mario Bros desarrollado usando Smalltalk, el mismo lenguaje de programación que se usa en Pharo. Es como tener el Mario original pero programado de manera educativa para entender cómo funcionan los videojuegos por dentro.

## 🎮 ¿Qué puedes hacer en el juego?
- **Controlar a Mario** y moverlo por el nivel
- **Saltar sobre enemigos** (Goombas y Koopas)
- **Romper bloques** y descubrir sorpresas
- **Recoger monedas**
- **Llegar a la bandera** al final del nivel
- **Esquivar obstáculos** y pipes

## 🛠 ¿Cómo instalarlo?

### Requisitos:
- Tener instalado Pharo (versión 8 o 9)
- Conexión a internet

### Instrucciones:
- Abrir un playground y pegar lo siguiente:

```Smalltalk
Metacello new
    baseline: 'Mario';
    repository: 'github://akevalion/Mario';
    load.
``` 

- Para correr el juego ejecutar:
```Smalltalk
MaGame new run
```  


![image](https://user-images.githubusercontent.com/10532890/78724964-7ea42600-78fc-11ea-9ddd-42057e69542c.png)
