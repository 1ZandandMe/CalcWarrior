#include <stdio.h>
#include <string.h>
void func() {
    char buf[8];
    int flag = 0;
    strcpy(buf,"AAAAAAAAAAAAAAAAA");
    if (flag != 0) {
        printf("flag changed\n");
    }
}
int main(){
    // int arr[5] = {10, 20, 30, 40, 50};
    // int *p = arr;
    // printf("%d\n", *(p + 2));
    // printf("%d\n", arr[2]);
    int a = 10;
    int *p = &a;
    *p = 20;
    printf("%d\n", a);
    func();
}