/*
Sử dụng g1 (đọc g1 từ file input.txt)
    + Nhập đỉnh u
    + Xuất: - Bậc vào u
            - Bậc ra u
*/


#include "cgraph/cgraph.h"
#include <stdio.h>
#include <stdlib.h>

// bậc vào/ra của đỉnh
void print_degree (cgraph_t *gp, int u) {
	CGRAPH_INTEGER res;
	cgraph_degree_one(gp, &res, u, CGRAPH_OUT, false);
	printf("OUT DEGREE ONE: %d %d\n", u, (int)res);
}

// danh sách đỉnh đi tới đi ra u (ở demo-cgraph-1)

// void print_out_nei(cgraph_t *gp, int u) {
// 	cgraph_ivec_t neis = cgraph_ivec_create();
// 	cgraph_neighbors(gp, &neis, u, CGRAPH_OUT);
// 	printf("Out neis: \n");	//...
// }

int main() {
	FILE *inp = fopen("../input1.txt", "r");
	int n;
	fscanf(inp, "%d", &n);
	cgraph_ivec_t edges = cgraph_ivec_create();
	for(int i = 0; i < 2*n; i++) {
		int value;
		fscanf(inp, "%d", &value);
		cgraph_ivec_push_back(&edges, value);
	}
	fclose(inp);
	cgraph_ivec_print(edges);

	cgraph_t g;
	cgraph_create(&g, edges, 0, true);

	int u;
	printf("u: \n");
	scanf("%d", &u);

	print_degree(&g, u);

	// print_out_nei(&g, u);
	cgraph_destroy(&g);
	return 0;
}