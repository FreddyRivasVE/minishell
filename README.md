# Minishell

**Minishell** es un proyecto desarrollado como parte del plan de estudios de la escuela 42, cuyo objetivo es recrear una shell minimalista basada en Bash. El proyecto incluye la implementación de un intérprete de línea de comandos capaz de ejecutar programas, gestionar redirecciones, manejar pipes, interpretar comillas y variables de entorno, y ejecutar comandos internos (*built-ins*).

---

## Objetivos del Proyecto

- Implementar un *prompt* interactivo que emule el comportamiento de una shell real.
- Manejar múltiples comandos, redirecciones, pipes y variables de entorno.
- Ejecutar comandos del sistema usando `execve`.
- Gestionar señales como `SIGINT` (Ctrl+C) y `EOF` (Ctrl+D).
- Implementar comandos internos (*built-ins*).
- Crear una experiencia similar a Bash en cuanto al comportamiento.

---

## Características Principales

- ✅ Prompt interactivo y dinámico
- ✅ Manejo de señales (Ctrl+C, Ctrl+D, Ctrl+\)
- ✅ Pipes (`|`)
- ✅ Redirecciones (`>`, `>>`, `<`, `<<`)
- ✅ Heredocs (`<<`)
- ✅ Expansión de variables (`$`)
- ✅ Comillas simples y dobles
- ✅ Separación por punto y coma (`;`)
- ✅ Soporte para `&&` y `||` en ejecución condicional (si se implementa)
- ✅ Implementación completa de comandos internos (*built-ins*)

---

## Built-ins Implementados

| Comando   | Descripción                           |
|-----------|---------------------------------------|
| `cd`      | Cambia el directorio actual           |
| `echo`    | Imprime texto en la salida estándar   |
| `env`     | Muestra las variables de entorno      |
| `exit`    | Sale de la shell                      |
| `export`  | Define nuevas variables de entorno    |
| `pwd`     | Imprime el directorio actual          |
| `unset`   | Elimina variables de entorno          |

---

## Estructura del Proyecto

```
minishell-main/
├── codigo/
│   ├── include/           # Archivos de cabecera
│   ├── libs/libft/        # Biblioteca personalizada (libft)
│   ├── src/
│   │   ├── built_ins/     # Implementaciones de comandos internos
│   │   ├── execution/     # Ejecución de comandos y pipes
│   │   ├── initial/       # Inicialización y loop principal
│   │   ├── parce/         # Parser, tokenización y validación del input
│   │   └── utils/         # Funciones auxiliares
│   ├── valgrind/          # Archivos de supresión e informes de memoria
│   └── Makefile           # Script de compilación
├── Wiki/                  # Documentación y manuales de funciones usadas
└── README.md
```

---

## Compilación

Asegurate de tener `make` y `gcc` instalados. Luego, compilá el proyecto con:

```bash
git clone https://github.com/yourusername/minishell.git
cd minishell/codigo
make
```

---

## Ejecución

Una vez compilado, podés iniciar la shell con:

```bash
./minishell
```

Dentro de la shell, podés usar comandos como:

```bash
""ec''ho"" "Welcome to our 'minishell', I am $USER"
ls -la | grep minishell > resultado.txt
echo "Hola $'$'USER''"
cd -
cat << EOF
Texto de prueba
EOF
```

---

## Dependencias

- `readline` (para la lectura de líneas y manejo del prompt)
- Librerías estándar de C:
  - `unistd.h`
  - `stdlib.h`
  - `signal.h`
  - `fcntl.h`
  - `stdio.h`
  - `string.h`
  - entre otras...

---

## Pruebas y Debugging

- Uso de `valgrind` con supresiones personalizadas para evitar falsos positivos.
- Se implementaron validaciones de input y manejo robusto de errores.

---

## Errores manejados

- Comando no encontrado
- Redirecciones inválidas
- Uso incorrecto de comillas o pipes
- Comportamiento con EOF y señales
- Variables sin definir
- Para más detalles de manejo de errores recomendamos leer este [README](https://github.com/OliverKingz/minishell/blob/main/README.md)

---

## Autores

Desarrollado por:

- [Freddy Rivas](https://github.com/FreddyRivasVE)
- [Brenda Rivera](https://github.com/briveraarg)

---

## Licencia

Este proyecto es parte del plan de estudios de 42 y no está licenciado para distribución comercial. Uso educativo solamente.

---

## Recursos

- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Linux man pages](https://man7.org/linux/man-pages/)

