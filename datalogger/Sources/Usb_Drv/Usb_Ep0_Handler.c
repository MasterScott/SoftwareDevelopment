/*************************************************************************
 * DISCLAIMER *
 * Services performed by FREESCALE in this matter are performed          *
 * AS IS and without any warranty. CUSTOMER retains the final decision   *
 * relative to the total design and functionality of the end product.    *
 * FREESCALE neither guarantees nor will be held liable by CUSTOMER      *
 * for the success of this project. FREESCALE disclaims all warranties,  *
 * express, implied or statutory including, but not limited to,          *
 * implied warranty of merchantability or fitness for a particular       *
 * purpose on any hardware, software ore advise supplied to the project  *
 * by FREESCALE, and or any product resulting from FREESCALE services.   *
 * In no event shall FREESCALE be liable for incidental or consequential *
 * damages arising out of this agreement. CUSTOMER agrees to hold        *
 * FREESCALE harmless against any and all claims demands or actions      *
 * by anyone on account of any damage, or injury, whether commercial,    *
 * contractual, or tortuous, rising directly or indirectly as a result   *
 * of the advise or assistance supplied CUSTOMER in connection with      *
 * product, services or goods supplied under this Agreement.             *
 *************************************************************************/
/*************************************************************************************************
 * File name   : Usb_Setup_Pkt.c
 *
 * Description : This file deal all events on endpoint 0 in enumeration process
 *               
 *
 * History     :
 * 04/01/2007  : Initial Development
 * 
 *************************************************************************************************/
#include <stddef.h>
#include <MC9S08JM60.h>
#include "Usb_Bdt.h"

#include "Usb_Drv.h"
#include "Usb_Descriptor.h"
#include "Usr_Ep_Handler.h"


/*Local variable definition    */
byte Ctrl_Trf_State;                 /* Control Transfer State*/

/* Global variable definition  */
byte Ctrl_Trf_Session_Owner;         /* Current transfer session owner*/
byte *pSrc;                       /* Data source pointer*/
byte *pObj;                       /* Data destination pointer*/
int Transfer_Cnt;                /* Data counter*/


/* Local functions definition */
void USB_CtrlEP_SetupStage_Complete(void);

void USB_CtrlTrf_RxData(void);
void USB_CtrlTrf_TxData(void);

void USB_StdReq_Handler(void);
void USB_ClassReq_Handler(void);
void USB_StdGetDsc_Handler(void);
void USB_StdSetCfg_Handler(void);
void USB_StdGetStatus_Handler(void);
void USB_StdFeatureReq_Handler(void);


/* Global functions definition  */
void USB_CtrlTrf_SetupStage_Processing(void);
void USB_CtrlTrf_OUT_Handler(void);
void USB_CtrlTrf_IN_Handler(void);


void USB_Prepare_Next_Trf(void);


/******************************************************************************
 * Function:        void USB_CtrlTrf_OUT_Handler(void)
 * Input:           None
 * Output:          None
 * Overview:        This function handles an OUT transaction according to
 *                  which control transfer state is currently active.
 *****************************************************************************/
void USB_CtrlTrf_OUT_Handler(void)
{
    if(Ctrl_Trf_State == CTL_TRF_DATA_RX)
        USB_CtrlTrf_RxData();                            /*Data stage*/
    else    
        USB_Prepare_Next_Trf();                          /*Current transfer completes*/
   
    return;
}


/******************************************************************************
 * Function:        void USB_CtrlTrf_RxData(void)
 * Input:           None
 *
 * Output:          None
 * Overview:        
 * Note:            None
 *****************************************************************************/
