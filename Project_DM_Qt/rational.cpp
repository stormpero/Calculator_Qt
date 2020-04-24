#include "rational.h"


///////////////////////////////////////////////////////////////////////////////////////////////     ������� ������     //

Drob SUB_QQ_Q(Drob f, Drob s)
{
	if (POZ_Z_D(s.numerator) == 0) // ���� s == 0
		return f;
	s.numerator = MUL_ZM_Z(s.numerator); // ����� ����������� ���� �������
	return ADD_QQ_Q(f, s); // �������� �-�� �������� ����� �����, �� ���������� �� ����� � ��������������� ������	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////     �������� ������     //

int INT_Q_B(Drob a)
{
	a = RED_Q_Q(a); //�������� ���������� �����
	if (a.denominator[0] == 1 && a.denominator.size() == 1)  // ��������, �������� �� ��� ������ ������� �������� � �����������
		return 1; // ���� ��, �� ������� �������
	else
		return 0; // ���� ���, �� ����
}

Drob DIV_QQ_Q(Drob a, Drob b)
{
	Drob null;
	null.numerator = { 0, 0 };
	null.denominator = { 1 };
	Drob result;
	if (POZ_Z_D(b.numerator) == 0)
		throw "Zero devider";
	if (POZ_Z_D(a.numerator) == 0)
		return null;
	result.numerator = MUL_ZZ_Z(a.numerator, TRANS_N_Z(b.denominator)); // ������� ��������� ����� a �� ����������� ����� b
	result.denominator = MUL_NN_N(a.denominator, TRANS_Z_N(b.numerator)); // ���������� ��� �����������
	if (POZ_Z_D(result.numerator) == 0)
	{
		result = RED_Q_Q(result);
		return result;
	}
	if ((POZ_Z_D(a.numerator) == POZ_Z_D(b.numerator)))
		result.numerator[0] = 0;
	else
		result.numerator[0] = 1;

	result = RED_Q_Q(result); // �������� ���������� �����
	return(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////     ������� ������      //

Drob MUL_QQ_Q(Drob num1, Drob num2)
{
	Drob result;	//��������� ������
	result.numerator = MUL_ZZ_Z(num1.numerator, num2.numerator); //������������ ������������ ����������
	result.denominator = MUL_NN_N(num1.denominator, num2.denominator);  // ������������ ������������ ������������
	result = RED_Q_Q(result);
	return result; //���������� �������� ���������
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////     �������� ����      //

Drob ADD_QQ_Q(Drob a, Drob b) 
{
	Drob res;
	a = RED_Q_Q(a);
	b = RED_Q_Q(b);
	if ((a.denominator == b.denominator) && (POZ_Z_D(ADD_ZZ_Z(a.numerator, b.numerator)) == 0))
	{
		res.numerator.push_back(0);
		res.numerator.push_back(0);
		res.denominator.push_back(1);
		return res;
	}
	vector <int> f = LCM_NN_N(a.denominator, b.denominator);

	a.numerator = MUL_ZZ_Z(a.numerator, TRANS_N_Z(DIV_NN_N(f, a.denominator)));
	b.numerator = MUL_ZZ_Z(b.numerator, TRANS_N_Z(DIV_NN_N(f, b.denominator)));

	res.numerator = ADD_ZZ_Z(a.numerator, b.numerator);
	res.denominator = f;

	return res;
}

vector<int> TRANS_Q_Z(Drob a)
{
	vector <int> one = { 1 };
	a = RED_Q_Q(a);
	if (a.denominator != one)
		throw "Error, impossible to make integer of rational";
	return a.numerator;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////     �������� �����      //

Drob TRANS_Z_Q(vector <int> a) 
{
	Drob p;	//����� ���������
	p.numerator = a; // ����������� ����� � ���������	
	p.denominator.push_back(1);  // ����������� 1 � �����������
	return p; // ���������� ���������
}

Drob RED_Q_Q(Drob a)
{
	if (POZ_Z_D(a.numerator) == 0)
	{
		a.denominator = { 1 };
		return a;
	}
	vector<int> Nod = GCF_NN_N(ABS_Z_N(a.numerator), a.denominator);
	a.denominator = DIV_NN_N(a.denominator, Nod);
	Nod.insert(Nod.begin(), 0);
	a.numerator = DIV_ZZ_Z(a.numerator, Nod);	
	
	return a;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////