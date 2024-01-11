/******************************************************************************
  Filename:       ESP32_Clock.h
  Revised:        $Date: 2019-12-02  
  Revision:        

  Description:    ESP32 Clock definition and manipulation functions.
******************************************************************************/

#ifndef __ESP32_CLOCK_H__
#define __ESP32_CLOCK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"

#include "driver/gpio.h"
#include <errno.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_sntp.h"

#ifdef __cplusplus
extern "C"
{
#endif




//定义一个全局变量 
typedef struct
{
	uint16_t type;			//设备类型： 0代表无设备；1~255表示lora/sub1g设备；0xfffe表示433设备
	uint32_t device_id;	//设备id
	uint32_t delay_value;	//设备延迟重复触发时间(单位是s);如果为0  触发的时候重新赋值  再次触发 检测不为0 则触发无效
	uint32_t leave_value;	//红外多久无人上报
}REPEATTRIGGER_Info;

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * MACROS
 */

#define	IsLeapYear(yr)	(!((yr) % 400) || (((yr) % 100) && !((yr) % 4)))

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * TYPEDEFS
 */

// number of seconds since 0 hrs, 0 minutes, 0 seconds, on the
// 1st of January 1900 UTC
//typedef uint32_t UTCTime;
typedef time_t UTCTime;
// To be used with
typedef struct
{
	uint8_t seconds;  // 0-59
	uint8_t minutes;  // 0-59
	uint8_t hour;     // 0-23
	uint8_t day;      // 0-30
	uint8_t month;    // 0-11
	uint16_t year;    // 1900+
} UTCTimeStruct;


//struct tm
//{
//	int tm_sec;       // 秒 – 取值区间为[0,59]
//	int tm_min;       // 分 - 取值区间为[0,59]
//	int tm_hour;      // 时 - 取值区间为[0,23]
//	int tm_mday;      // 一个月中的日期 - 取值区间为[1,31]
//	int tm_mon;       // 月份（从一月开始，0代表一月） - 取值区间为[0,11]
//	int tm_year;      // 年份，其值等于实际年份减去1900
//	int tm_wday;      // 星期 – 取值区间为[0,6]，其中0代表星期天，1代表星期一，以此类推
//	int tm_yday;      // 从每年的1月1日开始的天数 – 取值区间为[0,365]，其中0代表1月1日，1代表1月2日，以此类推
//	int tm_isdst;     // 夏令时标识符，实行夏令时的时候，tm_isdst为正。不实行夏令时的进候，tm_isdst为0；不了解情况时，tm_isdst()为负。
//};

/*********************************************************************
 * GLOBAL VARIABLES
 */

/*********************************************************************
 * FUNCTIONS
 */

  /*
   * Updates the OSAL clock and Timers from the MAC 320us timer tick.
   */
  extern void esp32TimeUpdate( void );

  /*
   * Set the new time.  This will only set the seconds portion
   * of time and doesn't change the factional second counter.
   *     newTime - number of seconds since 0 hrs, 0 minutes,
   *               0 seconds, on the 1st of January 1900 UTC
   */
  //extern void esp32_setClock( UTCTime newTime );
  extern void esp32_setClock(UTCTime newTime);
  /*
   * Gets the current time.  This will only return the seconds
   * portion of time and doesn't include the factional second counter.
   *     returns: number of seconds since 0 hrs, 0 minutes,
   *              0 seconds, on the 1st of January 1900 UTC
   */
  extern UTCTime esp32_getClock( void );

  /*
   * Converts UTCTime to UTCTimeStruct
   *
   * secTime - number of seconds since 0 hrs, 0 minutes,
   *          0 seconds, on the 1st of January 1900 UTC
   * tm - pointer to breakdown struct
   */
  extern void esp32_ConvertUTCTime( UTCTimeStruct *tm, UTCTime secTime );

  /*
   * Converts UTCTimeStruct to UTCTime (seconds since 00:00:00 01/01/1900)
   *
   * tm - pointer to UTC time struct
   */
  extern UTCTime esp32_ConvertUTCSecs( UTCTimeStruct *tm );

  /*
   * Update/Adjust the esp32 clock and timers
   * Msec - elapsed time in milli seconds 
   */
  extern void esp32AdjustTimer( uint32_t Msec );


void esp32TimeTask(void *pvParameters);

/*********************************************************************
*********************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* OSAL_CLOCK_H */
