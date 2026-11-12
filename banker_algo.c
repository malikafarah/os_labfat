#include <stdio.h>
#include <stdbool.h>

int main(){
    int n,m;
    scanf("%d %d", &n, &m);

    int allocation[n][m], max[n][m], need[n][m];
    int work[m], available[m];
    bool finish[n];
    int safe[n];

    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            scanf("%d", &allocation[i][j]);
        }
    }

    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            scanf("%d", &max[i][j]);
        }
    }

    for(int i = 0; i<n; i++){
        finish[i] = false;
        for(int j = 0; j<n; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int count = 0;
    while(count < n){
        bool found = false;

        for(int i = 0; i<n; i++){
            if(!finish[i]){
                bool can_allocate = true;
                for(int j = 0; j<m; j++){
                    if(work[j] < need[i][j]){
                        can_allocate = false;
                        break;
                    }
                }

                for(int j = 0; j<n; j++){
                    if(work[j] < need[i][j]){
                        can_allocate = false;
                        break;
                    }
                }

                if(can_allocate){
                    for(int j= 0; j<m; j++){
                        work[j] += allocation[i][j];
                    }
                    
                    safe[count++];
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found){
            printf("\nSystem is in an UNSAFE state!");
            return 0;
        }
    }

    printf("\nSystem is in a SAFE state. \nSafe Sequence: ");
    for(int i = 0; i< n; i++){
        printf("P%d%s", safe[i], (i < n - 1) ? " -> " : "\n");
    }

    return 0;
}