#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
int A[500'005];
int tmp[500'005];
ll R = 0;
void mergesort(int s, int e) {
    if(s >= e) return;
    int mid = (s+e)/2;
    mergesort(s, mid);
    mergesort(mid+1, e);

    int lidx = s;
    int ridx = mid + 1;
    int tidx = s;
    while(lidx <= mid && ridx <= e) {
        if(A[lidx] <= A[ridx]) tmp[tidx++] = A[lidx++];
        else {
            tmp[tidx++] = A[ridx++];
            R += mid - lidx + 1;
        }
    }  
    while(lidx <= mid) tmp[tidx++] = A[lidx++];
    while(ridx <= e)   tmp[tidx++] = A[ridx++];

    for(int i = s; i <= e; i++) {
        A[i] = tmp[i];
    }
}

int main() {
    cin >> N;
    for(int i = 0; i < N; i++) cin >> A[i];
    mergesort(0, N-1);
    cout << R;
}