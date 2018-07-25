#include "head.h"
#include <functional>
#include <stdio.h> 
#include <math.h> 



double Inner(double a[3],double b[3]){
	double k=0;
	int i;
	for(i=0;i<3;i++){
		k=k+a[i]*b[i];
	}
	return k;
}

void Update(double total[3], double a[3]){
	int i=0,j=0;
	double B=0;
	double k1,k2;
	double a1,a2,b1,b2; // cos thita, sin thita, cos phi, sin phi 
	double ncos=0;
	double phi=0;
	double nsin=0;
	
	for(i=0;i<3;i++){
		B=B+total[i]*total[i];
		a[i]=0;
	}
	B=sqrt(B);
	
	for(i=0;i<3;i++){
		total[i]=total[i]/B;
	}
	
	k1=RNG();
	k2=RNG();
	ncos=1-log(1-k1+exp(2*JT*B)*k1)/JT/B;
	phi=2*M_PI*k2;
	nsin=sqrt(1-ncos*ncos);
	double spin0[3]={nsin*cos(phi),nsin*sin(phi),ncos};
//	printf("%f %f %f\n",spin0[0],spin0[1],spin0[2]);
	a1=total[2];
	a2=sqrt(1-a1*a1);
	if(a2==0) {
		for(i=0;i<3;i++){
			a[i]=spin0[i];
		}
	}
	else {
		b1=total[0]/a2;
		b2=total[1]/a2;
		double Rotation[3][3]={{a1*b1,-b2,a2*b1},{a1*b2,b1,a2*b2},{-a2,0,a1}};
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				a[i]=a[i]+Rotation[i][j]*spin0[j];
			}
		}
	//	printf("%f\n",Inner(a,a));
	}
//	printf("%f %f %f %f\n",a1,a2,b1,b2);
//	printf("%f %f %f\n",a[0],a[1],a[2]);

} 
