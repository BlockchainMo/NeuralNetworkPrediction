#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

	float training_data[30][16] =
	{
	{0,0,1,1,1,0,1,0,1,0,1,0,1,0,0,0},{0,0,0,1,1,1,0,1,0,1,0,1,0,1,0,0},{1,0,0,0,1,1,1,0,1,0,1,0,1,0,1,0},{1,1,0,0,0,1,1,1,0,1,0,1,0,1,0,1},{1,1,1,0,0,0,1,1,1,0,1,0,1,0,1,0},
	{0,1,1,1,0,0,0,1,1,1,0,1,0,1,0,1},{0,0,1,1,1,0,0,0,1,1,1,0,1,0,1,0},{0,0,0,1,1,1,0,0,0,1,1,1,0,1,0,1},{1,0,0,0,1,1,1,0,0,0,1,1,1,0,1,0},{1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,1},
	{1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0},{0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1},{1,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1},{0,1,0,1,1,1,0,0,0,1,1,1,0,0,0,1},{1,0,1,0,1,1,1,0,0,0,1,1,1,0,0,0},
	{1,1,0,1,0,1,1,1,0,0,0,1,1,1,0,0},{1,1,1,0,1,0,1,1,1,0,0,0,1,1,1,0},{1,1,1,1,0,1,0,1,1,1,0,0,0,1,1,1},{1,1,1,1,1,0,1,0,1,1,1,0,0,0,1,1},{1,1,1,1,1,1,0,1,0,1,1,1,0,0,0,1},
	{0,1,1,1,1,1,1,0,1,0,1,1,1,0,0,0},{1,0,1,1,1,1,1,1,0,1,0,1,1,1,0,0},{0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,0},{1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1},{1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1},
	{0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1},{0,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0},{1,0,0,1,1,0,1,0,1,1,1,1,1,1,0,1},{0,1,0,0,1,1,0,1,0,1,1,1,1,1,1,0},{0,0,1,0,0,1,1,0,1,0,1,1,1,1,1,1}
	};
	
float w1_[16];
float w2_[16];
float w3_[3];

float y1_;
float y2_;
float z_;

float learn_rate = 0.5;

int changed = 1;
int pass_count = 0;

int flag[30] = {0};

void initw(int count, float w[])
{	
	float temp;
	
	for(int i=0;i<count;i++)
	{
		//w[i]=(float)rand()/RAND_MAX;
		temp = rand() % 199 - 99;
		temp = temp/100;
		w[i] = temp; 
	}
}

float cal_y1(int count)
{
	float sum = 0;
	
	sum += (-1*w1_[0]);
	for(int i=1;i<16;i++)
	{
		sum = sum + training_data[count][i-1]*w1_[i];
		//printf("training_data[%d][%d] = %f ",count,i,training_data[count][i]);
		//printf("w1_[%d] = %f ",i,w1_[i]);
		//printf("sum = %f\n",sum);
	}
	
	sum = exp(sum*(-1))+1;
	sum = 1/sum;
	
	return sum;
}

float cal_y2(int count)
{
	float sum = 0;
	
	sum += (-1*w2_[0]);
	for(int i=1;i<16;i++)
	{
		sum = sum + training_data[count][i-1]*w2_[i];
		//printf("training_data[%d][%d] = %f ",count,i,training_data[count][i]);
		//printf("w2_[%d] = %f ",i,w2_[i]);
		//printf("sum = %f\n",sum);
	}
	
	sum = exp(sum*(-1))+1;
	sum = 1/sum;
	
	return sum;
}

float cal_z(void)
{
	float sum = 0;
	sum += -1*w3_[0];
	sum += y1_*w3_[1];
	sum += y2_*w3_[2];
	
	//printf("w3_[0] = %f ",w3_[0]);
	//printf("w3_[1] = %f y1_ = %f",w3_[1],y1_);
	//printf("w3_[2] = %f y2_ = %f\n",w3_[2],y2_);
	
	sum = exp(sum*(-1))+1;
	
	sum = 1/sum;
	//printf("sum => %f\n",sum);
	
	return sum;
}

