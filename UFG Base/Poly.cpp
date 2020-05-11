#include "Poly.h"
        std::vector< SectionInformation_t > m_vMorphTheseSections;

		SectionInformation_t cPoly::GetSectionInformation( HMODULE hModule, const char *pszName )
        {
            SectionInformation_t si;

            si.start    = 0;
            si.end        = 0;

            if( hModule )
            {
                IMAGE_DOS_HEADER *pDosHeader = reinterpret_cast<IMAGE_DOS_HEADER *>( hModule );

                if( pDosHeader->e_magic != IMAGE_DOS_SIGNATURE )
                    return si;

                IMAGE_NT_HEADERS *pNTHeaders = reinterpret_cast<IMAGE_NT_HEADERS *>( ( DWORD )hModule + pDosHeader->e_lfanew );

                if( pNTHeaders->Signature != IMAGE_NT_SIGNATURE )
                    return si;

                IMAGE_SECTION_HEADER *pSectionHeader = reinterpret_cast<IMAGE_SECTION_HEADER *>( ( DWORD )pNTHeaders + 
                    sizeof( IMAGE_FILE_HEADER ) + sizeof( DWORD ) + pNTHeaders->FileHeader.SizeOfOptionalHeader );

                for( unsigned int i = 0; i < pNTHeaders->FileHeader.NumberOfSections; i++ )
                {
                    IMAGE_SECTION_HEADER *pSection = &pSectionHeader[ i ];

                    if( pSection == NULL )
                        continue;

                    if( memcmp( pszName, ( CHAR* )pSection->Name, strlen( pszName ) ) == 0 )
                    {
                        si.start    = ( ( DWORD )hModule + ( DWORD )pSection->VirtualAddress );
                        si.end        = si.start + ( DWORD ) pSection->SizeOfRawData;

                        break;
                    }
                }
            }

            return si;
        }

		void cPoly::DestroyAndMorphSection( HMODULE hModule, const char *pszName )
        {
            SectionInformation_t si = GetSectionInformation( hModule, pszName );

            if( si.start && si.end )
            {
                m_vMorphTheseSections.push_back( si );
            }
        }

		void UseThisAndThenMorphIt( void )
        {
            _asm nop;        //0000
            _asm nop;        //0001
            _asm nop;        //0002
            _asm nop;        //0003
            _asm nop;        //0004
            _asm nop;        //0005
            _asm nop;        //0006
            _asm nop;        //0007
            _asm nop;        //0008
            _asm nop;        //0009
            _asm nop;        //0010
            _asm nop;        //0011
            _asm nop;        //0012
            _asm nop;        //0013
            _asm nop;        //0014
            _asm nop;        //0015
            _asm nop;        //0016
            _asm nop;        //0017
            _asm nop;        //0018
            _asm nop;        //0019
            _asm nop;        //0020
            _asm nop;        //0021
            _asm nop;        //0022
            _asm nop;        //0023
            _asm nop;        //0024
            _asm nop;        //0025
            _asm nop;        //0026
            _asm nop;        //0027
            _asm nop;        //0028
            _asm nop;        //0029
            _asm nop;        //0030
            _asm nop;        //0031
            _asm nop;        //0032
            _asm retn;        //0033
        }

		void cPoly::RandomizeCodeAtPlace( unsigned long begin, unsigned long end )
        {
            BYTE *ArrayOfCode = reinterpret_cast< BYTE* >( begin );

            int seed = (( rand() % 9999 ) ^ 0xFFFFFFFF );

            srand( GetTickCount() ^ seed );

            MEMORY_BASIC_INFORMATION mbi;

            VirtualQuery( ( LPCVOID ) begin, &mbi, sizeof( mbi ) );

            VirtualProtect( mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect );

            for( size_t i = 0; i < ( end - begin ); i++ )
            {
                int CurrentRandomSeed = ( GetTickCount() ^ seed * ( ArrayOfCode[ i + 1 ] & 0xFFFF ) );

                srand( CurrentRandomSeed );

                ArrayOfCode[ i ] = rand() % 0xFF;
            }

            VirtualProtect( mbi.BaseAddress, mbi.RegionSize, mbi.Protect, NULL ); 

            FlushInstructionCache( GetCurrentProcess(), ( LPCVOID ) begin, ( end - begin ) ); 
        }

		void cPoly::RunFrame( void )
        {
            RandomizeCodeAtPlace( 
                ( unsigned long ) UseThisAndThenMorphIt, 
                ( unsigned long ) UseThisAndThenMorphIt + 32 );

            for( size_t i = 0; i < m_vMorphTheseSections.size(); i++ )
            {
                SectionInformation_t si = m_vMorphTheseSections[ i ];

                if( si.start == 0 || si.end == 0 ) continue;

                RandomizeCodeAtPlace( si.start, si.end );
            }
        }
