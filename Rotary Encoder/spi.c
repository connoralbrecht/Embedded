#include "spi.h"

void InitializeSPI()
{
    RESET_USCIA0_MOSI;
    SET_USCIA0_MOSI_AS_AN_OUTPUT;
    RESET_SPI_SCK;
    SET_SPI_SCK_AS_AN_OUTPUT;

}

void SPISendByte(unsigned char SendValue)
{
    int i;
    for(i = 0; i < 8; i++){
        if((SendValue & BIT7)){
            SET_USCIA0_MOSI;
        }
        else{
            RESET_USCIA0_MOSI;
        }
        SendValue <<= 1;
        TOGGLE_SPI_SCK;
        TOGGLE_SPI_SCK;
    }

}


unsigned char SPIReceiveByte()
{
    return 0;
}
