#include "integer.h"

///////////////////////////////////////////////////////////////////////////////////////////////     Старосельский Александр     //

vector<int> ABS_Z_N(vector<int> a)
{
	a.erase(a.begin());
	return a;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////     Ермольев Максим     //

vector<int> MUL_ZZ_Z(vector<int> a, vector<int> b) // Ермольев Максим Викторович
{
	vector<int> result; // Перменнная, которая хранит результат умножения
	if (POZ_Z_D(a) == 0 || POZ_Z_D(b) == 0) //  Если одно из чисел равно 0, то их произведение тоже равно 0
	{
		result.push_back(0);
		result.push_back(0);
	}
		
	else
	{
		result = MUL_NN_N(ABS_Z_N(a), ABS_Z_N(b)); // Переведем целые в натуральные и выполним умножение
		result = TRANS_N_Z(result); // Переведем натуральные в целые
		if (POZ_Z_D(a) != POZ_Z_D(b)) //Проверим равны ли знаки чисел, если нет, то поменяем знак
			result = MUL_ZM_Z(result); // Умножим число на -1
	}
	return(result);   // Возвращаемое значение
}

vector<int>  MOD_ZZ_Z(vector<int> a, vector<int> b)
{
	vector<int> q; // Частное
	vector<int> aq_or_bq; // Значение, которое хранит произведение меньшего числа на частное
	vector<int> result; // Перменнная, которая хранит результат 
	q = DIV_ZZ_Z(a, b); // Частное от деления чисел а b 
	if (COM_NN_D(a, b) == 2) // Если а, больше b
	{
		aq_or_bq = MUL_ZZ_Z(b, q); // То целая часть это частное умноженное на меньшее из 
		result = SUB_ZZ_Z(a, aq_or_bq); // Отнимаем целую часть от a
	}
	else if (COM_NN_D(a, b) == 1)
	{
		aq_or_bq = MUL_ZZ_Z(a, q);
		result = SUB_ZZ_Z(b, aq_or_bq);
	}

	return(result);   // Возвращаемое значение
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////     Астахов Михаил      //

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
	vector<int> result; // Перменнная, которая хранит результат сложения
		 
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
	else if ((POZ_Z_D(num1) == 1) && (POZ_Z_D(num2) == 2)) //POZ_Z_D 1 - отриц, 2 - полож
	{
		result = SUB_NN_N(ABS_Z_N(num1), ABS_Z_N(num2));
		result = TRANS_N_Z(result);
		if (COM_NN_D(ABS_Z_N(num1), ABS_Z_N(num2)) == 2) // COM_NN_D 2 - num1 > num2; 1 - num2 > num1		
			result= MUL_ZM_Z(result);		
	}
	else if ((POZ_Z_D(num1) == 2) && (POZ_Z_D(num2) == 1)) // num1 - полож, num2 - отриц
	{
		result = SUB_NN_N(ABS_Z_N(num1), ABS_Z_N(num2));
		result = TRANS_N_Z(result);
		if (COM_NN_D(ABS_Z_N(num1), ABS_Z_N(num2)) == 1)
			result = MUL_ZM_Z(result);
	}
	return(result);   // Возвращаемое значение
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////     Игорь Темников      //

vector<int> MUL_ND_N(vector<int> entry, int number) 
{
	if (entry.empty())
		throw "Error:Empty entry";

	short digit = 0;// переменная отвечающая за увеличение следующего разряда

	for (int i = entry.size() - 1; i >= 0; i--)
	{
		short multiplication;
		multiplication = number * entry[i];   // произведение цифры и разряда

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

	if (digit != 0) //если последний разряд >= 10 то дописываем новый элемент в начало вектора
		entry.insert(entry.begin(), digit);

	return entry;
}

vector<int> SUB_ZZ_Z(vector<int> vector_1, vector<int> vector_2) //Вычитание целых чисел
{
	vector<int> result;
	if (POZ_Z_D(vector_2) == 0) //проверка что одно из чисел 0, сразу возвращаем обратно один из векторов
		return (vector_1);
	if (POZ_Z_D(vector_1) == 0)
		return (vector_2);

	if (POZ_Z_D(vector_2) == 1 && POZ_Z_D(vector_1) == 2) {//1 +, 2 -, складываем как натуральные добавляем 1 в начало	
		vector_1.erase(vector_1.begin());
		vector_2.erase(vector_2.begin());
		result = ADD_NN_N(vector_1, vector_2);
		result.insert(result.begin(), 0);
		return (result);
	}

	if (POZ_Z_D(vector_2) == 1 && POZ_Z_D(vector_1) == 1) {//1 -, 2-// тут 3 случая
		vector_1.erase(vector_1.begin());
		vector_2.erase(vector_2.begin());
		if (COM_NN_D(vector_1, vector_2) == 0)//Проверка на равенство, если так сразу возвращаем 0		
			return { 0, 0 };

		if (COM_NN_D(vector_1, vector_2) == 2) { // 1й больше 2го вычитаем возвращаем со знаком -
			result = SUB_NN_N(vector_1, vector_2);
			result.insert(result.begin(), 1);
			return (result);
		}

		if (COM_NN_D(vector_1, vector_2) == 1) { //2й больше 1го вычитаем возвращаем с +
			result = SUB_NN_N(vector_2, vector_1);
			result.insert(result.begin(), 0);
			return (result);
		}
	}

	if (POZ_Z_D(vector_2) == 2 && POZ_Z_D(vector_1) == 2) {//1+, 2+ аналогично предыдущему, только вместо вычтем сложим 
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

	if (POZ_Z_D(vector_1) == 1 && POZ_Z_D(vector_2) == 2) {// если 1 -, 2 + складываем как натуральные добавляем 1 в начало		
		vector_1.erase(vector_1.begin());
		vector_2.erase(vector_2.begin());
		result = ADD_NN_N(vector_1, vector_2);
		result.insert(result.begin(), 1);
		return (result);
	}
}

vector<int> DIV_ZZ_Z(vector<int> vector_1_N, vector<int> vector_2_N)
{
	if ((POZ_Z_D(vector_2_N) == 0))// если Делитель = 0 ошибка
		throw ("Divider 0!");
	
		if ((POZ_Z_D(vector_1_N) == 0))// если Делимое = 0 возвращаем 0 
			return { 0 };

		bool f;//Отвечает за знак
		if (((POZ_Z_D(vector_1_N) == 2) && (POZ_Z_D(vector_2_N) == 1)) || ((POZ_Z_D(vector_1_N) == 1) && (POZ_Z_D(vector_2_N) == 2)))
			f = 1;
		else f = 0;

		vector_1_N.erase(vector_1_N.begin());//Чистим знаки чисел
		vector_2_N.erase(vector_2_N.begin());

		vector<int> result;
		result = DIV_NN_N(vector_1_N, vector_2_N);//Делим как целые
		result.insert(result.begin(), f);//Вставляем знак
		return (result);
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////     Табояков Иван      //

vector<int> MUL_ZM_Z(vector<int> input)
{
	input[0] ^= 1;
	return input;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////     Жиренкин Артем      //

vector<int> TRANS_Z_N(vector<int> a)
{
	a.erase(a.begin());	
	return (a);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
