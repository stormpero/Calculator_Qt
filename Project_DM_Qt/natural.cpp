#include "natural.h"

///////////////////////////////////////////////////////////////////////////////////////////////     Старосельский Александр     //

int NZER_N_B(vector<int> a_Z) // Проверка на ноль: если число не равно нулю, то «да» иначе «нет» 
{
	if ((a_Z[0] == 0) || ((a_Z[0] == 0) && a_Z[1] == 0))
		return 0;
	else
		return 1;
}

vector<int> GCF_NN_N(vector<int> a, vector<int> b) // НОД натуральных чисел
{
	while (NZER_N_B(b)) // Цикл пока b != 0
	{
		vector <int> c; //Вспомогательный вектор
		c = MOD_NN_N(a, b); // Остаток от деления a на b
		a = b;
		b = c;
	}
	return a;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////     Михаил Киришский     //

vector<int> ADD_1N_N(vector<int> input) // Добавление 1 к натуральному числу
{
	// Создаем копию входного вектора
	vector<int> res(input);

	// Проверяем если в функцию передан пустой вектор
	if (input.empty())
		throw "Empty input";

	// Сохраняем в память число 1,
	// на которое необходимо увеличить входное значение
	int mem(1);

	// В цикле идем с конца к началу вектора (пока в памяти что-то хранится)
	for (int i(input.size() - 1); mem && i >= 0; --i)
	{
		// Если цифра не попадает в диапазон 0-9,
		// кидаем исключение о неправильном вводе
		if (input[i] < 0 || input[i] > 9)
			throw "Input is not a valid number";

		res[i] = (input[i] + mem) % 10;
		mem = (input[i] + mem) / 10;
	}

	// Если прошлись по всему вектору, но память все еще не пуста,
	// добавляем в начало новый элемент со значением из памяти
	if (mem)
		res.insert(res.begin(), mem);

	return res;
}

vector<int> MUL_NN_N(vector<int> first, vector<int> second) // Перемножение натуральных чисел
{
	// Проверяем если в функцию передан пустой вектор
	if (first.empty() || second.empty())
		throw "Empty input";

	// Сделаем больший по длине вектор первым
	if (first.size() < second.size())
	{
		vector<int> temp(first);
		first = second;
		second = temp;
	}

	vector<int> result{ 0 }, k{ 0 };
	for (int i(second.size() - 1); i >= 0; --i, k = ADD_1N_N(k))
	{
		// Перемножаем первый вектор на каждую цифру второго
		vector<int> addition(MUL_ND_N(first, second[i]));

		// Сдвигаем число на 1 разряд влево (как в умножении в столбик)
		addition = MUL_Nk_N(addition, k);

		// Складываем все эти числа и записываем в результат
		result = ADD_NN_N(result, addition);
	}
	return result;
}

vector<int> DIV_NN_N(vector<int> first, vector<int> second) // Кратное от деления 2 натуральных чисел
{
	// Проверяем если в функцию передан пустой вектор
	if (first.empty() || second.empty())
		throw "Empty input";

	vector<int> result{ 0 }, k{ 0 };
	int i(0);
	// Пока первое число >= второго
	while (COM_NN_D(first, second) == 2 || !COM_NN_D(first, second))
	{
		// Вычисляем первую цифру деления first на second
		// умноженную на 10 в степени ее позиции
		vector<int> temp(DIV_NN_Dk(first, second));

		// Прибавляем это число к result
		result = ADD_NN_N(result, temp);

		// Теперь умножаем это число на делитель
		temp = MUL_NN_N(temp, second);

		// И отнимаем получившееся от делимого
		first = SUB_NN_N(first, temp);

		++i;
	}
	return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////     Чиганов Даниил     //

vector <int>MUL_Nk_N(vector<int> N, vector<int> k) // Умножить натуральное число на 10^k
{
	// Проверяем если в функцию передан пустой вектор
	if (N.empty() || k.empty())
		throw "Empty input";
	//Проверяем чтобы вводимые данные были натуральными числами
	//До тех пор пока i не равно k прибавлять в конец числа 0, что эквивалентно умножению на 10
	for (vector <int>i = { 0 }; i != k; i = ADD_1N_N(i))
		N.push_back(0);
	return N;
}

vector <int>SUB_NDN_N(vector<int> a, vector<int> b, int k) // Вычитание из натурального другого натурального, умноженного на цифру для случая с неотрицательным результатом
{
	vector<int> bk = MUL_ND_N(b, k);// save result of b * k (Для того, чтобы не считать его 2 раза)
	vector<int> ak = MUL_ND_N(a, k);
	short abk = COM_NN_D(a, bk);
	short bak = COM_NN_D(b, ak);

	if (abk == 2 || abk == 0) // Если a > bk или a = bk, result = a - bk
		return SUB_NN_N(a, bk);
	else if (bak == 2 || bak == 0)// Если b > ak или b = ak, result = b - ak
		return SUB_NN_N(b, ak);
	else throw "Wrong input"; // Инача
}

vector <int>MOD_NN_N(vector<int> first, vector<int> second) // Остаток от деления большего натурального числа на меньшее или равное натуральное с остатком(делитель отличен от нуля)
{
	// Проверяем если в функцию передан пустой вектор
	if (first.empty() || second.empty())
		throw "Empty input";
	if (COM_NN_D(first, second) == 1)
		swap(first, second);
	return SUB_NN_N(first, MUL_NN_N(second, DIV_NN_N(first, second)));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////     Ермольев Максим     //

vector<int> SUB_NN_N(vector<int> a, vector<int> b) // Вычитание из первого большего натурального числа второго меньшего или равного
{
	if (COM_NN_D(a, b) == 2)      // 2 если a>b, 0 если a=b, 1 если a<b
	{
		vector <int> result(a.size());                         //Созданим вектор, который хранит резльтат вычитания, и назначим ему размерность большего числа
		while (a.size() != b.size())  b.insert(b.begin(), 0); // Если вектор b меньше по размерности, то добавим в его начало нули
		for (int i = a.size() - 1; i >= 0; i--) // Цикл вычитания
		{
			result[i] = a[i] - b[i];
			if (result[i] < 0)
			{
				result[i] += 10;
				a[i - 1]--;
			}
		}
		while (result[0] == 0) // Если после вычитания в начале вектора остаютя нули, то их  нужно убрать
		{
			result.erase(result.begin());
		}
		return result;
	}
	if (COM_NN_D(a, b) == 0)
	{
		vector <int> result = { 0 }; // Так как натуральные числа равны, то их разность дает 0
		return result;
	}
	if (COM_NN_D(a, b) == 1)
	{
		vector <int> result(b.size());                         //Созданим вектор, который хранит резльтат вычитания, и назначим ему размерность большего числа
		while (a.size() != b.size())  a.insert(a.begin(), 0); // Если вектор a меньше по размерности, то добавим в его начало нули
		for (int i = b.size() - 1; i >= 0; i--) // Цикл вычитания
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
		return result;   // Возвращаемое значение - результат вычитания двух натуральных чисел
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////     Астахов Михаил      //

int COM_NN_D(vector<int> num1, vector<int> num2) // 2 - num1 > num2, 0 - num1=num2, 1 - num2 > num1
{
	if (num1.size() > num2.size())	return 2; // Если num1 > num2  - 2
	else if (num1.size() < num2.size())	return 1; // Если num1 < num2  - 1
	else // Если num1 = num2  - 0
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
//	if (num1.size() == num2.size())  //если у чисел одинаковое колл-во разрядов
//	{
//		for (int i = 0; i < num1.size(); i++)//уравниваем каждый разр¤д в отдельности
//		{
//			s = 0;
//			if (num1[i] == num2[i])
//				s = 1; //разряды равны
//			if (s != 1) //если разряд не равен, то смотрим какой из них больше
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
//	if (s == 1) //каждые разряды равны
//		return 0;
//
//	if (num1.size() < num2.size())
//		return 1;
//
//	if (num1.size() > num2.size())
//		return 2;
//}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////     Игорь Темников      //

vector<int> DIV_NN_Dk(vector<int> vector_1, vector<int> vector_2) // Вычисление первой цифры деления большего натурального на меньшее, 
{																  // домноженное на 10^k,где k - номер позиции этой цифры (номер считается с нуля)
	if (vector_1.empty() || vector_2.empty()) //Проверка на пустой
		throw "Empty input";

	if (COM_NN_D(vector_1, vector_2) == 1) 
	{ //Если 1й вектор < 2го
		vector<int> number = { 0 };
		return number;
	}

	if (COM_NN_D(vector_1, vector_2) == 0) 
	{ //Если векторы равны
		vector<int> number = { 1 };
		return number;
	}

	if (COM_NN_D(vector_1, vector_2) == 2) 
	{      //Если 2й больше 1го

		vector<int> number = { 0 };               //это целая часть числа при делении 2го на 1е

		while (COM_NN_D(vector_1, vector_2) == 2) { //Далее идет подсчет целого и дополненная функция Макса, так как иначе нихрена не получалось // до $$$$$
			vector <int> a = vector_1, b = vector_2;
			vector <int> result(a.size());                         //Созданим вектор, который хранит резльтат вычитания, и назначим ему размерность большего числа
			while (a.size() != b.size())  b.insert(b.begin(), 0); // Если вектор b меньше по размерности, то добавим в его начало нули
			for (int i = a.size() - 1; i >= 0; i--) // Цикл вычитания
			{
				result[i] = a[i] - b[i];
				if (result[i] < 0)
				{
					result[i] += 10;
					a[i - 1]--;
				}
			}
			while (result[0] == 0) // Если после вычитания в начале вектора остаютя нули, то их  нужно убрать
				result.erase(result.begin());

			while (b[0] == 0) // А вот тут дополнение: Если после вычетания в начале вектора остаютя нули, то их  нужно убрать 
				b.erase(b.begin());

			number = ADD_1N_N(number); // увеличиваем целое
			vector_1 = result;
		}
		if (COM_NN_D(vector_1, vector_2) == 0) // если делятся нацело, то увеличиваем вектор еще на 1цу
			number = ADD_1N_N(number);

		for (int i = 1; i < number.size(); i++) //Так как мы считаем до 1й значащей цифры то остальное заменяем нулями
			number[i] = 0;

		return number;
	}
}

vector<int> MUL_ND_N(vector<int> entry, int number)
{
    if (entry.empty())
        throw "Error:Empty entry";

    if (number < 0 || number > 9)       //Вводи нормальную цифру мамкин хацкер!!!!!
        throw "Entered wrong";

    short digit = 0;// переменная отвечающая за увеличение следующего разряда

    for (int i = entry.size() - 1; i >= 0; i--)
    {
        short multiplication;
        multiplication = number * entry[i];   // произведение цифры и разряда

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

    if (digit != 0) //если последний разряд >= 10 то дописываем новый элемент в начало вектора
        entry.insert(entry.begin(), digit);

    return entry;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////     Табояков Иван      //

vector<int> TRANS_N_Z(vector<int> input) // Преобразование натурального числа в целое
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


///////////////////////////////////////////////////////////////////////////////////////////////     Жиренкин Артем      //

vector<int> ADD_NN_N(vector<int> a, vector<int> b) // Сложение натуральных чисел
{
	// Проверяем если в функцию передан пустой вектор
	if (a.empty()|| b.empty())
		throw "Empty input";

	vector<int> c;

	int one = 0; // Переменная для хранения нового разряда
	if (COM_NN_D(a, b) == 2)      // 2 если a>b, 0 если a=b, 1 если a<b
	{
		int k = a.size() - b.size();
		for (int i = 0; i < k; i++)
			b.insert(b.begin(), 0); // Уравниваем число до одного кол-ва знаков
	}
	else  
	{
		int k = b.size() - a.size();
		for (int i = 0; i < k; i++)
			a.insert(a.begin(), 0); // Уравниваем число до одного кол-ва знаков
	}
	for (int i = a.size() - 1; i >= 0; i--)
	{
		if ((a[i] + b[i] + one) > 9) // Если сумма разрядов больше 9, записываем 1 в переменную 
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
	if (one == 1) // Если осталась 1, то добавляем ещё один разряд
		c.insert(c.begin(), 1);

	return c;
}

//vector<int> ADD_NN_N(vector<int> a, vector<int> b) // Сложение натуральных чисел
//{
//
//	if (COM_NN_D(a, b) == 2)      // 2 если a>b, 0 если a=b, 1 если a<b
//	{
//		reverse(a.begin(), a.end());//читаем вектор справа налево
//		reverse(b.begin(), b.end());//читаем вектор справа налево
//		b.resize((a.size() + 1), 0);//Обновляем размер вектора, который хранит резльтат сложения, и назначим ему размерность большего числа 
//		for (int ix = 0; ix < ((b.size() - 1)); ix++)
//		{
//			b[ix] += a[ix]; // суммируем последние разряды чисел
//			b[ix + 1] += (b[ix] / 10); // если есть разряд для переноса, переносим его в следующий разряд
//			b[ix] %= 10; // если есть разряд для переноса он отсекается
//		}
//
//		if (b[b.size() - 1] == 0)//если последняя цифра(первая в исходном числе) является нулем,то удаляем его,как незначащий
//			b.pop_back();
//		reverse(b.begin(), b.end());// читаем итоговую сумму слева направо
//	}
//	else {
//
//		reverse(b.begin(), b.end());//читаем вектор справа налево
//		reverse(a.begin(), a.end());//читаем вектор справа налево
//		a.resize(b.size(), 0);//Обновляем размер вектора,у которого будет размер большего
//		b.resize((b.size() + 1), 0);//Обновляем размер вектора, который хранит резльтат сложения, и назначим ему размерность большего числа 
//		for (int ix = 0; ix < ((b.size() - 1)); ix++)
//		{
//
//			b[ix] += a[ix]; // суммируем последние разряды чисел
//			b[ix + 1] += (b[ix] / 10); // если есть разряд для переноса, переносим его в следующий разряд
//			b[ix] %= 10; // если есть разряд для переноса он отсекается
//		}
//
//		if (b[b.size() - 1] == 0)//если последняя цифра(первая в исходном числе) является нулем,то удаляем его,как незначащий
//			b.pop_back();
//		reverse(b.begin(), b.end());// читаем итоговую сумму слева направо
//	}
//	return (b);
//}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
