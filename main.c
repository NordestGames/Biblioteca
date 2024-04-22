#include "biblioteca.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int main(void) {
	int opLogin;
	bool logado = false;
	bool registrado = false;

    while (!logado) {
        printf("\n1. Entrar\n");
        printf("2. Cadastrar\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opLogin);

        switch (opLogin) {
            case 1:
                if (loginUser()) {
                	logado = true;
				}
                break;
            case 2:
                registrarUsuario();
                registrado = true;
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
	}
	
    int op;
    telaInicial();
    menu();
    scanf("%d", &op);
    while (op != 0) {
        if (op == 1) {
           cadastrar();
        } else if (op == 2) {
            listar();
        } else if (op == 3) {
            int id;
            printf("Informe o id do livro que deseja buscar:\n");
            scanf("%d", &id);
            buscar(id);
        } else if (op == 4) {
            int n = tamanho();
            printf("Quantidade de livros: %d\n", n);
        } else if (op == 5) {
            int id;
            printf("Informe o id para excluir o livro:\n");
            scanf("%d", &id);
            excluir(id);
        } else if (op == 6) {
            int id;
            printf("Informe o id do livro para editar o valor:\n");
            scanf("%d", &id);
            editar(id);
        }
        menu();
        scanf("%d", &op);
    }
    return 0;
}
