#include "serial_flash.h"

void InitializeSerialFlash()
{
    DISABLE_FLASH_MEMORY_U3;
    SET_ENABLE_U3_AS_AN_OUTPUT;
    DISABLE_HOLD_U3;
    SET_HOLD_U3_AS_AN_OUTPUT;
    DISABLE_FLASH_MEMORY_U2;
    SET_ENABLE_U2_AS_AN_OUTPUT;
    DISABLE_HOLD_U2;
    SET_HOLD_U2_AS_AN_OUTPUT;
    DISABLE_WRITE_PROTECT;
    SET_WRITE_PROTECT_AS_AN_OUTPUT;
}

unsigned int ReadFlashMemoryID(unsigned char ComponentNumber)
{
    unsigned char id0, id1;
    unsigned int returnValue;
    if(ComponentNumber == FLASH_MEMORY_U3){
        ENABLE_FLASH_MEMORY_U3;
    }
    else{
        ENABLE_FLASH_MEMORY_U2;
    }
    SPISendByte(READ_ID);
    SPISendByte(0x00);
    SPISendByte(0x00);
    SPISendByte(0x00);
    //Receive Device ID, one byte at a time
    id1 = SPIReceiveByte();
    id0 = SPIReceiveByte();
    returnValue = (unsigned int)(id1<<8);
    returnValue = returnValue | (unsigned int)id0;
    if(ComponentNumber == FLASH_MEMORY_U3){
        DISABLE_FLASH_MEMORY_U3;
    }
    else{
        DISABLE_FLASH_MEMORY_U2;
    }

    return returnValue;
}

unsigned char ReadFlashMemoryStatusRegister(unsigned char ComponentNumber)
{
    unsigned char returnValue;
    if(ComponentNumber == FLASH_MEMORY_U3){
        ENABLE_FLASH_MEMORY_U3;
    }
    else{
        ENABLE_FLASH_MEMORY_U2;
    }

    SPISendByte(0x05);
    returnValue = SPIReceiveByte();

    if(ComponentNumber == FLASH_MEMORY_U3){
        DISABLE_FLASH_MEMORY_U3;
    }
    else{
        DISABLE_FLASH_MEMORY_U2;
    }


    return returnValue;
}

void WriteFlashMemoryStatusRegister(unsigned char WriteValue,unsigned char ComponentNumber)
{
    if(ComponentNumber == FLASH_MEMORY_U3){
                ENABLE_FLASH_MEMORY_U3;
            }
    else{
                ENABLE_FLASH_MEMORY_U2;
            }
    SPISendByte(0x50);

    if(ComponentNumber == FLASH_MEMORY_U3)
            DISABLE_FLASH_MEMORY_U3;
    else
            DISABLE_FLASH_MEMORY_U2;

    if(ComponentNumber == FLASH_MEMORY_U3){
            ENABLE_FLASH_MEMORY_U3;
                }
    else{
            ENABLE_FLASH_MEMORY_U2;
                }

    SPISendByte(0x01);


    SPISendByte(WriteValue);


    if(ComponentNumber == FLASH_MEMORY_U3)
            DISABLE_FLASH_MEMORY_U3;
    else
            DISABLE_FLASH_MEMORY_U2;
}

void ReadFlashMemory(unsigned long StartAddress, unsigned char* DataValuesArray,
unsigned int NumberOfDataValues, unsigned char ComponentNumber, unsigned char ReadMode)
{
    if(ComponentNumber == FLASH_MEMORY_U3){
        ENABLE_FLASH_MEMORY_U3;
    }
    else{
        ENABLE_FLASH_MEMORY_U2;
    }

    SPISendByte(ReadMode);
    SPISendByte(((StartAddress & 0xFFFFFF) >> 16));
    SPISendByte(((StartAddress & 0xFFFF) >> 8));
    SPISendByte(StartAddress & 0xFF);

    volatile unsigned int i;
    for(i = 0; i < NumberOfDataValues; i++)
        DataValuesArray[i] = SPIReceiveByte();

    if(ComponentNumber == FLASH_MEMORY_U3){
        DISABLE_FLASH_MEMORY_U3;
    }
    else{
        DISABLE_FLASH_MEMORY_U2;
    }
}

void ByteProgramFlashMemory(unsigned long MemoryAddress, unsigned char WriteValue, unsigned char ComponentNumber)
{
    WriteEnable(ComponentNumber);

    if(ComponentNumber == FLASH_MEMORY_U3){
        ENABLE_FLASH_MEMORY_U3;
    }
    else{
        ENABLE_FLASH_MEMORY_U2;
    }

    SPISendByte(0x02);
    SPISendByte((MemoryAddress) >> 16);
    SPISendByte((MemoryAddress) >> 8);
    SPISendByte(MemoryAddress);
    SPISendByte(WriteValue);


    if(ComponentNumber == FLASH_MEMORY_U3){
        DISABLE_FLASH_MEMORY_U3;
    }
    else{
        DISABLE_FLASH_MEMORY_U2;
    }
    while(FlashMemoryBusy(ComponentNumber)==1);
    WriteDisable(ComponentNumber);

}

