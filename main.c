#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DISCOS 10

typedef struct{
    int discos[MAX_DISCOS];
    int topo;
} Pilha;

int movimentos = 0;
int n;

// Inicializa as três torres com topo = -1, ou seja, vazio.
void inicializar(Pilha torres[]){
    for (int i = 0; i < 3; i++){
        torres[i].topo = -1;
    }
}

void desenhar(Pilha torres[]){
    system("clear"); //limpa a tela pra atualização da animação

    printf("TORRES DE HANOI\n");
    printf("Discos: %d | Movimento: %d/%d\n\n",
           n, movimentos, (1 << n) - 1);

    for (int nivel = n - 1; nivel >= 0; nivel--) {
        for (int t = 0; t < 3; t++) {
            int disco = 0;
            
            if (nivel <= torres[t].topo) {
                disco = torres[t].discos[nivel];
            }
            int largura = 2 * n + 1;
            
            if (disco == 0) {
                printf("%*s|%*s", n, "", n, "");
            }
            else {
                int tamanho = disco * 2 - 1;
                int margem = (largura - tamanho) / 2;
                
                printf("%*s", margem, "");
                
                for (int j = 0; j < tamanho; j++) {
                    printf("=");
                }
                printf("%*s", largura - margem - tamanho, "");
            }
            printf("     ");
        }
        printf("\n");
    }
    for (int t = 0; t < 3; t++) {
        printf("%*s_%*s     ", n, "", n, "");
    }
    printf("\n");
    for (int t = 0; t < 3; t++) {
        printf("%*s%c%*s     ", n, "", 'A' + t, n, "");
    }
    printf("\n");
}

void mover(Pilha *origem, Pilha *destino, Pilha torres[], char a, char b){
    int disco;
    
    if (origem->topo == -1) {
        printf("Movimento invalido!\n");
        exit(1);
    }
    
    disco = origem->discos[origem->topo];
    
    if (destino->topo != -1 && disco > destino->discos[destino->topo]){
        printf("Movimento invalido!\n");
        exit(1);
    }
    
    origem->topo--;
    
    destino->topo++;
    destino->discos[destino->topo] = disco;
    
    movimentos++;
    
    desenhar(torres);
    
    printf("\nDisco %d: %c -> %c\n", disco, a, b);
    
    //delay de 0,9s
    struct timespec tempo;
    tempo.tv_sec = 0;
    tempo.tv_nsec = 900000000;
    nanosleep(&tempo, NULL);
}

// Recursividade
void hanoi(int quantidade,
           Pilha *origem,
           Pilha *destino,
           Pilha *auxiliar,
           Pilha torres[],
           char a, char b, char c) {
    
    if (quantidade == 1) {
        mover(origem, destino, torres, a, b);
        return;
    }
    
    hanoi(quantidade - 1, origem, auxiliar, destino,
          torres, a, c, b);
    mover(origem, destino, torres, a, b);
    hanoi(quantidade - 1, auxiliar, destino, origem,
          torres, c, b, a);
}

int main() {
    Pilha torres[3];
    inicializar(torres);
    
    printf("Quantidade de discos (1 a %d): ", MAX_DISCOS);
    
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_DISCOS){
        printf("Quantidade invalida!\n");
        return 1;
    }
    
    //Coloca todos os discos na primeira torre
    for (int i = n; i >= 1; i--){
        torres[0].topo++;
        torres[0].discos[torres[0].topo] = i;
    }
    
    desenhar(torres);
    
    //delay de 0,9s
    struct timespec tempo;
    tempo.tv_sec = 0;
    tempo.tv_nsec = 900000000;
    nanosleep(&tempo, NULL);

    hanoi(n, &torres[0], &torres[2], &torres[1],
          torres, 'A', 'C', 'B');
          
    printf("\nPROBLEMA RESOLVIDO!\n");
    printf("Total de movimentos: %d\n", movimentos);
    printf("Movimentos minimos: %d\n", (1 << n) - 1);
    
    return 0;
}
