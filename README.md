# Corrida-de-Threads

🧵 Thread Race Simulation (C / Pthreads)

Simulação de uma corrida utilizando múltiplas threads em C com a biblioteca pthread. Cada thread representa um competidor com velocidade variável, simulada por atrasos aleatórios.

O projeto foca em conceitos fundamentais de concorrência, incluindo sincronização e controle de acesso a regiões críticas.

⚙️ Funcionalidades
Execução concorrente com múltiplas threads
Largada sincronizada com pthread_barrier
Definição segura do vencedor com pthread_mutex
Simulação de velocidade aleatória (usleep)
Resultado não determinístico
🧠 Conceitos aplicados
Programação concorrente
Sincronização de threads
Exclusão mútua
Condição de corrida (race condition)
Região crítica
▶️ Compilação e execução
gcc corrida.c -o corrida -lpthread
./corrida
