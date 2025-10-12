#include <stdio.h>

#define FALSE 0
#define LIMIT_FOL 5
#define BASE_SYS 8


int ten_in_oct(long int n){
	if (n == 0)
		return 0;
	ten_in_oct(n / BASE_SYS);
	printf("%li", n % BASE_SYS);
}

int main(){
        double num;
	long int num_cor;
        short correct;
        short folus = 0;

        //Ввод данных и их проверка
	 while (folus < LIMIT_FOL){
                printf("Введите натуральное число: ");
                short correct = scanf("%lf", &num);

                if ((correct == FALSE) || (num <= 0) || (num != (long int) num)){
                        folus++;
                        printf("Некорректный ввод данных\n\n");
                        scanf("%*[^\n]");
                        continue;
		}
		else {
			num_cor = num;
		}
                break;
	}

	//Перевод и вывод
	ten_in_oct(num_cor);
	printf("\n");
	return 0;
}
