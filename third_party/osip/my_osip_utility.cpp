#include "my_osip_utility.hpp"

static int dialog_fill_route_set (osip_dialog_t * dialog, osip_message_t * request);

std::string event_type_to_string(int type) {
    std::string s;
    switch(type) {
    TO_STRING_ENTRY(TIMEOUT_A)
    TO_STRING_ENTRY(TIMEOUT_B)
    TO_STRING_ENTRY(TIMEOUT_D)               
    TO_STRING_ENTRY(TIMEOUT_E)             
    TO_STRING_ENTRY(TIMEOUT_F)             
    TO_STRING_ENTRY(TIMEOUT_K)             
    TO_STRING_ENTRY(TIMEOUT_G)           
    TO_STRING_ENTRY(TIMEOUT_H)                
    TO_STRING_ENTRY(TIMEOUT_I)                
    TO_STRING_ENTRY(TIMEOUT_J)                
    TO_STRING_ENTRY(RCV_REQINVITE)     
    TO_STRING_ENTRY(RCV_REQACK)            
    TO_STRING_ENTRY(RCV_REQUEST)      
    TO_STRING_ENTRY(RCV_STATUS_1XX)      
    TO_STRING_ENTRY(RCV_STATUS_2XX)      
    TO_STRING_ENTRY(RCV_STATUS_3456XX)    
    TO_STRING_ENTRY(SND_REQINVITE)      
    TO_STRING_ENTRY(SND_REQACK)            
    TO_STRING_ENTRY(SND_REQUEST)              
    TO_STRING_ENTRY(SND_STATUS_1XX)  
    TO_STRING_ENTRY(SND_STATUS_2XX)           
    TO_STRING_ENTRY(SND_STATUS_3456XX)        
    TO_STRING_ENTRY(KILL_TRANSACTION)        
    TO_STRING_ENTRY(UNKNOWN_EVT)
    default:
        assert(false);
        break;
    }
    return s;
}

std::string kill_transaction_to_string(int type) {
    std::string s;
    switch (type) {
    TO_STRING_ENTRY(OSIP_ICT_KILL_TRANSACTION)
    TO_STRING_ENTRY(OSIP_IST_KILL_TRANSACTION)
    TO_STRING_ENTRY(OSIP_NICT_KILL_TRANSACTION)
    TO_STRING_ENTRY(OSIP_NIST_KILL_TRANSACTION)
    default:
        std::cout << "wrong type:" << type << std::endl;
        break;
    }

    return s;
}

