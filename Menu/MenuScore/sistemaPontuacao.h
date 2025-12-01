#include "raylib.h"
#include "Fase/Pontuacao/pontuacao.h"

#define MAXRANKING 10

typedef struct {
    char nome[32];
    int pontos;
} JogadorPontos;

/**
 * @brief Lê o arquivo de ranking e preenche o vetor com as entradas encontradas.
 *
 * @param ranking Vetor que receberá os jogadores lidos.
 * @param maxEntradas Capacidade máxima do vetor fornecido.
 * @return Quantidade de jogadores carregados ou -1 em caso de falha.
 */
int leRanking(JogadorPontos *ranking, int maxEntradas);
/**
 * @brief Ordena o vetor de jogadores do ranking em ordem decrescente de pontos.
 *
 * @param ranking Vetor contendo os jogadores carregados.
 * @param totalJogadores Quantidade de posições válidas no vetor.
 */
void ordenaRankingPorPontuacao(JogadorPontos *ranking, int totalJogadores);
/**
 * @brief Desenha na tela cada entrada do ranking ordenado.
 *
 * @param ranking Vetor já ordenado com nome e pontos.
 * @param totalJogadores Quantidade de jogadores a serem mostrados.
 */
void imprimeRankingJogadores(const JogadorPontos *ranking, int totalJogadores);