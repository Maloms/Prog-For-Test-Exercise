// Prog for test exercise

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>


using namespace std;
int main()
{
    setlocale(LC_ALL, "ru");
    string path = "emrasdb-sample1.rf1";

    //Чтение файла
    ifstream file;             
    file.open(path);

    if (!file.is_open())
    {
       cout << ("Ошибка: Невозможно открыть файл!") << endl << "Примечание: Файл должен находится в папке с программой.";
    }
    else
    {
        cout << ("Файл успешно открыт!") << endl;
        string str;
        string allstr[1500];  //Массив диапазонов
        double Fcentr[1500];  //Массив центральных частот
        int g = 0;            //Конечный размер этих массивов
       while (!file.eof())
        {
            getline(file, str);
            cout << str << endl;     //Вывод данных диапазона на экран
            int n = 0;
            char mas[30];
            double fr[2];
            int b = 0;
            char kilo[9];
            for (int i = 0; (i<str.length())&&(b<=1); i++)    //Цикл для получения значений начальной и конечной частот
            {
                if (str[i]>='0'&&str[i]<='9')
                {
                    mas[n]=str[i];
                    n++;
                }
                else
                {
                    if (n > 8)
                    {
                        for (int j = 0; j <= 8; j++)
                        {
                            kilo[j] = mas[j];
                        }
                        fr[b] = atoi(kilo)*pow(10,n-15);
                        b++;
                        n = 0;
                    }
                    else if (n <= 8)
                    {
                        fr[b] = atoi(mas)/(pow(10,6));
                        b++;
                        n = 0;              
                    }
                }
            }
            double Fc = (fr[1] - fr[0]) / 2;     //Расчет центральной частоты                                   
            cout << "Центральная частота равна: " << Fc << "МГц" << endl << endl; //Вывод центральной частоты на экран
            allstr[g] = str;     //Заполнения массива диапазонов
            Fcentr[g] = Fc;      //Заполнение массива центральных частот
            g++;
        }
        
        //Сортировка по убыванию центральной частоты методом шейкерной сортировки
        int left = 0;
        int right = g - 1;
        while (left <= right)
        {
            for (int i = right; i > left; --i)
            {
                if (Fcentr[i - 1] < Fcentr[i])
                {
                    swap(Fcentr[i - 1], Fcentr[i]);
                    swap(allstr[i - 1], allstr[i]);
                }
            }
            ++left;
        }
       
        for (int i = left; i < right; ++i)
        {
            if (Fcentr[i] < Fcentr[i + 1])
            {
                swap(Fcentr[i], Fcentr[i + 1]);
                swap(allstr[i], allstr[i + 1]);
            }
            --right;
        }
        
        
        //Запись отсортированных диапазонов в файл
        ofstream sort;
        sort.open("emrasdb-sample1_sorted.rf1");
        for (int i = 0; i < g; i++)
        {
            sort << allstr[i];
            sort << "\n";
            sort << "Центральная частота: ";
            sort << Fcentr[i];
            sort << " МГц";
            sort << "\n";
            sort << "\n";
        }
        sort.close();
    }   
    file.close();

   
    return 0;
}

