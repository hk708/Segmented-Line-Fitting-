#include <bits/stdc++.h>
using namespace std;
#include <string>
int num, penalty;
float errors[1000][1000], slopes[1000][1000], y_intercepts[1000][1000];
int segments[1000];
///Struct to represent a point
typedef struct Point
{
    float xval, yval;
}Point;
///Struct to represent a line
///start_p and end_p represents the starting and end points with respect to the input set of points, and line_e and line_s are the actual start and ending points of the segment used later in visualization
typedef struct Line
{
    float slope;
    float intercept;
    int start;
    int end;
    Point start_p;
    Point end_p;
    Point line_s;
    Point line_e;
}Line;
///Swap function to use in bubble sort
void swap(Point *xp, Point *yp) 
{ 
    Point temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}
///Bubble sort to sort the points in ascending order based on their x-coordinates
void sort(Point arr[],int size)
{
    int i, j; 
    for (i = 1; i <= size-1; i++)
    { 
        for (j = 1; j <= size-i-1; j++)
        { 
            if (arr[j].xval > arr[j+1].xval) 
                swap(&arr[j], &arr[j+1]);
        }
    }
}
///Function to calculate the line of best fit and the error associated for that line of best fit between a specified start and end point for an interval in the points array
float min_error(Point arr[], int start, int end)
{
    if(start == end)
    return 0;
    int n;
    float xsum=0,ysum=0,x2sum=0,xysum=0;
    float a, b, denom;
    n = end - start + 1;
    for(int i = start; i<= end; i++)
    {
        xsum += arr[i].xval;
        ysum += arr[i].yval;
        xysum += arr[i].xval*arr[i].yval;
        x2sum += arr[i].xval*arr[i].xval;
    }
    if(n*x2sum - xsum*xsum != 0)
    {
    a = (n*xysum -xsum*ysum);
    denom = (n*x2sum -xsum*xsum);
    a = a/denom;
    slopes[start][end] = a;
    }
    else
    a = INT_MAX;
    b = (ysum - a*xsum)/n;
    y_intercepts[start][end] = b;
    float error = 0;
    for(int i = start; i<= end; i++)
    {
        double temp;
        if(a == INT_MAX)
        {
        temp = arr[i].xval - (xsum/n);
        slopes[start][end] = 6969;
        y_intercepts[start][end] = (xsum/n);
        }
        else
        temp = arr[i].yval - a*arr[i].xval - b;
        error += temp*temp;
    }
    return error;
}
///Main function
int main()
{
    printf("Enter Number of Points : \n");
    cin>>num;
    float memo[num+1];
    Point points[num+1];
    memo[0] = 0;

    printf("Enter Points :\n");
    fstream input;
    input.open("input.txt",ios::out);
    for(int i = 1; i<=num; i++)
    {
        cin>>points[i].xval>>points[i].yval;
        input<<"("<<points[i].xval<<","<<points[i].yval<<")\n";
    }
    input.close();
    printf("Enter cost of creating a line segment :\n");
    cin>>penalty;
    sort(points, num+1);
    for(int i = 1; i<=num; i++)
    {
        for(int j = i; j<=num; j++)
            errors[i][j] = min_error(points, i, j);
    }
    for(int i = 1; i<=num; i++)
    {
        float min = INT_MAX, m = 0;
        int min_index;
        for(int j = 1; j<=i; j++)
        {
            m = errors[j][i] + penalty + memo[j-1];
            if(m<min)
            {
                min = m;
                min_index = j;
            }
        }
        memo[i] = min;
        segments[i] = min_index;
    }
    int size = 0;
    Line segment_list[1000];
    for (int i = num, j = segments[num]; i > 0; i = j-1, j = segments[i])
    {
        segment_list[size].slope = slopes[j][i];
        segment_list[size].intercept = y_intercepts[j][i];
        segment_list[size].start = j;
        segment_list[size].end = i;
        segment_list[size].start_p = points[j];
        segment_list[size].end_p = points[i];
        segment_list[size].line_s.xval = (segment_list[size].start_p.xval + segment_list[size].slope*segment_list[size].start_p.yval - segment_list[size].slope*segment_list[size].intercept)/(1 + segment_list[size].slope*segment_list[size].slope);
        segment_list[size].line_s.yval = (segment_list[size].slope*segment_list[size].start_p.xval + segment_list[size].slope*segment_list[size].slope*segment_list[size].start_p.yval + segment_list[size].intercept)/(1 + segment_list[size].slope*segment_list[size].slope);
        segment_list[size].line_e.xval = (segment_list[size].end_p.xval + segment_list[size].slope*segment_list[size].end_p.yval - segment_list[size].slope*segment_list[size].intercept)/(1 + segment_list[size].slope*segment_list[size].slope);
        segment_list[size].line_e.yval = (segment_list[size].slope*segment_list[size].end_p.xval + segment_list[size].slope*segment_list[size].slope*segment_list[size].end_p.yval + segment_list[size].intercept)/(1 + segment_list[size].slope*segment_list[size].slope);
        if(slopes[j][i] == 6969)
        {
        segment_list[size].line_s = segment_list[size].start_p;
        segment_list[size].line_e = segment_list[size].end_p;
        }
        size++;
	}
    printf("Optimum solution is %f\n", memo[num]);
    printf("The segments are :\n");
    fstream output_p;
    output_p.open("segment_points.txt",ios::out);
    for(int i = size-1; i>=0; i--)
    {
        if(segment_list[i].slope == 6969)
        printf("Segment x = %f from (%f,%f) to (%f,%f) with square error %f.\n",segment_list[i].intercept,segment_list[i].start_p.xval,segment_list[i].start_p.yval,segment_list[i].end_p.xval,segment_list[i].end_p.yval,errors[segment_list[i].start][segment_list[i].end]);
        else
        printf("Segment y = %f * x + %f from (%f,%f) to (%f,%f) with square error %f.\n",segment_list[i].slope, segment_list[i].intercept,segment_list[i].start_p.xval,segment_list[i].start_p.yval,segment_list[i].end_p.xval,segment_list[i].end_p.yval,errors[segment_list[i].start][segment_list[i].end]);
        output_p<<"("<<segment_list[i].line_s.xval<<","<<segment_list[i].line_s.yval<<")"<<" "<<"("<<segment_list[i].line_e.xval<<","<<segment_list[i].line_e.yval<<")"<<"\n";
    }
    output_p.close();
    return 0;
}