int galoi_log []= {1,2,4,8,16,32,64,128,29,58,116,232,205,135,19,38,76,152,45,90,180,117,234,201,143,3,6,12,24,48,96,192,157,39,78,156,37,74,148,53,106,212,181,119,238,193,159,35,70,140,5,10,20,40,80,160,93,186,105,210,185,111,222,161,95,190,97,194,153,47,94,188,101,202,137,15,30,60,120,240,253,231,211,187,107,214,177,127,254,225,223,163,91,182,113,226,217,175,67,134,17,34,68,136,13,26,52,104,208,189,103,206,129,31,62,124,248,237,199,147,59,118,236,197,151,51,102,204,133,23,46,92,184,109,218,169,79,158,33,66,132,21,42,84,168,77,154,41,82,164,85,170,73,146,57,114,228,213,183,115,230,209,191,99,198,145,63,126,252,229,215,179,123,246,241,255,227,219,171,75,150,49,98,196,149,55,110,220,165,87,174,65,130,25,50,100,200,141,7,14,28,56,112,224,221,167,83,166,81,162,89,178,121,242,249,239,195,155,43,86,172,69,138,9,18,36,72,144,61,122,244,245,247,243,251,235,203,139,11,22,44,88,176,125,250,233,207,131,27,54,108,216,173,71,142,1},
galoi_ant[] = {0,1,25,2,50,26,198,3,223,51,238,27,104,199,75,4,100,224,14,52,141,239,129,28,193,105,248,200,8,76,113,5,138,101,47,225,36,15,33,53,147,142,218,240,18,130,69,29,181,194,125,106,39,249,185,201,154,9,120,77,228,114,166,6,191,139,98,102,221,48,253,226,152,37,179,16,145,34,136,54,208,148,206,143,150,219,189,241,210,19,92,131,56,70,64,30,66,182,163,195,72,126,110,107,58,40,84,250,133,186,61,202,94,155,159,10,21,121,43,78,212,229,172,115,243,167,87,7,112,192,247,140,128,99,13,103,74,222,237,49,197,254,24,227,165,153,119,38,184,180,124,17,68,146,217,35,32,137,46,55,63,209,91,149,188,207,205,144,135,151,178,220,252,190,97,242,86,211,171,20,42,93,158,132,60,57,83,71,109,65,162,31,45,67,216,183,123,164,118,196,23,73,236,127,12,111,246,108,161,59,82,41,157,85,170,251,96,134,177,187,204,62,90,203,89,95,176,156,169,160,81,11,245,22,235,122,117,44,215,79,174,213,233,230,231,173,232,116,214,244,234,168,80,88,175};
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int somaGaloi(int a,int b){
	if (a==-1) return b;
	if (b==-1) return a;
	if (a==b) return -1;
	int xor = galoi_log[a]^galoi_log[b];
	return galoi_ant[xor-1];
}
int multGaloi(int a,int b){
	if (a==-1 || b==-1) return -1;
	int ans = a+b;
	if (ans >= 255) ans=ans%255;
	return ans;
}
int bin2dec(char *bin){
	int length = strlen(bin) -1,i,dec =0,p;
	for(i=0,p=1;i<=length;i++,p*=2)
		dec += (bin[length-i]-'0')*p;
	return dec;
}
int aloca =0;
void *alc(int size){
	if (size<=0) return 0;
	aloca++;
	return calloc(size,1);
}
void libe(void *p){
	if(p==0)return;
	free(p);
	aloca--;
}
typedef struct {
 	int *v,size;
 }Vetor;
 void prt(Vetor a){
 	int i;
 	printf("{");
 	if(a.size>0)printf("%d",a.v[0]);
 	for(i=1;i<a.size;i++)
 		printf(", %d",a.v[i]);
 	printf("}\n");
 }
 Vetor V_new_v(int *v,int size){
 	Vetor ans ={0,size};
 	int i;
 	ans.v =(int *) alc(size*sizeof(int));
 	for(i=0;i<size;i++)
 	ans.v[i] = v[i];
 	return ans;
 }
 Vetor V_new_cte (int v,int size){
 	Vetor ans ={0,size};
 	int i;
 	ans.v =(int *) alc(size*sizeof(int));
 	for(i=0;i<size;i++)
 		ans.v[i] = v;
 	return ans;
 }
 
 Vetor V_copy(Vetor a,int begin,int end,int dest){
 	end = end<=0 && end+a.size >=0?end+a.size:end>a.size?a.size:end;
 	begin =  begin>=0 && begin<a.size&&begin<end?begin:0;
 	Vetor ans = V_new_v(a.v+begin,end-begin);
 	if(dest)libe(a.v);
 	return ans;
 }
  Vetor V_cat(Vetor a,Vetor b,int dest_a,int dest_b){
 	Vetor ans = V_new_cte(-1, a.size+b.size);
 	int i;
 	for(i=0;i<a.size;i++) ans.v[i]=a.v[i];
 	for(i=0;i<b.size;i++) ans.v[i+a.size]=b.v[i];
 	if(dest_a)libe(a.v);
 	if(dest_b)libe(b.v);
 	return ans;
 }
 
 Vetor multPolyGaloi(Vetor a,Vetor b,int dest_a,int dest_b){
 	Vetor ans = V_new_cte(-1, a.size+b.size);
 	int i,j;
 	for(i=0;i<a.size;i++)
 		for(j=0;j<b.size;j++){
 			if(ans.v[i+j]==-1){
 				ans.v[i+j] = multGaloi(a.v[i],b.v[j]);
 			}else {
 				ans.v[i+j] = somaGaloi(ans.v[i+j],multGaloi(a.v[i],b.v[j]));
 			}
 		}
 	for(i=0;i<ans.size;i++) 
 		if(ans.v[ans.size-i-1]!=-1)break;
 	if(dest_a)libe(a.v);
 	if(dest_b)libe(b.v);
 	return V_copy(ans, 0, -i, 1);
 }
 	