void USB_CtrlTrf_RxData(void)
{
    int Byte_Num;

    Byte_Num = (int)Bdtmap.ep0Bo.Cnt;
    
    Transfer_Cnt = Transfer_Cnt + Byte_Num;
    pSrc = (byte*)&CtrlTrf_Data;

    while(Byte_Num)
    {
        *pObj = *pSrc;			/*Please init the pObj when receiving data in enumeration process*/
        pObj++;
        pSrc++;
        Byte_Num--;
    }
  
  
   if(Bdtmap.ep0Bo.Stat.McuCtlBit.DTS == 0)
     Bdtmap.ep0Bo.Stat._byte = _SIE|_DATA1|_DTS;
   else
     Bdtmap.ep0Bo.Stat._byte = _SIE|_DATA0|_DTS;  
  
  return;  
}

 
 /******************************************************************************
 * Function:        void USB_CtrlTrf_IN_Handler(void)
 * Input:           None
 * Output:          None
 * Overview:        This function handles an IN transaction according to
 *                  which controls transfer state is currently active.
 *                  It will check if it is the set-address transaction
 *
 *****************************************************************************/
void USB_CtrlTrf_IN_Handler(void)
{
   if(Usb_Device_State == ADDR_PENDING_STATE)
    {
      ADDR = Setup_Pkt.CtlAdd.bDevADR._byte;
                              
      if(ADDR > 0x00)
        Usb_Device_State = ADDRESS_STATE; 
      else
        Usb_Device_State = DEFAULT_STATE; 
    }
    
    if(Ctrl_Trf_State == CTL_TRF_DATA_TX)
      USB_CtrlTrf_TxData();
    else 
      USB_Prepare_Next_Trf();
   
   return;
}

/******************************************************************************
 * Function:        void USB_CtrlTrf_TxData(void)
 * Input:           None
 * Output:          None
 * Overview:       
 *
 *****************************************************************************/
void USB_CtrlTrf_TxData(void)
{    
    int Byte_To_Send;
    
    if(Transfer_Cnt < EP0_BUFF_SIZE)
        Byte_To_Send = Transfer_Cnt;
    else
        Byte_To_Send = EP0_BUFF_SIZE;
    
    Bdtmap.ep0Bi.Cnt = (byte)(Byte_To_Send);
    
    Transfer_Cnt = Transfer_Cnt - Byte_To_Send;
    
    pObj = (byte*)&CtrlTrf_Data;               

    while(Byte_To_Send)
      {
          *pObj = *pSrc;
          pObj++;
          pSrc++;
          Byte_To_Send--;
      }
      
    if(Ctrl_Trf_State == CTL_TRF_DATA_TX)
     {
      if(Bdtmap.ep0Bi.Stat.McuCtlBit.DATA == 0)
        Bdtmap.ep0Bi.Stat._byte = _SIE|_DATA1|_DTS;
      else
        Bdtmap.ep0Bi.Stat._byte = _SIE|_DATA0|_DTS;  
     }
   return;
}

/******************************************************************************
 * Function:        void USB_CtrlTrf_SetupStage_Processing(void)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        This function has 3 steps
 *                  1. init the control transfer state machine.
 *                  2. calls on each of the module that may know how to
 *                     service the Setup Request from the host.
 *                  3. Once each of the modules has a chance to check if
 *                     it is responsible for servicing the request
 *                     then checks direction of the transfer to determine how
 *                     to prepare EP0 for control transfer.
 *
 *****************************************************************************/
void USB_CtrlTrf_SetupStage_Processing(void)
{
    Transfer_Cnt = 0;
    Ctrl_Trf_State = WAIT_SETUP;
    Ctrl_Trf_Session_Owner = CLASS_NULL;    
    
    USB_StdReq_Handler();  
    
    if(Ctrl_Trf_Session_Owner == CLASS_NULL)     /*if it is not USB standard request*/
      USB_ClassReq_Handler();                    /*verify if it is class request*/
    
    USB_CtrlEP_SetupStage_Complete();          
    
    return;
}



/******************************************************************************
 * Function:        void USB_CtrlEP_SetupStage_Complete(void)
 * Input:           None
 *
 * Output:          None
 * Overview:        This function wrap up the ramaining tasks in servicing
 *                  a Setup Request. Its main task is to set the endpoint
 *                  controls appropriately for a given situation. 
 *****************************************************************************/