std::string message_callback_type_to_string(int type) {
    std::string s;
    switch (type) {
    TO_STRING_ENTRY(OSIP_ICT_INVITE_SENT)       
    TO_STRING_ENTRY(OSIP_ICT_INVITE_SENT_AGAIN)             
    TO_STRING_ENTRY(OSIP_ICT_ACK_SENT)                      
    TO_STRING_ENTRY(OSIP_ICT_ACK_SENT_AGAIN)                
    TO_STRING_ENTRY(OSIP_ICT_STATUS_1XX_RECEIVED)           
    TO_STRING_ENTRY(OSIP_ICT_STATUS_2XX_RECEIVED)           
    TO_STRING_ENTRY(OSIP_ICT_STATUS_2XX_RECEIVED_AGAIN)     
    TO_STRING_ENTRY(OSIP_ICT_STATUS_3XX_RECEIVED)           
    TO_STRING_ENTRY(OSIP_ICT_STATUS_4XX_RECEIVED)           
    TO_STRING_ENTRY(OSIP_ICT_STATUS_5XX_RECEIVED)           
    TO_STRING_ENTRY(OSIP_ICT_STATUS_6XX_RECEIVED)           
    TO_STRING_ENTRY(OSIP_ICT_STATUS_3456XX_RECEIVED_AGAIN)  

    TO_STRING_ENTRY(OSIP_IST_INVITE_RECEIVED)               
    TO_STRING_ENTRY(OSIP_IST_INVITE_RECEIVED_AGAIN)         
    TO_STRING_ENTRY(OSIP_IST_ACK_RECEIVED)                  
    TO_STRING_ENTRY(OSIP_IST_ACK_RECEIVED_AGAIN)            
    TO_STRING_ENTRY(OSIP_IST_STATUS_1XX_SENT)               
    TO_STRING_ENTRY(OSIP_IST_STATUS_2XX_SENT)               
    TO_STRING_ENTRY(OSIP_IST_STATUS_2XX_SENT_AGAIN)         
    TO_STRING_ENTRY(OSIP_IST_STATUS_3XX_SENT)               
    TO_STRING_ENTRY(OSIP_IST_STATUS_4XX_SENT)               
    TO_STRING_ENTRY(OSIP_IST_STATUS_5XX_SENT)               
    TO_STRING_ENTRY(OSIP_IST_STATUS_6XX_SENT)               
    TO_STRING_ENTRY(OSIP_IST_STATUS_3456XX_SENT_AGAIN)      

    TO_STRING_ENTRY(OSIP_NICT_REGISTER_SENT)                
    TO_STRING_ENTRY(OSIP_NICT_BYE_SENT)                     
    TO_STRING_ENTRY(OSIP_NICT_OPTIONS_SENT)                 
    TO_STRING_ENTRY(OSIP_NICT_INFO_SENT)                    
    TO_STRING_ENTRY(OSIP_NICT_CANCEL_SENT)                  
    TO_STRING_ENTRY(OSIP_NICT_NOTIFY_SENT)                  
    TO_STRING_ENTRY(OSIP_NICT_SUBSCRIBE_SENT)               
    TO_STRING_ENTRY(OSIP_NICT_UNKNOWN_REQUEST_SENT)         
    TO_STRING_ENTRY(OSIP_NICT_REQUEST_SENT_AGAIN)           
    TO_STRING_ENTRY(OSIP_NICT_STATUS_1XX_RECEIVED)          
    TO_STRING_ENTRY(OSIP_NICT_STATUS_2XX_RECEIVED)          
    TO_STRING_ENTRY(OSIP_NICT_STATUS_2XX_RECEIVED_AGAIN)    
    TO_STRING_ENTRY(OSIP_NICT_STATUS_3XX_RECEIVED)          
    TO_STRING_ENTRY(OSIP_NICT_STATUS_4XX_RECEIVED)          
    TO_STRING_ENTRY(OSIP_NICT_STATUS_5XX_RECEIVED)          
    TO_STRING_ENTRY(OSIP_NICT_STATUS_6XX_RECEIVED)          
    TO_STRING_ENTRY(OSIP_NICT_STATUS_3456XX_RECEIVED_AGAIN) 

    TO_STRING_ENTRY(OSIP_NIST_REGISTER_RECEIVED)            
    TO_STRING_ENTRY(OSIP_NIST_BYE_RECEIVED)                 
    TO_STRING_ENTRY(OSIP_NIST_OPTIONS_RECEIVED)             
    TO_STRING_ENTRY(OSIP_NIST_INFO_RECEIVED)                
    TO_STRING_ENTRY(OSIP_NIST_CANCEL_RECEIVED)              
    TO_STRING_ENTRY(OSIP_NIST_NOTIFY_RECEIVED)              
    TO_STRING_ENTRY(OSIP_NIST_SUBSCRIBE_RECEIVED)           

    TO_STRING_ENTRY(OSIP_NIST_UNKNOWN_REQUEST_RECEIVED)     
    TO_STRING_ENTRY(OSIP_NIST_REQUEST_RECEIVED_AGAIN)       
    TO_STRING_ENTRY(OSIP_NIST_STATUS_1XX_SENT)              
    TO_STRING_ENTRY(OSIP_NIST_STATUS_2XX_SENT)              
    TO_STRING_ENTRY(OSIP_NIST_STATUS_2XX_SENT_AGAIN)        
    TO_STRING_ENTRY(OSIP_NIST_STATUS_3XX_SENT)              
    TO_STRING_ENTRY(OSIP_NIST_STATUS_4XX_SENT)              
    TO_STRING_ENTRY(OSIP_NIST_STATUS_5XX_SENT)              
    TO_STRING_ENTRY(OSIP_NIST_STATUS_6XX_SENT)              
    TO_STRING_ENTRY(OSIP_NIST_STATUS_3456XX_SENT_AGAIN)     

    TO_STRING_ENTRY(OSIP_ICT_STATUS_TIMEOUT)                
    TO_STRING_ENTRY(OSIP_NICT_STATUS_TIMEOUT)               
    default:
        std::cout << "wrong type:" << type << std::endl;
        break;
    }

    return s;
}

