/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under 
 * the Apache License, Version 2.0  (the "License"); you may not use this file
 * except in compliance with the License.  
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

/*! \file s11_mme_session_manager.c
  \brief
  \author Sebastien ROUX, Lionel Gauthier
  \company Eurecom
  \email: lionel.gauthier@eurecom.fr
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "bstrlib.h"

#include "hashtable.h"
#include "obj_hashtable.h"
#include "log.h"
#include "msc.h"
#include "assertions.h"
#include "intertask_interface.h"
#include "hashtable.h"
#include "msc.h"

#include "NwGtpv2c.h"
#include "NwGtpv2cIe.h"
#include "NwGtpv2cMsg.h"
#include "NwGtpv2cMsgParser.h"

#include "s11_common.h"
#include "s11_mme_session_manager.h"

#include "../gtpv2-c/gtpv2c_ie_formatter/shared/gtpv2c_ie_formatter.h"
#include "s11_ie_formatter.h"
#include "s11_messages_types.h"


extern hash_table_ts_t                        *s11_mme_teid_2_gtv2c_teid_handle;

//------------------------------------------------------------------------------
int
s11_mme_create_session_request (
  nw_gtpv2c_stack_handle_t * stack_p,
  itti_s11_create_session_request_t * req_p)
{
  nw_gtpv2c_ulp_api_t                         ulp_req;
  nw_rc_t                                   rc;
  uint8_t                                 restart_counter = 0;
  OAILOG_FUNC_IN (LOG_S11);

  DevAssert (stack_p );
  DevAssert (req_p );
  memset (&ulp_req, 0, sizeof (nw_gtpv2c_ulp_api_t));
  ulp_req.apiType = NW_GTPV2C_ULP_API_INITIAL_REQ;
  /*
   * Prepare a new Create Session Request msg
   */
  rc = nwGtpv2cMsgNew (*stack_p, true, NW_GTP_CREATE_SESSION_REQ, req_p->teid, 0, &(ulp_req.hMsg));
  ulp_req.u_api_info.initialReqInfo.peerIp     = req_p->peer_ip;
  ulp_req.u_api_info.initialReqInfo.teidLocal  = req_p->sender_fteid_for_cp.teid;
  ulp_req.u_api_info.initialReqInfo.hUlpTunnel = 0;
  ulp_req.u_api_info.initialReqInfo.hTunnel    = 0;
  /*
   * Add recovery if contacting the peer for the first time
   */
  rc = nwGtpv2cMsgAddIe ((ulp_req.hMsg), NW_GTPV2C_IE_RECOVERY, 1, 0, (uint8_t *) & restart_counter);
  DevAssert (NW_OK == rc);
  /*
   * Putting the information Elements
   */
  gtpv2c_imsi_ie_set (&(ulp_req.hMsg), &req_p->imsi);
  gtpv2c_uli_ie_set (&(ulp_req.hMsg), &req_p->uli);
  gtpv2c_rat_type_ie_set (&(ulp_req.hMsg), &req_p->rat_type);
  gtpv2c_pdn_type_ie_set (&(ulp_req.hMsg), &req_p->pdn_type);
  gtpv2c_paa_ie_set(&(ulp_req.hMsg), &req_p->paa);
  gtpv2c_apn_restriction_ie_set(&(ulp_req.hMsg), 0);
  /**
   * Set the AMBR.
   */
  gtpv2c_ambr_ie_set(&ulp_req.hMsg, &req_p->ambr);

  /**
   * Indication Flags.
   */
  gtpv2c_indication_flags_ie_set (&(ulp_req.hMsg), &req_p->indication_flags);

  /*
   * Sender F-TEID for Control Plane (MME S11)
   */
  rc = nwGtpv2cMsgAddIeFteid ((ulp_req.hMsg), NW_GTPV2C_IE_INSTANCE_ZERO,
                              S11_MME_GTP_C,
                              req_p->sender_fteid_for_cp.teid,
                              req_p->sender_fteid_for_cp.ipv4 ? &req_p->sender_fteid_for_cp.ipv4_address : 0,
                              req_p->sender_fteid_for_cp.ipv6 ? &req_p->sender_fteid_for_cp.ipv6_address : NULL);

  /*
   * The P-GW TEID should be present on the S11 interface.
   * * * * In case of an initial attach it should be set to 0...
   */
  rc = nwGtpv2cMsgAddIeFteid ((ulp_req.hMsg), NW_GTPV2C_IE_INSTANCE_ONE,
                              S5_S8_PGW_GTP_C,
                              req_p->pgw_address_for_cp.teid,
                              req_p->pgw_address_for_cp.ipv4 ? &req_p->pgw_address_for_cp.ipv4_address : 0,
                              req_p->pgw_address_for_cp.ipv6 ? &req_p->pgw_address_for_cp.ipv6_address : NULL);

  int num_dots = 0;
  for (int i =  0; i < strlen(req_p->apn); i++) {
    if (req_p->apn[i] == '.') {
      num_dots++;
    }
  }
  // May check 2 dots
  if (num_dots) {
    gtpv2c_apn_ie_set (&(ulp_req.hMsg), req_p->apn);
  } else {
    gtpv2c_apn_plmn_ie_set (&(ulp_req.hMsg), req_p->apn, &req_p->serving_network);
  }

  gtpv2c_selection_mode_ie_set(&(ulp_req.hMsg), &req_p->selection_mode);
  
  gtpv2c_serving_network_ie_set (&(ulp_req.hMsg), &req_p->serving_network);
  if(req_p->pco.num_protocol_or_container_id){
    gtpv2c_pco_ie_set (&(ulp_req.hMsg), &req_p->pco);
  }
  if(req_p->bearer_contexts_to_be_created->num_bearer_context > 1){
	  gtpv2c_ebi_ie_set (&(ulp_req.hMsg), (unsigned)req_p->default_ebi, NW_GTPV2C_IE_INSTANCE_ZERO);
  }

  for (int i = 0; i < req_p->bearer_contexts_to_be_created->num_bearer_context; i++) {
    gtpv2c_bearer_context_to_be_created_ie_set (&(ulp_req.hMsg), &req_p->bearer_contexts_to_be_created->bearer_contexts[i]);
  }
  rc = nwGtpv2cProcessUlpReq (*stack_p, &ulp_req);
  DevAssert (NW_OK == rc);
  MSC_LOG_TX_MESSAGE (MSC_S11_MME, MSC_SGW, NULL, 0, "0 CREATE_SESSION_REQUEST local S11 teid " TEID_FMT " num bearers ctx %u",
    req_p->sender_fteid_for_cp.teid, req_p->bearer_contexts_to_be_created->num_bearer_context);

  hashtable_rc_t hash_rc = hashtable_ts_insert(s11_mme_teid_2_gtv2c_teid_handle,
      (hash_key_t) req_p->sender_fteid_for_cp.teid,
      (void *)ulp_req.u_api_info.initialReqInfo.hTunnel);
  if (HASH_TABLE_OK != hash_rc) {
    OAILOG_WARNING (LOG_S11, "Could not save GTPv2-C hTunnel %p for local teid %X\n", (void*)ulp_req.u_api_info.initialReqInfo.hTunnel, ulp_req.u_api_info.initialReqInfo.teidLocal);
    OAILOG_FUNC_RETURN (LOG_S11, RETURNerror);
  }
  OAILOG_FUNC_RETURN (LOG_S11, RETURNok);
}

