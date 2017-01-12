#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
int count = 0;

typedef struct {
    float x;
    float y;
    int index;
} point;

point p[250000];

typedef struct {
    int a;
    int b;
} pair;

pair q[200];

int compare (const void *p1, const void *p2) {
    point *a = (point *)p1;
    point *b = (point *)p2;
    if (a->x == b->x) {
        return (a->y - b->y);
    } else {
        return (a->x - b->x);
    }
}

int compare_q (const void *p1, const void *p2) {
    pair *x = (pair *)p1;
    pair *y = (pair *)p2;
    if (x->a == y->a) {
        return (x->b - y->b);
    } else {
        return (x->a - y->a);
    }
}


float find_min (float a, float b) {
    if (a <= b) {
        return a;
    }
    return b;
}

float find_distance (point *p, int i, int j) {
    return sqrt((p[i].x - p[j].x)*(p[i].x - p[j].x) + (p[i].y - p[j].y)*(p[i].y - p[j].y));
}

float closest_pair (point *p, int start, int end) {
    int i, j;
    if (end - start < 10) {
        float d = FLT_MAX;
        for (i = start; i <= end; i++) {
            for (j = start; j <= end; j++) {
                if (i < j) {
                    d = find_min(d, find_distance (p, i, j));
                }
            }
        }
        return d;
    }
    else {
        int m = (start + end) / 2;
        int new_start, new_end;
        float d1 = closest_pair (p, start, m);
        float d2 = closest_pair (p, m + 1, end);
        float d = find_min (d1, d2);
        for (new_start = start; p[new_start].x < p[m].x - d; new_start++);
        for (new_end = end; p[new_end].x > p[m].x + d ; new_end--);
        for (i = new_start; i <= m; i++) {
            for (j = m + 1; j <= new_end; j++) {
                d = find_min(d, find_distance (p, i, j));
            }
        }
        return d;
    }
}

void find_pair (point *p, pair *q, int start, int end, float d) {
    int i, j;
    if (end - start < 10) {
        for (i = start; i <= end; i++) {
            for (j = start; j <= end; j++) {
                if (i < j && d == find_distance (p, i, j)) {
                   q[count].a = p[i].index;
                   q[count].b = p[j].index;
                   count++;
                }
            }
        }
    }
    else {
        int m = (start + end) / 2;
        int new_start, new_end;
        find_pair (p, q, start, m, d);
        find_pair (p, q, m + 1, end, d);
        for (new_start = start; p[new_start].x < p[m].x - d; new_start++);
        for (new_end = end; p[new_end].x > p[m].x + d ; new_end--);
        for (i = new_start; i <= m; i++) {
            for (j = m + 1; j <= new_end; j++) {
                if (d == find_distance (p, i, j)) {
                   q[count].a = p[i].index;
                   q[count].b = p[j].index;
                   count++;
                }
            }
        }
    }
    return;
}

int main(void) {
    int n;
    int i;
    int temp;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%f %f", &(p[i].x), &(p[i].y));
        p[i].index = i + 1;
    }
    qsort(p, n, sizeof(point), compare);
    float d = closest_pair(p, 0, n-1);
    find_pair (p, q, 0, n-1, d);
    for (i = 0; i < count; i++) {
        if (q[i].a > q[i].b) {
            temp = q[i].a;
            q[i].a = q[i].b;
            q[i].b = temp;
        }
    }
    qsort(q, count, sizeof(pair), compare_q);
    printf("%.2f %d\n", d, count);
    for (i = 0; i < count; i++) {
        printf("%d %d\n", q[i].a, q[i].b);
    }
    return 0;
}

