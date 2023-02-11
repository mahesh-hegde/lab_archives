#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <omp.h>

using namespace std;

/// Strike marks all composite numbers in the range `[i, limit]`, in the intervals
/// of `step`.
inline int strike(vector<bool>& composite, int i, int step, int limit) {
	for (; i <= limit; i+=step) {
		composite[i] = 1;
	}
	return i;
}

int cacheUnfriendlySieve(int n, double *time) {
	vector<bool> composite(n+1, 0);
	int m = sqrt(n);
	int count = 0;
	double begin = omp_get_wtime();
	for (int i = 2; i <= m; i++) {
		if (!composite[i]) {
			count++;
			strike(composite, 2*i, i, n);
		}
	}
	for (int i = m+1; i < n; i++) {
		count += !composite[i];
	}
	double end = omp_get_wtime();
	*time = end - begin;
	return count;
}

int cacheFriendlySieve(int n, double *time) {
	vector<bool> composite(n+1, 0);
	int m = sqrt(n);
	int count = 0;
	vector<int> striker, factor;
	striker.reserve(m);
	factor.reserve(m);
	double begin = omp_get_wtime();
	for (int i = 2; i <= m; i++) {
		if (composite[i]) continue;
		count ++;
		int sk = strike(composite, 2*i, i, m);
		striker.push_back(sk);
		factor.push_back(i);
	}
	for (int w = m+1; w <= n; w += m) {
		int limit = min(w+m-1, n);
		for (int i = 0; i < factor.size(); i++) {
			striker[i] = strike(composite, striker[i], factor[i], limit);
		}
		for (int i = w; i <= limit; i++) {
			count += !composite[i];
		}
	}
	double end = omp_get_wtime();
	*time = end - begin;
	return count;
}

int (*func[])(int, double *) = {cacheUnfriendlySieve, cacheFriendlySieve};

int main() {
	printf("sizeof int %lu\n", sizeof(int));
	printf("%-20s%-25s%-25s\n", "N", "cache-unfriendly", "cache-friendly");
	for (int n = 10000; n <= 10000 * 1000; n *= 10) {
		printf("%-17d | ", n);
		for (int i = 0; i < 2; i++) {
			double time;
			int count = func[i](n, &time);
			printf("%-10.4lg (%-10d) | ", time*1000, count);
		}
		printf("\n");
	}
}
