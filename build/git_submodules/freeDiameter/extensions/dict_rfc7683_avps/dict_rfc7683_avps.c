/*
* Copyright (c) 2017 Sprint
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/****************
 Generated By: fdtool enhancements to diafuzzer
 License: same as freeDiameter
****************/


/* 
 * Dictionary definitions of objects specified in rfc7683_avps.
 */
#include <freeDiameter/extension.h>

#define PROTO_VER "unspecified"
#define GEN_DATE  1506697143.69

const char *rfc7683_avps_proto_ver = PROTO_VER;
const double rfc7683_avps_gen_date = GEN_DATE;

/* The content of this file follows the same structure as dict_base_proto.c */

#define CHECK_dict_new( _type, _data, _parent, _ref )                                     \
{                                                                                         \
    int _ret = fd_dict_new( fd_g_config->cnf_dict, (_type), (_data), (_parent), (_ref) ); \
    if ( _ret != 0 && _ret != EEXIST )                                                    \
       return _ret;                                                                       \
}

#define CHECK_dict_search( _type, _criteria, _what, _result )		\
    CHECK_FCT(  fd_dict_search( fd_g_config->cnf_dict, (_type), (_criteria), (_what), (_result), ENOENT) );

struct local_rules_definition {
    struct dict_avp_request avp_vendor_plus_name;
    enum rule_position	position;
    int 			min;
    int			max;
};

#define RULE_ORDER( _position ) ((((_position) == RULE_FIXED_HEAD) || ((_position) == RULE_FIXED_TAIL)) ? 1 : 0 )

/* Attention! This version of the macro uses AVP_BY_NAME_AND_VENDOR, in contrast to most other copies! */
#define PARSE_loc_rules( _rulearray, _parent) {                                                         \
        int __ar;                                                                                       \
        for (__ar=0; __ar < sizeof(_rulearray) / sizeof((_rulearray)[0]); __ar++) {                     \
                struct dict_rule_data __data = { NULL,                                                  \
                        (_rulearray)[__ar].position,                                                    \
                        0,                                                                              \
                        (_rulearray)[__ar].min,                                                         \
                        (_rulearray)[__ar].max};                                                        \
                __data.rule_order = RULE_ORDER(__data.rule_position);                                   \
                CHECK_FCT(  fd_dict_search(                                                             \
                        fd_g_config->cnf_dict,                                                          \
                        DICT_AVP,                                                                       \
                        AVP_BY_NAME_AND_VENDOR,                                                         \
                        &(_rulearray)[__ar].avp_vendor_plus_name,                                       \
                        &__data.rule_avp, 0 ) );                                                        \
                if ( !__data.rule_avp ) {                                                               \
                        TRACE_DEBUG(INFO, "AVP Not found: '%s'", (_rulearray)[__ar].avp_vendor_plus_name.avp_name);             \
                        return ENOENT;                                                                  \
                }                                                                                       \
                {                                                                                       \
                         int _ret = fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &(__data), (_parent), NULL ); \
                         if ( _ret != 0 && _ret != EEXIST )      {                                      \
                                TRACE_DEBUG(INFO, "Error on rule with AVP '%s'",                        \
                                            (_rulearray)[__ar].avp_vendor_plus_name.avp_name);          \
                                return EINVAL;                                                          \
                         }                                                                              \
                }                                                                                       \
        }                                                                                               \
}

#define CHECK_vendor_new( _data ) { \
        struct dict_object * vendor_found; \
        if (fd_dict_search(fd_g_config->cnf_dict,DICT_VENDOR,VENDOR_BY_ID,&_data.vendor_id,&vendor_found,ENOENT) == ENOENT) { \
                CHECK_FCT(fd_dict_new(fd_g_config->cnf_dict, DICT_VENDOR, &_data, NULL, NULL)); \
        } \
}

#define enumval_def_u32( _val_, _str_ )		\
    { _str_, 		{ .u32 = _val_ }}

#define enumval_def_os( _len_, _val_, _str_ )				\
    { _str_, 		{ .os = { .data = (unsigned char *)_val_, .len = _len_ }}}


