# Nome do executável
EXEC = programa

# Arquivos fonte
SRC = main.c

# Regra padrão
all: $(EXEC)

# Compilar o programa
$(EXEC): $(SRC)
	gcc $(SRC) -o $(EXEC)

# Rodar o programa 10 vezes
run:
	for i in $(shell seq 1 2 3 4 5 6 7 8 9 10); do ./$(EXEC); echo "------"; done

# Limpar os arquivos gerados
clean:
	del $(EXEC).exe