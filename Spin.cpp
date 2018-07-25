#include "head.h"

Spin::Spin(){
	int i,j;
	for(i=0;i<3;i++){
		this->cor[i]=0;
		this->ZC[i]=0;
		this->IP[i]=0;
		this->vector[i][0]=0;
		this->vector[i][1]=0;
		this->vector[i][2]=1;
	}
}


