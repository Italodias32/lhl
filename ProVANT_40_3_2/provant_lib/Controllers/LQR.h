/*
 * LQR.h
 *
 *  Created on: 10 de abr de 2019
 *      Author: arthur
 */

#ifndef LIB_CONTROLLERS_LQR_H_
#define LIB_CONTROLLERS_LQR_H_


/**
  ******************************************************************************
  * @file    modules/control/c_control_LQR.h
  * @author  Iuro Nascimento
  * @version V1.0.0
  * @date    28-July-2016
  * @brief   Controlador LQR baseado em c_rc_LQR_control.
  *****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/

#include "arm_math.h"
#include "../pv_typedefs.h"

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void c_control_lqrArthur_init();

//LQR attitude and height(AH) controller. Height control depends on global variable manual_height_control.
pv_type_actuation c_control_lqrArthur_controller(pv_msg_input inputData);



#endif /* LIB_CONTROLLERS_LQR_H_ */
