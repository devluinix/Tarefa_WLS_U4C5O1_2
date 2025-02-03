#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h" // Biblioteca para usar temporizadores

// Declaração dos pinos
#define BOTAO_PIN 5
#define LED_VERMELHO 13
#define LED_VERDE 12
#define LED_AZUL 11

// Enumeração para os passos da sequência de LEDs
typedef enum
{
    PASSO_DOIS,
    PASSO_UM,
    DESLIGAR
} passo_t;

volatile bool sequencia_ativa = false; // Variável para controlar se a sequência

// Função pra chamar o temporizador
int64_t passo_callback(alarm_id_t id, void *user_data)
{
    passo_t passo = (passo_t)user_data; // Recebe o passo atual da sequência
    switch (passo)
    {
    case PASSO_DOIS:
        gpio_put(LED_AZUL, 0); // Apaga o LED azul
        // Agenda o próximo passo (PASSO_UM) para daqui a 3 segundos
        add_alarm_in_ms(3000, passo_callback, (void *)PASSO_UM, true);
        break;
    case PASSO_UM:
        gpio_put(LED_VERMELHO, 0); // Apaga o LED vermelho
        // Agenda o próximo passo (DESLIGAR) para daqui a 3 segundos
        add_alarm_in_ms(3000, passo_callback, (void *)DESLIGAR, true);
        break;
    case DESLIGAR:
        gpio_put(LED_VERDE, 0);  // Apaga o LED verde
        sequencia_ativa = false; // Finaliza a sequência
        break;
    }
    return 0; // Retorno padrão (não usado aqui)
}

// Função para evitar que o botão seja lido várias vezes
int64_t funcao_debounce(alarm_id_t id, void *user_data)
{
    uint gpio = (uint)user_data; // Pino do botão

    // Verifica se o botão está pressionado
    if (!gpio_get(gpio) && !sequencia_ativa)
    {
        sequencia_ativa = true; // Ativa a sequência
        gpio_put(LED_AZUL, 1);
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 1);
        // Agenda o primeiro passo da sequência (PASSO_DOIS) para daqui a 3 segundos
        add_alarm_in_ms(3000, passo_callback, (void *)PASSO_DOIS, true);
    }
    // Reativa a interrupção do botão para que ele possa ser pressionado novamente
    gpio_set_irq_enabled(gpio, GPIO_IRQ_EDGE_FALL, true);
    return 0;
}

// Função chamada quando o botão é pressionado
void botao_pressionado(uint gpio, uint32_t eventos)
{
    // Desativa a interrupção do botão temporariamente para evitar leituras múltiplas
    gpio_set_irq_enabled(gpio, GPIO_IRQ_EDGE_FALL, false);
    // Agenda a função de debounce para ser chamada após 50ms
    add_alarm_in_ms(50, funcao_debounce, (void *)gpio, true);
}

int main()
{
    stdio_init_all(); // Inicializa a comunicação com o computador (para depuração)

    // Configuração dos LEDs
    gpio_init(LED_AZUL);
    gpio_init(LED_VERMELHO);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Configuração do botão
    gpio_init(BOTAO_PIN);
    gpio_set_dir(BOTAO_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_PIN);

    // Configura a interrupção para detectar quando o botão é pressionado
    gpio_set_irq_enabled_with_callback(BOTAO_PIN, GPIO_IRQ_EDGE_FALL, true, &botao_pressionado);

    while (true)
    {
        sleep_ms(100);
    }
}