std::string transport_error_to_string(int type)
{
    std::string s;
    switch (type) {
    TO_STRING_ENTRY(OSIP_ICT_TRANSPORT_ERROR)
    TO_STRING_ENTRY(OSIP_IST_TRANSPORT_ERROR)
    TO_STRING_ENTRY(OSIP_NICT_TRANSPORT_ERROR)
    TO_STRING_ENTRY(OSIP_NIST_TRANSPORT_ERROR)
    default:
        std::cout << "wrong type:" << type << std::endl;
        break;
    }

    return s;
}

std::string transaction_state_to_string(int type)
{
    std::string s;
    switch (type) {
    TO_STRING_ENTRY(ICT_PRE_CALLING)
    TO_STRING_ENTRY(ICT_CALLING)
    TO_STRING_ENTRY(ICT_PROCEEDING)
    TO_STRING_ENTRY(ICT_COMPLETED)
    TO_STRING_ENTRY(ICT_TERMINATED)
    TO_STRING_ENTRY(IST_PRE_PROCEEDING)
    TO_STRING_ENTRY(IST_PROCEEDING)
    TO_STRING_ENTRY(IST_COMPLETED)
    TO_STRING_ENTRY(IST_CONFIRMED)
    TO_STRING_ENTRY(IST_TERMINATED)
    TO_STRING_ENTRY(NICT_PRE_TRYING)
    TO_STRING_ENTRY(NICT_TRYING)
    TO_STRING_ENTRY(NICT_PROCEEDING)
    TO_STRING_ENTRY(NICT_COMPLETED)
    TO_STRING_ENTRY(NICT_TERMINATED)
    TO_STRING_ENTRY(NIST_PRE_TRYING)
    TO_STRING_ENTRY(NIST_TRYING)
    TO_STRING_ENTRY(NIST_PROCEEDING)
    TO_STRING_ENTRY(NIST_COMPLETED)
    TO_STRING_ENTRY(NIST_TERMINATED)
    default:
        std::cout << "wrong type:" << type << std::endl;
        break;
    }

    return s;
}

char* build_random_number()
{
  char *tmp = (char *)osip_malloc(33);
  unsigned number = osip_build_random_number();

  if (tmp == NULL)
    return NULL;

  sprintf (tmp, "%u", number);
  return tmp;
}

int build_response_default (osip_message_t** dest, osip_dialog_t* dialog, int status, osip_message_t* request)
{
  osip_generic_param_t *tag;
  osip_message_t *response;
  int pos;
  int i;

  *dest = NULL;
  if (request == NULL)
    return OSIP_BADPARAMETER;

  i = osip_message_init (&response);
  if (i != 0)
    return i;
  /* initialise osip_message_t structure */
  /* yet done... */

  response->sip_version = (char *) osip_malloc (8 * sizeof (char));
  if (response->sip_version == NULL) {
    osip_message_free (response);
    return OSIP_NOMEM;
  }
  sprintf (response->sip_version, "SIP/2.0");
  osip_message_set_status_code (response, status);

  // We don't use our own status.
  response->reason_phrase = osip_strdup(osip_message_get_reason(status));
  response->req_uri = NULL;
  response->sip_method = NULL;

    i = osip_to_clone (request->to, &(response->to));
    if (i != 0) {
        osip_message_free (response);
        return i;
    }

    i = osip_to_get_tag (response->to, &tag);
    if (i != 0) {                 /* we only add a tag if it does not already contains one! */
        if ((dialog != NULL) && (dialog->local_tag != NULL)) {
            /* it should contain the local TAG we created */
            osip_to_set_tag (response->to, osip_strdup (dialog->local_tag));
        } else {
            // dafei 100 need no tag ???
            if (status != 100)
                osip_to_set_tag (response->to, build_random_number());
        }
    }

  i = osip_from_clone (request->from, &(response->from));
  if (i != 0) {
    osip_message_free (response);
    return i;
  }

  pos = 0;
  while (!osip_list_eol (&request->vias, pos)) {
    osip_via_t *via;
    osip_via_t *via2;

    via = (osip_via_t *) osip_list_get (&request->vias, pos);
    i = osip_via_clone (via, &via2);
    if (i != 0) {
      osip_message_free (response);
      return i;
    }
    osip_list_add (&response->vias, via2, -1);
    pos++;
  }

  i = osip_call_id_clone (request->call_id, &(response->call_id));
  if (i != 0) {
    osip_message_free (response);
    return i;
  }
  i = osip_cseq_clone (request->cseq, &(response->cseq));
  if (i != 0) {
    osip_message_free (response);
    return i;
  }

  osip_message_set_user_agent (response, "xiaoming");

  *dest = response;
  return OSIP_SUCCESS;
}

