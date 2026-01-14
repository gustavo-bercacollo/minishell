# minishell

> Projeto **minishell** da 42 — uma implementação simplificada de um shell Unix, desenvolvida em C.

---

## 📌 Descrição

O **minishell** é um interpretador de comandos inspirado no Bash.
Ele permite a execução de comandos simples, comandos encadeados, redirecionamentos, pipes, expansões e built-ins, além de gerenciar variáveis de ambiente e sinais do sistema.

Este projeto foi desenvolvido com foco em:
- arquitetura modular
- gerenciamento correto de memória
- controle de processos (`fork`, `exec`, `wait`)
- manipulação de sinais
- compatibilidade com o comportamento esperado de um shell Unix

---

## ✨ Funcionalidades

### ✅ Execução de comandos
- Execução de comandos absolutos e relativos
- Busca automática no `PATH`
- Execução de programas externos

### ✅ Built-ins implementados
- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### ✅ Redirecionamentos
- `<` redirecionamento de entrada
- `>` redirecionamento de saída
- `>>` redirecionamento com append
- Pipes `|`

### ✅ Operadores lógicos
- `&&` (AND)
- `||` (OR)

### ✅ Expansões
- Expansão de variáveis (`$VAR`)
- Expansão do código de saída (`$?`)
- Tratamento correto de aspas simples e duplas

### ✅ Sinais
- `Ctrl-C` (SIGINT)
- `Ctrl-D` (EOF)
- `Ctrl-\\` (SIGQUIT)
- Comportamento correto em processos pai e filho

### ✅ Histórico
- Integração com `readline`
- Histórico de comandos funcional

---

## 🗂️ Estrutura do Projeto

```text
.
├── include/
│   └── minishell.h
│
├── libft/
│   └── Biblioteca pessoal (42)
│
├── src/
│   ├── builtins/
│   ├── env/
│   ├── execute/
│   ├── expansions/
│   ├── parser/
│   ├── redirections/
│   ├── signals/
│   ├── token/
│   ├── utils/
│   └── main.c
│
├── readline.supp
├── Makefile
└── README.md
```

---

## 🧠 Arquitetura

1. Leitura da entrada (readline, histórico, sinais)
2. Tokenização
3. Parsing e construção de AST
4. Expansões
5. Execução (built-ins, fork/exec, pipes)
6. Limpeza e liberação de recursos

---

## ⚙️ Compilação

```bash
make
```

Executar:

```bash
./minishell
```

---

## 🧪 Valgrind

```bash
make valgrind
```

- Execução interativa normal
- Log gerado em `valgrind.log`
- Supressões via `readline.supp`

---

## 🧹 Limpeza

```bash
make clean
make fclean
make re
```

---

## 👥 Autores

- gbercaco
- klima-do

Projeto desenvolvido na **42**.

---
