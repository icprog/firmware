/*C**************************************************************************
* NAME:  status_task.c
*----------------------------------------------------------------------------
* Copyright (c) 2013.
*----------------------------------------------------------------------------
* RELEASE:      2013.09.05
* REVISION:     9.4     
*----------------------------------------------------------------------------
* PURPOSE:          
*****************************************************************************/


/*_____ I N C L U D E S ____________________________________________________*/
#include "config.h"           /* system configuration */
#include "status_task.h"     


/*_____ D E F I N I T I O N ________________________________________________*/
#define DLY_BF_GetBase  (5000/SCHEDULER_TICK)   //��׼ֵ����ǰ��ʱ����λ��tick

/*_____ D E C L A R A T I O N ______________________________________________*/
extern  data  Uint16  gl_delay_tick;   /* ͨ����ʱ��tick */        

/* for system */
extern idata  Byte    system_status;   //ϵͳ״̬
                                       // 0 - ��ʼ�ϵ�
                                       // 1 - ��׼ֵ����ǰ��ʱ
                                       // 2 - ��׼ֵ����(10������)
                                       // 3 - ʵʱ���



/*F**************************************************************************
* NAME: status_task_init
*----------------------------------------------------------------------------
* PARAMS:
* return:
*----------------------------------------------------------------------------
* PURPOSE:
*****************************************************************************/
void status_task_init(void)
{
  system_status = SYS_PowerON;       //��ʼ�ϵ�
}


/*F**************************************************************************
* NAME: status_task
*----------------------------------------------------------------------------
* PARAMS:
* return:
*----------------------------------------------------------------------------
* PURPOSE:
*****************************************************************************/
void status_task(void)
{ 
  Uint16 temp16;

  switch (system_status)
  {
    case  SYS_PowerON://��ʼ�ϵ� 
                      Disable_interrupt();        
                      gl_delay_tick = 0;
                      Enable_interrupt();	        
                      system_status = SYS_B5S;                             
                      break;

    case  SYS_B5S:    //��׼ֵ����ǰ��ʱ(Լ5��)
                      Disable_interrupt();        
                      temp16 = gl_delay_tick;
                      Enable_interrupt();
                      if (temp16 > DLY_BF_GetBase)         
                        system_status = SYS_SAMP_BASE; 
                      break; 		  
    default:
	        break;		   
  }
}//end FUNC()