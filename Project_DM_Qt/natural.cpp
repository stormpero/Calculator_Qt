#include "natural.h"

///////////////////////////////////////////////////////////////////////////////////////////////     ������������� ���������     //

int NZER_N_B(vector<int> a_Z) // �������� �� ����: ���� ����� �� ����� ����, �� ��� ����� ���� 
{
	if ((a_Z[0] == 0) || ((a_Z[0] == 0) && a_Z[1] == 0))
		return 0;
	else
		return 1;
}

vector<int> GCF_NN_N(vector<int> a, vector<int> b) // ��� ����������� �����
{
	while (NZER_N_B(b)) // ���� ���� b != 0
	{
		vector <int> c; //��������������� ������
		c = MOD_NN_N(a, b); // ������� �� ������� a �� b
		a = b;
		b = c;
	}
	return a;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////     ������ ���������     //

vector<int> ADD_1N_N(vector<int> input) // ���������� 1 � ������������ �����
{
	// ������� ����� �������� �������
	vector<int> res(input);

	// ��������� ���� � ������� ������� ������ ������
	if (input.empty())
		throw "Empty input";

	// ��������� � ������ ����� 1,
	// �� ������� ���������� ��������� ������� ��������
	int mem(1);

	// � ����� ���� � ����� � ������ ������� (���� � ������ ���-�� ��������)
	for (int i(input.size() - 1); mem && i >= 0; --i)
	{
		// ���� ����� �� �������� � �������� 0-9,
		// ������ ���������� � ������������ �����
		if (input[i] < 0 || input[i] > 9)
			throw "Input is not a valid number";

		res[i] = (input[i] + mem) % 10;
		mem = (input[i] + mem) / 10;
	}

	// ���� �������� �� ����� �������, �� ������ ��� ��� �� �����,
	// ��������� � ������ ����� ������� �� ��������� �� ������
	if (mem)
		res.insert(res.begin(), mem);

	return res;
}

vector<int> MUL_NN_N(vector<int> first, vector<int> second) // ������������ ����������� �����
{
	// ��������� ���� � ������� ������� ������ ������
	if (first.empty() || second.empty())
		throw "Empty input";

	// ������� ������� �� ����� ������ ������
	if (first.size() < second.size())
	{
		vector<int> temp(first);
		first = second;
		second = temp;
	}

	vector<int> result{ 0 }, k{ 0 };
	for (int i(second.size() - 1); i >= 0; --i, k = ADD_1N_N(k))
	{
		// ����������� ������ ������ �� ������ ����� �������
		vector<int> addition(MUL_ND_N(first, second[i]));

		// �������� ����� �� 1 ������ ����� (��� � ��������� � �������)
		addition = MUL_Nk_N(addition, k);

		// ���������� ��� ��� ����� � ���������� � ���������
		result = ADD_NN_N(result, addition);
	}
	return result;
}

vector<int> DIV_NN_N(vector<int> first, vector<int> second) // ������� �� ������� 2 ����������� �����
{
	// ��������� ���� � ������� ������� ������ ������
	if (first.empty() || second.empty())
		throw "Empty input";

	vector<int> result{ 0 }, k{ 0 };
	int i(0);
	// ���� ������ ����� >= �������
	while (COM_NN_D(first, second) == 2 || !COM_NN_D(first, second))
	{
		// ��������� ������ ����� ������� first �� second
		// ���������� �� 10 � ������� �� �������
		vector<int> temp(DIV_NN_Dk(first, second));

		// ���������� ��� ����� � result
		result = ADD_NN_N(result, temp);

		// ������ �������� ��� ����� �� ��������
		temp = MUL_NN_N(temp, second);

		// � �������� ������������ �� ��������
		first = SUB_NN_N(first, temp);

		++i;
	}
	return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////     ������� ������     //

vector <int>MUL_Nk_N(vector<int> N, vector<int> k) // �������� ����������� ����� �� 10^k
{
	// ��������� ���� � ������� ������� ������ ������
	if (N.empty() || k.empty())
		throw "Empty input";
	//��������� ����� �������� ������ ���� ������������ �������
	//�� ��� ��� ���� i �� ����� k ���������� � ����� ����� 0, ��� ������������ ��������� �� 10
	for (vector <int>i = { 0 }; i != k; i = ADD_1N_N(i))
		N.push_back(0);
	return N;
}

vector <int>SUB_NDN_N(vector<int> a, vector<int> b, int k) // ��������� �� ������������ ������� ������������, ����������� �� ����� ��� ������ � ��������������� �����������
{
	vector<int> bk = MUL_ND_N(b, k);// save result of b * k (��� ����, ����� �� ������� ��� 2 ����)
	vector<int> ak = MUL_ND_N(a, k);
	short abk = COM_NN_D(a, bk);
	short bak = COM_NN_D(b, ak);

	if (abk == 2 || abk == 0) // ���� a > bk ��� a = bk, result = a - bk
		return SUB_NN_N(a, bk);
	else if (bak == 2 || bak == 0)// ���� b > ak ��� b = ak, result = b - ak
		return SUB_NN_N(b, ak);
	else throw "Wrong input"; // �����
}

vector <int>MOD_NN_N(vector<int> first, vector<int> second) // ������� �� ������� �������� ������������ ����� �� ������� ��� ������ ����������� � ��������(�������� ������� �� ����)
{
	// ��������� ���� � ������� ������� ������ ������
	if (first.empty() || second.empty())
		throw "Empty input";
	if (COM_NN_D(first, second) == 1)
		swap(first, second);
	return SUB_NN_N(first, MUL_NN_N(second, DIV_NN_N(first, second)));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////     �������� ������     //

vector<int> SUB_NN_N(vector<int> a, vector<int> b) // ��������� �� ������� �������� ������������ ����� ������� �������� ��� �������
{
	if (COM_NN_D(a, b) == 2)      // 2 ���� a>b, 0 ���� a=b, 1 ���� a<b
	{
		vector <int> result(a.size());                         //�������� ������, ������� ������ �������� ���������, � �������� ��� ����������� �������� �����
		while (a.size() != b.size())  b.insert(b.begin(), 0); // ���� ������ b ������ �� �����������, �� ������� � ��� ������ ����
		for (int i = a.size() - 1; i >= 0; i--) // ���� ���������
		{
			result[i] = a[i] - b[i];
			if (result[i] < 0)
			{
				result[i] += 10;
				a[i - 1]--;
			}
		}
		while (result[0] == 0) // ���� ����� ��������� � ������ ������� ������� ����, �� ��  ����� ������
		{
			result.erase(result.begin());
		}
		return result;
	}
	if (COM_NN_D(a, b) == 0)
	{
		vector <int> result = { 0 }; // ��� ��� ����������� ����� �����, �� �� �������� ���� 0
		return result;
	}
	if (COM_NN_D(a, b) == 1)
	{
		vector <int> result(b.size());                         //�������� ������, ������� ������ �������� ���������, � �������� ��� ����������� �������� �����
		while (a.size() != b.size())  a.insert(a.begin(), 0); // ���� ������ a ������ �� �����������, �� ������� � ��� ������ ����
		for (int i = b.size() - 1; i >= 0; i--) // ���� ���������
		{
			result[i] = b[i] - a[i];
			if (result[i] < 0)
			{
				result[i] += 10;
				b[i - 1]--;
			}
		}
		while (result[0] == 0)
		{
			result.erase(result.begin());
		}
		return result;   // ������������ �������� - ��������� ��������� ���� ����������� �����
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////     ������� ������      //

int COM_NN_D(vector<int> num1, vector<int> num2) // 2 - num1 > num2, 0 - num1=num2, 1 - num2 > num1
{
	if (num1.size() > num2.size())	return 2; // ���� num1 > num2  - 2
	else if (num1.size() < num2.size())	return 1; // ���� num1 < num2  - 1
	else // ���� num1 = num2  - 0
	{
		if (num1.front() > num2.front())
			return 2;
		else if (num1.front() < num2.front())
			return 1;
		else
			return 0;
	}
}

//int COM_NN_D(vector<int> num1, vector<int> num2)
//{
//	int s = 0;
//	if (num1.size() == num2.size())  //���� � ����� ���������� ����-�� ��������
//	{
//		for (int i = 0; i < num1.size(); i++)//���������� ������ ����� � �����������
//		{
//			s = 0;
//			if (num1[i] == num2[i])
//				s = 1; //������� �����
//			if (s != 1) //���� ������ �� �����, �� ������� ����� �� ��� ������
//			{
//				if (num1[i] > num2[i])
//					return 2;
//				if (num1[i] < num2[i])
//					return 1;
//				break;
//			}
//		}
//	}
//
//	if (s == 1) //������ ������� �����
//		return 0;
//
//	if (num1.size() < num2.size())
//		return 1;
//
//	if (num1.size() > num2.size())
//		return 2;
//}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////     ����� ��������      //

vector<int> DIV_NN_Dk(vector<int> vector_1, vector<int> vector_2) // ���������� ������ ����� ������� �������� ������������ �� �������, 
{																  // ����������� �� 10^k,��� k - ����� ������� ���� ����� (����� ��������� � ����)
	if (vector_1.empty() || vector_2.empty()) //�������� �� ������
		throw "Empty input";

	if (COM_NN_D(vector_1, vector_2) == 1) 
	{ //���� 1� ������ < 2��
		vector<int> number = { 0 };
		return number;
	}

	if (COM_NN_D(vector_1, vector_2) == 0) 
	{ //���� ������� �����
		vector<int> number = { 1 };
		return number;
	}

	if (COM_NN_D(vector_1, vector_2) == 2) 
	{      //���� 2� ������ 1��

		vector<int> number = { 0 };               //��� ����� ����� ����� ��� ������� 2�� �� 1�

		while (COM_NN_D(vector_1, vector_2) == 2) { //����� ���� ������� ������ � ����������� ������� �����, ��� ��� ����� ������� �� ���������� // �� $$$$$
			vector <int> a = vector_1, b = vector_2;
			vector <int> result(a.size());                         //�������� ������, ������� ������ �������� ���������, � �������� ��� ����������� �������� �����
			while (a.size() != b.size())  b.insert(b.begin(), 0); // ���� ������ b ������ �� �����������, �� ������� � ��� ������ ����
			for (int i = a.size() - 1; i >= 0; i--) // ���� ���������
			{
				result[i] = a[i] - b[i];
				if (result[i] < 0)
				{
					result[i] += 10;
					a[i - 1]--;
				}
			}
			while (result[0] == 0) // ���� ����� ��������� � ������ ������� ������� ����, �� ��  ����� ������
				result.erase(result.begin());

			while (b[0] == 0) // � ��� ��� ����������: ���� ����� ��������� � ������ ������� ������� ����, �� ��  ����� ������ 
				b.erase(b.begin());

			number = ADD_1N_N(number); // ����������� �����
			vector_1 = result;
		}
		if (COM_NN_D(vector_1, vector_2) == 0) // ���� ������� ������, �� ����������� ������ ��� �� 1��
			number = ADD_1N_N(number);

		for (int i = 1; i < number.size(); i++) //��� ��� �� ������� �� 1� �������� ����� �� ��������� �������� ������
			number[i] = 0;

		return number;
	}
}

vector<int> MUL_ND_N(vector<int> entry, int number)
{
    if (entry.empty())
        throw "Error:Empty entry";

    if (number < 0 || number > 9)       //����� ���������� ����� ������ ������!!!!!
        throw "Entered wrong";

    short digit = 0;// ���������� ���������� �� ���������� ���������� �������

    for (int i = entry.size() - 1; i >= 0; i--)
    {
        short multiplication;
        multiplication = number * entry[i];   // ������������ ����� � �������

        if (multiplication + digit >= 10) {
            entry[i] = (multiplication % 10) + digit;
            digit = multiplication / 10;
        }
        else
        {
            entry[i] = (multiplication % 10) + digit;
            digit = 0;
        }
    }

    if (digit != 0) //���� ��������� ������ >= 10 �� ���������� ����� ������� � ������ �������
        entry.insert(entry.begin(), digit);

    return entry;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////     �������� ����      //

vector<int> TRANS_N_Z(vector<int> input) // �������������� ������������ ����� � �����
{
	input.insert(input.begin(), 0);
	return input;
}

vector<int> LCM_NN_N(vector<int> vector_1, vector<int> vector_2)
{
	vector <int> mul = MUL_NN_N(vector_1, vector_2);
	vector <int> nod = GCF_NN_N(vector_1, vector_2);
	vector<int> res = DIV_NN_N(mul, nod);
	return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////     �������� �����      //

vector<int> ADD_NN_N(vector<int> a, vector<int> b) // �������� ����������� �����
{
	// ��������� ���� � ������� ������� ������ ������
	if (a.empty()|| b.empty())
		throw "Empty input";

	vector<int> c;

	int one = 0; // ���������� ��� �������� ������ �������
	if (COM_NN_D(a, b) == 2)      // 2 ���� a>b, 0 ���� a=b, 1 ���� a<b
	{
		int k = a.size() - b.size();
		for (int i = 0; i < k; i++)
			b.insert(b.begin(), 0); // ���������� ����� �� ������ ���-�� ������
	}
	else  
	{
		int k = b.size() - a.size();
		for (int i = 0; i < k; i++)
			a.insert(a.begin(), 0); // ���������� ����� �� ������ ���-�� ������
	}
	for (int i = a.size() - 1; i >= 0; i--)
	{
		if ((a[i] + b[i] + one) > 9) // ���� ����� �������� ������ 9, ���������� 1 � ���������� 
		{
			c.insert(c.begin(),(a[i] + b[i] + one) % 10);
			one = 1;
		}
		else
		{
			c.insert(c.begin(),a[i] + b[i] + one);
			one = 0;
		}			   
	}
	if (one == 1) // ���� �������� 1, �� ��������� ��� ���� ������
		c.insert(c.begin(), 1);

	return c;
}

//vector<int> ADD_NN_N(vector<int> a, vector<int> b) // �������� ����������� �����
//{
//
//	if (COM_NN_D(a, b) == 2)      // 2 ���� a>b, 0 ���� a=b, 1 ���� a<b
//	{
//		reverse(a.begin(), a.end());//������ ������ ������ ������
//		reverse(b.begin(), b.end());//������ ������ ������ ������
//		b.resize((a.size() + 1), 0);//��������� ������ �������, ������� ������ �������� ��������, � �������� ��� ����������� �������� ����� 
//		for (int ix = 0; ix < ((b.size() - 1)); ix++)
//		{
//			b[ix] += a[ix]; // ��������� ��������� ������� �����
//			b[ix + 1] += (b[ix] / 10); // ���� ���� ������ ��� ��������, ��������� ��� � ��������� ������
//			b[ix] %= 10; // ���� ���� ������ ��� �������� �� ����������
//		}
//
//		if (b[b.size() - 1] == 0)//���� ��������� �����(������ � �������� �����) �������� �����,�� ������� ���,��� ����������
//			b.pop_back();
//		reverse(b.begin(), b.end());// ������ �������� ����� ����� �������
//	}
//	else {
//
//		reverse(b.begin(), b.end());//������ ������ ������ ������
//		reverse(a.begin(), a.end());//������ ������ ������ ������
//		a.resize(b.size(), 0);//��������� ������ �������,� �������� ����� ������ ��������
//		b.resize((b.size() + 1), 0);//��������� ������ �������, ������� ������ �������� ��������, � �������� ��� ����������� �������� ����� 
//		for (int ix = 0; ix < ((b.size() - 1)); ix++)
//		{
//
//			b[ix] += a[ix]; // ��������� ��������� ������� �����
//			b[ix + 1] += (b[ix] / 10); // ���� ���� ������ ��� ��������, ��������� ��� � ��������� ������
//			b[ix] %= 10; // ���� ���� ������ ��� �������� �� ����������
//		}
//
//		if (b[b.size() - 1] == 0)//���� ��������� �����(������ � �������� �����) �������� �����,�� ������� ���,��� ����������
//			b.pop_back();
//		reverse(b.begin(), b.end());// ������ �������� ����� ����� �������
//	}
//	return (b);
//}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