//------------------------------------------------------------------------------
int
s11_mme_handle_create_session_response (
  nw_gtpv2c_stack_handle_t * stack_p,
  nw_gtpv2c_ulp_api_t * pUlpApi)
{
  nw_rc_t                                   rc = NW_OK;
  uint8_t                                 offendingIeType,
                                          offendingIeInstance;
  uint16_t                                offendingIeLength;
  itti_s11_create_session_response_t     *resp_p;
  MessageDef                             *message_p;
  nw_gtpv2c_msg_parser_t                     *pMsgParser;

  DevAssert (stack_p );
  message_p = itti_alloc_new_message (TASK_S11, S11_CREATE_SESSION_RESPONSE);
  resp_p = &message_p->ittiMsg.s11_create_session_response;

  resp_p->teid = nwGtpv2cMsgGetTeid(pUlpApi->hMsg);

  /*
   * Create a new message parser
   */
  rc = nwGtpv2cMsgParserNew (*stack_p, NW_GTP_CREATE_SESSION_RSP, s11_ie_indication_generic, NULL, &pMsgParser);
  DevAssert (NW_OK == rc);
  /*
   * Cause IE
   */
  rc = nwGtpv2cMsgParserAddIe (pMsgParser, NW_GTPV2C_IE_CAUSE, NW_GTPV2C_IE_INSTANCE_ZERO, NW_GTPV2C_IE_PRESENCE_MANDATORY,
      gtpv2c_cause_ie_get, &resp_p->cause);
  DevAssert (NW_OK == rc);
  /*
   * Sender FTEID for CP IE
   */
  rc = nwGtpv2cMsgParserAddIe (pMsgParser, NW_GTPV2C_IE_FTEID, NW_GTPV2C_IE_INSTANCE_ZERO, NW_GTPV2C_IE_PRESENCE_CONDITIONAL,
      gtpv2c_fteid_ie_get, &resp_p->s11_sgw_fteid);
  DevAssert (NW_OK == rc);
  /*
   * Sender FTEID for PGW S5/S8 IE
   */
  rc = nwGtpv2cMsgParserAddIe (pMsgParser, NW_GTPV2C_IE_FTEID, NW_GTPV2C_IE_INSTANCE_ONE, NW_GTPV2C_IE_PRESENCE_CONDITIONAL,
      gtpv2c_fteid_ie_get, &resp_p->s5_s8_pgw_fteid);
  DevAssert (NW_OK == rc);
  /*
   * PAA IE
   */
  /** Allocate the PAA IE. */
  resp_p->paa = calloc (1, sizeof(paa_t));
  rc = nwGtpv2cMsgParserAddIe (pMsgParser, NW_GTPV2C_IE_PAA, NW_GTPV2C_IE_INSTANCE_ZERO, NW_GTPV2C_IE_PRESENCE_CONDITIONAL,
      gtpv2c_paa_ie_get, resp_p->paa);
  DevAssert (NW_OK == rc);
  /*
   * APN RESTRICTION
   */
  rc = nwGtpv2cMsgParserAddIe (pMsgParser, NW_GTPV2C_IE_APN_RESTRICTION, NW_GTPV2C_IE_INSTANCE_ZERO, NW_GTPV2C_IE_PRESENCE_CONDITIONAL,
      gtpv2c_apn_restriction_ie_get, &resp_p->apn_restriction);
  DevAssert (NW_OK == rc);

  /** Add the AMBR. */
  rc = nwGtpv2cMsgParserAddIe (pMsgParser, NW_GTPV2C_IE_AMBR, NW_GTPV2C_IE_INSTANCE_ZERO, NW_GTPV2C_IE_PRESENCE_CONDITIONAL, gtpv2c_ambr_ie_get,
      &resp_p->ambr);
  DevAssert (NW_OK == rc);

  /*
   * PCO IE
   */
  rc = nwGtpv2cMsgParserAddIe (pMsgParser, NW_GTPV2C_IE_PCO, NW_GTPV2C_IE_INSTANCE_ZERO, NW_GTPV2C_IE_PRESENCE_CONDITIONAL,
      gtpv2c_pco_ie_get, &resp_p->pco);
  DevAssert (NW_OK == rc);
  /*
   * Bearer Contexts Created IE
   */
  rc = nwGtpv2cMsgParserAddIe (pMsgParser, NW_GTPV2C_IE_BEARER_CONTEXT, NW_GTPV2C_IE_INSTANCE_ZERO, NW_GTPV2C_IE_PRESENCE_CONDITIONAL,
      gtpv2c_bearer_context_created_ie_get, &resp_p->bearer_contexts_created);
  DevAssert (NW_OK == rc);
  /*
   * Bearer Contexts Marked For Removal IE
   */
  rc = nwGtpv2cMsgParserAddIe (pMsgParser, NW_GTPV2C_IE_BEARER_CONTEXT, NW_GTPV2C_IE_INSTANCE_ONE, NW_GTPV2C_IE_PRESENCE_CONDITIONAL,
      gtpv2c_bearer_context_marked_for_removal_ie_get, &resp_p->bearer_contexts_marked_for_removal);
  DevAssert (NW_OK == rc);
  /*
   * Run the parser
   */
  rc = nwGtpv2cMsgParserRun (pMsgParser, (pUlpApi->hMsg), &offendingIeType, &offendingIeInstance, &offendingIeLength);

  if (rc != NW_OK) {
    MSC_LOG_RX_DISCARDED_MESSAGE (MSC_S11_MME, MSC_SGW, NULL, 0, "0 CREATE_SESSION_RESPONSE local S11 teid " TEID_FMT " ", resp_p->teid);
    /*
     * TODO: handle this case
     */
    itti_free (ITTI_MSG_ORIGIN_ID (message_p), message_p);
    message_p = NULL;
    rc = nwGtpv2cMsgParserDelete (*stack_p, pMsgParser);
    DevAssert (NW_OK == rc);
    rc = nwGtpv2cMsgDelete (*stack_p, (pUlpApi->hMsg));
    DevAssert (NW_OK == rc);
    return RETURNerror;
  }

  rc = nwGtpv2cMsgParserDelete (*stack_p, pMsgParser);
  DevAssert (NW_OK == rc);
  rc = nwGtpv2cMsgDelete (*stack_p, (pUlpApi->hMsg));
  DevAssert (NW_OK == rc);

  MSC_LOG_RX_MESSAGE (MSC_S11_MME, MSC_SGW, NULL, 0, "0 CREATE_SESSION_RESPONSE local S11 teid " TEID_FMT " num bearer ctxt %u", resp_p->teid,
    resp_p->bearer_contexts_created.num_bearer_context);
  return itti_send_msg_to_task (TASK_MME_APP, INSTANCE_DEFAULT, message_p);
}

