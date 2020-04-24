#include "matrix.h"

///////////////////////////////////////////////////////////////////////////////////////////////     ������������� ���������      //

vector<int> MAT_Z_DET(vector<vector<vector<int>>> a) // 
{
	vector<int> ss;
	return ss;
}

int MAT_Z_RANK(vector<vector<vector<int>>> a)
{
	int as = 1;
	return as;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////     �������� �����      //

vector<vector<vector<int>>> MAT_Z_SUM(vector<vector<vector<int>>> a, vector<vector<vector<int>>> b)
{
	vector<vector<vector<int>>> c(b.size()); // ��������� ��������� ������,� ������� ����� ��������� ��������� ���������
	int sizec = c.size();
	for (int i = 0; i < sizec; i++)
	{
		c[i].resize(sizec);
		for (int j = 0; j < sizec; j++)
		{		
			c[i][j] = ADD_ZZ_Z(a[i][j],b[i][j]);
		}
	}
	return (c);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////     ������� ������      //

vector<vector<vector<int>>> MAT_Z_MUL(vector<vector<vector<int>>> a, vector<vector<vector<int>>> b)
{
	vector<vector<vector<int>>> c(b.size()); // ��������� ��������� ������,� ������� ����� ��������� ��������� ���������
	int sizec = c.size();
	for (int i = 0; i < sizec; i++)
	{
		c[i].resize(sizec);
		for (int j = 0; j < sizec; j++)
		{
			c[i][j].push_back(0);
			for (int k = 0; k < sizec; k++)
				c[i][j] = ADD_ZZ_Z(c[i][j], MUL_ZZ_Z(a[i][k], b[k][j]));
		}
	}
	return c;//���������� ������� ����������
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////