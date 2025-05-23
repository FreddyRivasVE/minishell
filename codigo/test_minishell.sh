#!/bin/bash

MINISHELL=./minishell
LOG_DIR=./test_logs
VALGRIND_LOG=$LOG_DIR/valgrind.log

mkdir -p "$LOG_DIR"

COMMANDS=(
  # Builtins simples
  "echo hola mundo"
  "pwd"
  "env"

  # Exportar y usar variable
  "export TEST_VAR=42"
  "echo \$TEST_VAR"
  "unset TEST_VAR"
  "echo \$TEST_VAR"

  # Redirección de salida
  "echo hola > out.txt"
  "cat out.txt"
  "rm out.txt"

  # Redirección con >>
  "echo primera linea > log.txt"
  "echo segunda linea >> log.txt"
  "cat log.txt"
  "rm log.txt"

  # Redirección de entrada
  "cat < Makefile"

  # Pipes simples
  "echo hola | cat"
  "ls | wc -l"
  "cat Makefile | grep NAME"

  # Pipes anidados
  "cat Makefile | grep NAME | wc -l"
  "echo hola | grep h | wc -c"

  # Comillas simples y dobles
  "echo 'entre comillas simples'"
  "echo \"entre comillas dobles\""
  "echo 'hola \$USER'"
  "echo \"hola \$USER\""

  # Comando inválido
  "comandoinexistente"
  "ls noexiste"

  # cd y pwd
  "cd .."
  "pwd"
  "cd -"

  # Expansión de ~
  "cd ~"
  "pwd"

  # Uso de $? (exit status)
  "false"
  "echo \$?"

  # Espacios y tabs
  "         echo        hola      mundo     "

  # Salida del shell
  "exit"
)

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

total=${#COMMANDS[@]}
passed=0
failed=0
valgrind_failed=0

echo "🔎 Iniciando tests sin ';' ni '&'..."
echo "------------------------------------"

i=0
while [ $i -lt $total ]; do
  CMD="${COMMANDS[$i]}"
  ID=$((i + 1))

  MINI_OUT="$LOG_DIR/mini_out_$ID.txt"
  MINI_ERR="$LOG_DIR/mini_err_$ID.txt"
  MINI_RET="$LOG_DIR/mini_ret_$ID.txt"

  BASH_OUT="$LOG_DIR/bash_out_$ID.txt"
  BASH_ERR="$LOG_DIR/bash_err_$ID.txt"
  BASH_RET="$LOG_DIR/bash_ret_$ID.txt"

  echo "$CMD" | bash > "$BASH_OUT" 2> "$BASH_ERR"
  echo "$?" > "$BASH_RET"

  echo "$CMD" | valgrind --leak-check=full --error-exitcode=42 \
    --log-file="$VALGRIND_LOG" "$MINISHELL" > "$MINI_OUT" 2> "$MINI_ERR"
  MINI_EXIT=$?
  echo "$MINI_EXIT" > "$MINI_RET"

  diff -q "$MINI_OUT" "$BASH_OUT" > /dev/null
  OUT_OK=$?
  diff -q "$MINI_ERR" "$BASH_ERR" > /dev/null
  ERR_OK=$?
  diff -q "$MINI_RET" "$BASH_RET" > /dev/null
  RET_OK=$?

  if [ $OUT_OK -eq 0 ] && [ $ERR_OK -eq 0 ] && [ $RET_OK -eq 0 ]; then
    echo -e "✅ ${GREEN}Test $ID PASSED${NC}: $CMD"
    passed=$((passed + 1))
  else
    echo -e "❌ ${RED}Test $ID FAILED${NC}: $CMD"
    failed=$((failed + 1))
    cp "$MINI_OUT" "$LOG_DIR/test_$ID.mini_stdout"
    cp "$MINI_ERR" "$LOG_DIR/test_$ID.mini_stderr"
    cp "$MINI_RET" "$LOG_DIR/test_$ID.mini_exitcode"
    cp "$BASH_OUT" "$LOG_DIR/test_$ID.bash_stdout"
    cp "$BASH_ERR" "$LOG_DIR/test_$ID.bash_stderr"
    cp "$BASH_RET" "$LOG_DIR/test_$ID.bash_exitcode"
  fi

  if [ $MINI_EXIT -eq 42 ]; then
    echo -e "   ${YELLOW}⚠ Valgrind detectó fuga en test $ID${NC}"
    valgrind_failed=$((valgrind_failed + 1))
  fi

  rm -f "$MINI_OUT" "$MINI_ERR" "$MINI_RET"
  rm -f "$BASH_OUT" "$BASH_ERR" "$BASH_RET"

  i=$((i + 1))
done

echo
echo "📊 Resultados:"
echo -e "   ${GREEN}✔ Pasaron    : $passed/${total}${NC}"
echo -e "   ${RED}✘ Fallaron   : $failed/${total}${NC}"
echo -e "   ${YELLOW}⚠ Valgrind KO: $valgrind_failed${NC}"
echo "   🗂 Logs en: $LOG_DIR/"

