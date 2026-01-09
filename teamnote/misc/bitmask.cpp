// n번째 비트 켜기 (Add/Set)
#define setBit(S, n) ((S) | (1LL << (n)))
// n번째 비트 끄기 (Remove/Unset)
#define clearBit(S, n) ((S) & ~(1LL << (n)))
// n번째 비트 반전 (Toggle)
#define toggleBit(S, n) ((S) ^ (1LL << (n)))
// n번째 비트 확인 (Check) - 0이 아니면 true
#define checkBit(S, n) ((S) & (1LL << (n)))
// n개의 비트가 모두 켜진 마스크 생성 (11...1)
#define allOnes(n) ((1LL << (n)) - 1)

// 켜져 있는 비트만 순회하기 (LSB 활용)
int temp = S;
while (temp > 0) {
    int lsb = temp & -temp; // 최하위 비트 추출 (예: 00100)
    int idx = __builtin_ctz(lsb); // 해당 비트의 인덱스 (예: 2)
    // TODO: idx에 대한 로직 수행
    temp -= lsb; // 최하위 비트 지우기
}