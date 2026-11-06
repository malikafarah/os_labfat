#include <stdio.h>
#include <stdbool.h>

int main(){
    int n,m;
    printf("Enter processes and resource type: ");
    scanf("%d %d",&n,&m);
    int alloc[n][m], max[n][m], need[n][m], avail[m];
    int work[m], finish[n], safe[n];

    printf("Enter Allocation matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) scanf("%d",&alloc[i][j]);

    printf("Enter Maximum matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) scanf("%d",&max[i][j]);

    printf("Enter Available resources:\n");
    for(int j=0;j<m;j++) scanf("%d",&avail[j]);

    for(int i =0; i<n; i++){
        finish[i] = false;
        for(int j = 0; j<m; j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int count = 0;
    while(count < n){
        bool found = false;

        for(int i = 0; i<n; i++){
            if(!finish[i]){
                bool can_allocate = true;

                for(int j = 0; j<m; j++){
                    if(need[i][j] > work[j]){
                        can_allocate = false;
                        break;
                    }
                }

                if(can_allocate){
                    for(int j = 0; j <m; j++){
                        work[j] += alloc[i][j];
                    }
                    safe[count++] = i;
                    finish[i]= true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("\nSystem is in an UNSAFE state! (Deadlock could occur)\n");
            return 0;
        }
    }

    printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d%s", safe_sequence[i], (i < n - 1) ? " -> " : "\n");
    }

    return 0;
}