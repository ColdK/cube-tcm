#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <dlfcn.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>


#include "data_type.h"
#include "alloc.h"
#include "memfunc.h"
#include "basefunc.h"
#include "struct_deal.h"
#include "crypto_func.h"
#include "channel.h"
#include "memdb.h"
#include "message.h"
#include "connector.h"
#include "ex_module.h"
#include "tcm_constants.h"
#include "app_struct.h"
#include "pik_struct.h"
#include "sm3.h"
#include "sm4.h"
#include "tspi.h"

int main(int argc,char **argv)
{

    int ret;
    TSM_HCONTEXT hContext;
    TSM_HTCM hTCM;

    int PcrLength;
    BYTE * PcrValue;

	
    ret=Tspi_Context_Create(&hContext);     
    if(ret!=TSM_SUCCESS)
    {
	printf("Tspi_Context_Create Error!\n");
	return ret;
    }

    printf("hContext is %x!\n",hContext);

    ret= Tspi_Context_GetTcmObject(hContext,&hTCM);
    if(ret!=TSM_SUCCESS)
    {
	printf("Tspi_Context_GetTcmObject Error!\n");
	return ret;
    }
    printf("hTCM is %x!\n",hTCM);

    BYTE * RandomData;

    ret= Tspi_TCM_GetRandom(hTCM,16,&RandomData);
    if(ret!=TSM_SUCCESS)
    {
	printf("Tspi_Context_GetRandom Error!\n");
	return ret;
    }

    printf("Random Data is :");
    for(int i=0;i<16;i++)
    	printf("%2.2x ",RandomData[i]);
    printf("\n");

    ret=Tspi_TCM_PcrRead(hTCM,0,&PcrLength,&PcrValue);
    if(ret!=TSM_SUCCESS)
    {
	printf("Tspi_TCM_PcrRead Error!\n");
	return ret;
    }
    for(int i=0;i<32;i++)
    	printf("%2.2x ",PcrValue[i]);
    printf("\n");

    char * ExtendValue="AAAAAAAAAAAAAAAA";

    ret=Tspi_TCM_PcrExtend(hTCM,0,Strlen(ExtendValue),ExtendValue,NULL,&PcrLength,&PcrValue);
    if(ret!=TSM_SUCCESS)
    {
	printf("Tspi_TCM_PcrRead Error!\n");
	return ret;
    }
    for(int i=0;i<32;i++)
    	printf("%2.2x ",PcrValue[i]);
    printf("\n");
    return ret;
}

