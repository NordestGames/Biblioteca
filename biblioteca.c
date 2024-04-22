#include <stdio.h>
#include "biblioteca.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    char nome[100];
    float valor;
} Livros;

struct no {
    Livros dado;
    struct no* prox;
};

struct Usuario {
    char email[50];
    char name[50];
    char senha[20];
};

struct Usuario users[10];
int contUsuario = 0;

int emailValido(const char *email) {
	int i;
    for (i = 0; i < contUsuario; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}

int emailVerifica(const char *email) {
    int i = 0;
    while (email[i] != '\0') {
        if (email[i] == '@') {
            return 1;
        }
        i++;
    }
    return 0;
}

void registrarUsuario() {
    struct Usuario novoUser;

    printf("Digite seu nome: ");
    scanf("%s", novoUser.name);

    do {
        printf("Digite seu email: ");
        scanf("%s", novoUser.email);

        if (!emailVerifica(novoUser.email)) {
            printf("Email invalido. O email deve conter o caractere '@'.\n");
        } else if (emailValido(novoUser.email)) {
            printf("Este email ja esta em uso. Tente outro.\n");
        }
    } while (!emailVerifica(novoUser.email) || emailValido(novoUser.email));

    printf("Digite sua senha: ");
    scanf("%s", novoUser.senha);

    users[contUsuario++] = novoUser;

    printf("Cadastro realizado com sucesso!\n");
}

int loginUser() {
    char email[50];
    char senha[20];
    int logado = 0;

    printf("Digite seu email: ");
    scanf("%s", email);

    printf("Digite sua senha: ");
    scanf("%s", senha);
	int i;
    for (i = 0; i < contUsuario; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].senha, senha) == 0) {
            printf("Login bem-sucedido! Bem-vindo, %s!\n", users[i].name);
            logado = 1;
            break;
        }
    }

    if (!logado) {
        printf("Email ou senha incorretos. Por favor, tente novamente.\n");
    }
}


int totalId = 1;

typedef struct no No;

typedef struct {
    No* inicio;
} Lista;

void adicionaFim(Lista *lista, Livros e) {
    No* novo = (No*) malloc(sizeof(No));
    novo->dado = e;
    novo->prox = NULL;
    if (lista->inicio == NULL) {
        lista->inicio = novo;
    }
    else {
        No* pi;
        for (pi = lista->inicio; pi->prox != NULL; pi = pi->prox);
        pi->prox = novo;
    }
}

void mostrar(Lista lista) {
    No* pi;
    for (pi = lista.inicio; pi != NULL; pi = pi->prox){
        Livros dado = pi->dado;
        printf("%d %s %f\n", dado.id, dado.nome , dado.valor);
    }
}

void editarValor(Lista* lista, int id, float valor) {
  if (lista->inicio == NULL) {
    printf("Lista vazia\n");
  }
  else {
    No* pi;
    for (pi = lista->inicio; pi != NULL && pi->dado.id != id; pi = pi->prox);
    if (pi == NULL) {
      printf("Livro nao encontrado\n");
    }
    else {
      pi->dado.valor = valor;
    }
  }  
}

void deletar(Lista *lista, int id) {
  if (lista->inicio == NULL) {
    printf("Lista vazia\n");
  }
  else {
      No* pa = NULL;
      No* pi;
      for (pi = lista->inicio; pi->prox != NULL && pi->dado.id != id; pi = pi->prox) {
        pa = pi;
      }
      if (pa == NULL) {
        if (pi->dado.id == id) {
          lista->inicio = pi->prox;
          free(pi);
        }
        else {
          printf("Elemento nao encontrado\n");
        }
      }
      else {
        if (pi->dado.id == id) {
          pa->prox = pi->prox;
          free(pi);
        }
        else {
          printf("Elemento nao encontrado\n");
        }
      }
  }
}


void ler(Livros *e) {
    printf("Informe os dados do livro:\n");
    scanf("%d %s %f", &e->id, e->nome, &e->valor);
}

void telaInicial(){
	printf("+===================================+\n");
	printf("    SEJA BEM VINDO A BIBLIOTECA      \n");
	printf("+===================================+\n");
}

void menu() {
    printf("+===== Escolha uma Opcao ======+\n");
    printf(" 1 - Cadastar livro\n");
    printf(" 2 - Listar livros\n");
    printf(" 3 - Buscar livros\n");
    printf(" 4 - Quantidade de livros\n");
    printf(" 5 - Excluir um livros\n");
    printf(" 6 - Editar o valor do livro\n");
    printf(" 0 - Sair\n");
    printf("+===============================+\n");
}

void cadastrar() {
    FILE* file = fopen("livros.b", "ab");
    Livros a;
    a.id = totalId++;
    printf("Informe o nome do livro:\n");
    scanf(" %[^\n]", a.nome);
    printf("Informe o valor do livro:\n");
    scanf("%f", &a.valor);
    fwrite(&a, sizeof(Livros), 1, file);
    fclose(file);
}

void buscar (int id) {
    FILE* file = fopen("livros.b", "rb");
    Livros a;
    int entrou = 0;
    while (fread(&a, sizeof(Livros), 1, file)) {
        if (a.id == id) {
            printf("%d: %s %f\n", a.id, a.nome, a.valor);
            entrou = 1;
        }
    }
    if (entrou == 0) {
        printf("Livro nao encontrado\n");
    }
    fclose(file);
}

void listar() {
    FILE* file = fopen("livros.b", "rb");
    Livros a;
    printf("+============================================================+\n");
    printf("                     LIVROS DISPON�VEIS                       \n");
	printf("+============================================================+\n");
    printf("| %3s | %-36s | %-5s |\n", "ID", "NOME", "VALOR");
    while (fread(&a, sizeof(Livros), 1, file)) {
        printf("| %3d | %-36s | %.2f |\n", a.id, a.nome, a.valor);
    }
    fclose(file);
}

int tamanho() {
    FILE* file = fopen("livros.b", "rb");
    Livros a;
    int cont = 0;
    while (fread(&a, sizeof(Livros), 1, file)) {
        cont++;
    }
    fclose(file);
    return cont;
}

void lerLista(Lista *lista) {
  FILE *file = fopen("livros.b", "rb");
  Livros e;
  while (fread(&e, sizeof(Livros), 1, file)) {
      adicionaFim(lista, e);
  }
  fclose(file);
}

void salvaLista(Lista *lista) {
  FILE *file = fopen("livros.b", "wb");
  No* pi;
  for (pi = lista->inicio; pi != NULL; pi = pi->prox) {
    fwrite(&pi->dado, sizeof(Livros), 1, file);
  }
  fclose(file);
}

void excluir(int id) {
    Lista lista;
    lista.inicio = NULL;
    lerLista(&lista);
    deletar(&lista, id);
    salvaLista(&lista);
}

void editar(int id) {
    Lista lista;
    lista.inicio = NULL;
    lerLista(&lista);
    float valor;
    printf("Informe o valor:\n");
    scanf("%f", &valor);
    editarValor(&lista, id, valor);
    salvaLista(&lista);
}