static int dict_rfc7683_avps_load_defs(char * conffile)
{
   TRACE_ENTRY("%p", conffile);

   /* AVP section */
   {
		struct dict_object * Address_type;
		struct dict_object * UTF8String_type;
		struct dict_object * DiameterIdentity_type;
		struct dict_object * DiameterURI_type;
		struct dict_object * Time_type;
		struct dict_object * IPFilterRule_type;

		CHECK_dict_search( DICT_TYPE, TYPE_BY_NAME, "Address", &Address_type);
		CHECK_dict_search( DICT_TYPE, TYPE_BY_NAME, "UTF8String", &UTF8String_type);
		CHECK_dict_search( DICT_TYPE, TYPE_BY_NAME, "DiameterIdentity", &DiameterIdentity_type);
		CHECK_dict_search( DICT_TYPE, TYPE_BY_NAME, "DiameterURI", &DiameterURI_type);
		CHECK_dict_search( DICT_TYPE, TYPE_BY_NAME, "Time", &Time_type);
		CHECK_dict_search( DICT_TYPE, TYPE_BY_NAME, "IPFilterRule", &IPFilterRule_type);
		/* OC-Feature-Vector */
		{
			struct dict_avp_data data = {
				622,	/* Code */
				0,	/* Vendor */
				"OC-Feature-Vector",	/* Name */
				AVP_FLAG_VENDOR,	/* Fixed flags */
				AVP_FLAG_VENDOR,	/* Fixed flag values */
				AVP_TYPE_UNSIGNED64	/* base type of data */
			};
			CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
		};
		/* OC-Sequence-Number */
		{
			struct dict_avp_data data = {
				624,	/* Code */
				0,	/* Vendor */
				"OC-Sequence-Number",	/* Name */
				AVP_FLAG_VENDOR,	/* Fixed flags */
				AVP_FLAG_VENDOR,	/* Fixed flag values */
				AVP_TYPE_UNSIGNED64	/* base type of data */
			};
			CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
		};
		/* OC-Validity-Duration */
		{
			struct dict_avp_data data = {
				625,	/* Code */
				0,	/* Vendor */
				"OC-Validity-Duration",	/* Name */
				AVP_FLAG_VENDOR,	/* Fixed flags */
				AVP_FLAG_VENDOR,	/* Fixed flag values */
				AVP_TYPE_UNSIGNED32	/* base type of data */
			};
			CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
		};
		/* OC-Report-Type */
		{
			struct dict_avp_data data = {
				626,	/* Code */
				0,	/* Vendor */
				"OC-Report-Type",	/* Name */
				AVP_FLAG_VENDOR,	/* Fixed flags */
				AVP_FLAG_VENDOR,	/* Fixed flag values */
				AVP_TYPE_INTEGER32	/* base type of data */
			};
			struct dict_object        *type;
			struct dict_type_data     tdata = { AVP_TYPE_INTEGER32, "Enumerated(OC-Report-Type)", NULL, NULL, NULL };
			struct dict_enumval_data        t_1 = { "HOST_REPORT", { .i32=0 }};
			struct dict_enumval_data        t_2 = { "REALM_REPORT", { .i32=1 }};
			struct dict_enumval_data        t_3 = { "Texas", { .i32=75034 }};
			struct dict_enumval_data        t_4 = { "CA", { .i32=95134 }};
			/* Create the Enumerated type, and then the AVP */
			CHECK_dict_new( DICT_TYPE, &tdata, NULL, &type);
			CHECK_dict_new( DICT_ENUMVAL, &t_1, type, NULL);
			CHECK_dict_new( DICT_ENUMVAL, &t_2, type, NULL);
			CHECK_dict_new( DICT_ENUMVAL, &t_3, type, NULL);
			CHECK_dict_new( DICT_ENUMVAL, &t_4, type, NULL);
			CHECK_dict_new( DICT_AVP, &data, type, NULL);
		};
		/* OC-Reduction-Percentage */
		{
			struct dict_avp_data data = {
				627,	/* Code */
				0,	/* Vendor */
				"OC-Reduction-Percentage",	/* Name */
				AVP_FLAG_VENDOR,	/* Fixed flags */
				AVP_FLAG_VENDOR,	/* Fixed flag values */
				AVP_TYPE_UNSIGNED32	/* base type of data */
			};
			CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
		};
		/* OC-Supported-Features */
		{
			/* Grouped */
			struct dict_object * avp;
			struct dict_avp_data data = {
				621,	/* Code */
				0,	/* Vendor */
				"OC-Supported-Features",	/* Name */
				AVP_FLAG_VENDOR,	/* Fixed flags */
				AVP_FLAG_VENDOR,	/* Fixed flag values */
				AVP_TYPE_GROUPED	/* base type of data */
			};
			CHECK_dict_new( DICT_AVP, &data , NULL, &avp);
		}
		/* OC-OLR */
		{
			/* Grouped */
			struct dict_object * avp;
			struct dict_avp_data data = {
				623,	/* Code */
				0,	/* Vendor */
				"OC-OLR",	/* Name */
				AVP_FLAG_VENDOR,	/* Fixed flags */
				AVP_FLAG_VENDOR,	/* Fixed flag values */
				AVP_TYPE_GROUPED	/* base type of data */
			};
			CHECK_dict_new( DICT_AVP, &data , NULL, &avp);
		}

	
   }

   /* Commands section */
   {

   }

   return 0;
}