void USB_CtrlEP_SetupStage_Complete(void)
{
	int Tmp;
   
  if(Ctrl_Trf_Session_Owner == CLASS_NULL)
    {
        Bdtmap.ep0Bo.Cnt = EP0_BUFF_SIZE;
        Bdtmap.ep0Bo.Addr = 0x0C;             /*can calculate the address according the offset in Bdtmap*/
        
        /*We can set the EPSTALL bit in EPCTL or the STALL bit in BDT register*/
        /*EPCTL0_EPSTALL = 1;*/
        Bdtmap.ep0Bo.Stat._byte = _SIE|_BDTSTALL;
        Bdtmap.ep0Bi.Stat._byte = _SIE|_BDTSTALL;
    }
   else    
    {
        if(Setup_Pkt.CtlReqT.DataDir == DEV_TO_HOST)
          {
          	Tmp = ((LSB(Setup_Pkt.CtlPara.W_Length)<<8) | (MSB(Setup_Pkt.CtlPara.W_Length))); //adjust endian

  		      if(Tmp < Transfer_Cnt)
                  Transfer_Cnt = Tmp;
  			
            USB_CtrlTrf_TxData();
            Ctrl_Trf_State = CTL_TRF_DATA_TX;
            
            Bdtmap.ep0Bo.Cnt = EP0_BUFF_SIZE;
            Bdtmap.ep0Bo.Addr = 0x0C;         /*can calculate the addree according the offset in Bdtmap*/
            Bdtmap.ep0Bo.Stat._byte = _SIE;         
      
            Bdtmap.ep0Bi.Addr = 0x08;         /*can calculate the addree according the offset in Bdtmap*/
            Bdtmap.ep0Bi.Stat._byte = _SIE|_DATA1|_DTS;
          }
        else    
          {
            Ctrl_Trf_State = CTL_TRF_DATA_RX;
            
            Bdtmap.ep0Bi.Cnt = 0;
      	    Bdtmap.ep0Bi.Addr = 0x08;         /*can calculate the addree according the offset in Bdtmap*/
            Bdtmap.ep0Bi.Stat._byte = _SIE|_DATA1|_DTS;

            Bdtmap.ep0Bo.Cnt = EP0_BUFF_SIZE;
            Bdtmap.ep0Bo.Addr = 0x0C;         /*can calculate the addree according the offset in Bdtmap*/
            Bdtmap.ep0Bo.Stat._byte = _SIE|_DATA1|_DTS;
          }
    }
    
    CTL_TSUSPEND = 0;
    
    return;
}


/******************************************************************************
 * Function:        void USB_Prepare_Next_Trf(void)
 * Input:           None
 * Output:          None
 * Overview:        The routine forces endpoint 0 OUT to be ready for a new Setup
 *                  transaction, and forces endpoint0 IN to be owned by MCU.
 * Note:            None
 *****************************************************************************/
void USB_Prepare_Next_Trf(void)
{
    Bdtmap.ep0Bo.Cnt = EP0_BUFF_SIZE;             
    Bdtmap.ep0Bo.Addr = 0x0C;         //((byte)(((byte*) &Setup_Pkt)-0x1880) >> 2 );   //
    Bdtmap.ep0Bo.Stat._byte = _SIE|_DATA0|_DTS; 
    Bdtmap.ep0Bi.Stat._byte = _CPU; 
    
    CTL_TSUSPEND = 0;
    Ctrl_Trf_State = WAIT_SETUP;            

    return;              
}

/******************************************************************************
 * Function:        void USB_StdReq_Handler(void)
 * Input:           None
 * Output:          None
 * Overview:        This function checks the setup data packet to see if it
 *                  knows how to handle it
 * Note:            None
 *****************************************************************************/
