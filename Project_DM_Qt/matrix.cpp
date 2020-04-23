#include "matrix.h"
#include <QDebug>
///////////////////////////////////////////////////////////////////////////////////////////////     Жиренкин Артем      //

vector<vector<vector<int>>> MAT_Z_SUM(vector<vector<vector<int>>> a, vector<vector<vector<int>>> b)
{
	vector<vector<vector<int>>> c(b.size()); // добавляем трёхмерный вектор,в который будет вноситься результат умножения
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


///////////////////////////////////////////////////////////////////////////////////////////////     Астахов Михаил      //

vector<vector<vector<int>>> MAT_Z_MUL(vector<vector<vector<int>>> a, vector<vector<vector<int>>> b)
{
	vector<vector<vector<int>>> c(b.size()); // добавляем трёхмерный вектор,в который будет вноситься результат умножения
	int sizec = c.size();
	for (int i = 0; i < sizec; i++)
	{
		c[i].resize(sizec);
		for (int j = 0; j < sizec; j++)
		{
			c[i][j].push_back(0);
            c[i][j].push_back(0);
			for (int k = 0; k < sizec; k++)
				c[i][j] = ADD_ZZ_Z(c[i][j], MUL_ZZ_Z(a[i][k], b[k][j]));
		}
	}
	return c;//возвращаем матрицу результата
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//for (int i = 0; i < b.size(); i++)
//{
//    for (int j = 0; j < b.size(); j++)
//    {
//        for (int k = 0; k < b.size(); k++)
//            qDebug() <<b[i][j][k]<<" ";
//    }
//   qDebug()<<endl;
//}
//qDebug()<<"--------------Stop------------------";
