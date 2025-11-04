#include <stdio.h>
#include <string.h>

#define MAX_TERRITORIO 5

struct Territorio {
  char nome[30];
  char cor[10];
  int tropas;
};

//Função para limpar o buffer de entrada
void limparBufferEntrada() {
  int c;
  while((c = getchar()) != '\n' && c != EOF);
};

int main() {
  struct Territorio continente[MAX_TERRITORIO];

  printf("============================================\n");
  printf("--- Cadastro dos 5 territórios iniciais ---\n");
  printf("============================================\n");
  printf("*** Não coloque acentuação nos nomes ***\n"); //Se colocar acentuação não aparece no console.

  for( int i = 0; i < MAX_TERRITORIO; i++) {
    printf("\n--- Cadastrando Território %d ---\n", i + 1);
    
    printf("Nome do território: ");
    fgets(continente[i].nome, 30, stdin);
    continente[i].nome[strcspn(continente[i].nome, "\n")] = '\0';  // Remove o \n

    printf("Cor do exercito: ");
    fgets(continente[i].cor, 10, stdin);
    continente[i].cor[strcspn(continente[i].cor, "\n")] = '\0';  // Remove o \n

    printf("Número de tropas: ");
    scanf("%d", &continente[i].tropas);
    limparBufferEntrada();  // Limpa todo o buffer do teclado
  };

  printf("\nCadastro inicial dos territórios concluído!\n\n");
  printf("============================================\n");
  printf("======= MAPA DO MUNDO - ESTADO ATUAL =======\n");
  printf("============================================\n");

  //Print dos cadastros feitos
  for( int i = 0; i < MAX_TERRITORIO; i++) {
    printf("\n--- Território %d ---\n", i + 1);
    printf("- Nome: %s\n", continente[i].nome);
    printf("- Dominado por: Exercito %s\n", continente[i].cor);
    printf("- Tropas: %d\n", continente[i].tropas);
  }

  return 0;
}

