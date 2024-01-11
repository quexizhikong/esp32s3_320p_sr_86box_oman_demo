/******************************************************************************
  Filename:       ESP32_Clock.c
  Revised:        $Date: 2019-12-02  
  Revision:        

  Description:    ESP32 Clock definition and manipulation functions.
******************************************************************************/
/*********************************************************************
 * INCLUDES
 */

#include "ESP32_Clock.h"

#define TAG "RTC"


TimerHandle_t  rtc_time_handle = NULL;

/*********************************************************************
 * MACROS
 */

#define	YearLength(yr)	(IsLeapYear(yr) ? 366 : 365)

/*********************************************************************
 * CONSTANTS
 */

// (MAXCALCTICKS * 5) + (max remainder) must be <= (uint16_t max),
// so: (13105 * 5) + 7 <= 65535
#define MAXCALCTICKS  ((uint16_t)(13105))

#define	BEGYEAR	        1900     // UTC started at 00:00:00 January 1, 1900

#define	DAY             86400UL  // 24 hours * 60 minutes * 60 seconds

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */
//static uint16_t previousLLTimerTick = 0;
//static uint16_t remUsTicks = 0;
//static uint16_t timeMSec = 0;

// number of seconds since 0 hrs, 0 minutes, 0 seconds, on the
// 1st of January 1900 UTC
//UTCTime esp32_timeSeconds = 0;
//struct tm timeinfo;
//char strftime_buf[64];
/*********************************************************************
 * LOCAL FUNCTION PROTOTYPES
 */
static uint8_t monthLength( uint8_t lpyr, uint8_t mon );

/*********************************************************************
 * FUNCTIONS
 *********************************************************************/



/*********************************************************************
 * @fn      esp32_setClock
 *
 * @brief   Set the new time.  This will only set the seconds portion
 *          of time and doesn't change the factional second counter.
 *
 * @param   newTime - number of seconds since 0 hrs, 0 minutes,
 *                    0 seconds, on the 1st of January 1900 UTC
 *
 * @return  none
 */
 //��������ȥ��SNTP����DS1302��ESP32 RTC
/*
 * newTime>0����ӷ�������sntp����(DS1302��ESP32-RTC)ʱ��; newTime=0������DS1302ʱ�����ESP32-RTC��ʱ��
 * value����ʱ��  value=NULL������ʱ��
*/
void esp32_setClock(UTCTime newTime)
{
}
/*********************************************************************
 * @fn      esp32_getClock
 *
 * @brief   Gets the current time.  This will only return the seconds
 *          portion of time and doesn't include the factional second
 *          counter.
 *
 * @param   none
 *
 * @return  number of seconds since 0 hrs, 0 minutes, 0 seconds,
 *          on the 1st of January 1900 UTC
 */
UTCTime esp32_getClock( void )
{
	//time_t now;

	return 0;//( now );
}

/*********************************************************************
 * @fn      esp32_ConvertUTCTime
 *
 * @brief   Converts UTCTime to UTCTimeStruct
 *
 * @param   tm - pointer to breakdown struct
 *
 * @param   secTime - number of seconds since 0 hrs, 0 minutes,
 *          0 seconds, on the 1st of January 1900 UTC
 *
 * @return  none
 */
void esp32_ConvertUTCTime( UTCTimeStruct *tm, UTCTime secTime )
{
  // calculate the time less than a day - hours, minutes, seconds
  {
    uint32_t day = secTime % DAY;
    tm->seconds = day % 60UL;
    tm->minutes = (day % 3600UL) / 60UL;
    tm->hour = day / 3600UL;
  }

  // Fill in the calendar - day, month, year
  {
    uint16_t numDays = secTime / DAY;
    tm->year = BEGYEAR;
    while ( numDays >= YearLength( tm->year ) )
    {
      numDays -= YearLength( tm->year );
      tm->year++;
    }

    tm->month = 0;
    while ( numDays >= monthLength( IsLeapYear( tm->year ), tm->month ) )
    {
      numDays -= monthLength( IsLeapYear( tm->year ), tm->month );
      tm->month++;
    }

    tm->day = numDays;
  }
}

