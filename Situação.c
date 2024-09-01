#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int peso;
    char descricao[100];
} Caixa;

typedef struct {
    Caixa *caixas;
    int topo;
    int capacidade;
} Pilha;

Pilha* criarPilha(int capacidade) {
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
    pilha->capacidade = capacidade;
    pilha->topo = -1;
    pilha->caixas = (Caixa*)malloc(capacidade * sizeof(Caixa));
    return pilha;
}

int isFull(Pilha* pilha) {
    return pilha->topo == pilha->capacidade - 1;
}

int isEmpty(Pilha* pilha) {
    return pilha->topo == -1;
}

void push(Pilha* pilha, Caixa caixa) {
    if (isFull(pilha)) {
        printf("A pilha está cheia! Não é possível adicionar mais caixas.\n");
        return;
    }
    pilha->caixas[++pilha->topo] = caixa;
}

Caixa pop(Pilha* pilha) {
    if (isEmpty(pilha)) {
        printf("A pilha está vazia! Não é possível remover caixas.\n");
        Caixa caixaVazia;
        caixaVazia.id = -1;
        return caixaVazia;
    }
    return pilha->caixas[pilha->topo--];
}

Caixa peek(Pilha* pilha) {
    if (isEmpty(pilha)) {
        printf("A pilha está vazia!\n");
        Caixa caixaVazia;
        caixaVazia.id = -1;
        return caixaVazia;
    }
    return pilha->caixas[pilha->topo];
}

int consultarCaixa(Pilha* pilha, int id) {
    for (int i = 0; i <= pilha->topo; i++) {
        if (pilha->caixas[i].id == id) {
            return i;
        }
    }
    return -1;
}

void removerCaixa(Pilha* pilhaA, Pilha* pilhaB, Pilha* pilhaC, int id) {
    int indice = consultarCaixa(pilhaA, id);
    if (indice == -1) {
        printf("Caixa com ID %d não encontrada na pilha A.\n", id);
        return;
    }

    while (pilhaA->topo >= indice) {
        Caixa caixa = pop(pilhaA);
        if (pilhaA->topo >= 0 && pilhaA->caixas[pilhaA->topo].peso < caixa.peso) {
            push(pilhaB, caixa);
        } else {
            push(pilhaC, caixa);
        }
    }

    printf("Caixa com ID %d removida.\n", id);

    while (!isEmpty(pilhaB)) {
        push(pilhaA, pop(pilhaB));
    }
    while (!isEmpty(pilhaC)) {
        push(pilhaA, pop(pilhaC));
    }
}

void inserirCaixa(Pilha* pilhaA, Pilha* pilhaB, Pilha* pilhaC, Caixa novaCaixa) {
    while (!isEmpty(pilhaA) && peek(pilhaA).peso < novaCaixa.peso) {
        push(pilhaB, pop(pilhaA));
    }

    push(pilhaA, novaCaixa);

    while (!isEmpty(pilhaB)) {
        push(pilhaA, pop(pilhaB));
    }
}

int main() {
    Pilha* pilhaA = criarPilha(100);
    Pilha* pilhaB = criarPilha(100);
    Pilha* pilhaC = criarPilha(100);

    int opcao;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Adicionar caixa\n");
        printf("2. Verificar caixa\n");
        printf("3. Retirar caixa\n");
        printf("4. Sair\n");
        printf("Selecione uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Caixa novaCaixa;
                printf("Digite o ID da caixa: ");
                scanf("%d", &novaCaixa.id);
                printf("Digite o peso da caixa (3, 5, ou 7 toneladas): ");
                scanf("%d", &novaCaixa.peso);
                printf("Digite uma descrição da caixa: ");
                scanf(" %[^\n]", novaCaixa.descricao);
                inserirCaixa(pilhaA, pilhaB, pilhaC, novaCaixa);
                break;
            }
            case 2: {
                int id;
                printf("Digite o ID da caixa para verificar: ");
                scanf("%d", &id);
                int posicao = consultarCaixa(pilhaA, id);
                if (posicao == -1) {
                    printf("Caixa com ID %d não encontrada na pilha A.\n", id);
                } else {
                    printf("Caixa com ID %d encontrada na posição %d da pilha A.\n", id, posicao);
                }
                break;
            }
            case 3: {
                int id;
                printf("Digite o ID da caixa para retirar: ");
                scanf("%d", &id);
                removerCaixa(pilhaA, pilhaB, pilhaC, id);
                break;
            }
            case 4:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 4);

    free(pilhaA->caixas);
    free(pilhaA);
    free(pilhaB->caixas);
    free(pilhaB);
    free(pilhaC->caixas);
    free(pilhaC);

    return 0;
}
