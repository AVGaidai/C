# Калькулятор для комплексных чисел

Функции: <br>
1) Сумма двух комплексных чисел (cn_add()). <br>
2) Разница двух комплексных чисел (cn_sub()). <br>
3) Произведение двух комплексных чисел (cn_mul()). <br>
4) Частное двух комплексных чисел (cn_div()). <br>
 <br>
Реализации: <br>
1) В виде статической библиотеки libcomplex_num.a. <br>
   Исходный текст тестовой программы находится в файле main_1.c. <br>
2) В виде динамической библиотеки libcomplex_num.so. <br>
   Исходный текст тестовой программы находится в файле main_1.c. <br>
   Для запуска программы нужно указать путь к каталогу с библиотекой <br>
   с помощью переменной окружения LD_LIBRARY_PATH <br>
   (LD_LIBRARY_PATH=$PWD\plugins:$LD_LIBRARY_PATH). <br>
3) В виде совокупности динамических библиотек (libcomplex_add.so, <br>
   libcomplex_sub.so, libcomplex_mul.so libcomplex_div.so). <br>
   Исходный текст тестовой программы находится в файле main_2.c. <br>
 <br>
Makefile: <br>
* Рецепт install создаёт библиотеки для всех трёх реализаций. <br>
* Рецепт uninstal удаляет созданные библиотеки. <br>
* Команда make по умолчанию компилирует три тестовые программы: <br>
  * main_1_1.out -- первая реализация; <br>
  * main_1_2.out -- вторая реализация; <br>
  * main_2.out -- третья реализация. <br>
* Рецепт clean удаляет тестовые программы. <br>
