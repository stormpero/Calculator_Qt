#include "rational.h"


///////////////////////////////////////////////////////////////////////////////////////////////     Чиганов Даниил     //

Drob SUB_QQ_Q(Drob f, Drob s)
{
	if (s.numerator[0] == 0 && s.numerator.size() == 1) // если s == 0
		return f;
	s.numerator[0] = !s.numerator[0]; // иначе инвертируем знак второго
	return ADD_QQ_Q(f, s); // вызываем ф-ию сложения целых чисел, но прибавляем мы число с противоположным знаком	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////     Ермольев Максим     //

int INT_Q_B(Drob a)
{
	a = RED_Q_Q(a); //Выполним сокращение дроби
	if (a.denominator[0] == 1)  // Проверим, является ли его первый элемент еденицей в знаменателе
		return 1; // Если да, то выведем еденицу
	else
		return 0; // Если нет, то ноль
}

Drob DIV_QQ_Q(Drob a, Drob b)
{
	Drob result;
	if ((POZ_Z_D(b.numerator) == 0)|| (POZ_Z_D(b.numerator) == 0))		
			throw ((string)"Error / zero \nIn File: " + __FILE__ + "\nIn line: " + to_string(__LINE__));

	if (POZ_Z_D(b.numerator) == 1)	
		b.denominator.insert(b.denominator.begin(), 1);	
	else // if (POZ_Z_D(b.numerator) == 2)	
		b.denominator.insert(b.denominator.begin(), 0);
	
	b.numerator = ABS_Z_N(b.numerator);
	swap(b.numerator, b.denominator);
		
	result = RED_Q_Q(MUL_QQ_Q(a,b)); // Выполним сокращение дроби
	return(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////     Астахов Михаил      //

Drob MUL_QQ_Q(Drob num1, Drob num2)
{
	Drob result;	//структура дробей
	result.numerator = MUL_ZZ_Z(num1.numerator, num2.numerator); //присваемваем произведения числителей
	result.denominator = MUL_NN_N(num1.denominator, num2.denominator);  // присваемваем произведение знаменателей
	result = RED_Q_Q(result);
	return result; //возвращаем значение структуры
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////     Табояков Иван      //

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



///////////////////////////////////////////////////////////////////////////////////////////////     Жиренкин Артем      //

Drob TRANS_Z_Q(vector <int> a) 
{
	Drob p;	//Новая структура
	p.numerator = a; // Присваиваем число к числителю	
	p.denominator.push_back(1);  // Присваиваем 1 к знаменателю
	return p; // Возвращаем структуру
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