/*
 * Log.c
 *
 *  Created on: Oct 9, 2024
 *      Author: 15845
 */

#include "Log.h"
#include "w25q64_ll.h"
#include <stdint.h>
static int count = 0;

SensorData buffer[BUFFER_SIZE];
void AddDataToBuffer(SensorData data, uint32_t *flash_start_addr) {
    if (count < BUFFER_SIZE) {  //如果缓冲区没有存满就放入缓冲区
    	buffer[count] = data;
        count++;
    }

    // 检查缓冲区是否已满
    if (count == BUFFER_SIZE) {
        WriteDataToFlash(flash_start_addr);
        count = 0;  // 清空缓冲区
        memset(buffer, 0, sizeof(buffer));
        buffer[count] = data;
        count++;
    }
}

void WriteDataToFlash(uint32_t *flash_start_addr) {
	if((*flash_start_addr==0)||(*flash_start_addr%SECTOR_SIZE==0)){
		BSP_W25Qx_Erase_Block(*flash_start_addr);//擦除扇区,4Kb
	}
	uint32_t  writeSize = BUFFER_SIZE * sizeof(SensorData);//设置写入大小
	BSP_W25Qx_Write((uint8_t*)buffer, *flash_start_addr, writeSize);//写入buffer
	SensorData receive;
	BSP_W25Qx_Read((uint8_t*)&receive,(uint32_t)(FLASH_START_ADDR+8),8);
//	for(int i=0;i<16;i++){
//		BSP_W25Qx_Read((uint8_t*)&receive,(uint32_t)(*flash_start_addr+8*i),8);
//	}
	*flash_start_addr = writeSize + *flash_start_addr;  // 计算下一次写入时的开始地址
}

void AddSensorData(SensorData data, uint32_t *flash_start_addr) {
    AddDataToBuffer(data, flash_start_addr);
}

//SensorData* ReadDataFromFlash()




