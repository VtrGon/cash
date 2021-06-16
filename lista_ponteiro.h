#ifndef LISTA_PONTEIRO_H_INCLUDED
#define LISTA_PONTEIRO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    char mes[8];
    float tot_T;
    float inv_T;
    float mom_T;
    float mot_T, mot_G;
    float cmg_T, cmg_G;
    float ots_T, ots_G;
    float res_T, res_G;
}Salario;

typedef struct Celula {
    Salario dado;
    struct Celula *prox;
}Celula;

typedef struct {
    Celula *inicio, *fim;
    int tam;
}Lista;

void create_lista(Lista *L) {

    Celula *temp = (Celula*)malloc(sizeof(Celula));
    temp->prox = NULL;
    L->inicio = L->fim = temp;
    L->tam = 0;
}

bool is_empty_lista(Lista L) {
    return L.inicio == L.fim;
}

void add_fim(Lista *L, Salario dado) {
    Celula *temp = (Celula*)malloc(sizeof(Celula));
    temp->prox = NULL;
    temp->dado = dado;
    L->fim->prox = temp;
    L->fim = temp;
    L->tam++;
}

void add_inicio(Lista *L, Salario dado) {
    Celula *temp = (Celula*)malloc(sizeof(Celula));
    temp->prox = L->inicio;
    L->inicio->dado = dado;
    L->inicio = temp;
    L->tam++;
}

void add_at(Lista *L, Salario dado, int pos) {
    if(pos < 0 || pos >= L->tam)
        return -1;

    Celula *ant = L->inicio;

    for(int i = 0; i < pos; i++)
        ant = ant->prox;

    Celula *temp;

    temp->prox = ant->prox;
    ant->prox = temp;
    temp->dado = dado;
    L->tam++;
}

void print_lista(Lista L) {
    Celula *temp = L.inicio->prox;

    printf("\n  ID    Mes/Ano      Total       Invest.      Mams       Moto       Cmg       Outros      Final\n"
           " ----   -------      ------      ------       ----       ----      -----      ------      -----\n");
    while(temp != NULL) {
        printf("  %02d     %s       %.2f      %.2f      %.2f     %.2f     %.2f       %.2f       %.2f\n", temp->dado.id, temp->dado.mes, temp->dado.tot_T, temp->dado.inv_T, temp->dado.mom_T, temp->dado.mot_T, temp->dado.cmg_T, temp->dado.ots_T, temp->dado.res_T);
        temp = temp->prox;
    }

    getch();
}

int detalhes(Lista L) {
    int pos;
    Celula *ant = L.inicio;

    printf("Digite a posicao que deseja visualizar: ");
    scanf("%d", &pos);

    if(pos < 0 || pos >= L.tam)
        return -1;

    for(int i = 0; i < pos; i++)
        ant = ant->prox;

    printf("\n  ID          Mes/Ano         Total          Invest.         Mams\n"
           " ----         -------         ------         ------          ----\n"
           "  %02d           %s          %.2f         %.2f         %.2f\n\n", ant->prox->dado.id, ant->prox->dado.mes, ant->prox->dado.tot_T, ant->prox->dado.inv_T, ant->prox->dado.mom_T);

    printf("            Moto       Cmg       Outros      Final\n"
           "            ----      -----      ------      -----\n"
           "TOTAL ->   %.2f     %.2f       %.2f       %.2f\n"
           "GASTO ->   %.2f      %.2f       %.2f       %.2f\n"
           "RESUL.->   %.2f     %.2f       %.2f       %.2f\n", ant->prox->dado.mot_T, ant->prox->dado.cmg_T, ant->prox->dado.ots_T, ant->prox->dado.res_T, ant->prox->dado.mot_G, ant->prox->dado.cmg_G, ant->prox->dado.ots_G, ant->prox->dado.res_G, ant->prox->dado.mot_T - ant->prox->dado.mot_G, ant->prox->dado.cmg_T - ant->prox->dado.cmg_G, ant->prox->dado.ots_T - ant->prox->dado.ots_G, ant->prox->dado.res_T - ant->prox->dado.res_G);

    getch();
    return 0;
}

void investido(Lista L) {
    Celula *temp = L.inicio->prox;
    float cont = 0;

    while(temp != NULL) {
        cont = cont + temp->dado.inv_T;
        temp = temp->prox;
    }
    printf("O total investido de %d meses eh de: %.2f", L.tam, cont);

    getch();
}

int remove_at(Lista *L, int pos) {
    if(pos > 0 || pos >= L->tam)
        return -1;

    Celula *ant = L->inicio;

    for(int i = 0; i < pos; i++)
        ant = ant->prox;

    Celula *temp = ant->prox;
    Salario dado = temp->dado;
    ant->prox = temp->prox;

    free(temp);

    L->tam--;

    if(ant->prox == NULL)
        L->fim = ant;

    return 0;
}

