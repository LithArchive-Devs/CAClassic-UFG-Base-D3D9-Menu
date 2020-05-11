#ifndef __POLY__
#define __POLY__
#pragma once
#include "Main.h"

        typedef struct
        {
            unsigned long start;
            unsigned long end;
        } SectionInformation_t;

class cPoly
{
	public:
        SectionInformation_t GetSectionInformation( HMODULE hModule, const char *pszName );

        void DestroyAndMorphSection( HMODULE hModule, const char *pszName );

       // void UseThisAndThenMorphIt( void );

		void RandomizeCodeAtPlace( unsigned long begin, unsigned long end );

        void RunFrame( void );
};

#endif  
