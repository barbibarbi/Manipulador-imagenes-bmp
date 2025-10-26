# 🖼️ Proyecto: `bmpmanipuleitor` - Manipulador de Imágenes BMP de 24 bits

El proyecto **`bmpmanipuleitor`** es un programa desarrollado en **C** para el procesamiento y manipulación de archivos de imagen **BMP** sin compresión de **24 bits** de profundidad. Permite aplicar una variedad de filtros, transformaciones, rotaciones, concatenaciones y utilidades de información.  
Comenzó como un trabajo practico universitario y decidí seguir implementando otras filtros por diversión.

---

## 🛠️ Especificaciones y Requisitos

El programa solo procesa archivos que cumplen estrictamente con las siguientes especificaciones:

* **Formato de Archivo:** Solo **BMP**.
* **Compresión:** Solo BMP **sin compresión**.
* **Profundidad de Color:** Solo **24 bits** de profundidad.

---

### 🎨 Filtros y Transformaciones

| Categoría | Comando | Parámetros | Descripción |
| :--- | :--- | :--- | :--- |
| **Básicos** | `--negativo` | No | Invierte los colores de la imagen. |
| **Básicos** | `--escala-de-grises` | No | Convierte a escala de grises promediando RGB. |
| **Básicos** | `--espejar-horizontal` | No | Voltea la imagen horizontalmente.  |
| **Básicos** | `--espejar-vertical` | No | Voltea la imagen verticalmente.  |
| **Contraste/Color** | `--aumentar-contraste` | `X` (0-100%) |Aumenta el contraste en un $X\%$. |
| **Contraste/Color** | `--reducir-contraste` | `X` (0-100%) | Reduce el contraste en un $X\%$. |
| **Contraste/Color** | `--tonalidad-azul-X` | `X` (0-100%) | Aumenta en un $X\%$ la intensidad del color azul. |
| **Contraste/Color** | `--tonalidad-verde $=X$` | `X` (0-100%) | Aumenta en un $X\%$ la intensidad del color verde. |
| **Contraste/Color** | `--tonalidad-roja X` | `X` (0-100%) | Aumenta en un $X\%$ la intensidad del color rojo. |
| **Dimensiones** | `--achicar X` | `X` (0-100%) | Reduce el tamaño re-escalando la imagen al $X\%$. |
| **Dimensiones** | `--recortar $=X$` | `X` (0-100%) | Mantiene solo $X\%$ del tamaño original, comenzando del origen.|
| **Rotación** | `--rotar-derecha` | No | Rota la imagen $90^{\circ}$ en sentido horario.  |
| **Rotación** | `--rotar-izquierda` | No | Rota la imagen $90^{\circ}$ en sentido anti-horario. |
| **Concatenación** | `--concatenar-horizontal` | No | Concatena dos imágenes una al lado de la otra, alineando por altura. |
| **Concatenación** | `--concatenar-vertical` | No | Concatena dos imágenes una arriba de la otra, alineando por ancho. |

---

### ⚙️ Utilidades

| Comando | Descripción |
| :--- | :--- |
| `--info` | Muestra información del archivo BMP (dimensiones, tamaño, etc.). |
| `--validar` | Solo valida el archivo sin procesar. |
| `--verbose` | Modo detallado de ejecución con mensajes informativos.  |
| `--help` | Muestra ayuda de uso y lista de comandos disponibles. |

--- 

### ✨ Filtros agregados por diversión

| Categoría | Comando | Parámetros | Descripción | Fecha en que se agregó |
| :--- | :--- | :--- | :--- | :--- |
| **Personalizado** | `--psicodelia` | No | Intercambia entre rojo, verde y azul de cada pixel aleatoriamente.| 25 Oct 2025 |

---
![Ejemplos de los filtros](https://raw.githubusercontent.com/barbibarbi/Manipulador-imagenes-bmp/main/Ejemplo_de_imagenes/ejemplo.png)
