#include <iostream>
#include <utility>
#include <tuple>
#include <cstdlib>
using namespace std;


template<class F, typename tuple, size_t ...indices >//F - функция, tuple - кортеж
void descendingPrintHelper(F f, tuple const& refs, index_sequence< indices... >){//аргументы: f - передаваемая функция, 
                                                                                 //refs - кортеж аргументов
                                                                                 //index_sequence< ...indices> - последовательность чисел типа size_t (представляет собой индексы аргументов)
    constexpr size_t back_index = sizeof...(indices) - 1;//back_index - индекс последнего элемента

    return f(forward<tuple_element_t<back_index - indices, tuple>>(get<back_index - indices>(refs))...);//вызывает функцию f, передает ей аргументы(в обратном порядке)
}

template<class F, typename ...types>//F - функция, types - типы данных 
void descendingPrint(F f, types &&... _values){//передаем функцию f и аргументы _values типов types
    return descendingPrintHelper(f, forward_as_tuple(forward<types>(_values)...), make_index_sequence<sizeof...(types)>{});//вызывает descendingPrintHelper, передает ей функцию f 
                                                                                                                           //forward_as_tuple конструирует кортеж ссылок на аргументы в types , подходящие для пересылки в качестве аргументов в функцию f
                                                                                                                           //make_index_sequence - создает последовательность чисел(индексы аргументов) типа size_t, 
}

void printf3(int x, int y, int z) {//выводит значения x, y, z
    cout << x << ' ' << y << ' ' << z << endl;
}

int main(){
    printf3(1, 2, 3);//вызывает функцию printf3
    descendingPrint(printf3, 1, 2, 3);//descendingPrint вызывает printf3, но передает аогументы в обратном порядке
    system("pause");
    return 0;
}