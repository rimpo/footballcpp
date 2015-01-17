// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>

#ifdef _WIN32
#include <tchar.h>
#endif

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
using namespace rapidjson;


#include<string>
#include<iostream>
#include<vector>
#include<memory>
#include<math.h>
#include<algorithm>
using namespace std;


#include"Util.h"
#include"Game.h"

CGame& GetGame();	



// TODO: reference additional headers your program requires here