void USB_StdReq_Handler(void)
{   
    if(Setup_Pkt.CtlReqT.RequestType != STANDARD) 
    	return;
    
    switch(Setup_Pkt.StdCtl.bRequest)
    {
        case GET_DSC:
            USB_StdGetDsc_Handler();
            break;
            
        case SET_CFG:
            USB_StdSetCfg_Handler();
            break;
            
        case SET_ADR:
            Usb_Device_State = ADDR_PENDING_STATE;       
            Ctrl_Trf_Session_Owner = STANDARD_CLASS_ID;
            break;
 
        case GET_CFG:
            pSrc = (byte*)&Usb_Active_Cfg;         
            Transfer_Cnt = 1;                            
            Ctrl_Trf_Session_Owner = STANDARD_CLASS_ID;
            break;
            
        case GET_STATUS:
            USB_StdGetStatus_Handler();
            break;
            
        case CLR_FEATURE:
        case SET_FEATURE:
            USB_StdFeatureReq_Handler();
            break;
            
        case GET_INTF:			/*Notice when the Setup_Pkt.bIntfId > 1*/
           if(Setup_Pkt.CtlIntf.bIntfID < MAX_NUM_INTF)
           {
              pSrc = (byte*)&Usb_Alt_Intf + Setup_Pkt.CtlIntf.bIntfID;  
              Transfer_Cnt = 1;                            
              Ctrl_Trf_Session_Owner = STANDARD_CLASS_ID;
           }
           /*
           else
            {
              //add code for more than 1 interface, notice the value of  MAX_NUM_INTF
            }
           */
           break;
            
        case SET_INTF:
            Usb_Alt_Intf[Setup_Pkt.CtlIntf.bIntfID] = Setup_Pkt.CtlIntf.bAltID;
            Ctrl_Trf_Session_Owner = STANDARD_CLASS_ID;
            break;
            
        case SET_DSC:
        case SYNCH_FRAME:
        default:
            break;
    }
    
  return;  
}

/******************************************************************************
 * Function:        void USB_ClassReq_Handler(void)
 * Input:           None
 * Output:          None
 * Overview:        The routine will be called when the request in setup packet 
 *                  can not be parsed. It will call the routines in Std_Class_Req_Handler,
 *                  The new routine for new class can be added to this array when 
 *                  a new standard class is required. The user can also add its owner 
 *                  processing for customize protocol.  
 * Note:            None
 *****************************************************************************/
void USB_ClassReq_Handler(void)
{
    byte i;
     
    for(i=0;i < (sizeof(Class_Req_Handler)/sizeof(pFunc)); i++)
     {
       if(Ctrl_Trf_Session_Owner != CLASS_NULL)  /*if the request has been parsed, return*/
         return;
            
       if(Class_Req_Handler[i])              /*if the routine is valid, then call*/
         Class_Req_Handler[i]();             
    }
    
    return;
}

/******************************************************************************
 * Function:        void USB_StdGetDsc_Handler(void)
 * Input:           None
 * Output:          None
 * Overview:        This function handles the standard GET_DESCRIPTOR request.
 *****************************************************************************/
void USB_StdGetDsc_Handler(void)
{
    if(Setup_Pkt.StdCtl.bmRequestType == 0x80)
    {
        switch(Setup_Pkt.ReqWval.bDscType)
        {
            case DSC_DEV:
                Transfer_Cnt = sizeof(Device_Dsc);
                pSrc = (byte*)&Device_Dsc;
                Ctrl_Trf_Session_Owner = STANDARD_CLASS_ID;
                break;
                
            case DSC_CFG:
                Transfer_Cnt = sizeof(USB_CFG);            
                pSrc =  Cfg_Des[Setup_Pkt.ReqWval.bDscIndex];			
                Ctrl_Trf_Session_Owner = STANDARD_CLASS_ID;
                break;
                
            case DSC_STR:
            	  Transfer_Cnt = *pSrc;                 
          		  pSrc = Str_Des[Setup_Pkt.ReqWval.bDscIndex];
                Ctrl_Trf_Session_Owner = STANDARD_CLASS_ID;
                break;
                
            default:
            break;
        }
        
    }
    
  return;
}

/******************************************************************************
 * Function:        void USB_StdSetCfg_Handler(void)
 * Input:           None
 * Output:          None
 * Overview:        This function disables all endpoints except 0 by clearing
 *                  EPCTL registers, then initializes these endpoints
 *
 * Note:            None
 *****************************************************************************/
