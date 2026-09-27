#include <ch32v10x.h>
#include <debug.h>
#include <cmath>

void tim2_init();
void set_buzzer_freq(float freq);
void buzzer_off();
float midi_num_to_freq(uint8_t midi_num);

const uint8_t chord[][3] = {
// Intro
    {38, 54, 64},
    {38, 54, 64},
    {0, 0, 0},
    {38, 54, 64},
    
    {0, 0, 0},
    {38, 54, 60},
    {38, 54, 64},
    {0, 0, 0},

    {55, 59, 67},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
// A section
    {43, 55, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    
    {43, 52, 60},
    {0, 0, 0},
    {0, 0, 0},
    {40, 48, 55},

    {0, 0, 0},
    {0, 0, 0},
    {36, 43, 52},
    {0, 0, 0},
    
    {0, 0, 0},
    {41, 48, 57},
    {0, 0, 0},
    {43, 50, 59},

    {0, 0, 0},
    {42, 49, 58},
    {41, 48, 57},
    {0, 0, 0},

    {40, 48, 55},
    {0, 0, 0},
    {48, 55, 64},
    {52, 59, 67},

    {53, 60, 69},
    {0, 0, 0},
    {50, 57, 65},
    {52, 59, 67},
    
    {0, 0, 0},
    {48, 57, 64},
    {0, 0, 0},
    {45, 52, 60},

    {47, 53, 62},
    {43, 50, 59},
    {0, 0, 0},
    {0, 0, 0},
// A section repeated    
    {43, 52, 60},
    {0, 0, 0},
    {0, 0, 0},
    {40, 48, 55},

    {0, 0, 0},
    {0, 0, 0},
    {36, 43, 52},
    {0, 0, 0},
    
    {0, 0, 0},
    {41, 48, 57},
    {0, 0, 0},
    {43, 50, 59},

    {0, 0, 0},
    {42, 49, 58},
    {41, 48, 57},
    {0, 0, 0},

    {40, 48, 55},
    {0, 0, 0},
    {48, 55, 64},
    {52, 59, 67},

    {53, 60, 69},
    {0, 0, 0},
    {50, 57, 65},
    {52, 59, 67},
    
    {0, 0, 0},
    {48, 57, 64},
    {0, 0, 0},
    {45, 52, 60},

    {47, 53, 62},
    {43, 50, 59},
    {0, 0, 0},
    {0, 0, 0},
// B Section
    {36, 0, 0},
    {0, 0, 0},
    {0, 64, 67},
    {43, 63, 66},

    {0, 62, 65},
    {0, 59, 63}, 
    {48, 0, 0},
    {0, 60, 64},

    {41, 0, 0},
    {0, 52, 56},
    {0, 53, 57},
    {48, 55, 60},

    {48, 0, 0},
    {0, 48, 57},
    {41, 52, 60},
    {0, 53, 62},

    {36, 0, 0},
    {0, 0, 0},
    {0, 64, 67},
    {40, 63, 66},

    {0, 62, 65},
    {0, 59, 63},
    {43, 0, 0},
    {48, 60, 64},

    {0, 0, 0},
    {67, 65, 72},
    {0, 0, 0},
    {67, 65, 72},
    
    {67, 65, 72},
    {0, 0, 0},
    {43, 0, 0},
    {0, 0, 0},

    {36, 0, 0},
    {0, 0, 0},
    {0, 64, 67},
    {43, 63, 66},

    {0, 62, 65},
    {0, 59, 63}, 
    {48, 0, 0},
    {0, 60, 64},

    {41, 0, 0},
    {0, 52, 56},
    {0, 53, 57},
    {48, 55, 60},

    {48, 0, 0},
    {0, 48, 57},
    {41, 52, 60},
    {0, 53, 62},

    {36, 0, 0},
    {0, 0, 0},
    {44, 56, 63},
    {0, 0, 0},

    {0, 0, 0},
    {46, 53, 62},
    {0, 0, 0},
    {0, 0, 0},

    {48, 52, 60},
    {0, 0, 0},
    {0, 0, 0},
    {43, 0, 0},

    {43, 0, 0},
    {0, 0, 0},
    {36, 0, 0},
    {0, 0, 0},
// B Section repeated
    {36, 0, 0},
    {0, 0, 0},
    {0, 64, 67},
    {43, 63, 66},

    {0, 62, 65},
    {0, 59, 63}, 
    {48, 0, 0},
    {0, 60, 64},

    {41, 0, 0},
    {0, 52, 56},
    {0, 53, 57},
    {48, 55, 60},

    {48, 0, 0},
    {0, 48, 57},
    {41, 52, 60},
    {0, 53, 62},

    {36, 0, 0},
    {0, 0, 0},
    {0, 64, 67},
    {40, 63, 66},

    {0, 62, 65},
    {0, 59, 63},
    {43, 0, 0},
    {48, 60, 64},

    {0, 0, 0},
    {67, 65, 72},
    {0, 0, 0},
    {67, 65, 72},
    
    {67, 65, 72},
    {0, 0, 0},
    {43, 0, 0},
    {0, 0, 0},

    {36, 0, 0},
    {0, 0, 0},
    {0, 64, 67},
    {43, 63, 66},

    {0, 62, 65},
    {0, 59, 63}, 
    {48, 0, 0},
    {0, 60, 64},

    {41, 0, 0},
    {0, 52, 56},
    {0, 53, 57},
    {48, 55, 60},

    {48, 0, 0},
    {0, 48, 57},
    {41, 52, 60},
    {0, 53, 62},

    {36, 0, 0},
    {0, 0, 0},
    {44, 56, 63},
    {0, 0, 0},

    {0, 0, 0},
    {46, 53, 62},
    {0, 0, 0},
    {0, 0, 0},

    {48, 52, 60},
    {0, 0, 0},
    {0, 0, 0},
    {43, 0, 0},

    {43, 0, 0},
    {0, 0, 0},
    {36, 0, 0},
    {0, 0, 0},
// C Section
    {32, 56, 60},
    {0, 56, 60},
    {0, 0, 0},
    {39, 56, 60},

    {0, 0, 0},
    {0, 56, 60},
    {44, 58, 62},
    {0, 0, 0},

    {43, 55, 64},
    {0, 52, 60},
    {0, 0, 0},
    {36, 52, 57},

    {0, }

};

int main() {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    printf(__TIMESTAMP__);
    printf("\r\n");
    const volatile uint32_t* pulUID = static_cast<const volatile uint32_t*>((const void*)0x1FFFF7E8UL);
    printf("Unique ID: %08lX %08lX %08lX\r\n", pulUID[2], pulUID[1], pulUID[0]);
    printf("SystemCoreClock: %d\r\n", (int)SystemCoreClock);

    tim2_init();

    TIM2->CTLR1 |= 0b0000000000000001;

    for (auto& step: chord) {
        for (int note_index = 0; note_index < 3; note_index++) {
            if (step[note_index] != 0) {
                set_buzzer_freq(midi_num_to_freq(step[note_index]));
            } else {
                buzzer_off();
            }
            Delay_Ms(100);
        }
        buzzer_off();
        Delay_Ms(50);
    }

    TIM2->ATRLR = 50;
    TIM2->CH3CVR = 40;

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

void set_buzzer_freq(float freq) {
    // freq is in Hz
    TIM2->ATRLR = static_cast<uint16_t>(1000000.0f / freq);
    TIM2->CH3CVR = static_cast<uint16_t>(1000000.0f / freq / 2);
}

void buzzer_off() {
    TIM2->ATRLR = 50;
    TIM2->CH3CVR = 40;
}

float midi_num_to_freq(uint8_t midi_num) {
  return 440.0f * std::pow(2.0f, (static_cast<float>(midi_num) - 69.0f) / 12.0f);
}