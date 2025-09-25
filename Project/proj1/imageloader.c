/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"
#define DEBUG

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.

char buf[100];
Image *readData(char *filename) 
{
	Image* img=(Image*)malloc(sizeof(Image)); 
	int scale;
	
	FILE *fp = fopen(filename,"r");
	if(!fp){
	    perror("fopen failed");
	    free(img);
	    return NULL;
	}

	fscanf(fp,"%s",buf);
	fscanf(fp,"%" SCNu32 " %" SCNu32 ,&img->cols,&img->rows);
	fscanf(fp,"%" SCNu8 ,&scale);
	
	img->image=(Color**)malloc(sizeof(Color*)*(img->rows));
	
#ifdef DEBUG
	printf("width=%d,height=%d,scale=%d\n",img->cols,img->rows,scale);
#endif
	
	// start reading pixels 
	for(int i=0;i<img->rows;i++)
	{
		img->image[i]=(Color*)malloc(sizeof(Color)*(img->cols));
		for(int j=0;j<img->cols;j++)
		{
			fscanf(fp,"%" SCNu8 " %" SCNu8 " %" SCNu8 ,
									&img->image[i][j].R, \
									&img->image[i][j].G, \
									&img->image[i][j].B);
		}	 
	}
	
	fclose(fp);
	return img;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	printf("P3\n");
	printf("%"PRIu32" %"PRIu32"\n",image->cols,image->rows);
	printf("255\n");
	for(int i=0;i<image->rows;i++)
	{
		for(int j=0;j<image->cols;j++)
		{
			printf("%3" PRIu8" %3" PRIu8 " %3" PRIu8 ,
									image->image[i][j].R, \
									image->image[i][j].G, \
									image->image[i][j].B);
			fflush(stdout);
			if(j!=image->cols-1)
				printf("   ");
		}
		printf("\n");
	}
	
	return;
}

//Frees an image
void freeImage(Image *image)
{
	for(int i=0;i<image->rows;i++)
		free(image->image[i]);		
	
	free(image->image);
	free(image);
	return ;
}
