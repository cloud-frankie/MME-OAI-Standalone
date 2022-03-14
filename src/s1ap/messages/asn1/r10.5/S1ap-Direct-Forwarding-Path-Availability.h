/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "S1AP-IEs"
 * 	found in "S1AP-IEs.asn"
 */

#ifndef	_S1ap_Direct_Forwarding_Path_Availability_H_
#define	_S1ap_Direct_Forwarding_Path_Availability_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum S1ap_Direct_Forwarding_Path_Availability {
	S1ap_Direct_Forwarding_Path_Availability_directPathAvailable	= 0
	/*
	 * Enumeration is extensible
	 */
} e_S1ap_Direct_Forwarding_Path_Availability;

/* S1ap-Direct-Forwarding-Path-Availability */
typedef long	 S1ap_Direct_Forwarding_Path_Availability_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_S1ap_Direct_Forwarding_Path_Availability;
asn_struct_free_f S1ap_Direct_Forwarding_Path_Availability_free;
asn_struct_print_f S1ap_Direct_Forwarding_Path_Availability_print;
asn_constr_check_f S1ap_Direct_Forwarding_Path_Availability_constraint;
ber_type_decoder_f S1ap_Direct_Forwarding_Path_Availability_decode_ber;
der_type_encoder_f S1ap_Direct_Forwarding_Path_Availability_encode_der;
xer_type_decoder_f S1ap_Direct_Forwarding_Path_Availability_decode_xer;
xer_type_encoder_f S1ap_Direct_Forwarding_Path_Availability_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _S1ap_Direct_Forwarding_Path_Availability_H_ */
#include <asn_internal.h>