void USB_StdSetCfg_Handler(void)
{
    Clear_Mem((byte*)&EPCTL1,6);                          
    Clear_Mem((byte*)&Usb_Alt_Intf,MAX_NUM_INTF);

    Usb_Active_Cfg = Setup_Pkt.CtrCfg.bCfgValue;
    
    Ctrl_Trf_Session_Owner = STANDARD_CLASS_ID;
    
    if(Setup_Pkt.CtrCfg.bCfgValue == 0)
        Usb_Device_State = ADDRESS_STATE;
    else
    {
        Usb_Device_State = CONFIGURED_STATE;

        Usr_Ep_Init();                    /*it can also be placed to the USB initialization routine*/
    }
    
    return;
}

/******************************************************************************
 * Function:        void USB_StdGetStatus_Handler(void)
 * Input:           None
 * Output:          None
 * Overview:        This function handles the standard GET_STATUS request
 * Note:            None
 *****************************************************************************/
void USB_StdGetStatus_Handler(void)
{
    CtrlTrf_Data.EachByte._byte0 = 0;                         
    CtrlTrf_Data.EachByte._byte1 = 0;
        
    switch(Setup_Pkt.CtlReqT.Recipient)
    {
        case RCPT_DEV:
             /* _byte0: bit0: Self-Powered Status [0] Bus-Powered [1] Self-Powered  */
             /*         bit1: RemoteWakeup        [0] Disabled    [1] Enabled       */
             
            if(Usb_Stat.BitCtl.Self_Power)
                CtrlTrf_Data.EachByte._byte0|=0b000000001;   
                       
            if(Usb_Stat.BitCtl.RemoteWakeup == 1)         
                CtrlTrf_Data.EachByte._byte0|=0b00000010;     
            
            Ctrl_Trf_Session_Owner = STANDARD_CLASS_ID;
            break;
            
        case RCPT_INTF:
            Ctrl_Trf_Session_Owner = STANDARD_CLASS_ID;     
            break;
            
        case RCPT_EP:
            if((Setup_Pkt.EpND.EPNum == 0b0001 ) && (Setup_Pkt.EpND.EPDir))
            {
              if(Bdtmap.ep1Bio.Stat.McuCtlBit.BDTSTALL) 
                CtrlTrf_Data.EachByte._byte0 |= 0x01;
              
              Ctrl_Trf_Session_Owner = STANDARD_CLASS_ID;              
            }
            break;
                  
          default:
            break;
    }
    
    if(Ctrl_Trf_Session_Owner == STANDARD_CLASS_ID)
    {
        Transfer_Cnt = 2;  
        pSrc = (byte*)&CtrlTrf_Data;           
                                 
    }
    
   return; 
}

/******************************************************************************
 * Function:        void USB_StdFeatureReq_Handler(void)
 * Input:           None
 * Output:          None
 * Overview:        This function dealt with the standard SET & CLEAR FEATURES
 *                  requests
 * Note:            None
 *****************************************************************************/
void USB_StdFeatureReq_Handler(void)
{
    if((Setup_Pkt.CtlReqT.bFeature == DEVICE_REMOTE_WAKEUP)&&
       (Setup_Pkt.CtlReqT.Recipient == RCPT_DEV))
    {
        if(Setup_Pkt.StdCtl.bRequest == SET_FEATURE)
            Usb_Stat.BitCtl.RemoteWakeup = 1;
        else
            Usb_Stat.BitCtl.RemoteWakeup = 0;
        
        Ctrl_Trf_Session_Owner = STANDARD_CLASS_ID; 
    }
    
    if((Setup_Pkt.CtlReqT.bFeature == ENDPOINT_HALT)&&
       (Setup_Pkt.CtlReqT.Recipient == RCPT_EP)&&
       (Setup_Pkt.EpND.EPNum != 0))
    {
       if(Setup_Pkt.EpND.EPNum == 0b0001)
       {
         if(Setup_Pkt.StdCtl.bRequest == SET_FEATURE)  
          {
            if(Setup_Pkt.EpND.EPDir)
            {
              Bdtmap.ep1Bio.Stat.McuCtlBit.BDTSTALL = 1;
            }
          }
         else
          {
            if(Setup_Pkt.EpND.EPDir)
            {
              Bdtmap.ep1Bio.Stat.McuCtlBit.BDTSTALL = 0;
            }
          }
          
         Ctrl_Trf_Session_Owner = STANDARD_CLASS_ID;          
       }

    }
    
  return;
}

