/* 	Notes 
	0x0:0x10:0x60:0xd1:0xc1:0x36
*/

#define COAP_RESPONSE_100       40   /* 100 Continue */
#define COAP_RESPONSE_200       80   /* 200 OK */
#define COAP_RESPONSE_201       81   /* 201 Created */
#define COAP_RESPONSE_304      124   /* 304 Not Modified */
#define COAP_RESPONSE_400      160   /* 400 Bad Request */
#define COAP_RESPONSE_404      164   /* 404 Not Found */
#define COAP_RESPONSE_405      165   /* 405 Method Not Allowed */
#define COAP_RESPONSE_415      175   /* 415 Unsupported Media Type */
#define COAP_RESPONSE_500      200   /* 500 Internal Server Error */
#define COAP_RESPONSE_503      203   /* 503 Service Unavailable */
#define COAP_RESPONSE_504      204   /* 504 Gateway Timeout */
#define COAP_RESPONSE_X_240    240   /* Token Option required by server */
#define COAP_RESPONSE_X_241    241   /* Uri-Authority Option required by server */
#define COAP_RESPONSE_X_242    242   /* Critical Option not supported */

/* the coap init checks if  */
err_t coap_init(u16_t port){
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
 /* the coap connect */
err_t coap_connect(struct ip_addr *dest, u16_t port){
	struct coap_hdr *hdr;
	struct pbuf *p;
	err_t ret = ERR_OK;

	LWIP_DEBUGF(COAP_DEBUG, ("coap_connect:\n"));

	if(client_pcb == NULL){
		client_pcb = udp_new();
		if( client_pcb == NULL){
			LWIP_DEBUGF(DBG_ON, ("coap_connect: couldn't allocate UDP pbc\n"));
      return ERR_MEM;
    	}
	udp_bind(client_pcb, IP_ADDR_ANY, COAP_DEFAULT_PORT);
	udp_recv(client_pcb, coap_input, NULL);
	udp_connect(client_pcb, dest, port);
	}
  
	p = pbuf_alloc(PBUF_RAW, sizeof(struct coap_hdr), PBUF_RAM);
	if( p == NULL){
		LWIP_DEBUGF(DBG_ON, ("coap_connect: couldn't allocate pbuf\n"));
		udp_remove(client_pcb);
		client_pcb = NULL;
		return ERR_MEM;
	}

	hdr = p->payload;
	hdr->status = 0x0b; 
	hdr->type = 0x00; // NTP stratum
	hdr->poll = 0;
	hdr->precision = 0x0;//-4;
	hdr->est_err = htonl(0);
	hdr->est_clk_drift = htonl(100);
	hdr->ref_clk_id = htonl(0);
	hdr->reference.integer = htonl(0);
	hdr->reference.fraction = htonl(0);
	hdr->originate.integer = htonl(0);
	hdr->originate.fraction = htonl(0);
	hdr->receive.integer = htonl(0);
	hdr->receive.fraction = htonl(0);
	hdr->transmit.integer = htonl(0);
	hdr->transmit.fraction = htonl(0);
  
	count = 0;
	//KS_starttimer(1, ntp_tmr);
    
	ret = udp_send(client_pcb, p);
	pbuf_free(p);

	if( ret != 0){
		udp_remove(client_pcb);
		client_pcb = NULL;
	}
  
	LWIP_DEBUGF(COAP_DEBUG, ("coap_connect: ret=%d\n", ret));
  
	return ret;
}

err_t coap_bind(){}

err_t coap_input(){}
