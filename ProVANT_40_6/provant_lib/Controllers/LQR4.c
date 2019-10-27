/**
  ******************************************************************************
  * @file    modules/control/c_control_lqrArthur.c
  * @author  Iuro Nascimento
  * @version V1.0.0
  * @date    28-July-2016
  * @brief   Implementa controlador lqrArthur baseado em c_rc_lqrArthur_control de Rodrigo Donadel.
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <LQR4.h>


//---------------------------------------------------------------------------------------------

/* Exported functions definitions --------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static pv_type_stability_error last_error={0};

/* DlqrArthur */

/*static float32_t K_f32[4][16] ={{-0.708576,	0.664812,	-14.986776,	-0.776799,	0.118369,	-0.268399,	6.965978,	7.071208,	-0.001229,	-0.002073,	-2.713855,	-0.003877,	0.147773,	-0.242210,	5.515657,	7.664070},
		{0.710318,	-0.662794,	14.986949,	1.058387,	-0.118370,	0.273579,	-6.966062,	7.070926,	0.001243,	0.002089,	2.713870,	0.239238,	-0.147776,	0.261981,	-5.515728,	7.664346},
		{3.610315,	0.517505,	0.371945,	2.092520,	0.076866,	0.630798,	-0.106075,	-0.000231,	0.134907,	0.008762,	0.094175,	0.444221,	0.107453,	0.553006,	-0.104833,	0.000427},
		{0.516506,	2.857548,	-0.370013,	2.434956,	-0.061736,	0.775000,	0.135053,	-0.000283,	0.009139,	0.129625,	-0.081029,	0.453630,	-0.085691,	0.669647,	0.119584,	0.000532}};*/

//static float32_t K_f32[4][16] ={{-4.9984 ,   5.0943 , -40.2674 ,   0.0396 ,   0.4630 ,   0.0019  ,  2.4259  ,  3.8526 ,  -0.0468  ,  0.0608 ,-18.0093 ,   0.0291  ,  0.4230  ,  0.0047  ,  5.4502  ,  6.6536},
//    {5.1234 ,  -5.0423 ,  40.5308  ,  0.0436 ,  -0.4660  ,  0.0015 ,  -2.4429  ,  3.8252  ,  0.0608  , -0.0476, 18.1119 ,   0.0291 ,  -0.4253,    0.0034,   -5.4875,    6.6059},
//    {0.4275,    0.2255,    0.1403,    0.1426,    0.0163,    0.0086,   -0.0081,   -0.0036,    0.0942,    0.0046, 0.0656,    0.0633,    0.0220 ,   0.0180,   -0.0185,   -0.0062},
//    {0.2267,    0.4242,   -0.1413 ,   0.1419 ,  -0.0164 ,   0.0085  ,  0.0082 ,  -0.0036  ,  0.0046  ,  0.0941 ,-0.0660 ,   0.0631,   -0.0220,    0.0179  ,  0.0187 ,  -0.0062}};



//static float32_t K_f32[4][16] ={{-6.1312,    6.0639,  -89.1064,    0.1338,    0.1030,    0.0024,    2.4074,   3.6883,   -0.0584,    0.0689,  -19.2803,    0.0474,    0.0178,    0.0255,  25.1370,   37.2629},
//  {6.0913,   -6.1601,   89.1649,    0.1898,   -0.1024,    0.0031,   -2.4118, 3.6694,    0.0689,   -0.0592,   19.2607,    0.0487,   -0.0166,    0.0322, -25.1820,   37.0707},
//  {0.5940,    0.3837,    0.2938,    0.4549,    0.0176,    0.0084,   -0.0075, -0.0034,    0.0957,    0.0060,    0.0695,    0.1204,    0.0234,    0.0884,  -0.0788,   -0.0348},
//  {0.3849,    0.5887,   -0.2955,    0.4532,   -0.0175,    0.0084,    0.0076,  -0.0034,    0.0060,    0.0956,   -0.0697,    0.1197,   -0.0232,    0.0887,   0.0793,   -0.0348}};




