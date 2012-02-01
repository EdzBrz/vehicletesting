/* 	Notes 
	0x0:0x10:0x60:0xd1:0xc1:0x36
*/

#include "proj_arch.h"

#ifdef LWIP_COAP
#include "coap.h" 

err_t coap_init(void){
	if(pcb)
		udp_remove(pcb);
  
	if( (pcb = udp_new()) == NULL){
		LWIP_DEBUGF(COAP_DEBUG, ("coap_init: could not allocate memory for UDP pcb\n"));
	return ERR_MEM; 
	}

	udp_bind(pcb, IP_ADDR_ANY, port);
	udp_recv(pcb, coap_input, NULL);
	return ERR_OK; 
}

err_t coap_input(void){
	LWIP_DEBUGF(COAP_DEBUG, ("Hej jag lever och far packet!\n"));
}

#endif LWIP_COAP
