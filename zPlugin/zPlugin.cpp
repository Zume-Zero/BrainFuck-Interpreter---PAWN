/* BrainFuck Interpreter - PAWN .. 
		>> _Zume */

#include <iostream>
#include <string>
#include "SDK\amx\amx.h"
#include "SDK\plugincommon.h"

char data[30000];
char *d;
const char *p;

typedef void (*logprintf_t)(char* format, ...);

logprintf_t logprintf;
extern void *pAMXFunctions;

struct ZBF
{
	char texto[200];
};

using namespace std;

/* _BFInterpret(dest[], code[], len = sizeof); */
cell AMX_NATIVE_CALL _BFInterpret(AMX* amx, cell* params)
{
	
	char *string = NULL;
	int _loop;
	cell *buf = NULL;	
	std::string SendSLandf;
	amx_StrParam(amx, params[2], string);
	char *file = new char;
	if((string ? string : NULL) != NULL)
	{
		 d = data;
		 p = string;
	 
		 while (*p) 
		 {
			switch (*p) 
			{
				case '>':
				{
					d++;
					break;
				}
				case '<':
				{
					d--;
					break;
				}
				case '+':
				{
					(*d)++;
					break;
				}
				case '-':
				{
					(*d)--;
					break;
				}
				case '.':
				{ 
					SendSLandf = SendSLandf + d; 
					break;
				}
				case '[':
				{
					_loop = 1;
					if (*d == '\0') 
					{
						do 
						{
							p++;
							if(*p == '[')
							{
								_loop++;
							}
							else if(*p == ']')
							{
								_loop--;
							}
						} while ( _loop != 0 );
					}
					break;
				}
				case ']':
				{
					_loop = 0;
					do 
					{
						if (*p == '['){
							_loop++;
						}
						else if (*p == ']'){
							_loop--;
						}
						p--;
					} while (_loop != 0 );
					break;
				}
			}
			p++;
		}
		amx_GetAddr(amx, params[1], &buf);
		amx_SetString(buf, SendSLandf.c_str(), 0, 0, params[3] > 0 ? params[3] : strlen(d) + 1);
    }
    return 1;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) 
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t) ppData[PLUGIN_DATA_LOGPRINTF];

    logprintf(" * BrainFuck Interpreter Loaded!");
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
    logprintf(" * BrainFuck Interpreter Unload!");
}

AMX_NATIVE_INFO PluginNatives[] =
{
    {"_BFInterpret", _BFInterpret},
    {0, 0}
};


PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
    return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) 
{
    return AMX_ERR_NONE;
}