#include "tm.h"
#include <stdio.h>
#include <math.h>


uint32_t tempo_medio(uint32_t acesso_l1, uint32_t t_miss_l1, uint32_t acesso_l2,  
	uint32_t t_miss_l2, uint32_t acesso_l3, uint32_t t_miss_l3, uint32_t acesso_mem){

	double tm;
	double t_miss_l1_2 = t_miss_l1;
	double t_miss_l2_2 = t_miss_l2;
	double t_miss_l3_2 = t_miss_l3;
	if(acesso_l1 == 0){
		return acesso_mem;
	}
		else if(acesso_mem == 0){
			return 0;

		}
	if(acesso_l1 > 0){
		tm=(double)acesso_l1+(t_miss_l1_2/100000)*acesso_mem;
	}
	if(acesso_l2>0){
		
		tm=((double)acesso_l2+(t_miss_l2_2/100000)*acesso_mem)*(t_miss_l1_2/100000)+acesso_l1;
	}
	if(acesso_l3>0){
		
		tm=(((double)acesso_l3+(t_miss_l3_2/100000)*acesso_mem)*(t_miss_l2_2/100000)+acesso_l2)*(t_miss_l1_2/100000)+acesso_l1;	
	}
		

	tm=ceil(tm);
		

return tm;
	
}
