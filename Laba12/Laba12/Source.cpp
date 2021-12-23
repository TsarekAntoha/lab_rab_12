#include <iostream>
#include <utility>
#include <tuple>
#include <cstdlib>
using namespace std;


template<class F, typename tuple, size_t ...indices >//F - �������, tuple - ������
void descendingPrintHelper(F f, tuple const& refs, index_sequence< indices... >){//���������: f - ������������ �������, 
                                                                                 //refs - ������ ����������
                                                                                 //index_sequence< ...indices> - ������������������ ����� ���� size_t (������������ ����� ������� ����������)
    constexpr size_t back_index = sizeof...(indices) - 1;//back_index - ������ ���������� ��������

    return f(forward<tuple_element_t<back_index - indices, tuple>>(get<back_index - indices>(refs))...);//�������� ������� f, �������� �� ���������(� �������� �������)
}

template<class F, typename ...types>//F - �������, types - ���� ������ 
void descendingPrint(F f, types &&... _values){//�������� ������� f � ��������� _values ����� types
    return descendingPrintHelper(f, forward_as_tuple(forward<types>(_values)...), make_index_sequence<sizeof...(types)>{});//�������� descendingPrintHelper, �������� �� ������� f 
                                                                                                                           //forward_as_tuple ������������ ������ ������ �� ��������� � types , ���������� ��� ��������� � �������� ���������� � ������� f
                                                                                                                           //make_index_sequence - ������� ������������������ �����(������� ����������) ���� size_t, 
}

void printf3(int x, int y, int z) {//������� �������� x, y, z
    cout << x << ' ' << y << ' ' << z << endl;
}

int main(){
    printf3(1, 2, 3);//�������� ������� printf3
    descendingPrint(printf3, 1, 2, 3);//descendingPrint �������� printf3, �� �������� ��������� � �������� �������
    system("pause");
    return 0;
}