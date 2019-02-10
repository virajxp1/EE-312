
#include <stdio.h>
#include <stdint.h>

int main(void) {
    int32_t year;
    int32_t month;
    int32_t day;
    int32_t d;

    while (1) {
        scanf("%d", &year);
        scanf("%d", &month);
        scanf("%d", &day);

        if (year == 0 || month == 0 || day == 0) {
            break;
        }

        switch(month) {
        case 4: case 6: case 9: case 11:
            d = 30;
            break;
        case 1: case 3: case 7: case 8: case 10: case 12:
            d = 31;
            break;
        case 2:
            d = (year % 4) == 0;
            break;
        }

        if (day < d) {
            day++;
        } else {
            day = 1;
            if (month < 12) {
                month++;
            } else {
                month = 1;
                year++;
            }
        }

        printf("%d %d %d\n", year, month, day);
    }

    return 0;
}
