int lo = -1, hi = n; // 탐색 범위 밖으로 설정
while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;
    if (check(mid)) hi = mid;
    else lo = mid;
} 