#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *arquivo;
char *nomearq = "impressora.dat";

typedef struct {
  int ID;
  char modelo[100];
  char marca[80];
  int capacidade;
  char pais[50];
  float peso;
  char tipo;
  float preco;
  int anof;
} impressora;

void Mostrar1IMP() {
  arquivo = fopen(nomearq, "rb");
  impressora imp;
  int tam = 0;
  int id;
  fseek(arquivo, 0, SEEK_SET);
  while (!feof(arquivo)) {
    fread(&imp, sizeof(impressora), 1, arquivo);
    if (feof(arquivo)) {
      break;
    };
    tam++;
  }
  printf("\nTAMANHO: %i\n", tam);
  printf("Digite qual o ID da impressora: ");
  scanf("%i", &id);
  getchar();
  
  fseek(arquivo, id * sizeof(impressora), SEEK_SET);
  fread(&imp, sizeof(impressora), 1, arquivo);
  printf("\nID Impressora Nº%i", imp.ID);
  printf("\nModelo: %s", imp.modelo);
  printf("\nMarca: %s", imp.marca);
  printf("\nCapacidade: %i", imp.capacidade);
  printf("\nPais de origem: %s", imp.pais);
  printf("\nPeso: %.2f", imp.peso);
  printf("\nTipo: %c", imp.tipo);
  printf("\nPreco: %.2f", imp.preco);
  printf("\nAno de fabricação: %i", imp.anof);
  fclose(arquivo);
  printf("\n\n");
}
void MostrarIMP() {
  system("clear");
  arquivo = fopen(nomearq, "rb");
  impressora imp;
  int tam = 0;
  fseek(arquivo, 0, SEEK_SET);
  while (!feof(arquivo)) {
    fread(&imp, sizeof(impressora), 1, arquivo);
    if (feof(arquivo)) {
      break;
    };
    printf("\n//------------------------------//");
    printf("\nID Impressora Nº%i", imp.ID);
    printf("\nModelo: %s", imp.modelo);
    printf("\nMarca: %s", imp.marca);
    printf("\nCapacidade: %i paginas", imp.capacidade);
    printf("\nPais de origem: %s", imp.pais);
    printf("\nPeso: %.2fKg", imp.peso);
    printf("\nTipo: %c", imp.tipo);
    printf("\nPreco: R$%.2f", imp.preco);
    printf("\nAno de fabricação: %i", imp.anof);
    tam++;
  }
  fclose(arquivo);
  printf("\n");
}
void InserirIMP() {
  system("clear");
  arquivo = fopen(nomearq, "ab+");
  impressora imp;
  fseek(arquivo, 0, SEEK_END);

 
  int id_existente;
  printf("Digite o ID da impressora: ");
  scanf("%i", &id_existente);
  getchar();

  while (1) {
    fseek(arquivo, 0, SEEK_SET);
    int id;
    int id_duplicado = 0;

  
    while (fread(&imp, sizeof(impressora), 1, arquivo)) {
      if (id_existente == imp.ID) {
        id_duplicado = 1;
        break;
      }
    }

    if (id_duplicado) {
      printf("ID em uso, digite outro por favor: ");
      scanf("%i", &id_existente);
      getchar();
    } else {
      break; 
    }
  }

  imp.ID = id_existente;

  printf("Digite o Modelo da impressora: ");
  gets(imp.modelo);
  printf("Digite a marca da impressora: ");
  gets(imp.marca);
  printf("Digite a capacidade da impressora: ");
  scanf("%i", &imp.capacidade);
  getchar();
  printf("Digite o Pais de origem: ");
  gets(imp.pais);
  printf("Digite o Peso: ");
  scanf("%f", &imp.peso);
  getchar();
  printf("Digite o Tipo (c para colorido e p para preto e branco): ");
  scanf(" %c", &imp.tipo);
  getchar();
  while (imp.tipo != 'P' && imp.tipo != 'C' && imp.tipo != 'p' && imp.tipo != 'c') {
    printf("Digite uma opção válida: ");
    scanf("%c", &imp.tipo);
    getchar();
  }
  printf("Digite o preco da impressora: ");
  scanf("%f", &imp.preco);
  getchar();
  printf("Digite o ano de fabricação: ");
  scanf("%i", &imp.anof);
  getchar();

  fwrite(&imp, sizeof(impressora), 1, arquivo);
  fclose(arquivo);
  printf("\n\n");
}
void RemoverIMP() {
  int id, i, j;
  int tam = 0;
  arquivo = fopen(nomearq, "rb");
  while (!feof(arquivo)) {
    impressora test;
    fread(&test, sizeof(impressora), 1, arquivo);
    if (feof(arquivo)) {
      break;
    };
    tam++;
  }
  impressora *vet;
  vet = malloc(tam * sizeof(impressora));
  printf("Digite o ID da impressora que deseja excluir: ");
  scanf("%i", &id);
  id--;
  getchar();
  while (id < 0 || id >= tam) {
    printf("Opção inválida, digite novamente: ");
    scanf("%i", &id);
    getchar();
  }
  fclose(arquivo);
  arquivo = fopen(nomearq, "rb");
  int x = 0;
  while (!feof(arquivo)) {
    impressora a;
    fread(&a, sizeof(impressora), 1, arquivo);
    if (feof(arquivo)) {
      break;
    };
    vet[x].ID = a.ID;
    strcpy(vet[x].modelo, a.modelo);
    strcpy(vet[x].marca, a.marca);
    strcpy(vet[x].pais, a.pais);
    vet[x].capacidade = a.capacidade;
    vet[x].peso = a.peso;
    vet[x].tipo = a.tipo;
    vet[x].preco = a.preco;
    vet[x].anof = a.anof;
    x++;
  }
  fclose(arquivo);
  arquivo = fopen(nomearq, "wb");
  x = 0;
  for (x = 0; x < tam; x++) {
    impressora imp;
    if (x != id) {
      imp.ID = vet[x].ID;
      strcpy(imp.modelo, vet[x].modelo);
      strcpy(imp.marca, vet[x].marca);
      strcpy(imp.pais, vet[x].pais);
      imp.capacidade = vet[x].capacidade;
      imp.peso = vet[x].peso;
      imp.tipo = vet[x].tipo;
      imp.preco = vet[x].preco;
      imp.anof = vet[x].anof;
      fwrite(&imp, sizeof(impressora), 1, arquivo);
      fseek(arquivo, 0, SEEK_END);
    }
  }
  free(vet);
  fclose(arquivo);
}
void AlterarIMP() {
  system("clear");
  arquivo = fopen(nomearq, "rb+");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  impressora imp;
  int id, i;

  printf("Digite o ID da impressora que deseja alterar: ");
  scanf("%d", &id);
  id--;
  getchar();

  fseek(arquivo, id * sizeof(impressora), SEEK_SET);
  fread(&imp, sizeof(impressora), 1, arquivo);

  if (feof(arquivo)) {
    printf("Impressora com ID %i não encontrada.\n", id);
    fclose(arquivo);
    return;
  }

  printf("\nID Impressora Nº%i", imp.ID);
  printf("\nModelo atual: %s", imp.modelo);
  printf("\nDigite o novo modelo: ");
  gets(imp.modelo);

  printf("\nMarca atual: %s", imp.marca);
  printf("\nDigite a nova marca: ");
  gets(imp.marca);

  printf("\nCapacidade atual: %i", imp.capacidade);
  printf("\nDigite a nova capacidade: ");
  scanf("%i", &imp.capacidade);
  getchar();

  printf("\nPais atual: %s", imp.pais);
  printf("\nDigite o novo Pais: ");
  gets(imp.pais);

  printf("\nPeso atual: %f", imp.peso);
  printf("\nDigite o novo peso: ");
  scanf("%f", &imp.peso);
  getchar();

  printf("\nTipo atual: %c", imp.tipo);
  printf("\nDigite o novo tipo: ");
  scanf("%c", &imp.tipo);
  getchar();

  printf("\nPreco atual: %f", imp.preco);
  printf("\nDigite o novo preco: ");
  scanf("%f", &imp.preco);
  getchar();

  printf("\nAno atual: %i", imp.anof);
  printf("\nDigite o novo ano: ");
  scanf("%i", &imp.anof);
  getchar();

  fseek(arquivo, -sizeof(impressora), SEEK_CUR);
  fwrite(&imp, sizeof(impressora), 1, arquivo);

  fclose(arquivo);
  printf("\nDados da impressora alterados com sucesso.\n\n");
}


main() {
  system("clear");
  int esc;
  do {
    printf("Digite uma opção\n1 - Mostrar uma impressora\n2 - Mostrar todas "
           "impressoras\n3 - Incluir uma impressora\n4 - Excluir uma impressora\n5 - Alterar uma "
         "impressora\n0 - Sair\n");
    scanf("%i", &esc);
    getchar();
    if (esc == 1) {
      Mostrar1IMP();
    } else if (esc == 2) {
      MostrarIMP();
    } else if (esc == 3) {
      InserirIMP();
    } else if (esc == 4) {
      RemoverIMP();
    } else if (esc == 5) {
      AlterarIMP();
    } else if (esc == 0) {
      printf("\nPrograma finalizado");
    } else {
      printf("Opção inválida");
    };
  } while (esc != 0);
}