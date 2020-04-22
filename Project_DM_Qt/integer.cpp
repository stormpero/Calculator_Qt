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

//    if (COM_NN_D(a, b) == 1)
//        swap(a, b);
    vector<int> res;
    res = SUB_ZZ_Z(a, MUL_ZZ_Z(b, DIV_ZZ_Z(a, b)));
    res[0] = 0;
    return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////     ������� ������      //

int POZ_Z_D(vector<int> num)
{
    if ((num.size() == 2) && (num[0] == 0) && (num[1] == 0))
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
    if ((POZ_Z_D(num1) == POZ_Z_D(num2)))
    {
        result = ADD_NN_N(ABS_Z_N(num1), ABS_Z_N(num2));
        result.insert(result.begin(), num1[0]);
    }
    else if (POZ_Z_D(num1) == 2 && POZ_Z_D(num2) == 1) // num1 - �����, num2 - �����
    {
        result = TRANS_N_Z(SUB_NN_N(ABS_Z_N(num1), ABS_Z_N(num2)));
        if (COM_NN_D(ABS_Z_N(num1), ABS_Z_N(num2)) == 1) // COM_NN_D 2 - num1 > num2; 1 - num2 > num1
            result = MUL_ZM_Z(result);
    }
    else if (POZ_Z_D(num1) == 1 && POZ_Z_D(num2) == 2) //POZ_Z_D 1 - �����, 2 - �����
    {
        result = TRANS_N_Z(SUB_NN_N(ABS_Z_N(num1), ABS_Z_N(num2)));
        if (COM_NN_D(ABS_Z_N(num1), ABS_Z_N(num2)) == 2)
            result = MUL_ZM_Z(result);
    }
    return(result);// ������������ ��������
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////     ����� ��������      //

vector<int> MUL_ND_N(vector<int> entry, int number) 
{
	if (entry.empty())
		throw "Error:Empty entry";

    if (number == 0)
            return { 0 };

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
    if (POZ_Z_D(vector_2) == 0 && POZ_Z_D(vector_1) == 0)
        return { 0, 0 };
    else if (POZ_Z_D(vector_2) == 0)
        return vector_1;
    else if (POZ_Z_D(vector_1) == 0)
        return MUL_ZM_Z(vector_2);
    else
        return ADD_ZZ_Z(vector_1, MUL_ZM_Z(vector_2));
}

vector<int> DIV_ZZ_Z(vector<int> vector_1_N, vector<int> vector_2_N)
{
    vector<int> result;
    if ((POZ_Z_D(vector_2_N) == 0))// anee Aaeeoaeu = 0 ioeaea
        throw ("Divider 0!");

        if ((POZ_Z_D(vector_1_N) == 0))// anee Aaeeiia = 0 aica?auaai 0
            return { 0,0 };

        bool first = POZ_Z_D(vector_1_N) == 1;
        bool second = POZ_Z_D(vector_2_N) == 1;

        if (!NZER_N_B(MOD_NN_N(ABS_Z_N(vector_1_N), ABS_Z_N(vector_2_N))) || (!first && !second))
        {
            if((first && !second) || (second && !first))
                result = MUL_ZM_Z(TRANS_N_Z(DIV_NN_N(ABS_Z_N(vector_1_N), ABS_Z_N(vector_2_N))));
            else
                result = TRANS_N_Z(DIV_NN_N(ABS_Z_N(vector_1_N), ABS_Z_N(vector_2_N)));
        }
        else if (first && !second)
            result = MUL_ZM_Z(TRANS_N_Z(ADD_1N_N(DIV_NN_N(ABS_Z_N(vector_1_N), ABS_Z_N(vector_2_N)))));
        else if (!first && second)
            result = MUL_ZM_Z(TRANS_N_Z(DIV_NN_N(ABS_Z_N(vector_1_N), ABS_Z_N(vector_2_N))));
        else
            result = TRANS_N_Z(ADD_1N_N(DIV_NN_N(ABS_Z_N(vector_1_N), ABS_Z_N(vector_2_N))));
        return result;
	
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