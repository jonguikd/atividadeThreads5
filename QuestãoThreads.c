#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


int somaMatriz = 0;
int tamanhoMatriz = 0;

void *sumMa(void *args);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct arguments {

        int line;
        int *actualLine;

};

int main() {

        scanf(" %d", &tamanhoMatriz);
        int matriz[tamanhoMatriz][tamanhoMatriz];
        
        pthread_t threads[tamanhoMatriz];
        
        for (int i = 0; i < tamanhoMatriz; i++) {
                for (int j = 0; j < tamanhoMatriz; j++) {
                        scanf(" %d", &matriz[i][j]);
                }  
        }

        for (int i = 0; i < tamanhoMatriz; i++) {
                struct arguments *args = malloc(sizeof(struct arguments));
                args->line = i;
                args->actualLine = malloc(tamanhoMatriz * sizeof(int));
                for (int j = 0; j < tamanhoMatriz; j++) {
                        args->actualLine[j] = matriz[i][j];
                }
                pthread_create(&(threads[i]), NULL, sumMa, (void *)args);
        }


        for (int i = 0; i < tamanhoMatriz; i++) {
                pthread_join(threads[i], NULL);
        }
       
        printf("\nTotal da suma: %d\n", somaMatriz);
}

void *sumMa(void *args) {

        pthread_mutex_lock(&mutex);
        struct arguments *argsCasted = (struct arguments *) args;
        printf("\n- Line %d: ", argsCasted->line);
        int x = 0;
        for (int i = 0; i < tamanhoMatriz; i++) {
                x += argsCasted->actualLine[i];
        }
        somaMatriz += x;
        printf("%d", x);
        
        pthread_mutex_unlock(&mutex);

        return args;

}
