#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <omp.h>

using namespace std;

/// Strike marks all composite numbers in the range `[i, limit]`, in the intervals
/// of `step`.
inline int strike(vector<int>& composite, int i, int step, int limit) {
	for (; i <= limit; i+=step) {
		composite[i] = 1;
	}
	return i;
}

int cacheUnfriendlySieve(int n, double *time) {
	vector<int> composite(n+1, 0);
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
	vector<int> composite(n+1, 0);
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

int parallelSieve(int n, double *time) {
	int count = 0, m = (int)sqrt(n);
	vector<int> factor;
	double begin = omp_get_wtime();

	// compute initial set of points
	vector<int> sv(m+1, false);
	for (int i = 2; i <= m; i++) {
		if (!sv[i]) {
			count++;
			factor.push_back(i);
			strike(sv, 2*i, i, m);
		}
	}
	#pragma omp parallel
	{
		// Assuming that OpenMP will divide The inner loop into largest
		// possible chunks. In that case we have to compute the striker
		// initially (if it's not computed in particular thread).
		vector<int> sv(m+1, false);
		vector<int> striker;
		int base = -1;
		#pragma omp for reduction(+:count)
		for (int w = m+1; w <= n; w+= m) {
			sv.assign(m+1, false); // reset
			int limit = min(w+m-1, n) - w;
			if (base != w) {
				for (auto f: factor) {
					striker.push_back((f+w-1) / f * f - w);
				}
			}
			// now we have strikers
			for (int i = 0;  i < factor.size(); i++) {
				striker[i] = strike(sv, striker[i], factor[i], limit) - m;
			}
			for (int i = 0; i <= limit; i++) {
				count += !sv[i];
			}
			base = limit;
		}
	}
	double end = omp_get_wtime();
	*time = end - begin;
	return count;
}

int (*func[])(int, double *) = {cacheUnfriendlySieve, cacheFriendlySieve, parallelSieve};

int main() {
	printf("sizeof int %lu\n", sizeof(int));
	printf("%-20s%-25s%-25s%-25s\n", "N", "cache-unfriendly", "cache-friendly", "parallel");
	for (int n = 10000; n <= 10000 * 1000; n *= 10) {
		printf("%-17d | ", n);
		for (int i = 0; i < 3; i++) {
			double time;
			int count = func[i](n, &time);
			printf("%-10.4lg (%-10d) | ", time*1000, count);
		}
		printf("\n");
	}
}