int build_request_within_dialog (osip_message_t ** dest, const char *method, osip_dialog_t * dialog)
{
  int i;
  osip_message_t *request;
  char locip[65];

  *dest = NULL;

  if (dialog == NULL) {
    LOG_DAFEI() << "dafei return" << std::endl;
    return OSIP_BADPARAMETER;
    }

  i = osip_message_init (&request);
  if (i != 0) {
    LOG_DAFEI() << "dafei return" << std::endl;
    return i;
  }

  // TODO dafei FIX it.

  // if (dialog->remote_contact_uri == NULL) {
  //    // this dialog is probably not established! or the remote UA
  //    //   is not compliant with the latest RFC
     
  //   osip_message_free (request);
  //   LOG_DAFEI() << "dafei return" << std::endl;
  //   return OSIP_SYNTAXERROR;
  // }

  /* prepare the request-line */
  request->sip_method = osip_strdup (method);
  if (request->sip_method == NULL) {
    osip_message_free (request);
    LOG_DAFEI() << "dafei return" << std::endl;
    return OSIP_NOMEM;
  }
  request->sip_version = osip_strdup ("SIP/2.0");
  if (request->sip_version == NULL) {
    osip_message_free (request);
    LOG_DAFEI() << "dafei return" << std::endl;
    return OSIP_NOMEM;
  }
  request->status_code = 0;
  request->reason_phrase = NULL;


  // TODO dafei this is for req_uri FIX IT
  // This is just a workaround.
    osip_uri_init(&(request->req_uri));
    if ((i = osip_uri_parse(request->req_uri, "sip:10.10.10.1")) != 0) {
        std::cout << "osip uri parse failed" << std::endl;
        osip_message_free(request);
        return -1;
    }

  // TODO dafei we use no contact and route.
  // /* and the request uri???? */
  // if (osip_list_eol (&dialog->route_set, 0)) {
  //   /* The UAC must put the remote target URI (to field) in the req_uri */
  //   i = osip_uri_clone (dialog->remote_contact_uri->url, &(request->req_uri));
  //   if (i != 0) {
  //     osip_message_free (request);
  //     return i;
  //   }
  // } else {
  //   /* fill the request-uri, and the route headers. */
  //   i = dialog_fill_route_set (dialog, request);
  //   if (i != 0) {
  //     osip_message_free (request);
  //     return i;
  //   }
  // }

  /* To and From already contains the proper tag! */
  i = osip_to_clone (dialog->remote_uri, &(request->to));
  if (i != 0) {
    osip_message_free (request);
    LOG_DAFEI() << "dafei return" << std::endl;
    return i;
  }
  i = osip_from_clone (dialog->local_uri, &(request->from));
  if (i != 0) {
    osip_message_free (request);
    LOG_DAFEI() << "dafei return" << std::endl;
    return i;
  }

  /* set the cseq and call_id header */
  osip_message_set_call_id (request, dialog->call_id);

  if (0 == strcmp ("ACK", method)) {
    osip_cseq_t *cseq;
    char *tmp;

    i = osip_cseq_init (&cseq);
    if (i != 0) {
      osip_message_free (request);
      LOG_DAFEI() << "dafei return" << std::endl;
      return i;
    }
    tmp = (char*)osip_malloc (20);
    if (tmp == NULL) {
      osip_message_free (request);
      LOG_DAFEI() << "dafei return" << std::endl;
      return OSIP_NOMEM;
    }
    sprintf (tmp, "%i", dialog->local_cseq);
    osip_cseq_set_number (cseq, tmp);
    osip_cseq_set_method (cseq, osip_strdup (method));
    request->cseq = cseq;
  } else {
    osip_cseq_t *cseq;
    char *tmp;

    i = osip_cseq_init (&cseq);
    if (i != 0) {
      osip_message_free (request);
      LOG_DAFEI() << "dafei return" << std::endl;
      return i;
    }
    dialog->local_cseq++;       /* we should we do that?? */
    tmp = (char*)osip_malloc (20);
    if (tmp == NULL) {
      osip_message_free (request);
      LOG_DAFEI() << "dafei return" << std::endl;
      return OSIP_NOMEM;
    }
    snprintf (tmp, 20, "%i", dialog->local_cseq);
    osip_cseq_set_number (cseq, tmp);
    osip_cseq_set_method (cseq, osip_strdup (method));
    request->cseq = cseq;
  }

  /* always add the Max-Forward header */
  osip_message_set_max_forwards (request, "70");        /* a UA should start a request with 70 */

  // TODO dafei add via
  // i = _eXosip_request_add_via (excontext, request, transport, locip);
  // if (i != 0) {
  //   osip_message_free (request);
  //   return i;
  // }

  char tmp[200] = { 0 };
  snprintf (tmp, 200, "SIP/2.0/%s %s:%s;branch=z9hG4bK%u", "UDP", "10.10.10.3", "5060", osip_build_random_number());
  osip_message_set_via(request, tmp);

  /* add specific headers for each kind of request... */
  if ((0 != strcmp ("BYE", method)) && (0 != strcmp ("CANCEL", method)))
  {
    // TODO dafei why we need contact for bye???
    // Because it will crash when init transaction.
    // _eXosip_dialog_add_contact (excontext, request);
    osip_message_set_contact(request, "<sip:bob@192.0.2.4>");
  }

  if (0 == strcmp ("NOTIFY", method)) {
  } else if (0 == strcmp ("INFO", method)) {

  } else if (0 == strcmp ("OPTIONS", method)) {
    osip_message_set_accept (request, "application/sdp");
  } else if (0 == strcmp ("ACK", method)) {
    /* The ACK MUST contains the same credential than the INVITE!! */
    /* TODO... */
  }

  osip_message_set_user_agent (request, osip_strdup("xiaoming"));
  /*  else if ... */
  *dest = request;
  return OSIP_SUCCESS;
}


