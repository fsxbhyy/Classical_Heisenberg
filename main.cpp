#include <iostream>
#include "head.h"
#include <functional>
#include <stdio.h> 
#include <math.h> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */




int main(int argc, char** argv) {
	FILE *fp;
	FILE *fp1;
	FILE *fp2;
	fp=fopen("data.csv","wt");
	fp1=fopen("data1.csv","wt");
	fp2=fopen("data2.csv","wt");
	long long int i; 
    long long int l;
	long long int j,k,i1;
	int k1=0,k2=0,k3=0;
	
	int label;
	double Z0=0;
	
	long long int N=100000000;
	double total[3];
	Spin spgp[NN][NN];


		for(i=0;i<100000000;i++){       //Thermalization
			k1=int(RNG()*NN);
			k2=int(RNG()*NN);
			k3=int(RNG()*3);
			for(j=0;j<3;j++){
				if(k3==0){
					total[j]=spgp[k1][k2].vector[1][j]+spgp[k1][(k2+NN-1)%NN].vector[2][j]+spgp[(k1+1)%NN][k2].vector[1][j]+spgp[(k1+1)%NN][k2].vector[2][j];
				}
				else if(k3==1){
					total[j]=spgp[k1][k2].vector[2][j]+spgp[k1][k2].vector[0][j]+spgp[(k1+NN-1)%NN][k2].vector[0][j]+spgp[k1][(k2+NN-1)%NN].vector[2][j];
				}
				else if(k3==2){
					total[j]=spgp[k1][k2].vector[1][j]+spgp[k1][(k2+1)%NN].vector[0][j]+spgp[k1][(k2+1)%NN].vector[1][j]+spgp[(k1+NN-1)%NN][k2].vector[0][j];
				}
			} 
		//	printf("%f %f %f \n",total[0],total[1],total[2]);
			Update(total,spgp[k1][k2].vector[k3]);
		//	printf("%f %f %f\n",spgp[k1][k2].vector[k3][0],spgp[k1][k2].vector[k3][1],spgp[k1][k2].vector[k3][2]);
		}
		
	
	
	

		for(i=0;i<NN;i++){
			for(j=0;j<NN;j++){
				for(k=0;k<3;k++){
					spgp[i][j].cor[k]=0;
					spgp[i][j].ZC[k]=0;
					spgp[i][j].IP[k]=Inner(spgp[0][0].vector[1], spgp[i][j].vector[k]);
				}			
			}
		}
		
  		
		for(l=0;l<N;l++){     
			k1=int(RNG()*NN);
			k2=int(RNG()*NN);
			k3=int(RNG()*3);
			for(j=0;j<3;j++){
				if(k3==0){
					total[j]=spgp[k1][k2].vector[1][j]+spgp[k1][(k2+NN-1)%NN].vector[2][j]+spgp[(k1+1)%NN][k2].vector[1][j]+spgp[(k1+1)%NN][k2].vector[2][j];
				}
				else if(k3==1){
					total[j]=spgp[k1][k2].vector[2][j]+spgp[k1][k2].vector[0][j]+spgp[(k1+NN-1)%NN][k2].vector[0][j]+spgp[k1][(k2+NN-1)%NN].vector[2][j];
				}
				else if(k3==2){
					total[j]=spgp[k1][k2].vector[1][j]+spgp[k1][(k2+1)%NN].vector[0][j]+spgp[k1][(k2+1)%NN].vector[1][j]+spgp[(k1+NN-1)%NN][k2].vector[0][j];
				}
			} 
		//	printf("%f %f %f \n",total[0],total[1],total[2]);
			Update(total,spgp[k1][k2].vector[k3]);
			Z0++;
			if(k1==0&&k2==0&&k3==1){
				for(i=0;i<NN;i++){
					for(j=0;j<NN;j++){
						for(k=0;k<3;k++){
							spgp[i][j].cor[k]=spgp[i][j].cor[k]+spgp[i][j].IP[k]*(Z0-spgp[i][j].ZC[k]);
							spgp[i][j].ZC[k]=Z0;
							spgp[i][j].IP[k]=Inner(spgp[0][0].vector[1], spgp[i][j].vector[k]);
						}			
					}
				}
			}
			else {
				spgp[k1][k2].cor[k3]=spgp[k1][k2].cor[k3]+spgp[k1][k2].IP[k3]*(Z0-spgp[k1][k2].ZC[k3]);
				spgp[k1][k2].ZC[k3]=Z0;
				spgp[k1][k2].IP[k3]=Inner(spgp[0][0].vector[1], spgp[k1][k2].vector[k3]);
			//	printf("%f\n",spgp[k1][k2].IP[k3]);
			}
		}
		
	
		for(i=0;i<NN;i++){
			for(j=0;j<NN;j++){
				for(k=0;k<3;k++){
					spgp[i][j].cor[k]=fabs(spgp[i][j].cor[k]+spgp[i][j].IP[k]*(Z0-spgp[i][j].ZC[k]));					
					fprintf(fp1,"%f,",spgp[i][j].cor[k]/Z0);
				}			
			}
			fprintf(fp1,"\n");
		}
		fprintf(fp2,"%d,%lf\n",spgp[0][0].cor[2]/Z0);
		fprintf(fp2,"%d,%lf\n",spgp[0][1].cor[0]/Z0);
		fprintf(fp2,"%d,%lf\n",spgp[0][1].cor[1]/Z0);
		fprintf(fp2,"%d,%lf\n",spgp[1][1].cor[1]/Z0);
		fprintf(fp2,"%d,%lf\n",spgp[1][1].cor[2]/Z0);
		fprintf(fp2,"%d,%lf\n",spgp[0][1].cor[2]/Z0);
		fprintf(fp2,"%d,%lf\n",spgp[NN-1][1].cor[1]/Z0);
		fprintf(fp2,"%d,%lf\n",spgp[0][2].cor[0]/Z0);
		fprintf(fp2,"%d,%lf\n",spgp[1][2].cor[1]/Z0);
		fprintf(fp2,"%d,%lf\n",spgp[2][2].cor[1]/Z0);
		fprintf(fp2,"%d,%lf\n",spgp[0][2].cor[1]/Z0);
		fprintf(fp2,"%d,%lf\n",spgp[1][2].cor[2]/Z0);
		fprintf(fp2,"%d,%lf\n",spgp[2][2].cor[2]/Z0);
		fprintf(fp2,"%d,%lf\n",spgp[0][2].cor[2]/Z0);

	
/*	for(i=0;i<NN;i++){ 
		for(j=0;j<NN;j++){
			printf("%f ",spgp[i][j].vector[0]);	
		}
		printf("\n");
	} */
	
	fclose(fp);
	fclose(fp1);
	fclose(fp2);	

return 0;
}
