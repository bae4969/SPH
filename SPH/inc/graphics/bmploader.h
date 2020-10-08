#pragma once

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#   pragma warning( disable : 4996 ) // disable deprecated warning 
#endif

#pragma pack(1)

typedef struct {
	short type;
	int size;
	short reserved1;
	short reserved2;
	int offset;
} BMPHeader;

typedef struct {
	int size;
	int width;
	int height;
	short planes;
	short bitsPerPixel;
	unsigned compression;
	unsigned imageSize;
	int xPelsPerMeter;
	int yPelsPerMeter;
	int clrUsed;
	int clrImportant;
} BMPInfoHeader;


typedef struct {
	unsigned char x, y, z, w;
} uchar4;

typedef unsigned char uchar;


void LoadBMPFile(uchar4** dst, int* width, int* height, const char* name)
{
	BMPHeader hdr;
	BMPInfoHeader infoHdr;
	int x, y;

	FILE* fd;

	if (sizeof(uchar4) != 4) {
		printf("***Bad uchar4 size***\n");
		exit(0);
	}

	if (!(fd = fopen(name, "rb"))) {
		printf("***BMP load error: file access denied***\n");
		exit(0);
	}

	fread(&hdr, sizeof(hdr), 1, fd);
	if (hdr.type != 0x4D42) {
		printf("***BMP load error: bad file format***\n");
		exit(0);
	}
	fread(&infoHdr, sizeof(infoHdr), 1, fd);

	if (infoHdr.bitsPerPixel != 24) {
		printf("***BMP load error: invalid color depth***\n");
		exit(0);
	}

	if (infoHdr.compression) {
		printf("***BMP load error: compressed image***\n");
		exit(0);
	}

	*width = infoHdr.width;
	*height = infoHdr.height;
	*dst = (uchar4*)malloc(*width * *height * 4);

	fseek(fd, hdr.offset - sizeof(hdr) - sizeof(infoHdr), SEEK_CUR);

	for (y = 0; y < infoHdr.height; y++) {
		for (x = 0; x < infoHdr.width; x++) {
			(*dst)[(y * infoHdr.width + x)].z = fgetc(fd);
			(*dst)[(y * infoHdr.width + x)].y = fgetc(fd);
			(*dst)[(y * infoHdr.width + x)].x = fgetc(fd);
		}

		for (x = 0; x < (4 - (3 * infoHdr.width) % 4) % 4; x++)
			fgetc(fd);
	}

	if (ferror(fd)) {
		printf("***Unknown BMP load error.***\n");
		free(*dst);
		exit(0);
	}

	fclose(fd);
}

void SaveBMPFile(uchar4* dst, int width, int height, const char* outputname, const char* inputname) {
	BMPHeader hdr;
	BMPInfoHeader infoHdr;
	int x, y;

	FILE* fd;

	if (sizeof(uchar4) != 4) {
		printf("***Bad uchar4 size***\n");
		exit(0);
	}

	if (!(fd = fopen(inputname, "rb"))) {
		printf("***BMP load error: file access denied***\n");
		exit(0);
	}

	// read headers from input BMP
	fread(&hdr, sizeof(hdr), 1, fd);
	fread(&infoHdr, sizeof(infoHdr), 1, fd);

	fclose(fd);

	// write new image
	if (!(fd = fopen(outputname, "wb"))) {
		printf("***BMP load error: file access denied***\n");
		exit(0);
	}

	fwrite(&hdr, sizeof(hdr), 1, fd);
	fwrite(&infoHdr, sizeof(infoHdr), 1, fd);

	fseek(fd, hdr.offset - sizeof(hdr) - sizeof(infoHdr), SEEK_CUR);

	// convert input to compatible to BMP
	int x_pad = (4 - (3 * infoHdr.width) % 4) % 4;
	unsigned char* out = (unsigned char*)malloc((infoHdr.width * 3 + x_pad) * infoHdr.height);
	unsigned int idx = 0;
	for (y = 0; y < infoHdr.height; y++)
	{
		for (x = 0; x < infoHdr.width; x++)
		{
			out[idx++] = dst[(y * infoHdr.width + x)].z;
			out[idx++] = dst[(y * infoHdr.width + x)].y;
			out[idx++] = dst[(y * infoHdr.width + x)].x;
		}

		for (x = 0; x < x_pad; x++)
			out[idx++] = 0;
	}


	fwrite(out, (infoHdr.width * 3 + x_pad) * infoHdr.height, 1, fd);

	free(out);
	fclose(fd);
}
