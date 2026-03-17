#include <stm32f4xx.h>
#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_usart.h>
#include <stm32f4xx_ll_gpio.h>

void uart2_init(void);
void uart2_write(char ch);

int main() {
    uart2_init();
    while(1){
        uart2_write('H');
        uart2_write('E');
        uart2_write('L');
        uart2_write('L');
        uart2_write('O');
        uart2_write('\n');

        for (int i=0; i<9000; i++){
        }
    }
}

void uart2_init(void){
    /*Enable clock access for UART gpio pin*/
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    /*Enable Clock access for UART module*/
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
    /*Set mode of uart tx pin to alternate function*/
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_ALTERNATE);
    /*Select UART tx alternate function type*/
    LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_2, LL_GPIO_AF_7);
    /*Configure UART protocol parameters*/
    LL_USART_Disable(USART2);
    LL_USART_SetTransferDirection(USART2, LL_USART_DIRECTION_TX);
    LL_USART_ConfigCharacter(USART2, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);
    LL_USART_SetBaudRate(USART2, 16000000, LL_USART_OVERSAMPLING_16, 115200);
    /*Enable UART module*/
    LL_USART_Enable(USART2);

}
void uart2_write(char ch){
 /*Wait for tx flag to be raise*/
 while(!LL_USART_IsActiveFlag_TXE(USART2)){}
 LL_USART_TransmitData8(USART2, ch);
}