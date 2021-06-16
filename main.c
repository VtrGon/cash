#include <stdio.h>
#include <stdlib.h>
#include "lista_ponteiro.h"

int main(){

    FILE *arq;
    Lista L;
    int op;

    create_lista(&L);
    carregar(&L, &arq);

    do{
        system("CLS");
        printf("------ ------ ------- ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------\n"
               "---- --- --- --- --- --- --- --- --- --- --- --- --- CONTABILIDADE --- --- --- --- --- --- --- --- --- --- --- --- ----\n"
               "------ ------ ------- ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ ------\n"
               "1 - ADICIONAR | 2 - NOVO GASTO | 3 - LISTAR | 4 - VISUALIZAR EM DETALHES | 5 - TOTAL INVESTIDO | 6 - REMOVER | 0 - SAIR\n"
               "-----------------------------------------------------------------------------------------------------------------------\n"
               "Escolha a opcao desejada: ");
        scanf("%d", &op);

        if(op > 0) {
            switch(op) {
            case 1:
                novo_mes(&L);
            break;
            case 2:
                novo_gasto(&L);
            break;
            case 3:
                print_lista(L);
            break;
            case 4:
                detalhes(L);
            break;
            case 5:
                investido(L);
            break;
            case 6:
                apagar(&L);
            break;
            default:
                printf("Opcao invalida!");
                getch();
            break;
            }
        }
    }while(op != 0);

    salvar(L, &arq);
    destroy_lista(&L);
    printf("\nArquivo salvo com sucesso!");

    return 0;
}
