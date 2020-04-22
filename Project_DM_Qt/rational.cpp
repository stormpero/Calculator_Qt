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
    if ((a.denominator[0] == 1) && (a.denominator.size() == 1)) // ��������, �������� �� ��� ������ ������� �������� � �����������
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

    if (POZ_Z_D(a.numerator) == 0)
        return null;
    result.numerator = MUL_ZZ_Z(a.numerator, TRANS_N_Z(b.denominator)); // Oiii?ei ?eneeoaeu a?iae a ia ciaiaiaoaeu a?iae b
    result.denominator = MUL_NN_N(a.denominator, TRANS_Z_N(b.numerator)); // Aiaeiae?ii aey ciaiaiaoaey
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

//	Drob result;
//	if ((POZ_Z_D(b.numerator) == 0)|| (POZ_Z_D(b.numerator) == 0))
//			throw ((string)"Error / zero \nIn File: " + __FILE__ + "\nIn line: " + to_string(__LINE__));

//	if (POZ_Z_D(b.numerator) == 1)
//		b.denominator.insert(b.denominator.begin(), 1);
//	else // if (POZ_Z_D(b.numerator) == 2)
//		b.denominator.insert(b.denominator.begin(), 0);
	
//	b.numerator = ABS_Z_N(b.numerator);
//    swap(b.numerator, b.denominator);
		
//	result = RED_Q_Q(MUL_QQ_Q(a,b)); // �������� ���������� �����
//	return(result);
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
	if ((a.denominator == b.denominator) && (POZ_Z_D(ADD_ZZ_Z(a.numerator, b.numerator)) == 0))
	{
		res.numerator.push_back(0);
		res.numerator.push_back(0);
		res.denominator.push_back(1);
		return res;
	}
	vector<int> zn1 = a.denominator;
	vector<int> zn2 = b.denominator;
	vector <int> zn = LCM_NN_N(a.denominator, b.denominator);	
	vector <int> mn = DIV_NN_N(zn, a.denominator);
	mn.insert(mn.begin(), 0);
	vector <int> chisl1 = MUL_ZZ_Z(a.numerator, mn);
	vector <int> mn1 = DIV_NN_N(zn, b.denominator);
	mn1.insert(mn1.begin(), 0);
	vector <int> chisl2 = MUL_ZZ_Z(b.numerator, mn1);
	res.numerator = ADD_ZZ_Z(chisl1, chisl2);
	res.denominator = zn;	
	return RED_Q_Q(res);
}

vector<int> TRANS_Q_Z(Drob a)
{
	vector<int> r = a.numerator;
	return r;
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
		return a;
	vector<int> Nod = GCF_NN_N(ABS_Z_N(a.numerator), a.denominator);
	a.denominator = DIV_NN_N(a.denominator, Nod);
	Nod.insert(Nod.begin(), 0);
	a.numerator = DIV_ZZ_Z(a.numerator, Nod);	
	
	return a;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////