/*********************************************************************
 * @fn      monthLength
 *
 * @param   lpyr - 1 for leap year, 0 if not
 *
 * @param   mon - 0 - 11 (jan - dec)
 *
 * @return  number of days in specified month
 */
static uint8_t monthLength( uint8_t lpyr, uint8_t mon )
{
  uint8_t days = 31;

  if ( mon == 1 ) // feb
  {
    days = ( 28 + lpyr );
  }
  else
  {
    if ( mon > 6 ) // aug-dec
    {
      mon--;
    }

    if ( mon & 1 )
    {
      days = 30;
    }
  }

  return ( days );
}

/*********************************************************************
 * @fn      esp32_ConvertUTCSecs
 *
 * @brief   Converts a UTCTimeStruct to UTCTime
 *
 * @param   tm - pointer to provided struct
 *
 * @return  number of seconds since 00:00:00 on 01/01/1900 (UTC)
 */
UTCTime esp32_ConvertUTCSecs( UTCTimeStruct *tm )
{
  uint32_t seconds;

  /* Seconds for the partial day */
  seconds = (((tm->hour * 60UL) + tm->minutes) * 60UL) + tm->seconds;

  /* Account for previous complete days */
  {
    /* Start with complete days in current month */
    uint16_t days = tm->day;

    /* Next, complete months in current year */
    {
      int8_t month = tm->month;
      while ( --month >= 0 )
      {
        days += monthLength( IsLeapYear( tm->year ), month );
      }
    }

    /* Next, complete years before current year */
    {
      uint16_t year = tm->year;
      while ( --year >= BEGYEAR )
      {
        days += YearLength( year );
      }
    }

    /* Add total seconds before partial day */
    seconds += (days * DAY);
  }

  return ( seconds );
}

/*********************************************************************
 * @fn      esp32Timeinit
 * @brief   esp32 Time init
 * @param   None.
 * @return  None.
 */
void esp32Timeinit(void)
{

}
/*********************************************************************
 * @fn      esp32TimeTask
 * @brief   Uses the free running rollover count of the MAC backoff timer;
 *          this timer runs freely with a constant 1s interval.    
 *          This function is intended to be invoked
 *          from the background, not interrupt level.
 *
 * @param   None.
 *
 * @return  None.
 */

//struct tm
//{
//  int tm_sec;                   //分后的秒(0~61)
//  int tm_min;                   //小时后的分(0~59)
//  int tm_hour;                  //小时(0~23)
//  int tm_mday;                  //一个月天数(0~31)
//  int tm_mon;                   //一个后的月数(0~11)
//  int tm_year;                  //1900年后的年数 Year - 1900.
//  int tm_wday;                  //星期日开始的天数(0~6)
//  int tm_yday;                  //从1月1日开始的时间(0~365)
//  int tm_isdst;                 //夏令时标志(大于0说明夏令时有效，等于0说明无效，小于0说明信息不可用)
//
//};
void esp32TimeTask(void *pvParameters)
{
	esp32Timeinit();

	ESP_LOGI(TAG,"esp32TimeTask running start");

	time_t now;
    struct tm timeinfo;

	while(1)
	{		
		vTaskDelay(1000/portTICK_RATE_MS);//1s
		//esp32_getClock();
		time(&now);
		localtime_r(&now, &timeinfo);
		ESP_LOGI(TAG,"time==%d:%d:%d:%d:%02d:%02d:%02d:%02d:%02d",
																timeinfo.tm_isdst, 		//是否为夏时制
																timeinfo.tm_yday,  		//一年过去的天数
																timeinfo.tm_wday,  		//星期，1对应星期一
																timeinfo.tm_year,       //年，距离1900年的差值，默认是70
																timeinfo.tm_mon,   		//月，从0开始 0~11
																timeinfo.tm_mday,  		//日，从1开始
																timeinfo.tm_hour,  		//时
																timeinfo.tm_min,   		//分
																timeinfo.tm_sec);  		//秒

	}
}


