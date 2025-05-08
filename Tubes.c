#include<stdio.h>

int main(){
    int n;

    printf("Pilih menu (1. Admin / 2. User) : "); scanf("%d", &n) ;
    switch (n)
    {
    case 1:
        printf("Menu Admin :");
        break;
    case 2:
        printf("Menu User : ");
        break;
    default:
        break;
    }
}