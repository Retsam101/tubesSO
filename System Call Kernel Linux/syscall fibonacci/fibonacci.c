//Putra Abi (14115011)
//Irfan Gerard (14115016)
//Ari Bambang Kurniawan (14115062)
#include <linux/kernel.h>

asmlinkage long sys_fibonacci(int n){
	int a=0, b=1, c, i;
if(n == 0)
return a;

for(i=2;i<=n;i++){
	c=a+b;
	a=b;
	b=c;
}
return b;
}
