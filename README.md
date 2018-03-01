# Лемматизатор
![Background image](https://github.com/spratskevich/Lemmatizer/blob/master/images/banner.png)

## Введение. Цель проекта
Это легковесная C++ библиотека, целью которой является реализация простого в использовании лемматизатора русского языка. Основное и единственное его назначение - вернуть для исходного слова его базовую словарную форму. Например, для русских существительных это форма именительного падежа единственного числа, для глаголов - форма инфинитива. Полученные результаты в дальнейшем можно испльзовать для поиска в словарях или других текстах, что может быть полезно в поисковых системах, при переводе с одного языка на другой, при проеверке грамматики и т. д. Основными достоинствами нашей реализации лемматизатора являются его скорость, эффективность и простота использования.

## Сравнение с аналогами
Название|Морфологический анализ|Точность|Скорость|Объём требуемой памяти
--------|----------------------|--------|--------|-----------------------
[Наш проект](https://github.com/spratskevich/Lemmatizer)|-|Высокая|Высокая|Небольшой
[MyStem](https://tech.yandex.ru/mystem/)|+|Высокая|Высокая|Средний
[Лемматизатор в грамматическом словаре](http://www.solarix.ru/for_developers/api/lemmatizator-api.shtml)|-|Высокая|Высокая|Небольшой

*Рыночная ниша проекта*
Это небольшой учебный проект группы студентов. Он, скорее, предназначен для познания основ и упрощений лингвистического анализа текстов, нежели для конкуренции с коммерческими продуктами. Здесь открытый исходный код, и любой желающий может использовать эту библиотеку, равно как и вносить вклад в её развитие. 

## Требования к аппаратуре
Это пока ещё разрабатывающаяся библиотека, поэтому конкретных требований пока нет. Скорее всего, вам потребуется процессор не хуже Intel Pentium 4, а оперативной памяти не менее 2 Гб. 

## Требования к программному обеспечению
Проект собирается для 32х- и 64х-битных платформ Windows.

## Средства разработки программного обеспечения
Для сборки продукта необходима система [CMake](https://cmake.org/) и любая из поддерживаемых CMake систем сборки.

## Характеристики продукта
*Расход памяти*
Максимальный расход памяти можно настраивать, однако это естественным образом повляиет на производительность.

*Производительность*
Опредеяется максимальным размером буфера, выделенного пользователем на обработку данного текста.

*Надежность*
Предполагается обучение с 95% точностью на тестовых примерах. 

## Формат входных данных
Входными данными является текст, подлежащий лемматизации. Текст может приниматься в виде строки или считываться из произвольного  входного потока (в частности, из файла). Подробности см. в параграфе "Описание API-библиотеки".

## Формат выходных данных
Выходные данные - последовательность лемм (начальные формы) слов входного текста в виде специализированного итератора или лемматизированный текст целиком в виде строки или выведенный в произвольных поток (например, файл). Подробности см. в параграфе "Описание API-библиотеки".

## Установка продукта
Продукт представляет собой библиотеку и распространяется в виде исходного кода на C++. Предполагается сборка с использованием 
системы [CMake](https://cmake.org/). Алгоритм подробной установки будет описан по реализации библиотеки.

## Запуск продукта
Продукт является библиотекой, а не самостоятельным приложением, поэтому не предполагает запуск.

Однако, при сборке библиотеки будет предусмотрена возможность сборки демонстрационного консольного приложения, реализующего тот же интерфейс, что и библиотека, но в текстовом режиме.

## Описание интерфейса пользователя
Продукт является библиотекой, её интерфейс пользователя - API. См. параграф "Описание API-библиотеки".

Интерфейс консольного приложения предполагается приблизительно следующим:
```
lemmatize (<входная строка> | -f <имя входного файла>)
```
Пример использования на Linux:
```
$ lemmatize "Хливкие шорьки пырялись по наве" > barmaglot.txt
$ cat barmaglot.txt
хливкий шорька пыряться по нава
```

## Описание API библиотеки
Интерфейс библиотеки составит одна функция lemmatize и один класс LemmaIterator. Функция lemmatize принимает входной текст в форме строки или произвольного входного потока и возвращает экземпляр класса LemmaIterator:
```C++
LemmaIterator lemmatize(std::istream &inputTextStream);
LemmaIterator lemmatize(const std::string &inputText);
```
Экземпляр класса LemmaIterator представляет собой итератор (категории [input iterator](http://www.cplusplus.com/reference/iterator/InputIterator/)), пробегающий леммы слов исходного текста в порядке их следования в нём. Помимо этой функциональности данный класс реализует возможность вывода лемматизированного текста в строку или произвольный выходной поток:
```C++
class LemmaIterator {
  //...
public:
  //...
  std::string str();
  friend std::ostream& operator<<(std::ostream &outputStream, LemmaIterator &lemmaIterator);
  //...
};
```

**Пример использования библиотеки:**
```C++

for (auto &&lemma: lemmatize("Хливкие шорьки пырялись по наве"))
  std::cout << lemma << std::endl;
```
*Вывод:*
```
хливкий
шорька
пыряться
по
нава
```

## Детали реализации
Предполагается использование подхода, основанного на нейронных сетях, например, одного из опубликованных в [1],[2],[3]. Для обучения сети (или сетей). Для обучения предполагается использование открытого размеченного корпуса русскоязычных текстов [OpenCorpora](http://opencorpora.org/).

## Тестирование
Тестирование результатов лемматизации будет производиться на размеченном корпусе русскоязычных текстов [OpenCorpora](http://opencorpora.org/).
Тестирование модулей будет производиться при помощи фреймворка QT, в частности посредством QTest.

## Ссылки и литература
* [1] Abhisek Chakrabarty, Akshay Chaturvedi, Utpal Garain, "A Neural Lemmatizer for Bengali", 2016 (https://pdfs.semanticscholar.org/12c6/1ee4f804d4007fc12cfd0d13ba260c051e48.pdf);
* [2] Kyunghyun Cho, Bart van Merrienboer, Caglar Gulcehre, Dzmitry Bahdanau, Fethi Bougares, Holger Schwenk, Yoshua Bengio, "Learning Phrase Representations using RNN Encoder–Decoder for Statistical Machine Translation", 2014 (https://arxiv.org/pdf/1406.1078.pdf);
* [3] Mike Kestemont, Guy de Pauw, Renske van Nie, Walter Daelemans, "Lemmatization for variation-rich languages using deep learning", 2016.
