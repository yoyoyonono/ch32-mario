#include <ch32v10x.h>
#include <debug.h>

void tim2_init();
void set_buzzer_freq(uint16_t freq);

int main() {
    USART_Printf_Init(115200);
    printf(__TIMESTAMP__);
    printf("\r\n");
    const volatile uint32_t* pulUID = static_cast<const volatile uint32_t*>((const void*)0x1FFFF7E8UL);
    printf("Unique ID: %08lX %08lX %08lX\r\n", pulUID[2], pulUID[1], pulUID[0]);
    printf("SystemCoreClock: %d\r\n", (int)SystemCoreClock);

    tim2_init();

//    TIM2->ATRLR = 50;
//    TIM2->CH3CVR = 40;

    set_buzzer_freq(500);

    return 0;
}

void tim2_init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM2->PSC = (SystemCoreClock / 1000000) - 1;
    TIM2->ATRLR = 1000;
    TIM2->CNT = 0;
    TIM2->CHCTLR2 = 0b0000000001100000;
    TIM2->CCER = 0b0000000100000000;
    TIM2->CH3CVR = 500;
}

void set_buzzer_freq(uint16_t freq) {
    // freq is in Hz
    TIM2->ATRLR = 1000000 / freq;
    TIM2->CH3CVR = 1000000 / freq / 2;
}