//------------------------------------------------------------------------------
int
s11_mme_delete_session_request (
  nw_gtpv2c_stack_handle_t * stack_p,
  itti_s11_delete_session_request_t * req_p)
{
  nw_gtpv2c_ulp_api_t                         ulp_req;
  nw_rc_t                                   rc;
  //uint8_t                                 restart_counter = 0;

  DevAssert (stack_p );
  DevAssert (req_p );
  memset (&ulp_req, 0, sizeof (nw_gtpv2c_ulp_api_t));
  ulp_req.apiType = NW_GTPV2C_ULP_API_INITIAL_REQ;
  /*
   * Prepare a new Delete Session Request msg
   */
  rc = nwGtpv2cMsgNew (*stack_p, true, NW_GTP_DELETE_SESSION_REQ, req_p->teid, 0, &(ulp_req.hMsg));
  ulp_req.u_api_info.initialReqInfo.peerIp = req_p->peer_ip;
  ulp_req.u_api_info.initialReqInfo.teidLocal = req_p->local_teid;
  ulp_req.u_api_info.initialReqInfo.noDelete  = req_p->noDelete;

  hashtable_rc_t hash_rc = hashtable_ts_get(s11_mme_teid_2_gtv2c_teid_handle,
      (hash_key_t) ulp_req.u_api_info.initialReqInfo.teidLocal,
      (void **)(uintptr_t)&ulp_req.u_api_info.initialReqInfo.hTunnel);

  if (HASH_TABLE_OK != hash_rc) {
    OAILOG_WARNING (LOG_S11, "Could not get GTPv2-C hTunnel for local teid %X\n", ulp_req.u_api_info.initialReqInfo.teidLocal);
    return RETURNerror;
  }

  /*
   * Sender F-TEID for Control Plane (MME S11)
   */
  rc = nwGtpv2cMsgAddIeFteid ((ulp_req.hMsg), NW_GTPV2C_IE_INSTANCE_ZERO,
                              S11_MME_GTP_C,
                              req_p->sender_fteid_for_cp.teid,
                              req_p->sender_fteid_for_cp.ipv4 ? &req_p->sender_fteid_for_cp.ipv4_address : 0,
                              req_p->sender_fteid_for_cp.ipv6 ? &req_p->sender_fteid_for_cp.ipv6_address : NULL);

  gtpv2c_ebi_ie_set (&(ulp_req.hMsg), (unsigned)req_p->lbi, NW_GTPV2C_IE_INSTANCE_ZERO);

  if ((req_p->indication_flags.oi) || (req_p->indication_flags.si)){
    gtpv2c_indication_flags_ie_set (&(ulp_req.hMsg), &req_p->indication_flags);
  }

  rc = nwGtpv2cProcessUlpReq (*stack_p, &ulp_req);
  DevAssert (NW_OK == rc);
  MSC_LOG_TX_MESSAGE (MSC_S11_MME, MSC_SGW, NULL, 0, "0 DELETE_SESSION_REQUEST local S11 teid " TEID_FMT " ",
		  req_p->local_teid);

  return RETURNok;
}

