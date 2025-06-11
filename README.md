
````markdown
# 🐚 minishell

Este proyecto es una implementación propia de una shell simplificada en lenguaje C, desarrollado como parte del currículo de 42 Madrid. `minishell` permite ejecutar comandos del sistema, gestionar redirecciones, tuberías, variables de entorno y más, emulando el comportamiento básico de una shell como `bash`.

---

## 🚀 Características

- Soporte para comandos **built-in**: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`.
- Ejecución de **comandos externos** (como `ls`, `cat`, etc.).
- Gestión de **pipes (`|`)** y **redirecciones** (`>`, `>>`, `<`, `<<`).
- **Expansión de variables de entorno** (`$VAR`, `$?`, etc.).
- Soporte para **comillas simples y dobles**.
- Soporte **interactivo y no interactivo**.
- Manejo de **señales** (`Ctrl+C`, `Ctrl+\`) con comportamiento custom.
- Gestión de memoria robusta con herramientas como `valgrind`.

---

## 🛠️ Compilación

Cloná el repositorio y ejecutá:

```bash
make
````

Esto compilará `minishell` y su dependencia `libft`.

### ⚙️ Reglas adicionales del Makefile

* `make clean` – Elimina archivos objeto.
* `make fclean` – Elimina objetos y ejecutable.
* `make re` – Limpia y recompila desde cero.
* `make valgrind` – Ejecuta con Valgrind usando configuración personalizada.
* `make norminette` – Revisa el código con las reglas de Norminette (42).

---

## 📦 Requisitos

* `readline` (en macOS instalar con Homebrew: `brew install readline`).
* Compatible con **Linux** y **macOS (Darwin)**.

---

## 🧪 Cómo usar

Una vez compilado, ejecutá:

```bash
./minishell
```

Podés escribir comandos como:

```bash
minishell> echo hola mundo
minishell> export NOMBRE=Brenda
minishell> echo $NOMBRE
minishell> ls -l | grep minishell > salida.txt
minishell> cat << EOF
texto libre
EOF
```

También podés pasarle scripts desde otro proceso usando:

```bash
echo "ls -a" | ./minishell
```

---

## 🧠 Arquitectura del proyecto

El código está modularizado en distintos directorios:

* `src/initial/`: inicialización, señales, loops principales.
* `src/parce/`: parser, manejo de comillas, expansión, tokens.
* `src/built_ins/`: implementación de comandos internos.
* `src/execution/`: ejecución de comandos y redirecciones.
* `src/utils/`: funciones auxiliares y gestión de errores.
* `libs/libft/`:  implementación de funciones de la libc.

---

## 👩‍💻 Autores

* Brenda Rivera 
* Freddy Rivas 

---

## 📝 Licencia

Este proyecto es parte del currículo de 42. Su uso está destinado únicamente a fines educativos.

---

## 📈 Estado

✅ Proyecto finalizado y funcional.
🧪 Probado con múltiples casos interactivos y no interactivos.

```

