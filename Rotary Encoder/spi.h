#ifndef USCI_SPI_H
#define USCI_SPI_H

#include <msp430.h>


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * USCI A0 Master-Out-Slave-In (MOSI)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.2
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define USCIA0_MOSI_BIT                 BIT7
#define USCIA0_MOSI_PORT                P1OUT
#define USCIA0_MOSI_DDR                 P1DIR
#define SET_USCIA0_MOSI_AS_AN_OUTPUT    USCIA0_MOSI_DDR |= USCIA0_MOSI_BIT
#define SET_USCIA0_MOSI                 USCIA0_MOSI_PORT |= USCIA0_MOSI_BIT
#define RESET_USCIA0_MOSI               USCIA0_MOSI_PORT &= ~USCIA0_MOSI_BIT

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Slave Clock for GPIO Flash Memory Board
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.4
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define SPI_SCK_BIT                 BIT5
#define SPI_SCK_PORT                P1OUT // SPI Slave Clock output
#define SPI_SCK_DDR                 P1DIR // SPI Slave Clock direction
#define SET_SPI_SCK_AS_AN_OUTPUT    SPI_SCK_DDR |= SPI_SCK_BIT
#define SET_SPI_SCK                 SPI_SCK_PORT |= SPI_SCK_BIT
#define RESET_SPI_SCK               SPI_SCK_PORT &= ~SPI_SCK_BIT
#define TOGGLE_SPI_SCK              SPI_SCK_PORT ^= SPI_SCK_BIT

#define BLANK_BIT                   BIT4
#define BLANK_PORT                  P1OUT
#define BLANK_DDR                   P1DIR
#define SET_BLANK_AS_AN_OUTPUT      BLANK_DDR |= BLANK_BIT
#define ENABLE_BLANK                BLANK_PORT |= BLANK_BIT
#define DISABLE_BLANK               BLANK_PORT &= ~BLANK_BIT
#define TOGGLE_BLANK                BLANK_PORT ^= BLANK_BIT

#define LATCH_BIT                   BIT0
#define LATCH_PORT                  P2OUT
#define LATCH_DDR                   P2DIR
#define SET_LATCH_AS_AN_OUTPUT      LATCH_DDR |= LATCH_BIT
#define ENABLE_LATCH                LATCH_PORT |= LATCH_BIT
#define DISABLE_LATCH               LATCH_PORT &= ~LATCH_BIT
#define TOGGLE_LATCH                LATCH_PORT ^= LATCH_BIT

/*
 * This function initializes all hardware and port pins to support SPI.
 */
void InitializeSPI();
void LEDDisplay();

/*
 * This function sends the byte, SendValue, using SPI.
 */
void SPISendByte(unsigned char SendValue);

/*
 * This function receives a byte using SPI.
 *
 * Return Value: The byte that is received over SPI.
 */
unsigned char SPIReceiveByte();

#endif
