#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define LIMITE 100

typedef struct {
    int id;
} ThreadData;

pthread_barrier_t largada;
pthread_mutex_t lock;

int *progresso;
int *ranking;
int posicao = 0;
int total_threads;

// Barra de progresso simples
void barra(int valor) {
    int tamanho = 20;
    int preenchido = (valor * tamanho) / LIMITE;

    printf("[");
    for (int i = 0; i < tamanho; i++) {
        if (i < preenchido) printf("#");
        else printf("-");
    }
    printf("] %d", valor);
}

// Imprime estado das threads
void imprimir_status() {
    printf("\n");
    for (int i = 0; i < total_threads; i++) {
        printf("T%d ", i);
        barra(progresso[i]);
        printf("\n");
    }
}

void *corrida(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int id = data->id;

    pthread_barrier_wait(&largada);

    for (int i = 0; i <= LIMITE; i++) {

        usleep(rand() % 50000);

        pthread_mutex_lock(&lock);

        progresso[id] = i;

        imprimir_status();

        if (i == LIMITE) {
            ranking[posicao++] = id;

            if (posicao == 1) {
                printf("Vencedor: T%d\n", id);
            }
        }

        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

int main() {
    int n;

    printf("Numero de threads: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Numero invalido\n");
        return 1;
    }

    total_threads = n;

    pthread_t *threads = malloc(sizeof(pthread_t) * n);
    ThreadData *dados = malloc(sizeof(ThreadData) * n);

    progresso = calloc(n, sizeof(int));
    ranking = malloc(sizeof(int) * n);

    pthread_barrier_init(&largada, NULL, n);
    pthread_mutex_init(&lock, NULL);

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        dados[i].id = i;
        pthread_create(&threads[i], NULL, corrida, &dados[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nRanking final:\n");
    for (int i = 0; i < n; i++) {
        printf("%d: T%d\n", i + 1, ranking[i]);
    }

    pthread_barrier_destroy(&largada);
    pthread_mutex_destroy(&lock);

    free(threads);
    free(dados);
    free(progresso);
    free(ranking);

    return 0;
}