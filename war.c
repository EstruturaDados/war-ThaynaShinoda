#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct Territorio {
  char nome[30];
  char cor[10];
  int tropas;
};

int qtdTerritorio;
struct Territorio *continentes;

//Função para limpar o buffer de entrada
void limparBufferEntrada() {
  int c;
  while((c = getchar()) != '\n' && c != EOF);
};

//Função alocar memória
void alocandoMemoria() {
  continentes = (struct Territorio *) calloc(qtdTerritorio, sizeof(struct Territorio));
}

//Função de cadastro
void inicializarTerritorios() {
  printf("============================================\n");
  printf("--- WAR ESTRUTURADO - CADASTRO INICIAL ---\n");
  printf("============================================\n");

  //Quantidade de territórios
  printf("Quantos territórios irá ter no jogo: ");
  scanf("%d", &qtdTerritorio);
  limparBufferEntrada();

  //Aloca memoria
  alocandoMemoria();

  //Se colocar acentuação não aparece no console.
  printf("\n*** Não coloque acentuação nos nomes ***\n"); 

  //Preenchimento de dados
  for( int i = 0; i < qtdTerritorio; i++) {
    printf("\n--- Cadastrando Território %d ---\n", i + 1);
    
    printf("Nome do território: ");
    fgets(continentes[i].nome, 30, stdin);
    continentes[i].nome[strcspn(continentes[i].nome, "\n")] = '\0';  // Remove o \n

    printf("Cor do exercito: ");
    fgets(continentes[i].cor, 10, stdin);
    continentes[i].cor[strcspn(continentes[i].cor, "\n")] = '\0';  // Remove o \n

    printf("Número de tropas: ");
    scanf("%d", &continentes[i].tropas);
    limparBufferEntrada();  // Limpa todo o buffer do teclado
  };

  printf("\nCadastro inicial dos territórios concluído!\n\n");
}

//Função de exibição
void exibirMapa(){
  printf("============================================\n");
  printf("======= MAPA DO MUNDO - ESTADO ATUAL =======\n");
  printf("============================================\n");

  //Print dos cadastros feitos
  for( int i = 0; i < qtdTerritorio; i++) {
    printf("%d. %s (Exercito %s, Tropas: %d)\n", i + 1, continentes[i].nome, continentes[i].cor, continentes[i].tropas);
  }
}

//Função de ataque
void ataque() {
  int atacante;
  int defensor;
  int dadoAtacante, dadoDefensor;
  
  //Inicializa o gerador de números aleatórios
  srand(time(NULL));
  
  //Escolher atacante e defensor
  printf("\n============================================\n");
  printf("--- FASE DE ATAQUE ---\n");
  printf("============================================\n");
  printf("Digite 0 para SAIR.\n\n");
  
  printf("Escolha o território atacante (Ex: 1): ");
  scanf("%d", &atacante);
  
  //Verifica se o usuário quer sair
  if(atacante == 0) {
    printf("Saindo da fase de ataque...\n");
    return;
  }
  
  //Valida se o território existe
  if(atacante < 1 || atacante > qtdTerritorio) {
    printf("Território inválido!\n");
    return;
  }
  
  //Verifica se o atacante tem tropas suficientes
  if(continentes[atacante - 1].tropas <= 1) {
    printf("Território atacante precisa ter mais de 1 tropa para atacar!\n");
    return;
  }

  printf("Escolha o território defensor (Ex: 3): ");
  scanf("%d", &defensor);
  
  //Valida se o território existe
  if(defensor < 1 || defensor > qtdTerritorio) {
    printf("Território inválido!\n");
    return;
  }
  
  //Verifica se não está atacando o próprio território
  if(atacante == defensor) {
    printf("Você não pode atacar seu próprio território!\n");
    return;
  }

  //Sortear dados para atacante e defensor (1 a 6)
  dadoAtacante = (rand() % 6) + 1;
  dadoDefensor = (rand() % 6) + 1;
  
  printf("\n--- BATALHA ---\n");
  printf("Atacante (%s): Dado = %d\n", continentes[atacante - 1].nome, dadoAtacante);
  printf("Defensor (%s): Dado = %d\n", continentes[defensor - 1].nome, dadoDefensor);
  
  //Determina o vencedor
  if(dadoAtacante > dadoDefensor) {
    printf("\n*** ATACANTE VENCEU! ***\n");
    continentes[defensor - 1].tropas--;
    printf("%s perdeu 1 tropa. Tropas restantes: %d\n", continentes[defensor - 1].nome, continentes[defensor - 1].tropas);
    
    //Verifica se o território foi conquistado
    if(continentes[defensor - 1].tropas == 0) {
      printf("\n*** TERRITÓRIO CONQUISTADO! ***\n");
      printf("%s conquistou %s!\n", continentes[atacante - 1].nome, continentes[defensor - 1].nome);
      strcpy(continentes[defensor - 1].cor, continentes[atacante - 1].cor);
      continentes[defensor - 1].tropas = 1;
      continentes[atacante - 1].tropas--;
    }
  } else {
    printf("\n*** DEFENSOR VENCEU! ***\n");
    continentes[atacante - 1].tropas--;
    printf("%s perdeu 1 tropa. Tropas restantes: %d\n", continentes[atacante - 1].nome, continentes[atacante - 1].tropas);
  }
  
  printf("\n");
}


//Função de liberação de memória (genérica - aceita qualquer tipo de ponteiro)
void liberarMemoria(void *estrutura) {
  if (estrutura != NULL) {
    free(estrutura);
    printf("Memória liberada!\n");
  } else {
    printf("Ponteiro já está NULL, nada para liberar.\n");
  }
}

int main() {
  int opcao;
  
  inicializarTerritorios();

  do {
    exibirMapa();
    
    printf("\n============================================\n");
    printf("1 - Realizar ataque\n");
    printf("0 - Sair do jogo\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    
    if(opcao == 1) {
      ataque();
    }
    
  } while(opcao != 0);
  
  printf("\nFim do jogo!\n");

  //Liberação de memória
  liberarMemoria(continentes);
  return 0;
}

