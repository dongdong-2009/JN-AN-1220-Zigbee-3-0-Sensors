/*****************************************************************************
 *
 * MODULE:              Demo board BULB controls
 *
 * COMPONENT:           $RCSfile: BULBControl.h,v $
 *
 * VERSION:             $Name: JN514x_SDK_V0002_RC0 $
 *
 * REVISION:            $Revision: 1.5 $
 *
 * DATED:               $Date: 2008/10/22 12:28:15 $
 *
 * STATUS:              $State: Exp $
 *
 * AUTHOR:              CJG
 *
 * DESCRIPTION:
 * Macros to make it easier to drive BULBs on demo boards
 *
 * LAST MODIFIED BY:    $Author: pjtw $
 *                      $Modtime: $
 *
 ****************************************************************************
 *
 * This software is owned by Jennic and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on Jennic products. You, and any third parties must reproduce
 * the copyright and warranty notice and any other legend of ownership on
 * each copy or partial copy of the software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". JENNIC MAKES NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE,
 * ACCURACY OR LACK OF NEGLIGENCE. JENNIC SHALL NOT, IN ANY CIRCUMSTANCES,
 * BE LIABLE FOR ANY DAMAGES, INCLUDING, BUT NOT LIMITED TO, SPECIAL,
 * INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER.
 *
 * Copyright Jennic Ltd 2009. All rights reserved
 *
 ***************************************************************************/

#ifndef Z1_KG_THS_INCLUDED
#define Z1_KG_THS_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include "jendefs.h"
#include "AppHardwareApi.h"
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define HI_HOME

#define LED_NUM 1
#define LED_0_BIT	(14)
#define LED_0_PIN	(1UL << LED_0_BIT)
#define LED_0_VAL            (0)
#define LED_CTRL_MASK_FFD     (LED_0_PIN)

/* SHT3x (HTS) is on DIO17 (data) and DIO16 (clock) */
#define PIN_HTS_DATA          (17)
#define PIN_HTS_CLK           (16)
#define HTS_DATA_DIO_BIT_MASK (1 << PIN_HTS_DATA)
#define HTS_CLK_DIO_BIT_MASK  (1 << PIN_HTS_CLK)
#define HTS_ALL_DIO_MASK		  (HTS_DATA_DIO_BIT_MASK | HTS_CLK_DIO_BIT_MASK)
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* Z1_KG_THS_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