void AAIProgramFlashMemory(unsigned long StartAddress, unsigned char* DataValuesArray,
unsigned int NumberOfDataValues, unsigned char ComponentNumber)
{
    WriteEnable(ComponentNumber);
    volatile unsigned int i;
    for(i = 0; i < NumberOfDataValues; i++){
        if(ComponentNumber == FLASH_MEMORY_U3){
                ENABLE_FLASH_MEMORY_U3;}
        else{
                ENABLE_FLASH_MEMORY_U2;}
        SPISendByte(0xAF);
        if(i == 0){

            SPISendByte(((StartAddress & 0xFFFFFF) >> 16));
            SPISendByte(((StartAddress & 0xFFFF) >> 8));
            SPISendByte(StartAddress & 0xFF);
        }
        SPISendByte(DataValuesArray[i]);
        if(ComponentNumber == FLASH_MEMORY_U3){
                DISABLE_FLASH_MEMORY_U3;}
        else{
                DISABLE_FLASH_MEMORY_U2;}

        while(FlashMemoryBusy(ComponentNumber)==1);

    }
    WriteDisable(ComponentNumber);

    if(ComponentNumber == FLASH_MEMORY_U3){
                ENABLE_FLASH_MEMORY_U3;}
    else{
                ENABLE_FLASH_MEMORY_U2;}
    SPISendByte(RDSR);

    volatile unsigned char Dout = SPIReceiveByte();

    if(ComponentNumber == FLASH_MEMORY_U3)
            DISABLE_FLASH_MEMORY_U3;
    else
            DISABLE_FLASH_MEMORY_U2;

    WriteDisable(ComponentNumber);


}

void ChipEraseFlashMemory(unsigned char ComponentNumber)
{
    WriteEnable(ComponentNumber);

    if(ComponentNumber == FLASH_MEMORY_U3){
        ENABLE_FLASH_MEMORY_U3;
    }
    else{
        ENABLE_FLASH_MEMORY_U2;
    }
    SPISendByte(CHIP_ERASE);

    if(ComponentNumber == FLASH_MEMORY_U3){
        DISABLE_FLASH_MEMORY_U3;
    }
    else{
        DISABLE_FLASH_MEMORY_U2;
    }
    while(FlashMemoryBusy(ComponentNumber)==1);
    WriteDisable(ComponentNumber);
}

void SectorBlockEraseFlashMemory(unsigned long StartAddress, unsigned char ComponentNumber, unsigned char EraseMode)
{
    WriteEnable(ComponentNumber);
    if(ComponentNumber == FLASH_MEMORY_U3){
            ENABLE_FLASH_MEMORY_U3;
                }
    else{
            ENABLE_FLASH_MEMORY_U2;
                }

        SPISendByte(EraseMode);
        SPISendByte((StartAddress) >> 16);
        SPISendByte((StartAddress) >> 8);
        SPISendByte(StartAddress);

        if(ComponentNumber == FLASH_MEMORY_U3)
                DISABLE_FLASH_MEMORY_U3;
        else
                DISABLE_FLASH_MEMORY_U2;
        while(FlashMemoryBusy(ComponentNumber)==1);
                WriteDisable(ComponentNumber);
}

void SetBlockProtection(unsigned char ProtectionLevel, unsigned char ComponentNumber)
{

    if(ProtectionLevel == 3)
        WriteFlashMemoryStatusRegister(0b00001100, ComponentNumber);
    else if(ProtectionLevel == 2)
        WriteFlashMemoryStatusRegister(0b00001000, ComponentNumber);
    else if(ProtectionLevel == 1)
        WriteFlashMemoryStatusRegister(0b00000100, ComponentNumber);
    else
        WriteFlashMemoryStatusRegister(0b00000000, ComponentNumber);
}

unsigned char FlashMemoryBusy(unsigned char ComponentNumber)
{
    unsigned char busy_bit = ReadFlashMemoryStatusRegister(ComponentNumber);
    busy_bit = busy_bit & SR_BUSY;
    return busy_bit;
}

void WriteEnable(unsigned char ComponentNumber){
    if(ComponentNumber == FLASH_MEMORY_U3){
        ENABLE_FLASH_MEMORY_U3;
    }
    else{
        ENABLE_FLASH_MEMORY_U2;
    }

        SPISendByte(WREN);

    if(ComponentNumber == FLASH_MEMORY_U3){
        DISABLE_FLASH_MEMORY_U3;
    }
    else{
        DISABLE_FLASH_MEMORY_U2;
    }
}

void WriteDisable(unsigned char ComponentNumber){
    if(ComponentNumber == FLASH_MEMORY_U3){
        ENABLE_FLASH_MEMORY_U3;
    }
    else{
        ENABLE_FLASH_MEMORY_U2;
    }

        SPISendByte(WRDI);

    if(ComponentNumber == FLASH_MEMORY_U3){
        DISABLE_FLASH_MEMORY_U3;
    }
    else{
        DISABLE_FLASH_MEMORY_U2;
    }
}
