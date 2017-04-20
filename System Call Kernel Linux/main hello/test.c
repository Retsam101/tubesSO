#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main(){
long int test = syscall(332);
printf("Putra Abi (14115011)\n");
printf("Irfan Gerard (14115016)\n");
printf("Ari Bambang (14115062)\n");
printf("sys_hello output : %ld\n", test);
return 0;
}
