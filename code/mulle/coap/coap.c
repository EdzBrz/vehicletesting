/* 	Notes 
	0x0:0x10:0x60:0xd1:0xc1:0x36
*/

#include "proj_arch.h"
#ifdef LWIP_COAP
#include "coap.h" 


err_t coap_init(void){
	static struct udp_pcb *pcb = NULL;
	static struct pbuf *p = NULL;
	struct ip_addr jorgen;
	char msg[]="hiv test HEEEEEEEEEEEEEEEEESTEN säger voff!";
	IP4_ADDR(&jorgen, 130,240,233,15);
	LWIP_DEBUGF(COAP_DEBUG, ("	  .oooooo.     .oooooo.         .o.       ooooooooo.   \n"));
	LWIP_DEBUGF(COAP_DEBUG, ("	 d8P'  `Y8b   d8P'  `Y8b       .888.      `888   `Y88. \n"));
	LWIP_DEBUGF(COAP_DEBUG, ("	888          888      888     .8'888.      888	 .d88' \n"));
	LWIP_DEBUGF(COAP_DEBUG, ("	888          888      888    .8' `888.     888ooo88P'  \n"));
	LWIP_DEBUGF(COAP_DEBUG, ("	888          888      888   .88ooo8888.    888         \n"));
	LWIP_DEBUGF(COAP_DEBUG, ("	`88b    ooo  `88b    d88'  .8'     `888.   888         \n"));
	LWIP_DEBUGF(COAP_DEBUG, ("	 `Y8bood8P'   `Y8bood8P'  o88o     o8888o o888o        \n"));
                                                       
                                                       
                                                       

	pcb = udp_new();
	udp_bind(pcb, IP_ADDR_ANY, 61616);
	udp_recv(pcb, coap_input, NULL);
	udp_sendto(pcb, p, &jorgen, 61616);
	// http://www.ultimaserial.com/avr_lwip_udp.html
   p = pbuf_alloc(PBUF_TRANSPORT,sizeof(msg),PBUF_RAM);
   memcpy (p->payload, msg, sizeof(msg));
   udp_sendto(pcb, p, &jorgen, 61616);
	pbuf_free(p);
}

err_t coap_input(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port){
	LWIP_DEBUGF(COAP_DEBUG, ("Hej jag lever och far packet!\n"));
}

#endif

