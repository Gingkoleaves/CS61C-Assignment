/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
    Color *newColor = (Color *)malloc(sizeof(Color));
    if (newColor == NULL) {
        return NULL; 
    }
	uint8_t bp = (image->image[row][col].B & 1) ? 0xFF : 0x00;
	newColor->R=bp;
	newColor->G=bp;
    newColor->B=bp;
	return newColor;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	Image* img=malloc(sizeof(Image));
	if(NULL==img){
		return NULL;
	}
	
	int cols=image->cols,rows=image->rows;
	img->image=malloc(rows*sizeof(void*));	
	if(NULL==img->image){
        free(img);
		return NULL;
	}
	img->cols=cols,img->rows=rows;	
	for(int i=0;i<rows;i++)
	{
		img->image[i]=malloc(sizeof(Color)*cols);	
		if(NULL==img->image[i]){
		    for (int k = 0; k <= i; k++) {
                free(img->image[k]);
            }
            free(img->image);
        	free(img);
			return NULL;
		}
		for(int j=0;j<cols;j++)
		{
			Color *nC=evaluateOnePixel(image,i,j);
			if(NULL==nC){
				for (int k = 0; k <= i; k++) 
                    free(img->image[k]);
                free(img->image);
        		free(img);
				return NULL;
			}
			img->image[i][j].R=nC->R;
			img->image[i][j].G=nC->G;
			img->image[i][j].B=nC->B;
			free(nC);
		}
	}
	return img;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	if(argc!=2){
		printf("usage: %s filename\n",argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		return -1;
	}
	
	char*filename=argv[1];
	
	Image* ppm=readData(filename);
	Image* hidden_ppm=steganography(ppm);
	writeData(hidden_ppm);
	freeImage(hidden_ppm);
	freeImage(ppm);
	
	return 0;
}