int dialog_fill_route_set (osip_dialog_t * dialog, osip_message_t * request)
{
  /* if the pre-existing route set contains a "lr" (compliance
     with bis-08) then the req_uri should contains the remote target
     URI */
  int i;
  int pos = 0;
  osip_uri_param_t *lr_param;
  osip_route_t *route;
  char *last_route;

  /* AMD bug: fixed 17/06/2002 */

  route = (osip_route_t *) osip_list_get (&dialog->route_set, 0);

  osip_uri_uparam_get_byname (route->url, "lr", &lr_param);
  if (lr_param != NULL) {       /* the remote target URI is the req_uri! */
    i = osip_uri_clone (dialog->remote_contact_uri->url, &(request->req_uri));
    if (i != 0)
      return i;
    /* "[request] MUST includes a Route header field containing
       the route set values in order." */
    /* AMD bug: fixed 17/06/2002 */
    pos = 0;                    /* first element is at index 0 */
    while (!osip_list_eol (&dialog->route_set, pos)) {
      osip_route_t *route2;

      route = (osip_route_t*)osip_list_get (&dialog->route_set, pos);
      i = osip_route_clone (route, &route2);
      if (i != 0)
        return i;
      osip_list_add (&request->routes, route2, -1);
      pos++;
    }
    return OSIP_SUCCESS;
  }

  /* if the first URI of route set does not contain "lr", the req_uri
     is set to the first uri of route set */


  i = osip_uri_clone (route->url, &(request->req_uri));
  if (i != 0)
    return i;
  /* add the route set */
  /* "The UAC MUST add a route header field containing
     the remainder of the route set values in order. */
  pos = 0;                      /* yes it is */

  while (!osip_list_eol (&dialog->route_set, pos)) {    /* not the first one in the list */
    osip_route_t *route2;

    route = (osip_route_t*)osip_list_get (&dialog->route_set, pos);
    i = osip_route_clone (route, &route2);
    if (i != 0)
      return i;
    if (!osip_list_eol (&dialog->route_set, pos + 1))
      osip_list_add (&request->routes, route2, -1);
    else
      osip_route_free (route2);
    pos++;
  }

  /* The UAC MUST then place the remote target URI into
     the route header field as the last value */
  i = osip_uri_to_str (dialog->remote_contact_uri->url, &last_route);
  if (i != 0)
    return i;
  i = osip_message_set_route (request, last_route);
  osip_free (last_route);
  if (i != 0) {
    return i;
  }

  /* route header and req_uri set */
  return OSIP_SUCCESS;
}
