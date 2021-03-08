/* Alunos:
Gabriel Alves Hussein   17/0103200
Victor Amaral Cerqueira 17/0164411
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Cidade{
    char nome[50];
    int valido;
    int visitado;
}CIDADE;

void mostrarCidades(CIDADE *nCidades);
void adicionaCidade(int *nCidades, CIDADE *cidade);
void removeCidade(int *nCidades, CIDADE *cidade, int relacoes[100][100]);
void mostraMenu(int nCidades);
void adicionaRota(CIDADE *cidade, int relacoes[100][100], int distancia[100][100]);
void removeRota(CIDADE *cidade, int relacoes[100][100], int distancia[100][100]);
void listaCidades(int pessoa, CIDADE *cidade, int relacoes[100][100], int distancia[100][100]);
void pesquisaRota(CIDADE *cidade, int relacoes[100][100], int *nCidades, int distancia[100][100]);
int dijkstra(int cidadeOrigem, int cidadeDestino, int relacoes[100][100], CIDADE *cidade, int *nCidades, int distancia[100][100]);
void geraLista(CIDADE * cidade, int relacoes[100][100], int distancia[100][100], int *nCidades);

int cnt;
int pre[100];

int main(){
    CIDADE cidade[100];
    int relacoes[100][100] = {0};
    int distancia[100][100] = {0}; 
    int nCidades = 0;
    int opcao = 0;

    for(int i = 0;i < 100; i++)
        cidade[i].valido = 0;

    geraLista(cidade, relacoes, distancia, &nCidades);

    do{
        mostraMenu(nCidades);
        scanf("%d",&opcao);
        system("clear");
        switch(opcao){
        case 1:
            pesquisaRota(cidade, relacoes, &nCidades, distancia);
            getc(stdin);
            printf("Aperte enter para voltar ao menu.");
            break;
        case 2:
            printf("Lista de cidades cadastradas:\n");
            mostrarCidades(cidade);
            printf("Aperte enter para voltar ao menu.");
            getc(stdin);
            break;
        case 3:
            adicionaCidade(&nCidades,cidade);
            break;
        case 4:
            removeCidade(&nCidades,cidade,relacoes);
            break;
        case 5:
            adicionaRota(cidade, relacoes, distancia);
            break;
        case 6:
            removeRota(cidade, relacoes, distancia);
            break;
        case 7:
            for(int i = 0;i < 100; i++){
               if(cidade[i].valido != 0){
                  printf("Caminhos de %s:\n",cidade[i].nome);
                  listaCidades(i+1, cidade, relacoes, distancia);
                  printf("\n");
               }
            }
            printf("Aperte enter para voltar ao menu.");
            getc(stdin);
        }

  }while(opcao != 0);
    

    return 0;
}

void pesquisaRota(CIDADE *cidade, int relacoes[100][100], int *nCidades, int distancia[100][100]){
    int cidadeOrigem, cidadeDestino;
    int distanciaTotal = 0;
    
    mostrarCidades(cidade);
    printf("Informe o numero da cidade de origem e o numero da cidade de destino: ");
    scanf("%d", &cidadeOrigem);
    scanf("%d", &cidadeDestino);
    
    distanciaTotal = dijkstra(cidadeOrigem-1, cidadeDestino-1, relacoes, cidade, nCidades, distancia);
    printf("A menor rota possível da cidade %s a cidade %s e de %d Km\n", cidade[cidadeOrigem-1].nome, cidade[cidadeDestino-1].nome, distanciaTotal);
}

int dijkstra(int cidadeOrigem, int cidadeDestino, int relacoes[100][100], CIDADE *cidade, int *nCidades, int distancia[100][100]){
    int distanciaParcial = 9999999;
    int distanciaTotal = 0;
    int cidadeAlvo = cidadeOrigem;
    int cidadesVisitadas = 0;
    printf("Menor rota possivel de %s a %s \n", cidade[cidadeOrigem].nome, cidade[cidadeDestino].nome);
    
    for(int x=0; x <= *nCidades; x++){
        if(cidadeAlvo==x && cidadeAlvo!=cidadeDestino){
            cidade[x].visitado = 1;
            for(int y=0; y <= *nCidades; y++){
                if(relacoes[x][y]==1 && cidade[y].visitado == 0){
                    if(distancia[x][y] < distanciaParcial){
                        distanciaParcial = distancia[x][y];
                        cidadeAlvo = y;
                    }
                }
            }
            printf("%s -> %s Distancia: %d Km\n", cidade[x].nome, cidade[cidadeAlvo].nome, distanciaParcial);
            distanciaTotal += distanciaParcial;
            x=0;
        }
        for(int i=0; i <= *nCidades; i++){
            if(cidade[i].visitado==1){
                cidadesVisitadas++;
            }
            if(cidadesVisitadas==*nCidades){
                return distanciaTotal;
            }
        }
    }
}

void mostrarCidades(CIDADE *cidade){
    for(int i = 0;i < 100; i++){
        if(cidade[i].valido != 0){
            printf("%d - %s\n",i+1,cidade[i].nome);
        }
    }
}

void adicionaCidade(int *nCidades,CIDADE *cidade){
    if(*nCidades < 100){
        int i = 0;
        while(cidade[i].valido != 0){
            i++;
        }
        printf("Informe a cidade a ser cadastrada:\n");
        scanf (" %[^\n]s", cidade[i].nome);
        cidade[i].valido = 1;
        cidade[i].visitado = 0;
        *nCidades = *nCidades + 1;
    }
    else{
        printf("Numero maximo de cidades cadastradas.\n");
    }
}

void removeCidade(int *nCidades,CIDADE *cidade,int relacoes[100][100]){
    int suspeito;

    mostrarCidades(cidade);
    printf("Informe o numero da cidade a ser cadastrada:\n");
    scanf("%d",&suspeito);
    if(cidade[suspeito-1].valido = 1){
      cidade[suspeito-1].valido = 0;
      for(int i = 0;i < 100;i++){
        relacoes[suspeito-1][i] = 0;
        relacoes[i][suspeito-1] = 0;
      }
      *nCidades = *nCidades - 1;
    }
    else{
        printf("Numero informado nao corresponde ao de uma cidade.\n");
    }
}

void mostraMenu(int nCidades){
  //system("clear");
  printf("\n");
  printf(" ====================================================\n");
  printf("|                 Hussein Turismo                    |\n");
  printf("|             >>>>>>>>> Menu <<<<<<<<<               |\n");
  printf("| 1 - Pesquisar rota                                 |\n");
  printf("| 2 - Mostrar todas as cidades                       |\n");
  printf("| 3 - Adicionar Cidade (%d disponíveis para cadastro)|\n",100 - nCidades);
  printf("| 4 - Remover Cidade (%d disponíveis para cadastro)  |\n", nCidades);
  printf("| 5 - Adicionar rota                                 |\n");
  printf("| 6 - Remover rota                                   |\n");
  printf("| 7 - Visualizar todas as rotas                      |\n");
  printf("| 0 - Sair                                           |\n");
  printf(" ====================================================\n");
  printf("Sua opcao: ");
}

void adicionaRota(CIDADE *cidade, int relacoes[100][100], int distancia[100][100]){
    int cidadeOrigem,cidadeDestino, distanciaCidades;
    mostrarCidades(cidade);
    printf("Descreva uma nova rota entre cidades:");
    scanf("%d",&cidadeOrigem);
    scanf("%d",&cidadeDestino);
    if(cidade[cidadeOrigem-1].valido == 1 && cidade[cidadeDestino-1].valido == 1){
      if(relacoes[cidadeOrigem-1][cidadeDestino-1] == 0){
        printf("Qual a distancia entre as duas cidades?");
        scanf("%d", &distanciaCidades);
        relacoes[cidadeDestino-1][cidadeOrigem-1] = 1;
        relacoes[cidadeOrigem-1][cidadeDestino-1] = 1;
        distancia[cidadeOrigem-1][cidadeDestino-1] = distanciaCidades;
        distancia[cidadeDestino-1][cidadeOrigem-1] = distanciaCidades;
      }
      else{
        printf("Ja existe uma rota registrada entre essas duas cidades, favor apertar enter para voltar ao menu");
        getc(stdin);
      }
    }
    else{
      printf("Algum dos numeros informados nao corresponde a nenhuma cidade cadastrada, aperte enter para voltar ao menu.");
      getc(stdin);
    }
}

void removeRota(CIDADE *cidade, int relacoes[100][100], int distancia[100][100]){
    int cidadeOrigem,cidadeDestino;
    mostrarCidades(cidade);
    printf("Digite o numero de duas cidades e remova a rota existente entre elas:");
    scanf("%d",&cidadeOrigem);
    scanf("%d",&cidadeDestino);
    if(cidade[cidadeOrigem-1].valido == 1 && cidade[cidadeDestino-1].valido == 1){
      if(relacoes[cidadeOrigem-1][cidadeDestino-1] == 1){
         relacoes[cidadeOrigem-1][cidadeDestino-1] = 0;
         relacoes[cidadeDestino-1][cidadeOrigem-1] = 0;
         distancia[cidadeOrigem-1][cidadeDestino-1] = 0;
         distancia[cidadeDestino-1][cidadeOrigem-1] = 0;
      }
      else{
          printf("Nao ha rota registrada entre essas duas cidades, favor verificar se o numero cadastrado esta correto, aperte enter para voltar ao menu.");
          getc(stdin);
      }
    }
    else{
      printf("Algum dos numeros informados nao corresponde a nenhuma cidade cadastrada, aperte enter para voltar ao menu.");
      getc(stdin);
    }
}

void listaCidades(int pessoa, CIDADE *cidade, int relacoes[100][100], int distancia[100][100]){
    for(int i = 0;i < 100; i++){
        if(relacoes[pessoa-1][i] != 0){
            printf("%d - %s\n",i+1,cidade[i].nome);
            printf("    Distância entre cidades: %d km\n", distancia[pessoa-1][i]);
        }
    }
}

void geraLista(CIDADE *cidade, int relacoes[100][100], int distancia[100][100], int *nCidade){
    strcpy(cidade[0].nome, "Brasilia");
    cidade[0].valido = 1;
    *nCidade = *nCidade + 1;
    strcpy(cidade[1].nome, "Sao Paulo");
    cidade[1].valido = 1;
    *nCidade = *nCidade + 1;
    strcpy(cidade[2].nome, "Rio de Janeiro");
    cidade[2].valido = 1;
    *nCidade = *nCidade + 1;
    strcpy(cidade[3].nome, "Recife");
    cidade[3].valido = 1;
    *nCidade = *nCidade + 1;

    relacoes[0][1] = 1;
    distancia[0][1] = 1000;
    relacoes[1][0] = 1;
    distancia[1][0] = 1000;
    relacoes[1][2] = 1;
    distancia[1][2] = 434;
    relacoes[2][1] = 1;
    distancia[2][1] = 434;
    relacoes[0][3] = 1;
    distancia[0][3] = 1500;
    relacoes[3][0] = 1;
    distancia[3][0] = 1500;
    relacoes[1][3] = 1;
    distancia[1][3] = 400;
    relacoes[3][1] = 1;
    distancia[3][1] = 400;
}