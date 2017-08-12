/*
 * sds.c
 *
 *  Created on: 2016年12月21日
 *      Author: xzxin
 */
/*
 * main.c
 *
 *  Created on: 2016年12月21日
 *      Author: xzxin
 */

#include <stdio.h>
#include <string.h>

int hei[101],ldp[101],rdp[101];
int main()
{
	int n;
	while (scanf("%d",&n)!=EOF)
	{
		if(n==-1) break;
		int i;
		memset(ldp,0,sizeof(ldp));
		for (i=1;i<=n;i++)
		{
			scanf("%d",&hei[i]);
			ldp[i]=1;
		}
	int j;
	for (i=1;i<=n;i++)
	{
		for (j=i-1;j>=0;j--)
		{
			if (hei[j]<hei[i]&&ldp[i]<ldp[j]+1)
			{
				ldp[i]=ldp[j]+1;
			}
		}
	}
	memset(rdp,0,sizeof(rdp));
	for (i=1;i<=n;i++)
	{
		rdp[i]=1;
	}
	for (i=n;i>=1;i--)
	{
		for (j=i+1;j<=n;j++)
		{
			if (hei[j]<hei[i]&&rdp[i]<rdp[j]+1)
			{
				rdp[i]=rdp[j]+1;
			}
		}
	}

	int max=0;
	for (i=1;i<=n;i++)
	{
		if (rdp[i]+ldp[i]>max)
		{
			max=rdp[i]+ldp[i];
		}
	}
	max--;

	printf("%d\n",n-max);
	}
	return 0;
}