void apagar(Lista *L) {
    int pos;
    Celula *ant = L->inicio;

    printf("Digite a posicao que deseja deletar: ");
    scanf("%d", &pos);

    if(pos < 0 || pos >= L->tam)
        return -1;

    remove_at(L, pos);
    print_lista(*L);
}

void novo_mes(Lista *L) {
    Salario dado;
    dado.id = L->tam;

    printf("\nValor da entrada: ");
    scanf("%f", &dado.tot_T);

    printf("\nMes de entrada: ");
    scanf("%s", &dado.mes);

    printf("\nInvestimento: ");
    scanf("%f", &dado.inv_T);

    printf("\nValor mams: ");
    scanf("%f", &dado.mom_T);

    printf("\nValor para gastos com a moto: ");
    scanf("%f", &dado.mot_T);

    printf("\nInvestimento em mim: ");
    scanf("%f", &dado.cmg_T);

    printf("\nOutros: ");
    scanf("%f", &dado.ots_T);

    dado.res_T = dado.tot_T - (dado.inv_T + dado.mom_T + dado.mot_T + dado.cmg_T + dado.ots_T);
    dado.mot_G = dado.cmg_G = dado.ots_G = dado.res_G = 0,0;

    Celula *temp = L->inicio->prox;

    while(temp != NULL) {
        dado.mot_T = dado.mot_T + (temp->dado.mot_T - temp->dado.mot_G);
        dado.cmg_T = dado.cmg_T + (temp->dado.cmg_T - temp->dado.cmg_G);
        dado.ots_T = dado.ots_T + (temp->dado.ots_T - temp->dado.ots_G);
        dado.res_T = dado.res_T + (temp->dado.res_T - temp->dado.res_G);
        temp = temp->prox;
    }

    add_fim(L, dado);
}

void novo_gasto(Lista *L) {
    int op;
    float aux;

    do{
        system("CLS");
        printf("------ ------ ------- ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------\n"
               "---- --- --- --- --- --- --- --- --- --- --- --- --- CONTABILIDADE --- --- --- --- --- --- --- --- --- --- --- --- ----\n"
               "------ ------ ------- ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------\n"
               "1 - ADICIONAR | 2 - NOVO GASTO | 3 - LISTAR | 4 - VISUALIZAR EM DETALHES | 5 - TOTAL INVESTIDO | 6 - REMOVER | 0 - SAIR\n"
               "-----------------------------------------------------------------------------------------------------------------------\n");
        printf("\n1 - MOTO | 2 - MIM | 3 - OUTROS | 4 - RESTANTE | 0 - VOLTAR"
               "\nQual a entrada: ");
        scanf("%d" ,&op);

        if(op > 0) {

            printf("\nQual o valor: ");
            scanf("%f", &aux);

            switch(op) {
            case 1:
                L->fim->dado.mot_G = L->fim->dado.mot_G + aux;
            break;
            case 2:
                L->fim->dado.cmg_G = L->fim->dado.cmg_G + aux;
            break;
            case 3:
                L->fim->dado.ots_G = L->fim->dado.ots_G + aux;
            break;
            case 4:
                L->fim->dado.res_G = L->fim->dado.res_G + aux;
            break;
            default:
                printf("Opcao invalida!");
                getch();
            break;
            }
        }
    }while(op != 0);
}

int carregar(Lista *L, FILE *arq) {
    Salario dado;
    arq = fopen("save.txt", "r");

    if(!arq){
        printf("404, file not found\n");
        return -1;
    }

    while(!feof(arq)) {
        fscanf(arq, "%i\t%[^\t]\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f", &dado.id, &dado.mes, &dado.tot_T, &dado.inv_T, &dado.mom_T, &dado.mot_T, &dado.cmg_T, &dado.ots_T, &dado.res_T, &dado.mot_G, &dado.cmg_G, &dado.ots_G, &dado.res_G);
        add_fim(L, dado);
    }

    fclose(arq);
    return 0;
}

int salvar(Lista L, FILE *arq) {
    arq = fopen("save.txt", "w");

    if(!arq){
        printf("404, file not found\n");
        return -1;
    }

    Celula *temp = L.inicio->prox;

    while(temp != NULL) {
        fprintf(arq, "%i\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", temp->dado.id, temp->dado.mes, temp->dado.tot_T, temp->dado.inv_T, temp->dado.mom_T, temp->dado.mot_T, temp->dado.cmg_T, temp->dado.ots_T, temp->dado.res_T, temp->dado.mot_G, temp->dado.cmg_G, temp->dado.ots_G, temp->dado.res_G);
        temp = temp->prox;
    }
    fclose(arq);
    return 0;
}

void destroy_lista(Lista *L) {

    while(!is_empty_lista(*L))
        remove_at(L, 0);
}

#endif // LISTA_PONTEIRO_H_INCLUDED
