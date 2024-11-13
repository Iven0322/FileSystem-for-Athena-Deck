/*
 * Log.h
 *
 *  Created on: Oct 9, 2024
 *      Author: 15845
 */


#ifndef INC_LOG_H_
#define INC_LOG_H_
#include <stdint.h>  // 为了使用标准整数类型
#include <string.h>
#define FLASH_SECTOR_SIZE 256
#define BUFFER_SIZE 32  // 定义缓冲区的大小
#define FLASH_START_ADDR ((uint32_t)0x00000000)
#define SECTOR_SIZE 4096  // 定义扇区大小为 4KB

// 定义包含XYZ坐标和时间戳的结构体
typedef struct {
	int16_t  x;
	int16_t  y;
	int16_t  z;
    uint8_t timestamp;
} SensorData;

// 缓冲区
extern SensorData buffer[];


void AddDataToBuffer(SensorData data, uint32_t *flash_start_addr); // 添加新的传感器数据到缓冲区
void WriteDataToFlash(uint32_t *flash_start_addr);
void AddSensorData(SensorData data, uint32_t *flash_start_addr);


#endif /* INC_LOG_H_ */
