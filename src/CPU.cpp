#include <string.h>
#include <unistd.h>
int main(int argc, char** argv)
{
	unsigned char R[3][2];
	unsigned char Test[2] = {2,3};
	while(1)
	{
		memcpy(&R[0][0], &Test[0], sizeof(Test));//CPU
		memcpy(&R[1][0], &Test[0], sizeof(Test));
		memcpy(&R[2][0], &Test[0], sizeof(Test));
		//for(int i=0;i<38600000;i++);//CPU_sleep10
		//sleep(1);
	}
	return 1;
}