void renew(int count)
{
	float s1,s2,s3;
	
	s3 = (training_data[count][15] - z_) * z_ * (1- z_);
	s1 = y1_ * (1-y1_) * s3 * w3_[1];
	s2 = y2_ * (1-y2_) * s3 * w3_[2];
	
	w1_[0] = w1_[0]+learn_rate*s1*(-1);
	w2_[0] = w2_[0]+learn_rate*s2*(-1);
	
	for(int i=1;i<16;i++)
	{
		w1_[i] = w1_[i]+learn_rate*s1*training_data[count][i-1];
		w2_[i] = w2_[i]+learn_rate*s2*training_data[count][i-1]; 
	}
		w3_[0] = w3_[0]+learn_rate*s3*(-1);
		w3_[1] = w3_[1]+learn_rate*s3*y1_;
		w3_[2] = w3_[2]+learn_rate*s3*y2_;
}

void forward(int n)
{
		y1_ = cal_y1(n);
		y2_ = cal_y2(n);
		z_ = cal_z();
		
		if(z_ >= 0.5)
		{
			if(training_data[n][15] == 1.0)
			{
				flag[n] = 1;
				pass_count += 1;
			}
			else //training_data[i][15] == 0.0
			{
				renew(n);
				pass_count = 0;
			}
		}
		else //z_ < 0.5
		{
			if(training_data[n][15] == 0.0)
			{
				flag[n] = 1;
				pass_count += 1; 
			}
			else //training_data[i][15] == 1.0
			{
				renew(n);
				pass_count = 0; 
			}	
		}
}

void UpDown(float proof[])
{
	float y11 = 0;
	
	y11 += (-1*w1_[0]);
	for(int i=1;i<16;i++)
	{
		y11 = y11 + proof[i-1]*w1_[i];
	}
	y11 = exp(y11*(-1))+1;
	y11 = 1/y11;
	
	float y22 = 0;
	
	y22 += (-1*w2_[0]);
	for(int i=1;i<16;i++)
	{
		y22 = y22 + proof[i-1]*w2_[i];
	}
	
	y22 = exp(y22*(-1))+1;
	y22 = 1/y22;
	
	float zz = 0;
	zz += -1*w3_[0];
	zz += y11*w3_[1];
	zz += y22*w3_[2];
	
	zz = exp(zz*(-1))+1;
	
	zz = 1/zz;
	
	printf("zz %f\n",zz);
	if(zz >= 0.5) printf("1,UP\n");
	else printf("0,DOWN\n"); 
}

int main()
{	
	srand(time(NULL));
	
	float proof[15] = {0};
	
	initw(16,w1_);
	initw(16,w2_);
	initw(3,w3_);
	
	printf(" w1_[]: ");
	for(int i=0;i<16;i++)
		printf("%f ",w1_[i]);
	printf("%\n");
	
	printf(" w2_[]: ");
	for(int i=0;i<16;i++)
		printf("%f ",w2_[i]);
	printf("%\n");
	
	printf(" w3_[]: ");
	for(int i=0;i<3;i++)
		printf("%f ",w3_[i]);
	printf("%\n");
	printf("%\n");

	changed = 1;
	
	int k=0;
		
	while(1)
	{		 
		forward(k%30);
		k+=1;
		if(pass_count == 30)
			break;
	}
	
	
	printf(" w1_[]: ");
	for(int i=0;i<16;i++)
		printf("%f ",w1_[i]);
	printf("%\n");
	
	printf(" w2_[]: ");
	for(int i=0;i<16;i++)
		printf("%f ",w2_[i]);
	printf("%\n");
	
	printf(" w3_[]: ");
	for(int i=0;i<3;i++)
		printf("%f ",w3_[i]);
	printf("%\n");
	printf("%\n");
	
	for(int i=0;i<15;i++)
		scanf("%f", &proof[i]);
	
	UpDown(proof);
	
	for(int l=0;l<30;l++)	
		printf("flag[%d] = %d\n",l,flag[l]);

	return 0;
}