static float32_t K_f32[4][16] ={{-4.5963,    4.5310, -189.2610,    0.4709,   -0.2079,    0.3242,  234.7676,   355.5676,   -0.0531,    0.0619,  -22.4682,    0.0690,   -0.3126,    0.1859,  106.6456,   63.0998},
								{4.5066,   -4.6478,  188.7322,    0.3671,    0.2087,    0.2050, -234.7688,  354.0207,    0.0614,   -0.0542,   22.3435,    0.0548,    0.3135,    0.1222,  -106.5175,   62.7401},
								{0.8198,    0.6216,    0.5906,    1.2474,    0.0188,    0.8050,   -0.6887,    -0.3321,    0.0978,    0.0081,    0.0790,    0.1910,    0.0248,    0.4599,     -0.3188,   -0.0590},
								{0.6231,    0.8215,   -0.5932,    1.2617,   -0.0181,    0.8338,    0.6933,   -0.3330,    0.0081,    0.0977,   -0.0787,    0.1910,   -0.0238,    0.4707,     0.3207,   -0.0589}};


















static float32_t equilibrium_point_f32[16]={0.577,0.577,0,-0.578,0,0,0,2,0,0,0,0,0,0,0,0};
static float32_t equilibrium_control_f32[4]={37.3,	37.3, 0, 0};
static float32_t state_vector_f32[16]={0};
static float32_t error_state_vector_f32[16]={0};
static float32_t control_output_f32[16]={0};
static float32_t delta_control_f32[16]={0};

static arm_matrix_instance_f32 equilibrium_control;
static arm_matrix_instance_f32 K;


/* Private function prototypes -----------------------------------------------*/
/* static arm_matrix_instance_f32 c_control_lqrArthur_calcErrorStateVector(pv_type_datapr_attitude attitude, pv_type_datapr_attitude attitude_reference, pv_type_datapr_position position, pv_type_datapr_position position_reference); */
arm_matrix_instance_f32 c_control_lqr4_calcErrorStateVector(pv_msg_input inputData);

/* Private functions ---------------------------------------------------------*/
arm_matrix_instance_f32 c_control_lqr4_calcErrorStateVector(pv_msg_input inputData) {
	pv_type_datapr_attitude attitude = inputData.attitude;
	//pv_type_datapr_attitude attitude_reference = inputData.attitude_reference;
	pv_type_datapr_position position = inputData.position;
	//pv_type_datapr_position position_reference = inputData.position_reference;
	pv_type_datapr_servos servos = inputData.servosOutput.servo;
	arm_matrix_instance_f32 error_state_vector, state_vector, equilibrium_point;

	equilibrium_point_f32[0] = 0.577;
	equilibrium_point_f32[1] = 0.577;
	equilibrium_point_f32[2] = inputData.attitude_reference.roll;
	equilibrium_point_f32[3] = inputData.attitude_reference.pitch;
	equilibrium_point_f32[4] = inputData.attitude_reference.yaw;
	equilibrium_point_f32[5] = inputData.position_reference.x;
	equilibrium_point_f32[6] = inputData.position_reference.y;
	equilibrium_point_f32[7] = inputData.position_reference.z;
	equilibrium_point_f32[8] = 0;
	equilibrium_point_f32[9] = 0;
	equilibrium_point_f32[10] = inputData.attitude_reference.dotRoll;
	equilibrium_point_f32[11] = inputData.attitude_reference.dotPitch;
	equilibrium_point_f32[12] = inputData.attitude_reference.dotYaw;
	equilibrium_point_f32[13] = inputData.position_reference.dotX;
	equilibrium_point_f32[14] = inputData.position_reference.dotY;
	equilibrium_point_f32[15] = inputData.position_reference.dotZ;

	state_vector_f32[0]=servos.alphar;
	state_vector_f32[1]=servos.alphal;
	state_vector_f32[2]=attitude.roll;
	state_vector_f32[3]=attitude.pitch;
	state_vector_f32[4]=attitude.yaw;
	state_vector_f32[5]=position.x;
	state_vector_f32[6]=position.y;
	state_vector_f32[7]=position.z;
	state_vector_f32[8]=servos.dotAlphar;
	state_vector_f32[9]=servos.dotAlphal;
	state_vector_f32[10]=attitude.dotRoll;
	state_vector_f32[11]=attitude.dotPitch;
	state_vector_f32[12]=attitude.dotYaw;
	state_vector_f32[13]=position.dotX;
	state_vector_f32[14]=position.dotY;
	state_vector_f32[15]=position.dotZ;
	




	//Initializes the matrices
	arm_mat_init_f32(&equilibrium_point, 16, 1, (float32_t *)equilibrium_point_f32);
	arm_mat_init_f32(&state_vector, 16, 1, (float32_t *)state_vector_f32);
	arm_mat_init_f32(&error_state_vector, 16, 1, (float32_t *)error_state_vector_f32);

	//e(t)=x(t)- equilibrium_point
	arm_mat_sub_f32(&state_vector, &equilibrium_point, &error_state_vector);

	return error_state_vector;
}


