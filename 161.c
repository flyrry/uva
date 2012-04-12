#include <stdio.h>
#include <string.h>

#define TIME 18001

char signals[TIME];
int i, h, m;
char* p;

void paste(char sig[], int gt, int rt) {
	p = sig;
	for (i = 0; i < TIME; i += rt) {
		if (i + rt >= TIME) return;
		p += gt;
		i += gt;
		if (i + rt >= TIME) {
			memset(p, 1, sizeof(char) * (TIME - i));
		} else {
			memset(p, 1, sizeof(char) * rt);
			p += rt;
		}
	}
}

int find_green(char sig[]) {
	i = 0;
	/* skip initial green */
	while (!sig[i++]);
	/* now find first green */
	for (; i < TIME; ++i) {
		if (!sig[i]) return i;
	}
	return -1;
}

void interpret(int time) {
	if (time < 0) {
		printf("Signals fail to synchronise in 5 hours\n");
		return;
	}
	printf("%02d:%02d:%02d\n", time/3600, (time%3600)/60, time%60);
}

int main(void) {
	int t;
	for (;;) {
		memset(signals, 0, sizeof signals);
		scanf("%d", &t);
		if (!t) return 0;
		
		while (t) {
			paste(signals, t-5, t+5);
			scanf("%d", &t);
		}
		
		t = find_green(signals);
		interpret(t);
	}
}
