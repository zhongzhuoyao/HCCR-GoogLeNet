#include "gradient.h"
#include "OfflineGridUBytePicture.h"
//judge the gradient area in terms of (x,y)
template <typename _T>
int Judge( _T x, _T y)    //
{
 if( x==0&&y==0 )
   return 0;
 if ( x>0&&y==0 )
   return 0;
 if ( y>0&&x>y )
   return 1;
 if ( x>0&&y==x )
   return 2;
 if ( x>0&&x<y )
   return 3;
 if ( x==0&&y>0 )
   return 4;
 if ( x<0&&y>(abs(x)) )
   return 5;
 if ( x<0&&y==(abs(x)))
   return 6;
 if ( x<0&&y<(abs(x))&&y>0 )
   return 7;
 if ( y==0&&x<0 )
   return 8;
 if ( y<0&&y>x )
   return 9;
 if ( x<0&&y==x )
   return 10;
 if ( x<0&&y<x )
   return 11;
 if ( x==0&&y<0 )
   return 12;
 if ( y<0&&x<(abs(y))&&x>0 )
   return 13;
 if ( y<0&&x==(abs(y)) )
   return 14;
 if ( y<0&&x>(abs(y)) )
   return 15;
 else
   return 0;
}

void FeaExtractByGradient(cv::Mat img, vector<cv::Mat> &featureMaps)
{
	float Gx;
	float Gy;
	int us_direction=8;
	int imgHeight=img.rows;
	int imgWidth=img.cols;
	int v_gx [maskHeight][maskWidth]={};
	int v_gy [maskHeight][maskWidth]={};
	int image[maskHeight][maskWidth]={};
	//make some confirm
	for(int i=0;i<maskHeight;i++){
		for(int j=0;j<maskWidth;j++){
			image[i][j]=img.at<uchar>(i,j);
		}
	}
	//Use Sobel to compute the gradient value of each pixel
	for(int i=0;i<maskHeight;i++)
	{
		for(int j=0;j<maskWidth;j++)
		{
			if((i==maskHeight-1)||(j==maskWidth-1)||(i==0)||(j==0))
			{
				v_gx[i][j]=image[i][j];
				v_gy[i][j]=image[i][j];
			}
			else
			{
				v_gx[i][j]=image[i-1][j-1]+2*image[i-1][j]+image[i-1][j+1]-image[i+1][j-1]-2*image[i+1][j]-image[i+1][j+1];
				v_gy[i][j]=image[i-1][j-1]+2*image[i][j-1]+image[i+1][j-1]-image[i-1][j+1]-2*image[i][j+1]-image[i+1][j+1];
			}
		}
	}
	float * v_G=new float[maskHeight*maskWidth*us_direction];
	//Decompose each gradient value vector to eight directions
	for(int i=0;i<maskHeight;i++)
	{
		for(int j=0;j<maskWidth;j++)
		{
			Gx=(float)v_gx[i][j];
			Gy=(float)v_gy[i][j];
			int us_index=i*maskWidth+j;
			int Dec_Pos=Judge(Gx,Gy);
			switch(Dec_Pos)
			{
			case 0: v_G[us_index]=Gx;break;
			case 1: v_G[us_index]=Gx-Gy;v_G[maskHeight*maskWidth+us_index]=(float)1.414214*Gy;break;
			case 2: v_G[maskHeight*maskWidth+us_index]=(float)1.414214*Gy;break;
			case 3: v_G[maskHeight*maskWidth+us_index]=(float)1.414214*Gx;v_G[maskHeight*maskWidth*2+us_index]=Gy-Gx;break;
			case 4: v_G[maskHeight*maskWidth*2+us_index]=Gy;break;
			case 5: v_G[maskHeight*maskWidth*2+us_index]=Gx+Gy;v_G[maskHeight*maskWidth*3+us_index]=(float)1.414214*abs(Gx);break;//abs(1.414214*Gx);break;
			case 6: v_G[maskHeight*maskWidth*3+us_index]=(float)1.414214*Gy;break;
			case 7: v_G[maskHeight*maskWidth*3+us_index]=(float)1.414214*Gy;v_G[maskHeight*maskWidth*4+us_index]=abs(Gx+Gy);break;
			case 8: v_G[maskHeight*maskWidth*4+us_index]=abs(Gx);break;
			case 9: v_G[maskHeight*maskWidth*4+us_index]=Gy-Gx;v_G[maskHeight*maskWidth*5+us_index]=(float)1.414214*abs(Gy);break;
			case 10:v_G[maskHeight*maskWidth*5+us_index]=(float)1.414214*abs(Gy);break;
			case 11:v_G[maskHeight*maskWidth*5+us_index]=(float)1.414214*abs(Gx);v_G[maskHeight*maskWidth*6+us_index]=Gx-Gy;break;
			case 12:v_G[maskHeight*maskWidth*6+us_index]=abs(Gy);break;
			case 13:v_G[maskHeight*maskWidth*6+us_index]=abs(Gx+Gy);v_G[maskHeight*maskWidth*7+us_index]=(float)1.414214*abs(Gx);break;
			case 14:v_G[maskHeight*maskWidth*7+us_index]=(float)1.414214*Gx;break;
			case 15:v_G[maskHeight*maskWidth*7+us_index]=(float)1.414214*abs(Gy);v_G[us_index]=abs(Gx+Gy);break;
			}
		}
	}
	for(int c=0;c<us_direction;c++)
	{
		float min=9999999;
		float max=-1;
		cv::Mat graFeaMap(maskHeight,maskHeight,CV_8UC1);
		for(int i=0;i<maskHeight;i++)
		{
			for(int j=0;j<maskWidth;j++)
			{
				//make some confirm
				if(v_G[c*maskHeight*maskWidth+i*maskWidth+j]<0)
				{
					v_G[c*maskHeight*maskWidth+i*maskWidth+j]=0;
				}
				if(max<v_G[c*maskHeight*maskWidth+i*maskWidth+j])
				{
					max=v_G[c*maskHeight*maskWidth+i*maskWidth+j];
				}
				if(min>v_G[c*maskHeight*maskWidth+i*maskWidth+j])
				{
					min=v_G[c*maskHeight*maskWidth+i*maskWidth+j];
				}
			}
		}
		for(int i=0;i<maskHeight;i++)
		{
			for(int j=0;j<maskWidth;j++)
			{
				v_G[c*maskHeight*maskWidth+i*maskWidth+j]=255*((float)(v_G[c*maskHeight*maskWidth+i*maskWidth+j]-min))/(max-min);// confirm 0-255
				graFeaMap.at<uchar>(i,j)=(uchar)v_G[c*maskHeight*maskWidth+i*maskWidth+j];
			}
		}
		GaussianBlur(graFeaMap,graFeaMap,Size(3, 3),0,0);
		featureMaps.push_back(graFeaMap);
		graFeaMap.release();
	}
	delete[]v_G;
}