Vetor geraPoly(int ncode){	
	if(ncode<7){printf("o numero de codigo corretor deve ser maior ou igual a 7");exit(-1);}
	int i, init[] ={21, 102, 238, 149, 146, 229, 87, 0};
	Vetor ans = V_new_v(init,8);
	
	Vetor m = V_new_cte(0, 2);
	for(i=7;i<ncode;i++){
		m.v[0] = i;
		ans = multPolyGaloi(ans, m, 1, 0);
	}
	libe(m.v);
	return ans;
}
int * divPolyGaloi(Vetor num, Vetor den,int destroi_num,int destroi_den){
	num = V_copy(num, 0,num.size , destroi_num);
	den = V_copy(den, 0,den.size , destroi_den);
	int i,etapas,ld = den.size;
	int ln = num.size;
	num = V_cat(V_new_cte(-1, ld-1),num,1,1);
	den = V_cat(V_new_cte(-1,num.size - ld),den,1,1);
	Vetor div={0};
	for (etapas=1;etapas<=ln;etapas++){
		div = V_copy(den, 0, den.size, 0);
		for(i=0;i<div.size;i++) div.v[i] = multGaloi(div.v[i],num.v[num.size-1]);
		for(i=0;i<num.size;i++)num.v[i]=somaGaloi(num.v[i],div.v[i]);
		num = V_copy(num, 0, -1, 1);
		den = V_copy(den, 1, den.size, 1);
		libe(div.v);
	}

	for(i=0;i<num.size && num.v[num.size - i]==-1;i++);
	div = V_copy(num, 0, -i, 0);
	int j;
	for(j=0;j<div.size;j++)div.v[j]= galoi_log[num.v[num.size-1-i-j]];
	libe(num.v);
	libe(den.v);
	return div.v;
}
	#define _()\
	printf("\n %d alocados\n",aloca);
	
int main(){
	int p1[]={100, 122, 100, 122, 100, 122, 6, 98, 145, 187, 155, 161, 78, 238, 92, 5},p2[]=
{45, 32, 94, 64, 70, 118, 61, 46, 67, 251, 0};
	Vetor  u = {divPolyGaloi( V_new_v(p1, 16), V_new_v(p2, 11), 1, 1),10};
	prt(u);
	libe(u.v);
	

	_()
	return 0;
}