//------------------------------------------------------------------------------
int
s11_mme_handle_delete_session_response (
  nw_gtpv2c_stack_handle_t * stack_p,
  nw_gtpv2c_ulp_api_t * pUlpApi)
{
  nw_rc_t                                 rc = NW_OK;
  uint8_t                                 offendingIeType,
                                          offendingIeInstance;
  uint16_t                                offendingIeLength;
  itti_s11_delete_session_response_t     *resp_p = NULL;
  MessageDef                             *message_p = NULL;
  nw_gtpv2c_msg_parser_t                 *pMsgParser = NULL;
  hashtable_rc_t                          hash_rc = HASH_TABLE_OK;

  DevAssert (stack_p );
  message_p = itti_alloc_new_message (TASK_S11, S11_DELETE_SESSION_RESPONSE);
  resp_p = &message_p->ittiMsg.s11_delete_session_response;

  resp_p->teid = nwGtpv2cMsgGetTeid(pUlpApi->hMsg);
  resp_p->internal_flags = pUlpApi->u_api_info.triggeredRspIndInfo.trx_flags;

  /*
   * Create a new message parser
   */
  rc = nwGtpv2cMsgParserNew (*stack_p, NW_GTP_DELETE_SESSION_RSP, s11_ie_indication_generic, NULL, &pMsgParser);
  DevAssert (NW_OK == rc);
  /*
   * Cause IE
   */
  rc = nwGtpv2cMsgParserAddIe (pMsgParser, NW_GTPV2C_IE_CAUSE, NW_GTPV2C_IE_INSTANCE_ZERO, NW_GTPV2C_IE_PRESENCE_MANDATORY,
      gtpv2c_cause_ie_get, &resp_p->cause);
  DevAssert (NW_OK == rc);
  /*
   * Recovery IE
   */
  /* TODO rc = nwGtpv2cMsgParserAddIe (pMsgParser, NW_GTPV2C_IE_RECOVERY, NW_GTPV2C_IE_INSTANCE_ZERO, NW_GTPV2C_IE_PRESENCE_CONDITIONAL, s11_fteid_ie_get,
		  &resp_p->recovery);
  DevAssert (NW_OK == rc); */
  /*
   * PCO IE
   */
  rc = nwGtpv2cMsgParserAddIe (pMsgParser, NW_GTPV2C_IE_PCO, NW_GTPV2C_IE_INSTANCE_ZERO, NW_GTPV2C_IE_PRESENCE_CONDITIONAL,
      gtpv2c_pco_ie_get, &resp_p->pco);
  DevAssert (NW_OK == rc);

  /*
   * Run the parser
   */
  rc = nwGtpv2cMsgParserRun (pMsgParser, (pUlpApi->hMsg), &offendingIeType, &offendingIeInstance, &offendingIeLength);

  if (rc != NW_OK) {
    MSC_LOG_RX_DISCARDED_MESSAGE (MSC_S11_MME, MSC_SGW, NULL, 0, "0 DELETE_SESSION_RESPONSE local S11 teid " TEID_FMT " ", resp_p->teid);
    /*
     * TODO: handle this case
     */
    itti_free (ITTI_MSG_ORIGIN_ID (message_p), message_p);
    message_p = NULL;
    rc = nwGtpv2cMsgParserDelete (*stack_p, pMsgParser);
    DevAssert (NW_OK == rc);
    rc = nwGtpv2cMsgDelete (*stack_p, (pUlpApi->hMsg));
    DevAssert (NW_OK == rc);
    return RETURNerror;
  }

  rc = nwGtpv2cMsgParserDelete (*stack_p, pMsgParser);
  DevAssert (NW_OK == rc);
  rc = nwGtpv2cMsgDelete (*stack_p, (pUlpApi->hMsg));
  DevAssert (NW_OK == rc);

  MSC_LOG_RX_MESSAGE (MSC_S11_MME, MSC_SGW, NULL, 0, "0 DELETE_SESSION_RESPONSE local S11 teid " TEID_FMT " ", resp_p->teid);

  // delete local tunnel, if nothing against
  if(pUlpApi->u_api_info.triggeredRspIndInfo.noDelete){
    OAILOG_INFO(LOG_S11, "Not deleting the local tunnel since \"noDelete\" flag is set. \n");
  }else{
    OAILOG_INFO (LOG_S11, "Deleting the local tunnel. \n");
    nw_gtpv2c_ulp_api_t                         ulp_req;
    memset (&ulp_req, 0, sizeof (nw_gtpv2c_ulp_api_t));
    ulp_req.apiType = NW_GTPV2C_ULP_DELETE_LOCAL_TUNNEL;
    hash_rc = hashtable_ts_get(s11_mme_teid_2_gtv2c_teid_handle,
        (hash_key_t) resp_p->teid,
        (void **)(uintptr_t)&ulp_req.u_api_info.deleteLocalTunnelInfo.hTunnel);
    if (HASH_TABLE_OK != hash_rc) {
      OAILOG_ERROR (LOG_S11, "Could not get GTPv2-C hTunnel for local teid %X (skipping deletion of tunnel)\n", resp_p->teid);
      MSC_LOG_EVENT (MSC_S11_MME, "Failed to deleted teid " TEID_FMT "", resp_p->teid);
    } else {
      rc = nwGtpv2cProcessUlpReq (*stack_p, &ulp_req);
      DevAssert (NW_OK == rc);
      MSC_LOG_EVENT (MSC_S11_MME, "Deleted teid " TEID_FMT "", resp_p->teid);
      hash_rc = hashtable_ts_free(s11_mme_teid_2_gtv2c_teid_handle, (hash_key_t) resp_p->teid);
      DevAssert (HASH_TABLE_OK == hash_rc);
    }

  }
  return itti_send_msg_to_task (TASK_MME_APP, INSTANCE_DEFAULT, message_p);
}

