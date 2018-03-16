/*****************************************************************************
 *
 * MODULE:             JN-AN-1220 ZLO Sensor Demo
 *
 * COMPONENT:          App_LightSensor.c
 *
 * DESCRIPTION:        ZLO Demo LTO Sensor -Implementation
 *
 ****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].
 * You, and any third parties must reproduce the copyright and warranty notice
 * and any other legend of ownership on each copy or partial copy of the
 * software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Copyright NXP B.V. 2016. All rights reserved
 *
 ***************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <jendefs.h>
#include "zps_gen.h"
#include "dbg.h"
#include <string.h>
#include "app_led_interface.h"
//#include "TSL2550.h"
#include "app_common.h"
#include "App_DoorLock.h"
#include "app_main.h"
#include "sht.h"
#include "pdum_gen.h"
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
tsHA_DoorLockDevice sDoorLock;
const uint8 u8MyEndpoint = DOORLOCK_SENSOR_ENDPOINT;

#define DEBUG_LIGHT_TEMP_OCC_SENSOR
#ifdef DEBUG_LIGHT_TEMP_OCC_SENSOR
    #define TRACE_LIGHT_TEMP_OCC_SENSOR TRUE
#else
    #define TRACE_LIGHT_TEMP_OCC_SENSOR FALSE
#endif

/****************************************************************************/
/* define the default reports */
tsReports asDefaultReports[ZCL_NUMBER_OF_REPORTS] = \
{\
    {CLOSURE_CLUSTER_ID_DOOR_LOCK,{0, E_ZCL_UINT8,E_CLD_DOOR_LOCK_ATTR_ID_LOCK_STATE,ZLO_MIN_REPORT_INTERVAL,ZLO_MAX_REPORT_INTERVAL,0,{1}}},\
};

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 *
 * NAME: eApp_ZCL_RegisterEndpoint
 *
 * DESCRIPTION:
 * Register ZLO endpoints
 *
 * PARAMETER
 * Type                        Name                  Descirption
 * tfpZCL_ZCLCallBackFunction  fptr                  Pointer to ZCL Callback function
 *
 * RETURNS:
 * teZCL_Status
 *
 ****************************************************************************/
teZCL_Status eApp_ZCL_RegisterEndpoint(tfpZCL_ZCLCallBackFunction fptr)
{
    teZCL_Status eZCL_Status;

    // Register the Light Sensor on its own endpoint
    eZCL_Status = eHA_RegisterDoorLockEndPoint(FINGERPRINTLOCK_SENSOR_ENDPOINT,
                                              fptr,
                                              &sDoorLock);

    // Check if the light sensor was successfully registered
    if (eZCL_Status != E_ZCL_SUCCESS)
    {
        DBG_vPrintf(TRACE_LIGHT_TEMP_OCC_SENSOR, "Unable to register light sensor : %x", eZCL_Status);
    }

    return eZCL_Status;
}

/****************************************************************************
 *
 * NAME: vAPP_ZCL_DeviceSpecific_Init
 *
 * DESCRIPTION:
 * ZCL Device Specific initialization
 *
 * PARAMETER: void
 *
 * RETURNS: void
 *
 ****************************************************************************/
void vAPP_ZCL_DeviceSpecific_Init(void)
{
    /* -- Initialise Illuminance Endpoint cluster attributes -- */
    // Initialise the strings in Basic
    memcpy(sDoorLock.sBasicServerCluster.au8ManufacturerName, "NXP", CLD_BAS_MANUF_NAME_SIZE);
    memcpy(sDoorLock.sBasicServerCluster.au8ModelIdentifier, "ZLO-LTOSensor", CLD_BAS_MODEL_ID_SIZE);
    memcpy(sDoorLock.sBasicServerCluster.au8DateCode, "20160210", CLD_BAS_DATE_SIZE);
    memcpy(sDoorLock.sBasicServerCluster.au8SWBuildID, "4000-0001", CLD_BAS_SW_BUILD_SIZE);
    memcpy(sDoorLock.sBasicServerCluster.au8ProductURL, "www.nxp.com", CLD_BAS_URL_SIZE);
    memcpy(sDoorLock.sBasicServerCluster.au8ProductCode, "1234", CLD_BAS_PCODE_SIZE);
    sDoorLock.sBasicServerCluster.eGenericDeviceType = E_CLD_BAS_GENERIC_DEVICE_TYPE_MOTION_OR_LIGHT_SENSOR;

}

/****************************************************************************
 *
 * NAME: vAPP_ZCL_DeviceSpecific_SetIdentifyTime
 *
 * DESCRIPTION:
 * ZCL Device Specific setting of identify time
 *
 * PARAMETER:
 * uint16 u16Time Identify time duration
 *
 * RETURNS: void
 *
 ****************************************************************************/
PUBLIC void vAPP_ZCL_DeviceSpecific_SetIdentifyTime(uint16 u16Time)
{
    sDoorLock.sIdentifyServerCluster.u16IdentifyTime=u16Time;
}
/****************************************************************************
 *
 * NAME: vAPP_ZCL_DeviceSpecific_UpdateIdentify
 *
 * DESCRIPTION:
 * ZCL Device Specific identify updates
 *
 * PARAMETER: void
 *
 * RETURNS: void
 *
 ****************************************************************************/
PUBLIC void vAPP_ZCL_DeviceSpecific_UpdateIdentify(void)
{
    if(sDoorLock.sIdentifyServerCluster.u16IdentifyTime%2)
    {
    	APP_vSetLed(TRUE);
//        bRGB_LED_SetGroupLevel(LED_LEVEL);
//        bRGB_LED_On();
    }
    else
    {
    	APP_vSetLed(FALSE);
//        bRGB_LED_Off();
    }
}
/****************************************************************************
 *
 * NAME: vAPP_ZCL_DeviceSpecific_IdentifyOff
 *
 * DESCRIPTION:
 * ZCL Device Specific stop identify
 *
 * PARAMETER: void
 *
 * RETURNS: void
 *
 ****************************************************************************/
PUBLIC void vAPP_ZCL_DeviceSpecific_IdentifyOff(void)
{
    vAPP_ZCL_DeviceSpecific_SetIdentifyTime(0);
    APP_vSetLed(FALSE);
//    bRGB_LED_Off();
}

/****************************************************************************
 *
 * NAME: APP_cbTimerLightTempSensorSample
 *
 * DESCRIPTION:
 * Callback for timer of Light and Temp sensor sampling
 *
 * PARAMETER: void
 *
 * RETURNS: void
 *
 ****************************************************************************/
PUBLIC void APP_cbTimerLightTempSensorSample(void *pvParam)
{
    if(APP_bPersistantPolling == TRUE)
    {

    }
}


/****************************************************************************
 *
 * NAME: app_u8GetDeviceEndpoint
 *
 * DESCRIPTION:
 * Returns the application endpoint
 *
 * PARAMETER: void
 *
 * RETURNS: void
 *
 ****************************************************************************/
PUBLIC uint8 app_u8GetDeviceEndpoint( void)
{
    return DOORLOCK_SENSOR_ENDPOINT;
}



/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
