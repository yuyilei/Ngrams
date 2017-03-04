// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "vector.h"
#include "simpio.h"

using namespace std;

void InputFile( ifstream & in ){

    while (true) {
    
        cout << "Input file name?"  << endl ;
        string name ;
        cin >> name ;
        in.open(name.c_str()) ;

        if ( !in.fail() )
            break ;
        else {
        
            cout << "Unable to open that file. " << endl ;
            in.clear() ;
        }
    }
}


void ReadFile( ifstream & in , Vector<string> & lines ){

    while (true){
         
        string text ;
        in >> text ;
        if ( in.fail() )
            break ;
        else {

        lines.add(text) ;
        }
    }

}

void GenerateMap( Vector<string> &lines , int N , Map<Vector<string>,Vector<string>> &map , Vector<Vector<string>> &keys ){

    int len ;
    len = lines.size() ;
    int i = 0 ;
    int j ;
    while ( i < len - N  ){
    
        Vector<string> key ; 

        int end ;

        if ((i+N) > len - 1 )
            end = len - 1 ;
        else
            end = i + N ;

        for( j = i ; ; j++ ){

            if ( j >= end )
                break ;
            key.add(lines[j]) ;

        }

        string rela ;
        rela = lines.get(end) ;

        Vector<string> values ;
        i = i + 1 ;
        if ( map.containsKey(key) ){
        
            values = map.get(key) ;
            values.add(rela) ;
            map.put(key,values) ;
        }

        else{
        
            values.add(rela) ;
            map.put(key,values) ;
            keys.add(key) ;

        }
    }
}


void GenerateRandom(Vector<string> & inital , Map<Vector<string>,Vector<string>> map , Vector<string> &res ,int number ){
    while ( res.size() <= number ){
    
        Vector<string> former ;
        former = map.get(inital) ;
        int key_ ;
        key_ = randomInteger(0,former.size()-1) ;
        res.add(former[key_]) ;
        inital.remove(0) ;
        inital.add(former[key_]) ; 
     }
}

int main() {
    // TODO: Finish the program!

    ifstream in ;
     
    cout << "Welcome to CS 106B Random Writer ('N-Grams')." << endl ;
    cout << "This program makes random text based on a document. " << endl ;
    cout << "Give me an input file and an 'N' value for groups " << endl ;
    cout << "of words, and I'll create random text for you." << endl ;
    
    Map<Vector<string>,Vector<string>> map ;
    Vector<Vector<string>> keys ;
    InputFile( in ) ;
    Vector<string> lines ;
    ReadFile( in , lines ) ;

    int N ;
    cout << "Value of N ?" << endl ;
    cin >> N ;
    GenerateMap(lines,N-1,map ,keys) ;


    while( true ){
    
        cout << "# of random words to generate (0 to quit)?" << endl ;
        int number ; 
        cin >> number ;
        if ( number == 0 ){
        
            cout << "Exiting." << endl ;
            break ;
        }

        int size ;
        size = map.size() ;
        int start ;
        start = randomInteger( 0, size -1) ;
        Vector<string> res ;
        Vector<string> inital = keys[start] ;
        res = inital ;
        if (number != 1 )
            number = number -1 ;

        GenerateRandom(inital,map,res,number  ) ;
        cout << "..."  ;
        for (  int i = 0 ; i < res.size() ; i++  )
            cout << res[i] << " " ;
        cout << "..." << endl ;
    }

    return 0;
}