/* Exported functions definitions --------------------------------------------*/

/** \brief Inicilização do controle de estabilidade.
 *
 * O controlador utiliza a API de DSP da CMSIS, e portanto se baseia fortemente no uso do
 * tipo arm_matrix_instance_f32. Esta \b struct contêm os valores de número de linhas e
 * colunas de matriz, além de um ponteiro para seus elementos (na forma de array).
 * Estes arrays são prealocados globalmente (ver código fonte), para evitar overhead
 * de alocação dinâmica em cada chamada e para evitar que, a cada alocação em uma função, a memória para
 * a qual o ponteiro aponta saia de escopo e seja deletada. Uma vez que as funções são privadas e chamadas
 * em ordem determinística, mutexes não são implementadas (por simplicidade apenas)
 */
void c_control_lqr4_init() {

	// Inicializa as matrizes estaticas
	arm_mat_init_f32(&equilibrium_control, 4, 1, (float32_t *)equilibrium_control_f32);
	arm_mat_init_f32(&K, 4, 16, (float32_t *)K_f32);
}



/** \brief lqrArthur Controller.  */
pv_type_actuation c_control_lqr4_controller(pv_msg_input inputData){

	/*pv_type_datapr_attitude attitude = inputData.attitude;
	pv_type_datapr_attitude attitude_reference = inputData.attitude_reference;
	pv_type_datapr_position position = inputData.position;
	pv_type_datapr_position position_reference = inputData.position_reference;
	pv_type_datapr_servos servos = inputData.servosOutput.servo;*/
	pv_type_actuation actuation_signals;
	
	arm_matrix_instance_f32 error_state_vector, delta_control, control_output;
	
	//Initialize result matrices
	arm_mat_init_f32(&control_output, 4, 1, (float32_t *)control_output_f32);
	arm_mat_init_f32(&delta_control,4,1,(float32_t *)delta_control_f32);
	pv_type_stability_error error;
	float temp_height_takeoff=0;

	error_state_vector = c_control_lqr4_calcErrorStateVector(inputData);

	/* -delta_u = K*delta_x */
	arm_mat_mult_f32(&K, &error_state_vector, &delta_control);
	/* u = ur - delta_u */
	arm_mat_sub_f32(&equilibrium_control, &delta_control, &control_output);
	//
	//The result must be in a struct pv_msg_io_actuation
	actuation_signals.escRightNewtons= (float)control_output.pData[0];
	actuation_signals.escLeftNewtons=	 (float)control_output.pData[1];
	actuation_signals.servoRight=	 (float)control_output.pData[2];
	actuation_signals.servoLeft=	 (float)control_output.pData[3];
    //Declares that the servos will use angle control, rather than torque control
	actuation_signals.servoTorqueControlEnable = 0;

	return actuation_signals;
}

/* IRQ handlers ------------------------------------------------------------- */


