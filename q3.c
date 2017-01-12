#include <stdio.h>
#include <stdlib.h>

int package;
int item_number;

typedef struct {
    double profit;
    double weight;
    double profit_per_weight;
} item;

item t[1000];

double maxprofit = 0;

// sort from big to small
int compare (const void *p1, const void *p2) {
    item *a = (item *)p1;
    item *b = (item *)p2;
    if (b->profit_per_weight > a->profit_per_weight)
        return 1;
    return -1;
}
// level represent current level of node
float count_bound (int level, double profit, double weight) {
    int i;
    for (i = level + 1; i < item_number; i++) {
        if (weight + t[i].weight <= package) {
            weight = weight + t[i].weight;
            profit = profit + t[i].profit;
        } else {
            profit = profit + (package - weight) * t[i].profit_per_weight;
            weight = package;
            break;
        }
    }
    return profit;
}

void branch_and_bound (int level, double profit, double weight, double bound) {
    if (weight > package) {
        return;
    }
    if (level == item_number) {
        return;
    }
    if (profit > maxprofit) {
        maxprofit = profit;
    }
    float left_bound = count_bound(level + 1, profit + t[level + 1].profit, weight + t[level + 1].weight);
    float right_bound = count_bound(level + 1, profit, weight);
    if (left_bound > maxprofit) {
       branch_and_bound (level + 1, profit + t[level + 1].profit, weight + t[level + 1].weight, left_bound);
    }
    if (right_bound > maxprofit) {
        branch_and_bound (level + 1, profit, weight, right_bound);
    }
    return;
}

int main(void) {
    int i;
    scanf("%d %d", &package, &item_number);
    for (i = 0; i < item_number; i++) {
        scanf("%lf %lf", &t[i].profit, &t[i].weight);
        t[i].profit_per_weight = t[i].profit / t[i].weight;
    }
    qsort(t, item_number, sizeof(item), compare);
    double bound = count_bound (-1, 0, 0);
    branch_and_bound (-1, 0, 0, bound);
    printf("%d\n", (int)maxprofit);
    return 0;
}
