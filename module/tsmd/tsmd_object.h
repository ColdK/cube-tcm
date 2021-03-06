#ifndef TSMD_OBJECT_H
#define TSMD_OBJECT_H
enum tsmd_key_object_state
{
	TSMD_KEY_STATE_NULL,
	TSMD_KEY_STATE_GETBLOB,
	TSMD_KEY_STATE_LOAD,
	TSMD_KEY_STATE_UNWRAP,
	TSMD_KEY_STATE_AUTH,
	TSMD_KEY_STATE_ERROR
};

struct tsmd_object_tcm
{
	UINT32 tcm_state;
	UINT32 tcm_flags;
	TSM_HTCM tcmhandle;
	TSM_HPOLICY policy;
	
}__attribute__((packed));

struct tsmd_object_key
{
	UINT32 key_state;
	UINT32 keyflags;
	TCM_KEY_HANDLE keyhandle;
	TCM_AUTHHANDLE authhandle;
	TSM_HPOLICY policy;
	
	TCM_PUBKEY * pubKey;	
}__attribute__((packed));

enum tsmd_policy_object_state
{
	TSMD_POLICY_STATE_NULL,
	TSMD_POLICY_STATE_GETOBJECT,
	TSMD_POLICY_STATE_LOAD,
};
struct tsmd_object_policy
{
	UINT32 policy_state;
	UINT32 policyflags;
	TSM_HANDLE objecthandle;
	TCM_AUTHHANDLE authhandle;
	BYTE AuthData[DIGEST_SIZE];
}__attribute__((packed));
#endif
