/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "TPO.h"
/***********************************************************************************************************************************
*** FUNCIONES DEL MODULO
**********************************************************************************************************************************/

/**
	@fn  		void sig_finish (int s)
	@brief 		Levanta una bandera al recibir señal de interrupcion
 	@author 	Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 		20/12/16
 	@param [in] s:	Signal value
 	@return 	void
*/

void sig_finish (int s)
{
  extern int Flag;
  Flag=1;	
}