//------------------------------------------------------------------------------
int
s11_mme_handle_ulp_error_indicatior(
  nw_gtpv2c_stack_handle_t * stack_p,
  nw_gtpv2c_ulp_api_t * pUlpApi)
{
  /** Get the failed transaction. */
  /** Check the message type. */
  OAILOG_FUNC_IN (LOG_S11);

  nw_gtpv2c_msg_type_t msgType = pUlpApi->u_api_info.rspFailureInfo.msgType;
  MessageDef * message_p = NULL;
  switch(msgType){
  case NW_GTP_CREATE_SESSION_REQ: /**< Message which was sent!. */
  {
    itti_s11_create_session_response_t            *rsp_p;
    /** Respond with an S10 Context Reponse Failure. */
    message_p = itti_alloc_new_message (TASK_S11, S11_CREATE_SESSION_RESPONSE);
    rsp_p = &message_p->ittiMsg.s11_create_session_response;
    memset(rsp_p, 0, sizeof(*rsp_p));
    /** Set the destination TEID (our TEID). */
    rsp_p->teid = pUlpApi->u_api_info.rspFailureInfo.teidLocal;
    /** Set the transaction for the triggered acknowledgment. */
    rsp_p->trxn = (void *)pUlpApi->u_api_info.rspFailureInfo.hUlpTrxn;
    /** Set the cause. */
    rsp_p->cause.cause_value = SYSTEM_FAILURE; /**< Would mean that this message either did not come at all or could not be dealt with properly. */
  }
    break;
  case NW_GTP_MODIFY_BEARER_REQ:
  {
    itti_s11_modify_bearer_response_t            *rsp_p;
    message_p = itti_alloc_new_message (TASK_S11, S11_MODIFY_BEARER_RESPONSE);
    rsp_p = &message_p->ittiMsg.s11_modify_bearer_response;
    memset(rsp_p, 0, sizeof(*rsp_p));
    /** Set the destination TEID (our TEID). */
    rsp_p->teid = pUlpApi->u_api_info.rspFailureInfo.teidLocal;
    /** Set the transaction for the triggered acknowledgment. */
    rsp_p->trxn = (void *)pUlpApi->u_api_info.rspFailureInfo.hUlpTrxn;
    /** Set the cause. */
    rsp_p->cause.cause_value = SYSTEM_FAILURE; /**< Would mean that this message either did not come at all or could not be dealt with properly. */
  }
    break;
  case NW_GTP_DELETE_SESSION_REQ:
  {
    /**
     * We will omit the error and send success back.
     * UE context should always be removed.
     */
    itti_s11_delete_session_response_t            *rsp_p;
    message_p = itti_alloc_new_message (TASK_S11, S11_DELETE_SESSION_RESPONSE);
    rsp_p = &message_p->ittiMsg.s11_delete_session_response;
    memset(rsp_p, 0, sizeof(*rsp_p));
    /** Set the destination TEID (our TEID). */
    rsp_p->teid = pUlpApi->u_api_info.rspFailureInfo.teidLocal;
    /** Set the transaction for the triggered acknowledgment. */
    rsp_p->trxn = (void *)pUlpApi->u_api_info.rspFailureInfo.hUlpTrxn;
    /** Set the cause. */
    rsp_p->cause.cause_value = REQUEST_ACCEPTED; /**< Would mean that this message either did not come at all or could not be dealt with properly. */
    OAILOG_ERROR (LOG_S11, "DELETE_SESSION_RESPONE could not be received for for local teid " TEID_FMT". Sending ACCEPTED back (ignoring the network failure). \n", rsp_p->teid);
  }
    break;
  case NW_GTP_RELEASE_ACCESS_BEARERS_REQ:
   {
     /**
      * We will omit the error and send success back.
      * UE context should always be removed.
      */
     itti_s11_release_access_bearers_response_t            *rsp_p;
     message_p = itti_alloc_new_message (TASK_S11, S11_RELEASE_ACCESS_BEARERS_RESPONSE);
     rsp_p = &message_p->ittiMsg.s11_release_access_bearers_response;
     memset(rsp_p, 0, sizeof(*rsp_p));
     /** Set the destination TEID (our TEID). */
     rsp_p->teid = pUlpApi->u_api_info.rspFailureInfo.teidLocal;
     /** Set the transaction for the triggered acknowledgment. */
     rsp_p->trxn = (void *)pUlpApi->u_api_info.rspFailureInfo.hUlpTrxn;
     /** Set the cause. */
     rsp_p->cause.cause_value = REQUEST_ACCEPTED; /**< Would mean that this message either did not come at all or could not be dealt with properly. */
     OAILOG_ERROR (LOG_S11, "RELEASE_ACCESS_BEARERS_RESPONSE could not be received for for local teid " TEID_FMT". Sending ACCEPTED back (ignoring the network failure). \n", rsp_p->teid);
   }
     break;
       /** Failed commands. */
  case NW_GTP_DELETE_BEARER_CMD:
  {
    /**
     * We will omit the error and send success back.
     * UE context should always be removed.
     */
    itti_s11_delete_bearer_failure_indication_t            *ind_p;
    message_p = itti_alloc_new_message (TASK_S11, S11_DELETE_BEARER_FAILURE_INDICATION);
    ind_p = &message_p->ittiMsg.s11_delete_bearer_failure_indication;
    /** Set the destination TEID (our TEID). */
    ind_p->teid = pUlpApi->u_api_info.rspFailureInfo.teidLocal;
    /** Set the transaction for the triggered acknowledgment. */
    ind_p->trxn = (void *)pUlpApi->u_api_info.rspFailureInfo.hUlpTrxn;
    /** Set the cause. */
    ind_p->cause.cause_value = SYSTEM_FAILURE; /**< Would mean that this message either did not come at all or could not be dealt with properly. */
  }
  break;

  /** Failed commands --> Send to NAS_ESM layer.. */
  case NW_GTP_BEARER_RESOURCE_CMD:
  {
	  /**
       * We will omit the error and send success back.
       * UE context should always be removed.
       */
      itti_s11_bearer_resource_failure_indication_t            *ind_p;
      message_p = itti_alloc_new_message (TASK_S11, S11_BEARER_RESOURCE_FAILURE_INDICATION);
      ind_p = &message_p->ittiMsg.s11_bearer_resource_failure_indication;
      /** Set the destination TEID (our TEID). */
      ind_p->teid = pUlpApi->u_api_info.rspFailureInfo.teidLocal;
      /** Set the transaction for the triggered acknowledgment. */
      ind_p->trxn = (void *)pUlpApi->u_api_info.rspFailureInfo.hUlpTrxn;
      /** Set the PTI from the flags. */
      ind_p->pti  = pUlpApi->u_api_info.rspFailureInfo.trx_flags;
      /** Set the cause. */
      ind_p->cause.cause_value = SYSTEM_FAILURE; /**< Would mean that this message either did not come at all or could not be dealt with properly. */
  }
  /** Send this one directly to the ESM. */
  int rc = itti_send_msg_to_task (TASK_NAS_ESM, INSTANCE_DEFAULT, message_p);
  OAILOG_FUNC_RETURN (LOG_S11, rc);

  default:
    OAILOG_ERROR (LOG_S10, "Received an unhandled error indicator for the local S11-TEID " TEID_FMT " and message type %d. \n",
        pUlpApi->u_api_info.rspFailureInfo.teidLocal, pUlpApi->u_api_info.rspFailureInfo.msgType);
    OAILOG_FUNC_RETURN (LOG_S11, RETURNerror);
  }
  OAILOG_WARNING (LOG_S10, "Received an error indicator for the local S11-TEID " TEID_FMT " and message type %d. \n",
      pUlpApi->u_api_info.rspFailureInfo.teidLocal, pUlpApi->u_api_info.rspFailureInfo.msgType);
  int rc = itti_send_msg_to_task (TASK_MME_APP, INSTANCE_DEFAULT, message_p);
  OAILOG_FUNC_RETURN (LOG_S11, rc);
}