static int dict_rfc7683_avps_load_rules(char * conffile)
{
   /* Grouped AVP section */
   {
	  /* OC-Supported-Features */
	  {
		/* Grouped */
		struct dict_object * avp;
		struct dict_avp_request avp_vendor_plus_name =  { .avp_vendor = 0, .avp_name = "OC-Supported-Features"};
		CHECK_dict_search(DICT_AVP,  AVP_BY_NAME_AND_VENDOR, &avp_vendor_plus_name, &avp)
		struct local_rules_definition rules[] =
		{
			{ { .avp_vendor = 0, .avp_name = "OC-Feature-Vector"}, RULE_OPTIONAL, -1, -1 }
		};
		PARSE_loc_rules( rules, avp );
	  }
	  /* OC-OLR */
	  {
		/* Grouped */
		struct dict_object * avp;
		struct dict_avp_request avp_vendor_plus_name =  { .avp_vendor = 0, .avp_name = "OC-OLR"};
		CHECK_dict_search(DICT_AVP,  AVP_BY_NAME_AND_VENDOR, &avp_vendor_plus_name, &avp)
		struct local_rules_definition rules[] =
		{
			{ { .avp_vendor = 0, .avp_name = "OC-Sequence-Number"}, RULE_FIXED_HEAD, -1, -1 },
			{ { .avp_vendor = 0, .avp_name = "OC-Report-Type"}, RULE_FIXED_HEAD, -1, -1 },
			{ { .avp_vendor = 0, .avp_name = "OC-Reduction-Percentage"}, RULE_OPTIONAL, -1, -1 },
			{ { .avp_vendor = 0, .avp_name = "OC-Validity-Duration"}, RULE_OPTIONAL, -1, -1 }
		};
		PARSE_loc_rules( rules, avp );
	  }

   }	

   /* Commands section */
   {

   }

   LOG_D( "Extension 'Dictionary definitions for rfc7683_avps (None)' initialized");
   return 0;
}

int dict_entry(char * conffile)
{
	dict_rfc7683_avps_load_defs(conffile);
	return dict_rfc7683_avps_load_rules(conffile);
}

const char* dict_rfc7683_avps_proto_ver(char * conffile) {
	return rfc7683_avps_proto_ver;
}

const double dict_rfc7683_avps_gen_ts(char * conffile) {
	return rfc7683_avps_gen_date;
}

EXTENSION_ENTRY2("dict_rfc7683_avps", dict_rfc7683_avps_load_defs, dict_rfc7683_avps_load_rules);



