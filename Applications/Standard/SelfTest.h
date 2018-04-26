#ifndef SELFTEST_H
#define SELFTEST_H

#define KEY_TEST_INIT               	0
#define KEY_TEST_WAIT              	1

#define LCD_TEST_INIT               0
#define LCD_TEST_WAIT              1
#define LCD_TEST_CLEAN              2
#define LCD_TEST_RESULT             3
#define LCD_TEST_END             	4
#define LCD_TEST_CBT100_END     5



#define VOLTAGE_TEST_INIT               0
#define VOLTAGE_TEST_WAIT              1

#define BT_TEST_INITIALIZE                0
#define BT_TEST_WAIT                		1
#define BT_TEST_COMPLETED              	2
#define BT_TEST_END                		3

#define BLE_TEST_INITIALIZE                0
#define BLE_TEST_WAIT                		1
#define BLE_TEST_COMPLETED              	2
#define BLE_TEST_CLOSE_BLE               3
#define BLE_TEST_END                		4

#define FLASH_TEST_INITIALIZE                0
#define FLASH_TEST_WAIT                		1

#define TESTRESULT_PASS      0
#define TESTRESULT_FAIL      1

extern void Uart_Port1_Test(void);
extern void Uart_Port2_Test(void);
extern void KeyTestState(void);
extern void LcdTestState(void);
//extern void KeyTestState(void);
extern void VoltageTestState(void);
extern void BTTestState(void);
//extern void BLETestState(void);

#endif // SELFTEST_H
