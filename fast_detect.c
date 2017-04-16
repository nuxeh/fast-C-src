#include <stdio.h>
#include <stdlib.c>

#include "fast.h"

unsigned char *pgm_read(const char *filename, int *width, int *height)
{
    FILE *f = fopen(filename,"rb");
    unsigned char *r = 0;
    if(f) {
        char id[3];
        int w,h,d;
        fscanf(f,"%2s %d %d %d\n",id,&w,&h,&d);
        if(id[0]=='P'&&id[1]=='5') {
            r = malloc(w*h);
            fread(r,w,h,f);
            if(width)*width=w;
            if(height)*height=h;
        }
        fclose(f);
    }
    return r;
}

void pgm_write(const char *filename,int width,int height,unsigned char *buf)
{
    FILE *f = fopen(filename,"wb");
    if(f) {
        fprintf(f,"P5\n%d %d\n255\n",width,height);
        fwrite(buf,width,height,f);
        fclose(f);   
    }
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("usage:\n\t%s <pgm-file> <x-value> <threshold> [out-file]\n", argv[0]);
		return 1;
	}

	printf("reading PGM file: %s\n", argv[1]);

	int w, h;
	unsigned char *data = pgm_read(argv[1], &w, &h);
	unsigned char *out;
	xy *c;
	int nc;

	int x = atoi(argv[2]);
	int t = atoi(argv[3]);

	int i, cx, cy, ci;
	char *out_path;

	int ret = 0;

	switch (x)
	{
	case 9:
		c = fast9_detect_nonmax(data, w, h, w, t, &nc);
		break;
	case 10:
		c = fast10_detect_nonmax(data, w, h, w, t, &nc);
		break;
	case 11:
		c = fast11_detect_nonmax(data, w, h, w, t, &nc);
		break;
	case 12:
		c = fast12_detect_nonmax(data, w, h, w, t, &nc);
		break;
	default:
		printf("invalid x value.\n");
		ret = 1;
		goto out_d;
	}

	/* annotate output image */
	out = malloc(w * h);
	memcpy(out, data, w * h);

	/* draw a cross on each corner */
	while (nc-- > 0)
	{
		for (cx = c[nc].x - CW/2; c < c[nc].x + CW/2; cx++) {
			for (cy = c[nc].y - CW/2; c < c[nc].y + CW/2; cy++)
			{
				ci = cx + cy * w;
				

			}
		}
		
	}

	if (argc > 3)
		out_path = argv[3]
	else
		out_path = "/tmp/fast.pgm";

	printf("writing output to %s\n", out_path);
	pgm_write(out_path, w, h, out);

	/* clean up */
	free(c);
	free(out);

out_d:
	free(data);

	return ret;
}
