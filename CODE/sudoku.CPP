//============================================================================
// Name        : Sudoku.cpp
// Author      : wzlf11
// Version     : a.0
// Copyright   : Your copyright notice
// Description : Sudoku in C++.
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int table[9][9];

void shuffle(int arr[], int n){
    
    int tmp, rd;

    //��������˳��
    for(int i = 0; i < n; i++){
        rd = rand() % 9;
        tmp = arr[rd];
        arr[rd] = arr[i];
        arr[i] = tmp;
    }
}

bool test(int x, int y, int v){
    
    int _x = x / 3 * 3;
    int _y = y / 3 * 3;

    //����3 * 3�������Ƿ����ظ�����
    for(int i=_x; i<_x + 3; i++)
    {
        for(int j = _y; j < _y + 3; j++)
        {
            if(table[i][j] == v)
            {
                return false;
            }
        }
    }

    //���Ժ��������Ƿ����ظ�����
    for(int m= 0; m< 9; m++)
    {
        if(table[x][m] == v || table[m][y] == v)
            return false;
    }
    
    return true;
}

bool put(int line, int index){
    
    if(index > 8)
        return true;
    
    //�����ǰ�����ڲ�����0��������������һ������
    if(table[line][index] != 0){
        return put(line, index + 1);
    }
    
    int num[] = {1,2,3,4,5,6,7,8,9};
    //���ҵ�ǰ׼��д�����ֵ�ǰ��˳��
    shuffle(num, 9);
    
    for(int i = 0; i < 9; i++){
        
        //���������Ƿ��������뵱ǰ����
        if( test(line, index, num[i]) == true ){

            table[line][index] = num[i];
            
            //����ɹ�������һ������
            if( put(line, index + 1) == true ){
                return true;
            }
        }
    }

    table[line][index] = 0; //ʧ�ܺ�λ

    return false;
}

bool put_line(int line){

    if(line > 8)
        return true;
    
    int b[9];
    
    //���ݵ�ǰһ��
    for(int i = 0; i < 9; i++){
        b[i] = table[line][i];
    }

    if( put(line, 0) == true ){
        //��ǰһ��������ɺ󣬽�����һ�����ظ�������
        if( put_line(line + 1) == true )
            return true;
    }
    
    //�ָ���ǰһ�е�ֵ
    for(int n = 0; n < 9; n++){
        table[line][n] = b[n];
    }
    
    return false;
}

int main() {

    //�������������ʼֵ
    for(int i = 0; i < 9; i++){
        table[0][i] = i + 1;
    }

    srand((unsigned int)time(NULL));
    //���ұ������д���
    shuffle((int *)&table[0], 9);

    //�ӵڶ��п�ʼ��������
    while(!put_line(1))
    {
        //ʧ�����¿�ʼ
        shuffle((int *)&table[0], 9);
    }
    
    //�����ʾ
    for(int x = 0; x < 9; x++){
        for(int y = 0; y < 9; y++){
            cout << table[x][y] << " ";
        }
        
        cout << endl;
    }

    return 0;
}