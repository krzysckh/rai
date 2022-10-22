#include <inttypes.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include <time.h>

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} Pixel;

typedef struct {
	Pixel **pxl;
} Image;

void free_img (Image img, int h) {
	int i;
	for (i = 0; i < h; i++) {
		free(img.pxl[i]);
	}

	free(img.pxl);
}

void print_ppm (Image img, int w, int h) {
	int i,
	    j;
	printf("P6 %d %d 255\n", w, h);

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			printf("%c%c%c", 
				img.pxl[i][j].r,
				img.pxl[i][j].g,
				img.pxl[i][j].b
			);
		}
	}
}

Image draw_triangle(Image img, int width, int height, int color_st[3]) {
	int sz, x, y, xs, ys, i, j;
	sz = rand() % width;
	ys = rand() % height;
	xs = rand() % width;
	y = ys;
	x = xs;

	fprintf(stderr, "tr sz: %d\n", sz);

	for (i = 0; i < sz; i++) {
		for (j = 0; j < (int)((sz - i)/2); j++) {
			x ++;
		}
		for (j = 0; j < i; j ++) {
			if (y < height && x < width) {
				img.pxl[y][x].r = color_st[0] + ((rand() % 2 == 0) ? (rand() % 20) : -(rand() % 20));
				img.pxl[y][x].g = color_st[1] + ((rand() % 2 == 0) ? (rand() % 20) : -(rand() % 20));
				img.pxl[y][x].b = color_st[2] + ((rand() % 2 == 0) ? (rand() % 20) : -(rand() % 20));
			}
			x ++;
		}
		x = xs;
		y ++;
	}

	return img;
}

Image draw_square(Image img, int width, int height, int color_st[3]) {
	int x, y, i, j, sz, xs;
	x = rand() % width;
	xs = x;
	y = rand() % height;
	sz = rand() % (height / 2);

	fprintf(stderr, "sqr sz: %d\n", sz);

	for (i = 0; i < sz; i++) {
		for (j = 0; j < sz; j++) {
			if (x < width && y < height) {
				img.pxl[y][x].r = color_st[0] + ((rand() % 2 == 0) ? (rand() % 40) : -(rand() % 20));
				img.pxl[y][x].g = color_st[1] + ((rand() % 2 == 0) ? (rand() % 40) : -(rand() % 20));
				img.pxl[y][x].b = color_st[2] + ((rand() % 2 == 0) ? (rand() % 40) : -(rand() % 20));
			}
			x ++;
		}
		x = xs;
		y ++;
	}

	return img;
}

Image draw_quirky_line(Image img, int width, int height, int color_st[3]) {
	int x, y, i, sz;

	x = rand() % width;
	y = rand() % height;
	sz = rand() % (width / 3);

	fprintf(stderr, "line sz: %d\n", sz);

	for (i = 0; i < sz; i++) {
		if (x < width && y < height && x > 0 && y > 0) {
			img.pxl[y][x].r = color_st[0] + ((rand() % 2 == 0) ? (rand() % 40) : -(rand() % 20));
			img.pxl[y][x].g = color_st[1] + ((rand() % 2 == 0) ? (rand() % 40) : -(rand() % 20));
			img.pxl[y][x].b = color_st[2] + ((rand() % 2 == 0) ? (rand() % 40) : -(rand() % 20));
		}
		x ++;
		y += ((rand() % 2 == 0) ? (rand() % 5) : -(rand() % 5));
	}

	return img;
}

int main (int argc, char *argv[]) {
	int opt,
	    width = 500,
	    height = 500,
	    i,
	    j,
	    color_tmp[3],
	    squares = 1,
	    triangles = 1,
	    quirky_lines = 1,
	    seed = time(NULL);
	Image img;

	while ((opt = getopt(argc, argv, "hs:W:H:n:")) != -1) {
		switch(opt) {
			case 'h':
				printf("usage: %s [-h] [-s seed] [-W width] [-H height] [-n stl]\n", argv[0]);
				exit(0);
				break;
			case 's':
				seed = atoi(optarg);
				break;
			case 'W':
				width = atoi(optarg);
				break;
			case 'H':
				height = atoi(optarg);
				break;
			case 'n':
				while (*optarg) {
					switch (*optarg) {
						case 's':
							squares = 0;
							break;
						case 't':
							triangles = 0;
							break;
						case 'l':
							quirky_lines = 0;
							break;
						default:
							fprintf(stderr, "bad argument '%c' for -n\n", *optarg);
							exit(1);
					}
					optarg++;
				}
				break;
			default:
				exit(1);
				break;
		}
	}
#ifdef __OpenBSD__
	srand_deterministic(seed);
#else
	srand(seed);
#endif

	img.pxl = malloc(sizeof(Pixel*) * (height + 1));

	for (i = 0; i < height; i++) {
		img.pxl[i] = malloc(sizeof(Pixel) * width);
	}

	color_tmp[0] = rand() % 255;
	color_tmp[1] = rand() % 255;
	color_tmp[2] = rand() % 255;

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {

			img.pxl[i][j].r = color_tmp[0] + ((rand() % 2 == 0) ? (rand() % 20) : -(rand() % 20));
			img.pxl[i][j].g = color_tmp[1] + ((rand() % 2 == 0) ? (rand() % 20) : -(rand() % 20));
			img.pxl[i][j].b = color_tmp[2] + ((rand() % 2 == 0) ? (rand() % 20) : -(rand() % 20));

			/*img.pxl[i][j].r = color_tmp[0];*/
			/*img.pxl[i][j].g = color_tmp[1];*/
			/*img.pxl[i][j].b = color_tmp[2];*/
		}
	}

	fprintf(stderr, "seed: %d\n", seed);

	if (triangles) {
		for (i = 0; i < rand() % 15; i++) {
			color_tmp[0] = rand() % 255;
			color_tmp[1] = rand() % 255;
			color_tmp[2] = rand() % 255;
			img = draw_triangle(img, width, height, color_tmp);
		}
	}

	if (squares) {
		for (i = 0; i < rand() % 15; i++) {
			color_tmp[0] = rand() % 255;
			color_tmp[1] = rand() % 255;
			color_tmp[2] = rand() % 255;
			img = draw_square(img, width, height, color_tmp);
		}
	}

	if (quirky_lines) {
		for (i = 0; i < rand() % 50; i++) {
			color_tmp[0] = rand() % 255;
			color_tmp[1] = rand() % 255;
			color_tmp[2] = rand() % 255;
			img = draw_quirky_line(img, width, height, color_tmp);
		}
	}

	
	print_ppm(img, width, height);
	free_img(img, height);
	return 0;
}
