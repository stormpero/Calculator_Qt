#include "integer.h"

///////////////////////////////////////////////////////////////////////////////////////////////     ������������� ���������     //

vector<int> ABS_Z_N(vector<int> a)
{
	a.erase(a.begin());
	return a;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////     �������� ������     //

vector<int> MUL_ZZ_Z(vector<int> a, vector<int> b) // �������� ������ ����������
{
	vector<int> result; // ����������, ������� ������ ��������� ���������
	if (POZ_Z_D(a) == 0 || POZ_Z_D(b) == 0) //  ���� ���� �� ����� ����� 0, �� �� ������������ ���� ����� 0
	{
		result.push_back(0);
		result.push_back(0);
	}
		
	else
	{
		result = MUL_NN_N(ABS_Z_N(a), ABS_Z_N(b)); // ��������� ����� � ����������� � �������� ���������
		result = TRANS_N_Z(result); // ��������� ����������� � �����
		if (POZ_Z_D(a) != POZ_Z_D(b)) //�������� ����� �� ����� �����, ���� ���, �� �������� ����
			result = MUL_ZM_Z(result); // ������� ����� �� -1
	}
	return(result);   // ������������ ��������
}

vector<int>  MOD_ZZ_Z(vector<int> a, vector<int> b)
{
	vector<int> q; // �������
	vector<int> aq_or_bq; // ��������, ������� ������ ������������ �������� ����� �� �������
	vector<int> result; // ����������, ������� ������ ��������� 
	q = DIV_ZZ_Z(a, b); // ������� �� ������� ����� � b 
	if (COM_NN_D(a, b) == 2) // ���� �, ������ b
	{
		aq_or_bq = MUL_ZZ_Z(b, q); // �� ����� ����� ��� ������� ���������� �� ������� �� 
		result = SUB_ZZ_Z(a, aq_or_bq); // �������� ����� ����� �� a
	}
	else if (COM_NN_D(a, b) == 1)
	{
		aq_or_bq = MUL_ZZ_Z(a, q);
		result = SUB_ZZ_Z(b, aq_or_bq);
	}

	return(result);   // ������������ ��������
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////     ������� ������      //

int POZ_Z_D(vector<int> num)
{

	if ((num[0] == 0)&&(num.size()==1) || ((num[0]==0)&&(num[1]==0)))
		return 0;
	else if (num[0] == 1)
		return 1;
	else
		return 2;
}
vector<int> ADD_ZZ_Z(vector<int> num1, vector<int> num2)
{
	vector<int> result; // ����������, ������� ������ ��������� ��������
		 
	if (POZ_Z_D(num1) == 0)	return num2;
	if (POZ_Z_D(num2) == 0) return num1;
	if ((POZ_Z_D(num1) == 2) && (POZ_Z_D(num2) == 2))
	{
		result = ADD_NN_N(ABS_Z_N(num1), ABS_Z_N(num2));
		result = TRANS_N_Z(result);
	}		
	else if ((POZ_Z_D(num1) == 1) && (POZ_Z_D(num2) == 1))
	{
		result = ADD_NN_N(ABS_Z_N(num1), ABS_Z_N(num2));
		result.insert(result.begin(), 1);
	}
	else if ((POZ_Z_D(num1) == 1) && (POZ_Z_D(num2) == 2)) //POZ_Z_D 1 - �����, 2 - �����
	{
		result = SUB_NN_N(ABS_Z_N(num1), ABS_Z_N(num2));
		result = TRANS_N_Z(result);
		if (COM_NN_D(ABS_Z_N(num1), ABS_Z_N(num2)) == 2) // COM_NN_D 2 - num1 > num2; 1 - num2 > num1		
			result= MUL_ZM_Z(result);		
	}
	else if ((POZ_Z_D(num1) == 2) && (POZ_Z_D(num2) == 1)) // num1 - �����, num2 - �����
	{
		result = SUB_NN_N(ABS_Z_N(num1), ABS_Z_N(num2));
		result = TRANS_N_Z(result);
		if (COM_NN_D(ABS_Z_N(num1), ABS_Z_N(num2)) == 1)
			result = MUL_ZM_Z(result);
	}
	return(result);   // ������������ ��������
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////     ����� ��������      //

vector<int> MUL_ND_N(vector<int> entry, int number) 
{
	if (entry.empty())
		throw "Error:Empty entry";

	short digit = 0;// ���������� ���������� �� ���������� ���������� �������

	for (int i = entry.size() - 1; i >= 0; i--)
	{
		short multiplication;
		multiplication = number * entry[i];   // ������������ ����� � �������

		if (multiplication + digit >= 10) 
		{
			entry[i] = (multiplication + digit) % 10;
			digit = (multiplication + digit) / 10;
		}
		else
		{
			entry[i] = (multiplication + digit) % 10;
			digit = 0;
		}
	}

	if (digit != 0) //���� ��������� ������ >= 10 �� ���������� ����� ������� � ������ �������
		entry.insert(entry.begin(), digit);

	return entry;
}

vector<int> SUB_ZZ_Z(vector<int> vector_1, vector<int> vector_2) //��������� ����� �����
{
	vector<int> result;
	if (POZ_Z_D(vector_2) == 0) //�������� ��� ���� �� ����� 0, ����� ���������� ������� ���� �� ��������
		return (vector_1);
	if (POZ_Z_D(vector_1) == 0)
		return (vector_2);

	if (POZ_Z_D(vector_2) == 1 && POZ_Z_D(vector_1) == 2) {//1 +, 2 -, ���������� ��� ����������� ��������� 1 � ������	
		vector_1.erase(vector_1.begin());
		vector_2.erase(vector_2.begin());
		result = ADD_NN_N(vector_1, vector_2);
		result.insert(result.begin(), 0);
		return (result);
	}

	if (POZ_Z_D(vector_2) == 1 && POZ_Z_D(vector_1) == 1) {//1 -, 2-// ��� 3 ������
		vector_1.erase(vector_1.begin());
		vector_2.erase(vector_2.begin());
		if (COM_NN_D(vector_1, vector_2) == 0)//�������� �� ���������, ���� ��� ����� ���������� 0		
			return { 0, 0 };

		if (COM_NN_D(vector_1, vector_2) == 2) { // 1� ������ 2�� �������� ���������� �� ������ -
			result = SUB_NN_N(vector_1, vector_2);
			result.insert(result.begin(), 1);
			return (result);
		}

		if (COM_NN_D(vector_1, vector_2) == 1) { //2� ������ 1�� �������� ���������� � +
			result = SUB_NN_N(vector_2, vector_1);
			result.insert(result.begin(), 0);
			return (result);
		}
	}

	if (POZ_Z_D(vector_2) == 2 && POZ_Z_D(vector_1) == 2) {//1+, 2+ ���������� �����������, ������ ������ ������ ������ 
		vector_1.erase(vector_1.begin());
		vector_2.erase(vector_2.begin());
		if (COM_NN_D(vector_1, vector_2) == 0)
			return { 0, 0 };

		if (COM_NN_D(vector_1, vector_2) == 2) {
			result = SUB_NN_N(vector_1, vector_2);
			result.insert(result.begin(), 0);
			return (result);
		}

		if (COM_NN_D(vector_1, vector_2) == 1) {
			result = SUB_NN_N(vector_2, vector_1);
			result.insert(result.begin(), 1);
			return (result);
		}
	}

	if (POZ_Z_D(vector_1) == 1 && POZ_Z_D(vector_2) == 2) {// ���� 1 -, 2 + ���������� ��� ����������� ��������� 1 � ������		
		vector_1.erase(vector_1.begin());
		vector_2.erase(vector_2.begin());
		result = ADD_NN_N(vector_1, vector_2);
		result.insert(result.begin(), 1);
		return (result);
	}
}

vector<int> DIV_ZZ_Z(vector<int> vector_1_N, vector<int> vector_2_N)
{
	if ((POZ_Z_D(vector_2_N) == 0))// ���� �������� = 0 ������
		throw ("Divider 0!");
	
		if ((POZ_Z_D(vector_1_N) == 0))// ���� ������� = 0 ���������� 0 
			return { 0 };

		bool f;//�������� �� ����
		if (((POZ_Z_D(vector_1_N) == 2) && (POZ_Z_D(vector_2_N) == 1)) || ((POZ_Z_D(vector_1_N) == 1) && (POZ_Z_D(vector_2_N) == 2)))
			f = 1;
		else f = 0;

		vector_1_N.erase(vector_1_N.begin());//������ ����� �����
		vector_2_N.erase(vector_2_N.begin());

		vector<int> result;
		result = DIV_NN_N(vector_1_N, vector_2_N);//����� ��� �����
		result.insert(result.begin(), f);//��������� ����
		return (result);
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////     �������� ����      //

vector<int> MUL_ZM_Z(vector<int> input)
{
	input[0] ^= 1;
	return input;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////     �������� �����      //

vector<int> TRANS_Z_N(vector<int> a)
{
	a.erase(a.begin());	
	return (a);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
