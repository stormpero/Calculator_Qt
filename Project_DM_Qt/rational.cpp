#include "rational.h"


///////////////////////////////////////////////////////////////////////////////////////////////     Чиганов Даниил     //

Drob SUB_QQ_Q(Drob f, Drob s)
{
	if (POZ_Z_D(s.numerator) == 0) // если s == 0
		return f;
	s.numerator = MUL_ZM_Z(s.numerator); // иначе инвертируем знак второго
	return ADD_QQ_Q(f, s); // вызываем ф-ию сложения целых чисел, но прибавляем мы число с противоположным знаком	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////     Ермольев Максим     //

int INT_Q_B(Drob a)
{
	a = RED_Q_Q(a); //Выполним сокращение дроби
	if (a.denominator[0] == 1 && a.denominator.size() == 1)  // Проверим, является ли его первый элемент единицей в знаменателе
		return 1; // Если да, то выведем единицу
	else
		return 0; // Если нет, то ноль
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
	result.numerator = MUL_ZZ_Z(a.numerator, TRANS_N_Z(b.denominator)); // Умножим числитель дроби a на знаменатель дроби b
	result.denominator = MUL_NN_N(a.denominator, TRANS_Z_N(b.numerator)); // Аналогично для знаменателя
	if (POZ_Z_D(result.numerator) == 0)
	{
		result = RED_Q_Q(result);
		return result;
	}
	if ((POZ_Z_D(a.numerator) == POZ_Z_D(b.numerator)))
		result.numerator[0] = 0;
	else
		result.numerator[0] = 1;

	result = RED_Q_Q(result); // Выполним сокращение дроби
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